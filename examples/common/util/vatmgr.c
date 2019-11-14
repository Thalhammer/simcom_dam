#include "util/vatmgr.h"
#include "qapi/qapi_dam.h"
#include "util/debug.h"
#include "util/trace.h"
#include <stddef.h>

#ifndef URC_MAX_HANDLERS
#define URC_MAX_HANDLERS 64
#endif

//#define VATMGR_TRACE

#ifdef VATMGR_TRACE
#define COND_TRACE(...) if(1) TRACE(__VA_ARGS__)
#else
#define COND_TRACE(...) if(0) TRACE(__VA_ARGS__)
#endif

#define TRACE_TAG "vatmgr"

typedef struct {
	const char* msg;
	int echo_received;
	int result_code;
	char* buf;
	int buflen;
	int(*result_fn)(const char*, void*);
	void* result_fn_data;
} exec_ctx_t;

static volatile const urc_handler_entry_t* _vatmgr_urc_handlers[URC_MAX_HANDLERS];
static char _vatmgr_line_buf[2049];
static unsigned int _vatmgr_line_idx;
static volatile const urc_handler_entry_t* _vatmgr_temp_urc;
static volatile int _vatmgr_temp_urc_remaining_lines;

static volatile exec_ctx_t* _vatmgr_exec_ctx;
static TX_EVENT_FLAGS_GROUP* _vatmgr_exec_done;
static volatile int _vatmgr_init_done = TX_FALSE;

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

static void vat_handle_response(const char* resp) {
	COND_TRACE("response: %s\r\n", resp);
	if(_vatmgr_exec_ctx != NULL) {
		int resplen = strlen(resp);
		if(_vatmgr_exec_ctx->echo_received == 0 && cmpline(resp, _vatmgr_exec_ctx->msg) == 0) {
			_vatmgr_exec_ctx->echo_received = 1;
			return;
		}

		if(_vatmgr_exec_ctx->buf != NULL) {
			memset(_vatmgr_exec_ctx->buf, 0, _vatmgr_exec_ctx->buflen);
			memcpy(_vatmgr_exec_ctx->buf, resp, resplen > (_vatmgr_exec_ctx->buflen-1) ? _vatmgr_exec_ctx->buflen-1 : resplen);
		}
		if(_vatmgr_exec_ctx->result_fn) {
			_vatmgr_exec_ctx->result_code = _vatmgr_exec_ctx->result_fn(resp, _vatmgr_exec_ctx->result_fn_data);
		} else _vatmgr_exec_ctx->result_code = strcmp("OK", resp) == 0 ? 1 : 0;
		// Unset _vatmgr_exec_ctx to prevent overwrite and urc problems
		_vatmgr_exec_ctx = NULL;
	}
	tx_event_flags_set(_vatmgr_exec_done, (1<<0), TX_OR);
}

static void vat_handle_urc(const char* urc, const char* value) {
	COND_TRACE("urc: %s, %s\r\n", urc, value);
	for(int i=0; i<URC_MAX_HANDLERS; i++) {
		if(_vatmgr_urc_handlers[i] != NULL) {
			if(_vatmgr_urc_handlers[i]->urc != NULL && strcmp(_vatmgr_urc_handlers[i]->urc, urc) == 0) {
				int res = _vatmgr_urc_handlers[i]->cb(urc, value);
				if(res != 0) {
					_vatmgr_temp_urc = _vatmgr_urc_handlers[i];
					_vatmgr_temp_urc_remaining_lines = res;
				}
				COND_TRACE("urcend_exact: %s, %s\r\n", urc, value);
				return;
			}
		}
	}
	for(int i=0; i<URC_MAX_HANDLERS; i++) {
		//COND_TRACE("hndl[%d]=%x\r\n",i, _vatmgr_urc_handlers[i]);
		if(_vatmgr_urc_handlers[i] != NULL) {
			if(_vatmgr_urc_handlers[i]->urc == NULL) {
				int res = _vatmgr_urc_handlers[i]->cb(urc, value);
				if(res != 0) {
					_vatmgr_temp_urc = _vatmgr_urc_handlers[i];
					_vatmgr_temp_urc_remaining_lines = res;
				}
				return;
			}
		}
	}
	COND_TRACE("urcend_default: %s, %s\r\n", urc, value);
}

static void vat_handle_line(char* line) {
	{
		char* val = line;
		while(*val != '\0' && *val != '\r' && *val != '\n') val++;
		*val = '\0';
	}
	if(line[0] == '\0') return;
	if(_vatmgr_temp_urc != NULL && _vatmgr_temp_urc->cb != NULL && _vatmgr_temp_urc_remaining_lines > 0) {
		_vatmgr_temp_urc->cb(NULL, line);
		_vatmgr_temp_urc_remaining_lines--;
		if(_vatmgr_temp_urc_remaining_lines <= 0) {
			_vatmgr_temp_urc = NULL;
		}
	} else if(line[0] == '+') {
		char* val = line + 1;
		while(*val != '\0' && *val != ':') val++;
		if(*val == ':') {
			*val = '\0';
			val++;
			while(*val == ' ') val++;
		}
		vat_handle_urc(line+1, val);
	}
	else {
		vat_handle_response(line);
	}
}

