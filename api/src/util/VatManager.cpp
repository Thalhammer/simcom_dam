#include "util/VatManager.h"
#include "util/trace.h"
#include "util/time.h"
#include <stddef.h>
#include <stdio.h>

extern "C" {
#include "qapi/qapi_dam.h"
}

#define TRACE_TAG "VatManager"

struct VatManager::exec_ctx {
	const struct execute_args* args;
	int echo_received;
	int result_code;
};

#define URC_MAX_HANDLERS ((sizeof(VatManager::m_urc_handlers) / sizeof(urc_handler_entry)))

#define EVT_FLAGS_EXEC_DONE (1 << 0)
#define EVT_FLAGS_EXEC_LOCK (1 << 1)

static const char* get_eol(const char* str) {
	while(*str != '\0' && *str != '\r' && *str != '\n') str++;
	return str;
}

static int cmpline(const char* str1, const char* str2) {
	int len1 = get_eol(str1) - str1;
	int len2 = get_eol(str2) - str2;
	int cmp = memcmp(str1, str2, len1 > len2 ? len2 : len1);
	if(cmp != 0) return cmp;
	if(len1 < len2) return str1[len1] - str2[len1];
	else if(len2 < len1) return str1[len2] - str2[len2];
	else return 0;
}

void VatManager::handle_response(const char* resp) noexcept {
	if(m_debug_enabled) TRACE("response: %s\r\n", resp);
	if(m_exec_context != NULL) {
		size_t resplen = strlen(resp);
		if(m_exec_context->echo_received == 0 && cmpline(resp, m_exec_context->args->msg) == 0) {
			m_exec_context->echo_received = 1;
			return;
		}

		if(m_exec_context->args->result_buf != NULL) {
			memset(m_exec_context->args->result_buf, 0, m_exec_context->args->result_buf_len);
			memcpy(m_exec_context->args->result_buf, resp,
				resplen > (m_exec_context->args->result_buf_len-1) ? m_exec_context->args->result_buf_len-1 : resplen);
		}
		if(m_exec_context->args->result_handler) {
			m_exec_context->result_code = m_exec_context->args->result_handler(resp, m_exec_context->args->result_handler_arg);
		} else m_exec_context->result_code = strcmp("OK", resp) == 0 ? 1 : 0;
		// Unset _vatmgr_exec_ctx to prevent overwrite and urc problems
		m_exec_context = NULL;
	}
	m_flags.set(EVT_FLAGS_EXEC_DONE);
}

void VatManager::handle_urc(const char* urc, const char* value) noexcept {
    if(m_debug_enabled) TRACE("urc: %s, %s\r\n", urc, value);
	if(m_exec_context != nullptr
	&& m_exec_context->args->urc_handlers != nullptr
	&& m_exec_context->args->urc_handlers_size != 0) {
		auto handlers = m_exec_context->args->urc_handlers;
		auto size = m_exec_context->args->urc_handlers_size;
		for(size_t i=0; i<size; i++) {
			if(handlers[i].cb != NULL
			&& handlers[i].urc != NULL
			&& strcmp(handlers[i].urc, urc) == 0) {
				int res = handlers[i].cb(urc, value, handlers[i].arg);
				if(res != 0) {
					m_temp_urc = &handlers[i];
					m_temp_urc_remaining_lines = res;
				}
				if(m_debug_enabled) TRACE("urcend_call: %s, %s\r\n", urc, value);
				return;
			}
		}
	}
	for(size_t i=0; i<URC_MAX_HANDLERS; i++) {
		if(m_urc_handlers[i].cb != NULL
		&& m_urc_handlers[i].urc != NULL
		&& strcmp(m_urc_handlers[i].urc, urc) == 0) {
			int res = m_urc_handlers[i].cb(urc, value, m_urc_handlers[i].arg);
			if(res != 0) {
				m_temp_urc = &m_urc_handlers[i];
				m_temp_urc_remaining_lines = res;
			}
			if(m_debug_enabled) TRACE("urcend_exact: %s, %s\r\n", urc, value);
			return;
		}
	}
	for(size_t i=0; i<URC_MAX_HANDLERS; i++) {
		if(m_urc_handlers[i].cb != NULL
		&& m_urc_handlers[i].urc == NULL) {
			int res = m_urc_handlers[i].cb(urc, value, m_urc_handlers[i].arg);
			if(res != 0) {
				m_temp_urc = &m_urc_handlers[i];
				m_temp_urc_remaining_lines = res;
			}
	        if(m_debug_enabled) TRACE("urcend_default: %s, %s\r\n", urc, value);
			return;
		}
	}
	if(m_debug_enabled) TRACE("no matching urc handler found\r\n");
}

