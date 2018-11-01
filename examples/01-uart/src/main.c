#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi_timer.h"
#include "uart.h"

#include "tx_api.h"

int dam_app_start(void)
{
	const char* msg = "Hello from DAM :) \r\n";

	uart_init();
	tx_thread_sleep(100);

	for(int i = 0; i<1000; i++) {
		uart_write_str(msg);
	}
	tx_thread_sleep(100);

	return TX_SUCCESS;
}