static void vat_dtr(void) {
	unsigned short res;
	do{
		static char read_buffer[2049];
		memset(read_buffer, 0, sizeof(read_buffer));
		res = qapi_DAM_Visual_AT_Output(read_buffer, sizeof(read_buffer)-1);
		if(res != 0) {
			COND_TRACE("received %d bytes: %s\r\n", (int)res, read_buffer);
			for(int i=0; i<res; i++) {
				_vatmgr_line_buf[_vatmgr_line_idx++] = read_buffer[i];
				if(_vatmgr_line_idx >= sizeof(_vatmgr_line_buf) - 1) {
					COND_TRACE("exceeded linebuf size\r\n");
					_vatmgr_line_idx = 0;
					_vatmgr_line_buf[sizeof(_vatmgr_line_buf) - 1] = 0x00;
					vat_handle_line(_vatmgr_line_buf);
					memset(_vatmgr_line_buf, 0, sizeof(_vatmgr_line_buf));
				}
				if((read_buffer[i] == '\r' || read_buffer[i] == '\n') && _vatmgr_line_idx != 0) {
					_vatmgr_line_idx = 0;
					vat_handle_line(_vatmgr_line_buf);
					memset(_vatmgr_line_buf, 0, sizeof(_vatmgr_line_buf));
				}
			}
		}
	} while(res != 0);
}

int vat_init(void) {
	if(_vatmgr_init_done != TX_FALSE) return 0;
	TRACE("vatmgr is initialising\r\n");
	_vatmgr_init_done = TX_TRUE;
	memset(_vatmgr_line_buf, 0, sizeof(_vatmgr_line_buf));
	_vatmgr_line_idx = 0;
	_vatmgr_exec_ctx = NULL;

	memset(_vatmgr_urc_handlers, 0, sizeof(_vatmgr_urc_handlers));
	_vatmgr_temp_urc = NULL;
	_vatmgr_temp_urc_remaining_lines = 0;

	if(txm_module_object_allocate((void**)&_vatmgr_exec_done, sizeof(TX_EVENT_FLAGS_GROUP)) != TX_SUCCESS) return -1;
	if(tx_event_flags_create(_vatmgr_exec_done, "vat_exec_flags") != TX_SUCCESS) {
		txm_module_object_deallocate(_vatmgr_exec_done);
		return -1;
	}

	(void)qapi_DAM_Visual_AT_Open((void*)vat_dtr);

	vat_execute("ATE0\r\n");
	return 0;
}

void vat_write(const char* msg) {
	COND_TRACE("write: %s\r\n", msg);
	int res = qapi_DAM_Visual_AT_Input(msg, strlen(msg));
	if(res != 0) COND_TRACE("failed to write AT command\r\n");
}

int vat_execute(const char* msg) {
	return vat_execute_res(msg, NULL, 0);
}

int vat_execute_res(const char* msg, char* res, int reslen) {
	return vat_execute_cb(msg, res, reslen, NULL, 0);
}

int vat_execute_cb(const char* msg, char* res, int reslen, int(*result_fn)(const char*, void*), void* data) {
	exec_ctx_t ctx;
	memset(&ctx, 0, sizeof(ctx));
	ctx.msg = msg;
	ctx.buf = res;
	ctx.buflen = reslen;
	ctx.result_fn = result_fn;
	ctx.result_fn_data = data;

	unsigned int act;
	tx_event_flags_get(&_vatmgr_exec_done, (1<<0), TX_AND_CLEAR, &act, TX_NO_WAIT);

	_vatmgr_exec_ctx = &ctx;
	vat_write(msg);
	tx_event_flags_get(&_vatmgr_exec_done, (1<<0), TX_AND_CLEAR, &act, TX_WAIT_FOREVER);
	_vatmgr_temp_urc = NULL;

	COND_TRACE("execute finished: res=%d, echo=%d\r\n", ctx.result_code, ctx.echo_received);
	return ctx.result_code;
}

int vat_register_urc(const urc_handler_entry_t* entries, int nentries) {
	int done = 0;
	for(int i=0; i<URC_MAX_HANDLERS && done < nentries; i++) {
		if(_vatmgr_urc_handlers[i] == NULL) {
			//COND_TRACE("done=%d e[name] = %s    e[cb] = %p\r\n", done, entries[done].urc ? entries[done].urc : "<NULL>", entries[done].cb);
			if(entries[done].cb != NULL) {
				_vatmgr_urc_handlers[i] = &entries[done];
			} else COND_TRACE("callback function null, ignoring\r\n");
			done++;
		}
	}
	return nentries == done ? 0 : -1;
}
