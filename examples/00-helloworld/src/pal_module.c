#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi_timer.h"
#include "qapi_uart.h"

#include "tx_api.h"

char send_buf[256];

int dam_app_start(void)
{
	const char* msg = "Hello from DAM :) \r\n";

	qapi_UART_Handle_t uart_handle;

	qapi_UART_Open_Config_t open_properties;
	memset (&open_properties, 0, sizeof (open_properties));
	open_properties.parity_Mode = QAPI_UART_NO_PARITY_E;
	open_properties.num_Stop_Bits= QAPI_UART_1_0_STOP_BITS_E;
	open_properties.baud_Rate	= 115200;
	open_properties.bits_Per_Char= QAPI_UART_8_BITS_PER_CHAR_E;
	qapi_UART_Open(&uart_handle, QAPI_UART_PORT_003_E, &open_properties);

	tx_thread_sleep(100);

	memset(send_buf, 0, sizeof (send_buf));
	memcpy(send_buf, (char*)msg, strlen(msg));
	qapi_UART_Transmit(uart_handle, send_buf, strlen(msg), NULL);
	tx_thread_sleep(100);
	return TX_SUCCESS;
}
