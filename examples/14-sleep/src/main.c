#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_timer.h"
#include "util/debug.h"
#include "util/trace.h"
#include "util/uart.h"
#include "util/boot_cfg.h"

#include "tx_api.h"

#define TRACE_TAG "main"

TX_EVENT_FLAGS_GROUP flags;

int i = 0;

void timer_cb(uint32_t data) {
	i++;
	tx_event_flags_set(&flags, 0x01, TX_OR);
}

int dam_app_start(void)
{
	int res;
	//if(boot_cfg() != 0) return TX_SUCCESS;
	if(debug_init() != QAPI_OK) return TX_SUCCESS;
	TRACE("waiting some time\r\n");
	qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true);
	TRACE("init\r\n");

	qapi_TIMER_handle_t timer_handle;
	qapi_TIMER_define_attr_t timer_def_attr;
	timer_def_attr.cb_type = QAPI_TIMER_FUNC1_CB_TYPE; //notification type
	timer_def_attr.sigs_func_ptr = &timer_cb; //callback to call when timer expires
	timer_def_attr.sigs_mask_data = 0x1; //this data will be returned in the callback
	// Set to true for deferrable timer. If you do this the timing is entirely
	// unpredictable and might exceed the configured time by a lot 
	timer_def_attr.deferrable = false;

	// Define the timer. Note: This call allocates memory and hence qapi_Timer_Undef()
	// should be called whenever the timer usage is done.
	res = qapi_Timer_Def( &timer_handle, &timer_def_attr);
	if(res != 0) {
		TRACE("failed to def timer: %d\r\n", res);
		return TX_SUCCESS;
	} else TRACE("timer initialized\r\n");

	qapi_TIMER_set_attr_t timer_set_attr;
	timer_set_attr.reload = 30000;
	timer_set_attr.time = 30000;
	timer_set_attr.unit = QAPI_TIMER_UNIT_MSEC; 
	res = qapi_Timer_Set(timer_handle, &timer_set_attr);
	if(res != 0){
		TRACE("failed to set timer: %d\r\n", res);
	}
	else TRACE("timer set\r\n");

	tx_event_flags_create(&flags, "flags");

	int res2 = uart_power_off(debug_get_handle());
	while(true) {
		unsigned int act;
		tx_event_flags_get(&flags, 0x01, TX_AND_CLEAR, &act, TX_WAIT_FOREVER);
		res = uart_power_on(debug_get_handle());
		TRACE("ping i=%d, res=%d, res2=%d\r\n", i, res, res2);
		res2 = uart_power_off(debug_get_handle());
	}
}
