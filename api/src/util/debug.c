#include "util/debug.h"
#include "util/uart.h"
#include "threadx_api/txm_module.h"
#include "qapi/qapi_usb.h"
#include <stdio.h>

static struct {
	uart_context_t ctx;
	int has_usb;
	TX_MUTEX* mutex;
	uint8_t uart[4096];
} _debug_state = {NULL, 0, NULL, {}};

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
	
	if(txm_module_object_allocate(&_debug_state.mutex, sizeof(TX_MUTEX)) != TX_SUCCESS) {
		uart_printf(_debug_state.ctx, "failed to alloc debug mutx\r\n");
		_debug_state.mutex = NULL;
	} else {
		if(tx_mutex_create(_debug_state.mutex, "debug_out_mtx", TX_INHERIT) != TX_SUCCESS) {
			uart_printf(_debug_state.ctx, "failed to create debug mutx\r\n");
			txm_module_object_deallocate(_debug_state.mutex);
			_debug_state.mutex = NULL;
		}
	}

	// Try to open ttyUSB4
	qapi_Status_t usb = qapi_USB_Open();
	if(usb == QAPI_OK) {
		//_debug_state.has_usb = 1;
	}
	return 0;
}

uart_context_t debug_get_handle(void) {
	return _debug_state.ctx;
}

void debug_printf(const char* fmt, ...) {
	if(_debug_state.ctx == NULL) return;
	if(_debug_state.mutex) {
		tx_mutex_get(_debug_state.mutex, TX_WAIT_FOREVER);
	}
	va_list args;
	va_start(args, fmt);
	if(_debug_state.has_usb != 1) {
		uart_vprintf(_debug_state.ctx, fmt, args);
	} else {
		char buf[1024];
		memset(buf, 0, sizeof(buf));
		int len = vsnprintf(buf, sizeof(buf), fmt, args);
		uart_write(_debug_state.ctx, buf, len);
		qapi_USB_Write(buf, len);
	}
	va_end(args);
	if(_debug_state.mutex) {
		tx_mutex_put(_debug_state.mutex);
	}
}
