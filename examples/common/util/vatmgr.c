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
	char* buf;
	int buflen;
	urc_handler_entry_t* turc;
	int turc_len;
	int result_code;
} exec_ctx_t;

urc_handler_entry_t* urc_handlers[URC_MAX_HANDLERS];
static char line_buf[2049];
static int line_idx;

static exec_ctx_t* exec_ctx;
static TX_EVENT_FLAGS_GROUP exec_done;

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
	if(exec_ctx != NULL) {
		int resplen = strlen(resp);
		if(exec_ctx->echo_received == 0 && cmpline(resp, exec_ctx->msg) == 0) {
			exec_ctx->echo_received = 1;
			return;
		}

		if(exec_ctx->buf != NULL) {
			memset(exec_ctx->buf, 0, exec_ctx->buflen);
			memcpy(exec_ctx->buf, resp, resplen > exec_ctx->buflen ? exec_ctx->buflen : resplen);
		}
		exec_ctx->result_code = strcmp("OK", resp) == 0 ? 0 : -1;
		// Unset exec_ctx to prevent overwrite and urc problems
		exec_ctx = NULL;
	}
	tx_event_flags_set(&exec_done, (1<<0), TX_OR);
}

static void vat_handle_urc(const char* urc, const char* value) {
	COND_TRACE("urc: %s, %s\r\n", urc, value);
	if(exec_ctx != NULL && exec_ctx->turc != NULL) {
		for(int i=0; i<exec_ctx->turc_len; i++) {
			if(exec_ctx->turc[i].urc == NULL || strcmp(exec_ctx->turc[i].urc, urc) == 0) {
				exec_ctx->turc[i].cb(urc, value);
			}
		}
	}
	for(int i=0; i<URC_MAX_HANDLERS; i++) {
		if(urc_handlers[i] != NULL) {
			if(urc_handlers[i]->urc == NULL || strcmp(urc_handlers[i]->urc, urc) == 0)
				urc_handlers[i]->cb(urc, value);
		}
	}
	COND_TRACE("urcend: %s, %s\r\n", urc, value);
}

static void vat_handle_line(char* line) {
	{	// Remove line end
		char* val = line;
		while(*val != '\0' && *val != '\r' && *val != '\n') val++;
		*val = '\0';
	}
	// Ignore empty line
	if(line[0] == '\0') return;
	if(line[0] == '+') {
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
				line_buf[line_idx++] = read_buffer[i];
				if(line_idx >= sizeof(line_buf) - 1) {
					COND_TRACE("exceeded linebuf size\r\n");
					line_idx = 0;
					vat_handle_line(line_buf);
					memset(line_buf, 0, sizeof(line_buf));
				}
				if((read_buffer[i] == '\r' || read_buffer[i] == '\n') && line_idx != 0) {
					line_idx = 0;
					vat_handle_line(line_buf);
					memset(line_buf, 0, sizeof(line_buf));
				}
			}
		}
	} while(res != 0);
}

void vat_init(void) {
	memset(line_buf, 0, sizeof(line_buf));
	line_idx = 0;
	memset(urc_handlers, 0, sizeof(urc_handlers));
	exec_ctx = NULL;

	tx_event_flags_create(&exec_done, "vat_exec_flags");

	(void)qapi_DAM_Visual_AT_Open((void*)vat_dtr);

	vat_execute("ATE0\r\n");
	/*unsigned short res;
	// Make sure buffer is empty
	do{
		static char read_buffer[2049];
		memset(read_buffer, 0, sizeof(read_buffer));
		res = qapi_DAM_Visual_AT_Output(read_buffer, sizeof(read_buffer)-1);
	} while(res != 0);*/
}

void vat_write(const char* msg) {
	int res = qapi_DAM_Visual_AT_Input(msg, strlen(msg));
	if(res != 0) COND_TRACE("failed to write AT command\r\n");
}

int vat_execute(const char* msg) {
	return vat_execute_res(msg, NULL, 0);
}

int vat_execute_res(const char* msg, char* res, int reslen) {
	return vat_execute_urc(msg, res, reslen, NULL, 0);
}

int vat_execute_urc(const char* msg, char* res, int reslen, urc_handler_entry_t* tentries, int tnentries) {
	exec_ctx_t ctx;
	memset(&ctx, 0, sizeof(ctx));
	ctx.msg = msg;
	ctx.buf = res;
	ctx.buflen = reslen;
	ctx.result_code = -1;
	ctx.turc = tentries;
	ctx.turc_len = tnentries;

	unsigned int act;
	tx_event_flags_get(&exec_done, (1<<0), TX_AND_CLEAR, &act, TX_NO_WAIT);

	exec_ctx = &ctx;
	vat_write(msg);
	tx_event_flags_get(&exec_done, (1<<0), TX_AND_CLEAR, &act, TX_WAIT_FOREVER);

	COND_TRACE("execute finished: res=%d, echo=%d\n", ctx.result_code, ctx.echo_received);
	return ctx.result_code;
}

int vat_register_urc(urc_handler_entry_t entries[], int nentries) {
	int done = 0;
	for(int i=0; i<URC_MAX_HANDLERS && done < nentries; i++) {
		if(urc_handlers[i] == NULL) {
			if(entries[i].cb != NULL) {
				urc_handlers[i] = &entries[done];
			} else COND_TRACE("callback function null, ignoring\r\n");
			done++;
		}
	}
	return nentries == done ? 0 : -1;
}
