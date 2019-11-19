#include "util/debug.h"
#include "util/uart.h"

static uart_context_t _debug_ctx = NULL;
static uint8_t _debug_uart[256];

int debug_init(void) {
	if(_debug_ctx != NULL) return 0;
	uart_init_config_t cfg;
	int res = uart_debug_cfg(&cfg);
	if(res != 0) return res;
	cfg.buf = _debug_uart;
	cfg.buf_len = 256;
	cfg.port = UART_PORT_DEFAULT;
	res = uart_init(&_debug_ctx, &cfg);
	if(res != 0) return res;
	return 0;
}

uart_context_t debug_get_handle(void) {
	return _debug_ctx;
}

void debug_printf(const char* fmt, ...) {
	if(_debug_ctx == NULL) return;
	va_list args;
	va_start(args, fmt);
	uart_vprintf(_debug_ctx, fmt, args);
	va_end(args);
}
