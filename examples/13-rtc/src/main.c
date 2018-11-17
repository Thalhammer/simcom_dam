#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_timer.h"
#include "qapi/qapi_pmapp_rtc.h"
#include "util/debug.h"
#include "util/trace.h"
#include "util/boot_cfg.h"

#include "tx_api.h"

#define TRACE_TAG "main"

void timer_cb(uint32_t data) {
	qapi_PM_Rtc_Julian_Type_t time;
	memset(&time, 0, sizeof(time));
	int res = qapi_PM_Rtc_Read_Cmd(&time);
	if(res != QAPI_OK) {
		TRACE("failed to read rtc: %d\r\n", res);
		return;
	} else TRACE("rtc read\r\n");

	TRACE("%d-%d-%d %d:%d:%d %d\r\n", time.year, time.month, time.day, time.hour, time.minute, time.second, time.day_of_week);
}

int dam_app_start(void)
{
	if(boot_cfg() != 0) return TX_SUCCESS;
	if(debug_init() != QAPI_OK) return TX_SUCCESS;
	TRACE("waiting some time\r\n");
	qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true);
	TRACE("init\r\n");

	int res = qapi_PM_Rtc_Init();
	if(res != QAPI_OK) {
		TRACE("failed to init rtc: %d\r\n", res);
		return TX_SUCCESS;
	} else TRACE("rtc initialized\r\n");

	// Note that the RTC does work, but I couldn't figure out how to set it.
	// There is no command to do so and mocking around with the parameters of
	// the read command didn't work.
	// You can set and read an rtc using "At+CCLK", which keeps its time,
	// but this doesn't seem to affekt the values returned by this rtc.

	qapi_TIMER_handle_t timer_handle;	  
	qapi_TIMER_define_attr_t timer_def_attr; 
	timer_def_attr.cb_type = QAPI_TIMER_FUNC1_CB_TYPE; //notification type
	timer_def_attr.sigs_func_ptr = &timer_cb; //callback to call when timer expires
	timer_def_attr.sigs_mask_data = 0x1; //this data will be returned in the callback
	timer_def_attr.deferrable = false; //set to true for non-deferrable timer

	//define the timer. Note: This call allocates memory and hence qapi_Timer_Undef()
	//should be called whenever the timer usage is done.
	res = qapi_Timer_Def( &timer_handle, &timer_def_attr);
	if(res != 0) {
		TRACE("failed to def timer: %d\r\n", res);
		return TX_SUCCESS;
	} else TRACE("timer initialized\r\n");

	qapi_TIMER_set_attr_t timer_set_attr; 
	timer_set_attr.reload = 1000;
	timer_set_attr.time = 1000; 
	timer_set_attr.unit = QAPI_TIMER_UNIT_MSEC; 
	res = qapi_Timer_Set(timer_handle, &timer_set_attr);
	if(res != 0){
		TRACE("failed to set timer: %d\r\n", res);
	}
	else TRACE("timer set\r\n");

	TRACE("done\r\n");
	return TX_SUCCESS;
}
