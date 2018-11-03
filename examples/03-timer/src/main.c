#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi_timer.h"
#include "util/uart.h"

#include "tx_api.h"

uart_context_t uart;
int i;

void timer_test_cb(uint32_t udata) {
	uart_printf(uart, "cb %d\r\n", i++);
}

uint8_t uart_buf[256];

int dam_app_start(void)
{
	i=0;
	uart_init_config_t uartcfg;
	uart_default_cfg(&uartcfg);
	uartcfg.buf = uart_buf;
	uartcfg.buf_len = 256;
	if(uart_init(&uart, &uartcfg) != QAPI_OK) return TX_SUCCESS;

	qapi_TIMER_handle_t timer_handle;	  
	qapi_TIMER_define_attr_t timer_def_attr; 
	timer_def_attr.cb_type = QAPI_TIMER_FUNC1_CB_TYPE; //notification type
	timer_def_attr.sigs_func_ptr = &timer_test_cb; //callback to call when timer expires
	timer_def_attr.sigs_mask_data = 0x1; //this data will be returned in the callback
	timer_def_attr.deferrable = false; //set to true for non-deferrable timer

	//define the timer. Note: This call allocates memory and hence qapi_Timer_Undef()
	//should be called whenever the timer usage is done.
	int res = qapi_Timer_Def( &timer_handle, &timer_def_attr);
	if(res != 0) {
		uart_printf(uart, "failed to def timer: %d\r\n", res);
		return TX_SUCCESS;
	}
	else uart_write_str(uart, "timer defined\r\n");

	qapi_TIMER_set_attr_t timer_set_attr; 
	timer_set_attr.reload = 1000;
	timer_set_attr.time = 1000; 
	timer_set_attr.unit = QAPI_TIMER_UNIT_MSEC; 
	res = qapi_Timer_Set(timer_handle, &timer_set_attr);
	if(res != 0){
		uart_printf(uart, "failed to set timer: %d\r\n", res);
	}
	else uart_write_str(uart, "timer set\r\n");

	// stop a running timer
	// qapi_Timer_stop(timer_handle);

	// Undef the timer. Releases memory allocated in qapi_Timer_Def()
	// qapi_Timer_undef(timer_handle);

	return TX_SUCCESS;
}
