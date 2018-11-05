#include "util/uart.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_uart.h"
#include "qapi_timer.h"

struct uart_context_s {
	int send_buf_len;
	qapi_UART_Handle_t handle;
	TX_SEMAPHORE mtx;
	char* sendbuf;
};

static void tx_cb(uint32_t num_bytes, void *cb_data) {
	uart_context_t ctx = (uart_context_t)cb_data;
	tx_semaphore_put(&ctx->mtx);
}

qapi_Status_t uart_required_buf(int* bufsize, int sendbuf) {
	if(sendbuf < 16) return QAPI_ERR_INVALID_PARAM;
	*bufsize = sizeof(struct uart_context_s) + sendbuf;
	return QAPI_OK;
}

qapi_Status_t uart_default_cfg(uart_init_config_t* cfg) {
	if(cfg == NULL) return QAPI_ERR_INVALID_PARAM;
	
	memset(cfg, 0, sizeof(uart_init_config_t));

	cfg->baud_Rate = 115200;
	cfg->bits_Per_Char = UART_8_BITS_PER_CHAR_E;
	cfg->enable_Flow_Ctrl = false;
	cfg->enable_Loopback = false;
	cfg->num_Stop_Bits = UART_1_0_STOP_BITS_E;
	cfg->parity_Mode = UART_NO_PARITY_E;
	cfg->port = UART_PORT_DEFAULT;

	return QAPI_OK;
}

qapi_Status_t uart_debug_cfg(uart_init_config_t* cfg) {
	int res = uart_default_cfg(cfg);
	if(res == QAPI_OK) {
		cfg->port = UART_PORT_DEBUG;
	}
	return res;
}

qapi_Status_t uart_init(uart_context_t* ctx, const uart_init_config_t* cfg) {
	if(cfg == NULL || ctx == NULL) return QAPI_ERR_INVALID_PARAM;
	if(cfg->buf_len <= sizeof(struct uart_context_s) + 16) return QAPI_ERR_INVALID_PARAM;
	if(cfg->buf == NULL) return QAPI_ERR_INVALID_PARAM;

	memset(cfg->buf, 0, cfg->buf_len);
	uart_context_t mctx = (uart_context_t)cfg->buf;
	mctx->sendbuf = (char*)cfg->buf + sizeof(struct uart_context_s);
	mctx->send_buf_len = cfg->buf_len - sizeof(struct uart_context_s);

	qapi_UART_Open_Config_t open_properties;
	memset (&open_properties, 0, sizeof(open_properties));
	open_properties.parity_Mode = (qapi_UART_Parity_Mode_e)cfg->parity_Mode;
	open_properties.num_Stop_Bits= (qapi_UART_Num_Stop_Bits_e)cfg->num_Stop_Bits;
	open_properties.baud_Rate	= cfg->baud_Rate;
	open_properties.bits_Per_Char= (qapi_UART_Bits_Per_Char_e)cfg->bits_Per_Char;
	open_properties.tx_CB_ISR = tx_cb;
	open_properties.rx_CB_ISR = cfg->rxCb;
	open_properties.enable_Flow_Ctrl = cfg->enable_Flow_Ctrl;
	open_properties.enable_Loopback = cfg->enable_Loopback;
	int res = qapi_UART_Open(&mctx->handle, cfg->port, &open_properties);
	if(res != QAPI_OK) return res;

	res = tx_semaphore_create(&mctx->mtx, "uart_send_mtx", 1);
	if(res != TX_SUCCESS) {
		//qapi_UART_Close(&mctx->handle);
		return res;
	}
	*ctx = mctx;

	return QAPI_OK;
}

qapi_Status_t uart_write_str(uart_context_t ctx, const char* str) {
	if(ctx == NULL || str == NULL) return QAPI_ERR_INVALID_PARAM;
	return uart_write(ctx, str, strlen(str));
}

qapi_Status_t uart_write(uart_context_t ctx, const char* str, size_t len) {
	if(ctx == NULL || str == NULL) return QAPI_ERR_INVALID_PARAM;

	if(len > ctx->send_buf_len) {
		while(true) {
			if(len <= ctx->send_buf_len) {
				uart_write(ctx, str, len);
				break;
			} else {
				uart_write(ctx, str, ctx->send_buf_len);
				str += ctx->send_buf_len;
				len -= ctx->send_buf_len;
			}
		}
	} else {
		// Lock semaphore
		tx_semaphore_get(&ctx->mtx, TX_WAIT_FOREVER);
		// Copy data to send buffer
		memset(ctx->sendbuf, 0, ctx->send_buf_len);
		memcpy(ctx->sendbuf, (char*)str, len);
		// Send data (async)
		qapi_UART_Transmit(ctx->handle, ctx->sendbuf, len, ctx);
	}
	return QAPI_OK;
}

#ifdef __GNUC__
static int vcb_uart_cb(char* buf, size_t done, void* param) {
	uart_write((uart_context_t)param, buf, done);
	return 0;
}

qapi_Status_t uart_vprintf(uart_context_t ctx, const char* fmt, va_list args) {
	char buf[256];
	vcbprintf(buf, sizeof(buf), vcb_uart_cb, ctx, fmt, args);
	return QAPI_OK;
}
#else
qapi_Status_t uart_vprintf(uart_context_t ctx, const char* fmt, va_list args) {
	char buf[256];
	vsnprintf(buf, sizeof(buf), fmt, args);
	uart_write_str(ctx, buf);
	return QAPI_OK;
}
#endif

qapi_Status_t uart_printf(uart_context_t ctx, const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int res = uart_vprintf(ctx, fmt, args);
	va_end(args);
	return res;
}
