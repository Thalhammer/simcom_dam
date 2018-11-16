#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_timer.h"
#include "qapi/qapi_device_info.h"
#include "util/debug.h"
#include "util/trace.h"
#include "util/boot_cfg.h"

#include "tx_api.h"

#define TRACE_TAG "main"

static const char* info_map[] = {
	"BUILD_ID", /**< Device BUILD_ID. */
	"IMEI", /**< Device IMEI. */
	"IMSI", /**< UIM IMSI. */
	"OS_VERSION", /**< Device OS version. */
	"MANUFACTURER", /**< Device manufacturer. */
	"MODEL_ID", /**< Device model ID. */
	"BATTERY_STATUS", /**< Device battery status. */
	"BATTERY_PERCENTAGE", /**< Device battery percentage. */
	"TIME_ZONE", /**< Device time zone. */
	"ICCID", /**< Device ICCID. */
	"4G_SIG_STRENGTH", /**< Network signal strength. */
	"BASE_STATION_ID", /**< Network base station ID. */
	"MCC", /**< Network MCC. */
	"MNC", /**< Network MNC. */
	"SERVICE_STATE", /**< Network service status. */
	"MDN", /**< Deivce MDN. */
	"TAC", /**< Network tracking area code. */
	"CELL_ID", /**< Network cell ID. */
	"RCCS", /**< Network RRC state. */
	"EMMS", /**< Network EMM state. */
	"DEPRACATED1", /** <Info to keep numbering of enum same> */
	"SERVING_PCI", /**< Network serving cell PCI. */
	"SERVING_RSRQ", /**< Serving cell RSRQ. */
	"SERVING_EARFCN", /**< Serving cell EARFCN. */
	"DEPRACATED2", /** <Info to keep numbering of enum same> */
	"DEPRACATED3", /** <Info to keep numbering of enum same> */
	"DEPRACATED4", /** <Info to keep numbering of enum same> */
	"DEPRACATED5", /** <Info to keep numbering of enum same> */
	"DEPRACATED6", /** <Info to keep numbering of enum same> */
	"NETWORK_IND", /**< Network indication */
	"ROAMING", /**< Roaming status. */
	"LAST_POWER_ON", /**< Last power on time. */
	"CHIPID_STRING", /**< Chipset name. */
	"APN_PROFILE_INDEX", /** < APN Profile Index > */
	"SIM_STATE"
};

static void devinfo_cb(const qapi_Device_Info_t* info) {
	if(info->info_type == QAPI_DEVICE_INFO_TYPE_BOOLEAN_E) {
		TRACE("info update %s: %s\r\n", info_map[info->id], (info->u.valuebool ? "yes" : "no"));
	} else if(info->info_type == QAPI_DEVICE_INFO_TYPE_INTEGER_E) {
		TRACE("info update %s: %d\r\n", info_map[info->id], info->u.valueint);
	} else if(info->info_type == QAPI_DEVICE_INFO_TYPE_BUFFER_E) {
		TRACE("info update %s: buffer(%d bytes)\r\n", info_map[info->id], info->u.valuebuf.len);
	} else {
		TRACE("unknown devinfo type for %s\r\n", info_map[info->id]);
	}
}

int dam_app_start(void)
{
	if(boot_cfg() != 0) return TX_SUCCESS;
	if(debug_init() != QAPI_OK) return TX_SUCCESS;
	TRACE("waiting some time\r\n");
	qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true);
	TRACE("init\r\n");

	int status = qapi_Device_Info_Init();
	if(status != QAPI_OK){
		TRACE("failed to init deviceinfo: %d\r\n", status);
		return TX_SUCCESS;
	}

	for(int i=0; i<=QAPI_DEVICE_INFO_SIM_STATE_E; i++) {
		if(i == DEPRACATED1 || (i >= DEPRACATED2 && i <= DEPRACATED6)) continue;
		qapi_Device_Info_t info;
		memset(&info, 0, sizeof(info));
		status = qapi_Device_Info_Get(i, &info);
		if(status != QAPI_OK) {
			TRACE("failed to get device info for %s: %d\r\n", info_map[i], status);
			continue;
		}
		if(info.info_type == QAPI_DEVICE_INFO_TYPE_BOOLEAN_E) {
			TRACE("%s: %s\r\n", info_map[info.id], (info.u.valuebool ? "yes" : "no"));
		} else if(info.info_type == QAPI_DEVICE_INFO_TYPE_INTEGER_E) {
			TRACE("%s: %d\r\n", info_map[info.id], info.u.valueint);
		} else if(info.info_type == QAPI_DEVICE_INFO_TYPE_BUFFER_E) {
			char buf[QAPI_DEVICE_INFO_BUF_SIZE + 1];
			memset(buf, 0, sizeof(buf));
			memcpy(buf, info.u.valuebuf.buf, info.u.valuebuf.len);
			TRACE("%s: \"%s\" (%d bytes)\r\n", info_map[info.id], buf, info.u.valuebuf.len);
		} else {
			TRACE("unknown devinfo type for %s\r\n", info_map[info.id]);
		}

		status = qapi_Device_Info_Set_Callback(i, devinfo_cb);
		if(status != QAPI_OK) {
			TRACE("failed to register callback for %s: %d\r\n", info_map[i], status);
		}
	}

	TRACE("done\r\n");
	return TX_SUCCESS;
}
