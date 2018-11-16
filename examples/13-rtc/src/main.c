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

	while(true) {
		res = qapi_Timer_Sleep(1, QAPI_TIMER_UNIT_SEC, true);
		if(res != QAPI_OK) TRACE("sleep failed: %d\r\n", res);

		qapi_PM_Rtc_Julian_Type_t time;
		memset(&time, 0, sizeof(time));
		res = qapi_PM_Rtc_Read_Cmd(&time);
		if(res != QAPI_OK) {
			TRACE("failed to read rtc: %d\r\n", res);
			return TX_SUCCESS;
		} else TRACE("rtc read\r\n");

		TRACE("%d-%d-%d %d:%d:%d %d\r\n", time.year, time.month, time.day, time.hour, time.minute, time.second, time.day_of_week);
	}
	TRACE("done\r\n");
	return TX_SUCCESS;
}