void VatManager::handle_line(char* line) noexcept {
	{
		char* val = line;
		while(*val != '\0' && *val != '\r' && *val != '\n') val++;
		*val = '\0';
	}
	if(line[0] == '\0') return;
	if(m_temp_urc != nullptr && m_temp_urc->cb != nullptr && m_temp_urc_remaining_lines > 0) {
		m_temp_urc->cb(nullptr, line, m_temp_urc->arg);
		m_temp_urc_remaining_lines--;
		if(m_temp_urc_remaining_lines <= 0) {
			m_temp_urc = nullptr;
		}
	} else if(line[0] == '+') {
		char* val = line + 1;
		while(*val != '\0' && *val != ':') val++;
		if(*val == ':') {
			*val = '\0';
			val++;
			while(*val == ' ') val++;
		}
		handle_urc(line+1, val);
	}
	else {
		handle_response(line);
	}
}

void VatManager::handle_dtr(void) noexcept {
	unsigned short res;
	do{
		static char read_buffer[2049];
		memset(read_buffer, 0, sizeof(read_buffer));
		res = qapi_DAM_Visual_AT_Output(read_buffer, sizeof(read_buffer)-1);
		if(res != 0) {
			if(m_debug_enabled) TRACE("received %d bytes: %+s\r\n", (int)res, read_buffer);
			for(int i=0; i<res; i++) {
				m_line_buf[m_line_idx++] = read_buffer[i];
				if(m_line_idx >= sizeof(m_line_buf) - 1) {
					if(m_debug_enabled) TRACE("exceeded linebuf size\r\n");
					m_line_idx = 0;
					m_line_buf[sizeof(m_line_buf) - 1] = 0x00;
					handle_line(m_line_buf);
					memset(m_line_buf, 0, sizeof(m_line_buf));
				}
				if((read_buffer[i] == '\r' || read_buffer[i] == '\n') && m_line_idx != 0) {
					m_line_idx = 0;
					handle_line(m_line_buf);
					memset(m_line_buf, 0, sizeof(m_line_buf));
				}
			}
		}
	} while(res != 0);
}

bool VatManager::begin() noexcept {
	if(m_init_done != false) return true;
	if(m_debug_enabled) TRACE("initialising\r\n");
	memset(m_line_buf, 0, sizeof(m_line_buf));
	m_line_idx = 0;
	m_exec_context = nullptr;

	memset((void*)m_urc_handlers, 0, sizeof(m_urc_handlers));
	m_temp_urc = nullptr;
	m_temp_urc_remaining_lines = 0;

    if(!m_flags.initialize("VatManager")) return false;

    void(*dtrfn)() = [](){
        VAT.handle_dtr();
    };
	(void)qapi_DAM_Visual_AT_Open((void*)dtrfn);
	
	m_init_done = true;

	m_flags.set(EVT_FLAGS_EXEC_LOCK);

	return execute("ATE0\r\n") == 1;
}

bool VatManager::end() noexcept {
    return true;
}

bool VatManager::write(const char* msg) noexcept {
	if(!m_init_done) return false;
	if(m_debug_enabled) TRACE("write: %+s\r\n", msg);
	int res = qapi_DAM_Visual_AT_Input(msg, strlen(msg));
	if(res != 0 && m_debug_enabled) TRACE("failed to write AT command\r\n");
    return res == 0;
}

int VatManager::execute(const char* msg) noexcept {
	execute_args args = {};
	args.msg = msg;
	return execute_ex(&args);
}

int VatManager::execute_ex(const execute_args* args) noexcept {
	if(!m_init_done) return -1;
	exec_ctx ctx;
	memset(&ctx, 0, sizeof(ctx));
	ctx.args = args;

    // We use this as a lock, wait until the flag is set and clear it if it is
    if(!m_flags.get_all(EVT_FLAGS_EXEC_LOCK, true, TX_WAIT_FOREVER)) return false;

    m_flags.clear(EVT_FLAGS_EXEC_DONE);

	m_exec_context = &ctx;
	write(args->msg);
    m_flags.get_all(EVT_FLAGS_EXEC_DONE, true, TX_WAIT_FOREVER);
	m_temp_urc = nullptr;

    // Set the flag to allow the next thread to enter
    m_flags.set(EVT_FLAGS_EXEC_LOCK);

	if(m_debug_enabled) TRACE("execute finished: res=%d, echo=%d\r\n", ctx.result_code, ctx.echo_received);
	return ctx.result_code;
}

