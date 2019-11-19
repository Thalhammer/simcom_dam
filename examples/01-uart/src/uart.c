#include "uart.h"
#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi_timer.h"
#include "qapi_uart.h"

#include "tx_api.h"

#define UART_SENDBUF_SIZE 256

static char send_buf[UART_SENDBUF_SIZE];
static qapi_UART_Handle_t uart_handle;
static TX_SEMAPHORE* uart_mtx;

static void tx_cb(uint32_t num_bytes, void *cb_data) {
	(void)num_bytes;
	(void)cb_data;
	tx_semaphore_put(uart_mtx);
}

void app_uart_init(void) {
	qapi_UART_Open_Config_t open_properties;
	memset (&open_properties, 0, sizeof(open_properties));
	open_properties.parity_Mode = QAPI_UART_NO_PARITY_E;
	open_properties.num_Stop_Bits= QAPI_UART_1_0_STOP_BITS_E;
	open_properties.baud_Rate	= 115200;
	open_properties.bits_Per_Char= QAPI_UART_8_BITS_PER_CHAR_E;
	open_properties.tx_CB_ISR = tx_cb;
	qapi_UART_Open(&uart_handle, QAPI_UART_PORT_003_E, &open_properties);
	if(txm_module_object_allocate((void**)&uart_mtx, sizeof(TX_SEMAPHORE)) != TX_SUCCESS) return;
	if(tx_semaphore_create(uart_mtx, "uart_send_mtx", 1) != TX_SUCCESS) return;
}

void app_uart_write_str(const char* str) {
	app_uart_write(str, strlen(str));
}

void app_uart_write(const char* str, size_t len) {
	if(len > UART_SENDBUF_SIZE) {
		while(true) {
			if(len <= UART_SENDBUF_SIZE) {
				app_uart_write(str, len);
				break;
			} else {
				app_uart_write(str, UART_SENDBUF_SIZE);
				str += UART_SENDBUF_SIZE;
				len -= UART_SENDBUF_SIZE;
			}
		}
	} else {
		// Lock semaphore
		tx_semaphore_get(uart_mtx, TX_WAIT_FOREVER);
		// Copy data to send buffer
		memset(send_buf, 0, UART_SENDBUF_SIZE);
		memcpy(send_buf, (char*)str, len);
		// Send data (async)
		qapi_UART_Transmit(uart_handle, send_buf, len, NULL);
	}
}
