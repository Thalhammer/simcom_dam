#include "util/debug.h"
#include "util/uart.h"

static struct {
	uart_context_t ctx;
	uint8_t uart[4096];
} _debug_state = {NULL, {}};

int debug_init(void) {
	if(_debug_state.ctx != NULL) return 0;
	uart_init_config_t cfg;
	int res = uart_debug_cfg(&cfg);
	if(res != 0) return res;
	cfg.buf = _debug_state.uart;
	cfg.buf_len = sizeof(_debug_state.uart);
	cfg.port = UART_PORT_DEFAULT;
	res = uart_init(&_debug_state.ctx, &cfg);
	if(res != 0) return res;
	return 0;
}

uart_context_t debug_get_handle(void) {
	return _debug_state.ctx;
}

void debug_printf(const char* fmt, ...) {
	if(_debug_state.ctx == NULL) return;
	va_list args;
	va_start(args, fmt);
	uart_vprintf(_debug_state.ctx, fmt, args);
	va_end(args);
}