bool VatManager::register_urcs(const urc_handler_entry* entries, size_t nentries) noexcept{
	if(!m_init_done) return false;
	for(size_t i=0; i < nentries; i++) {
		if(!register_urc(entries[i].urc, entries[i].cb, entries[i].arg)) return false;
	}
	return true;
}

bool VatManager::register_urc(const char* urc, int(*cb)(const char*, const char*, void*), void* arg) noexcept {
	if(!m_init_done) return false;
	for(size_t i=0; i<URC_MAX_HANDLERS; i++) {
		if(m_urc_handlers[i].cb == NULL) {
			m_urc_handlers[i].cb = cb;
			m_urc_handlers[i].urc = urc;
			m_urc_handlers[i].arg = arg;
			return true;
		}
	}
	return false;
}

int VatManager::set_cfun(int fun) noexcept {
	char buf[64] = {0};
	snprintf(buf, sizeof(buf), "AT+CFUN=%d\r\n", fun);
	return execute(buf);
}

static int cfun_handler(const char*, const char* val, void* res) {
	int* fun = (int*)res;
	if(fun) *fun = val[0] - '0';
	return 0;
}

int VatManager::get_cfun(int* fun) noexcept {
	execute_args args = {};
	args.msg = "AT+CFUN?\r\n";
	urc_handler_entry e = { "CFUN", cfun_handler, fun };
	args.urc_handlers = &e;
	args.urc_handlers_size = 1;
	return execute_ex(&args);
}

int VatManager::set_cclk(time_t timestamp) noexcept {
	char buf[64] = {0};
	time_gregorian_type ctime = time_convert_unix_to_gregorian(timestamp);
	snprintf(buf, sizeof(buf), "AT+CCLK=\"%02d/%02d/%02d,%02d:%02d:%02d+00\"\r\n",
		ctime.year%100, ctime.month, ctime.day, ctime.hour, ctime.minute, ctime.second);
	return execute(buf);
}

static int cclk_handler(const char*, const char* val, void* res) {
	if(res == nullptr) return 0;
	time_gregorian_type time;
	int r = time_parse_cclk_string(val, &time);
	if(r != 0) {
		TRACE("failed to parse time\r\n");
		return 0;
	}
	*((uint32_t*)res) = time_convert_gregorian_to_unix(time);
	return 0;
}

int VatManager::get_cclk(time_t* timestamp) noexcept {
	execute_args args = {};
	args.msg = "AT+CCLK?\r\n";
	urc_handler_entry e = { "CCLK", cclk_handler, timestamp };
	args.urc_handlers = &e;
	args.urc_handlers_size = 1;
	return execute_ex(&args);
}


int VatManager::set_cpsms(bool enabled) noexcept {
	char buf[64] = {0};
	snprintf(buf, sizeof(buf), "AT+CPSMS=%d\r\n", enabled ? 1:0);
	return execute(buf);
}

static int cpsms_handler(const char*, const char* val, void* res) {
	bool* en = (bool*)res;
	if(en) *en = val[0] == '1';
	return 0;
}

int VatManager::get_cpsms(bool* enabled) noexcept {
	execute_args args = {};
	args.msg = "AT+CPSMS?\r\n";
	urc_handler_entry e = { "CPSMS", cpsms_handler, enabled };
	args.urc_handlers = &e;
	args.urc_handlers_size = 1;
	return execute_ex(&args);
}

static int csq_handler(const char*, const char* val, void* res) {
	int* rssi = (int*)res;
	if(rssi == nullptr) return 0;
	if(val[1] == ',') *rssi = val[0] - '0';
	else *rssi = (val[0]-'0')*10 + (val[1]-'0');
	return 0;
}

int VatManager::get_csq(int* rssi) noexcept {
	execute_args args = {};
	args.msg = "AT+CSQ\r\n";
	urc_handler_entry e = { "CSQ", csq_handler, rssi };
	args.urc_handlers = &e;
	args.urc_handlers_size = 1;
	return execute_ex(&args);
}

VatManager VAT;