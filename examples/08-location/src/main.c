#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_timer.h"
#include "qapi/qapi_location.h"
#include "util/debug.h"
#include "util/trace.h"
#include "util/boot_cfg.h"

#include "tx_api.h"

#define TRACE_TAG "main"

static const char* error_map[] = {
	"SUCCESS",            /**< Success. */
    "GENERAL_FAILURE",    /**< General failure. */
    "CALLBACK_MISSING",   /**< Callback is missing. */
    "INVALID_PARAMETER",  /**< Invalid parameter. */
    "ID_EXISTS",          /**< ID already exists. */
    "ID_UNKNOWN",         /**< ID is unknown. */
    "ALREADY_STARTED",    /**< Already started. */
    "NOT_INITIALIZED",    /**< Not initialized. */
    "GEOFENCES_AT_MAX",   /**< Maximum number of geofences reached. */
    "NOT_SUPPORTED"       /**< Not supported. */
};

static void loc_cap_cb(qapi_Location_Capabilities_Mask_t caps)
{
	TRACE("capabilities received:\r\n");
	TRACE("time base tracking:     %s\r\n", ((caps & QAPI_LOCATION_CAPABILITIES_TIME_BASED_TRACKING_BIT)?"yes":"no"));
	TRACE("time base batching:     %s\r\n", ((caps & QAPI_LOCATION_CAPABILITIES_TIME_BASED_BATCHING_BIT)?"yes":"no"));
	TRACE("distance base tracking: %s\r\n", ((caps & QAPI_LOCATION_CAPABILITIES_DISTANCE_BASED_TRACKING_BIT)?"yes":"no"));
	TRACE("distance base batching: %s\r\n", ((caps & QAPI_LOCATION_CAPABILITIES_DISTANCE_BASED_BATCHING_BIT)?"yes":"no"));
	TRACE("geofence:               %s\r\n", ((caps & QAPI_LOCATION_CAPABILITIES_GEOFENCE_BIT)?"yes":"no"));
}

static void loc_response_cb(qapi_Location_Error_t err,uint32_t id)
{
	TRACE("single response callback\r\n");
	TRACE("Error: %s\r\n", error_map[err]);
	TRACE("ID:    %d\r\n", id);
}

static void loc_collective_response_cb(size_t count, qapi_Location_Error_t* err, uint32_t* ids)
{
	TRACE("collective response callback (%d values)\r\n", count);
	for(size_t i = 0; i < count; i++) {
		TRACE("[%d]Error: %s\r\n", i, error_map[err[i]]);
		TRACE("[%d]ID:    %d\r\n", i, ids[i]);
	}
}

static void loc_tracking_cb(qapi_Location_t loc)
{
	TRACE("tracking callback\r\n");
	if(loc.size != sizeof(qapi_Location_t)) {
		TRACE("param size missmatch\r\n");
		return;
	}
	TRACE("flags: pos=%s alt=%s speed=%s bearing=%s acc=%s vacc=%s sacc=%s bacc=%s\r\n",
		((loc.flags & QAPI_LOCATION_HAS_LAT_LONG_BIT)?"y":"n"),
		((loc.flags & QAPI_LOCATION_HAS_ALTITUDE_BIT)?"y":"n"),
		((loc.flags & QAPI_LOCATION_HAS_SPEED_BIT)?"y":"n"),
		((loc.flags & QAPI_LOCATION_HAS_BEARING_BIT)?"y":"n"),
		((loc.flags & QAPI_LOCATION_HAS_ACCURACY_BIT)?"y":"n"),
		((loc.flags & QAPI_LOCATION_HAS_VERTICAL_ACCURACY_BIT)?"y":"n"),
		((loc.flags & QAPI_LOCATION_HAS_SPEED_ACCURACY_BIT)?"y":"n"),
		((loc.flags & QAPI_LOCATION_HAS_BEARING_ACCURACY_BIT)?"y":"n")
	);
	TRACE("timestamp: %d\r\n", (int)(loc.timestamp/1000));
	if(loc.flags & QAPI_LOCATION_HAS_LAT_LONG_BIT) {
		TRACE("position:         %f %f\r\n", loc.latitude, loc.longitude);
	}
	if(loc.flags & QAPI_LOCATION_HAS_ALTITUDE_BIT) {
		TRACE("altitude:         %fm\r\n", loc.altitude);
	}
	if(loc.flags & QAPI_LOCATION_HAS_SPEED_BIT) {
		TRACE("speed:            %fm/s\r\n", loc.speed);
	}
	if(loc.flags & QAPI_LOCATION_HAS_BEARING_BIT) {
		TRACE("bearing:          %f°\r\n", loc.bearing);
	}
	if(loc.flags & QAPI_LOCATION_HAS_ACCURACY_BIT) {
		TRACE("accuracy:         %fm\r\n", loc.accuracy);
	}
	if(loc.flags & QAPI_LOCATION_HAS_VERTICAL_ACCURACY_BIT) {
		TRACE("vertical accuracy:%fm\r\n", loc.verticalAccuracy);
	}
	if(loc.flags & QAPI_LOCATION_HAS_SPEED_ACCURACY_BIT) {
		TRACE("speed accuracy:   %fm\r\n", loc.speedAccuracy);
	}
	if(loc.flags & QAPI_LOCATION_HAS_BEARING_ACCURACY_BIT) {
		TRACE("bearing accuracy: %fm\r\n", loc.bearingAccuracy);
	}
}

int dam_app_start(void)
{
	if(boot_cfg() != 0) return TX_SUCCESS;
	if(debug_init() != QAPI_OK) return TX_SUCCESS;
	TRACE("waiting some time\r\n");
	qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true);
	TRACE("init\r\n");

	qapi_Location_Callbacks_t cbs;
	memset(&cbs, 0, sizeof(cbs));
	cbs.size = sizeof(cbs);
	cbs.capabilitiesCb = loc_cap_cb;
	cbs.responseCb = loc_response_cb;
	cbs.collectiveResponseCb = loc_collective_response_cb;
	cbs.trackingCb = loc_tracking_cb;

	qapi_Location_Options_t opts;
	memset(&opts, 0, sizeof(opts));
	opts.size = sizeof(opts);
	opts.minInterval = 0;
	opts.minDistance = 0;

	qapi_loc_client_id clientid;
	uint32_t sessionid;
	qapi_Location_Error_t err = (qapi_Location_Error_t)qapi_Loc_Init(&clientid, &cbs);
	if(err != QAPI_LOCATION_ERROR_SUCCESS) {
		TRACE("failed to init location: %s\r\n", error_map[err]);
		return TX_SUCCESS;
	} else TRACE("location initialized\r\n");
	err = (qapi_Location_Error_t)qapi_Loc_Start_Tracking(clientid, &opts, &sessionid);
	if(err != QAPI_LOCATION_ERROR_SUCCESS) {
		TRACE("failed to start tracking: %s\r\n", error_map[err]);
		return TX_SUCCESS;
	} else TRACE("tracking started\r\n");

	TRACE("done\r\n");
	return TX_SUCCESS;
}
