#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "util/init_config.h"
#include "qapi_timer.h"
#include "uart.h"

#include "tx_api.h"

INIT_DISABLE_DEBUG_UART();
INIT_DISABLE_SAFETY_DELAY();

int dam_app_start(void)
{
	const char* msg = "Hello from DAM :) \r\n";

	app_uart_init();
	tx_thread_sleep(100);

	for(int i = 0; i<1000; i++) {
		app_uart_write_str(msg);
	}
	tx_thread_sleep(100);

	return TX_SUCCESS;
}
