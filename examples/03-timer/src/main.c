#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi_timer.h"
#include "uart.h"

#include "tx_api.h"

void timer_test_cb(uint32_t udata) {
	uart_write_str("cb\r\n");
}

int dam_app_start(void)
{
	uart_init();

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
		uart_write_str("failed to def timer\r\n");
		char str[] = {0, 0};
		str[0] = '0' + res;
		uart_write(str, 1);
	}
	else uart_write_str("timer defined\r\n");

	qapi_TIMER_set_attr_t timer_set_attr; 
	timer_set_attr.reload = 1000;
	timer_set_attr.time = 1000; 
	timer_set_attr.unit = QAPI_TIMER_UNIT_MSEC; 
	res = qapi_Timer_Set(timer_handle, &timer_set_attr);
	if(res != 0){
		uart_write_str("failed to set timer\r\n");
		char str[] = {0, 0};
		str[0] = '0' + res;
		uart_write(str, 1);
	}
	else uart_write_str("timer set\r\n");

	// stop a running timer
	// qapi_Timer_stop(timer_handle);

	// Undef the timer. Releases memory allocated in qapi_Timer_Def()
	// qapi_Timer_undef(timer_handle);

	return TX_SUCCESS;
}
