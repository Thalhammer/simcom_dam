#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_timer.h"
#include "qapi/qapi_psm.h"
#include "qapi/qapi_pmapp_rtc.h"
#include "util/debug.h"
#include "util/trace.h"
#include "util/boot_cfg.h"

#include "tx_api.h"

#define TRACE_TAG "main"

const char* status_map[] = {
	"NONE",
	"REJECT",            /**< PSM enter request is rejected */
	"READY",             /**< Ready to enter into PSM mode. */
	"NOT_READY",         /**< Not ready to enter PSM. */
	"COMPLETE",          /**< Entered into PSM mode, system might shutdown any time. */
	"DISCONNECTED",      /**< PSM Server is down. */
	"MODEM_LOADED",      /**< Modem is loaded as part of boot up. */
	"MODEM_NOT_LOADED",  /**< Modem is not loaded as part of boot up.*/
	"NW_OOS",            /** < Network is OOS. */
	"NW_LIMITED_SERVICE",/**< Network is Limited Service. */
	"HEALTH_CHECK",      /**< Application health check.*/
	"FEATURE_ENABLED",   /**< Feature is dynamically enabled.*/
	"FEATURE_DISABLED"
};

const char* reason_map[] = {
	"NONE",                /**< Reject reason None.*/
	"NOT_ENABLED",         /**< PSM feature is not enabled. */
	"MODEM_NOT_READY",     /**< Modem is not ready to enter into PSM mode.*/
	"DURATION_TOO_SHORT",  /**< PSM duration is too short to enter into PSM mode.*/
};

void psm_cb(psm_status_msg_type* msg) {
	TRACE("psm_cb client=%d reason=%s(%d) status=%s(%d)\r\n", msg->client_id, reason_map[msg->reason], msg->reason, status_map[msg->status], msg->status);
	if(msg->status == PSM_STATUS_HEALTH_CHECK)
		qapi_PSM_Client_Hc_Ack(msg->client_id);
	if(msg->status == PSM_STATUS_REJECT && msg->reason == PSM_REJECT_REASON_NOT_ENABLED)
		TRACE("PSM is not enabled, please enable it using AT or VisualAT in the APP\r\n");
	if(msg->status == PSM_STATUS_READY) {
		TRACE("ready state signaled, entering PSM any moment\r\n");
	}
}

int dam_app_start(void)
{
	if(boot_cfg() != 0) return TX_SUCCESS;
	if(debug_init() != QAPI_OK) return TX_SUCCESS;
	TRACE("waiting some time\r\n");
	qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true);
	TRACE("init\r\n");

	// It seems like RTC needs to be initialized or the module will enter PSM but never return.
	int res = qapi_PM_Rtc_Init();
	if(res != QAPI_OK) {
		TRACE("failed to init rtc: %d\r\n", res);
		return TX_SUCCESS;
	} else TRACE("rtc initialized\r\n");

	int32_t clientid;
	res = qapi_PSM_Client_Register(&clientid, psm_cb);
	if(res != QAPI_OK) {
		TRACE("failed to register client: %d\r\n", res);
		return TX_SUCCESS;
	} else TRACE("registered client with psmserver\r\n");

	if(qapi_Timer_Sleep(1, QAPI_TIMER_UNIT_SEC, true) != QAPI_OK) {
		TRACE("sleep failed\r\n");
		return TX_SUCCESS;
	}

	// The app is now registered as being PSM aware. This results in the module not entering
	// PSM mode anymore until you sign your intent to enter it.
	psm_info_type info;
	memset(&info, 0, sizeof(info));
	// You might specify PSM_WAKEUP_MEASUREMENT_ONLY if you don't want to do network access on next wakeup.
	// If you do so, the modem might not get loaded which should save startuptime and power.
	info.psm_wakeup_type = PSM_WAKEUP_MEASUREMENT_NW_ACCESS;
	info.psm_time_info.time_format_flag = PSM_TIME_IN_SECS; // Time is specified in seconds
	// Time to sleep for in seconds (Minimum 550 seconds, 9:10 minutes)
	// however this time might not be accurate
	info.psm_time_info.psm_duration_in_secs = 600;
	info.active_time_in_secs = 10; // Time in secs to wait until entering PSM mode
	res = qapi_PSM_Client_Enter_Psm(clientid, &info);
	if(res != QAPI_OK) {
		TRACE("failed to enter psm: %d\r\n", res);
		return TX_SUCCESS;
	} else TRACE("entering psm mode\r\n");
	// We exit here, but entering psm is async, so we might get turned off at any time.
	// When we return from PSM the application will start from the beginning.
	// Memory contents might not be preserved.

	TRACE("done\r\n");
	return TX_SUCCESS;
}
