#include "util/GNSS_Client.h"
#include "util/trace.h"
#include <qapi/qapi_location_txm.h>
#include "util/AsmBuilder.h"
#include "assert.h"

#define TRACE_TAG "GNSS_Client"

#define EVT_FLAG_INIT_DONE (1<<0)
#define EVT_FLAG_GOT_FIX (1<<1)

constexpr static const char* error_map[] = {
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

void GNSS_Client::Capabilities_Callback(GNSS_Client* instance, uint32_t caps) noexcept
{
    instance->m_capabilities = caps;
    if(instance->m_debug_enabled) {
        TRACE("capabilities received:\r\n");
        TRACE("time base tracking:     %s\r\n", ((caps & QAPI_LOCATION_CAPABILITIES_TIME_BASED_TRACKING_BIT)?"yes":"no"));
        TRACE("time base batching:     %s\r\n", ((caps & QAPI_LOCATION_CAPABILITIES_TIME_BASED_BATCHING_BIT)?"yes":"no"));
        TRACE("distance base tracking: %s\r\n", ((caps & QAPI_LOCATION_CAPABILITIES_DISTANCE_BASED_TRACKING_BIT)?"yes":"no"));
        TRACE("distance base batching: %s\r\n", ((caps & QAPI_LOCATION_CAPABILITIES_DISTANCE_BASED_BATCHING_BIT)?"yes":"no"));
        TRACE("geofence:               %s\r\n", ((caps & QAPI_LOCATION_CAPABILITIES_GEOFENCE_BIT)?"yes":"no"));
    }
}

void GNSS_Client::Tracking_Callback(GNSS_Client* instance, void* location) noexcept
{
    qapi_Location_t* loc = reinterpret_cast<qapi_Location_t*>(location);
    if(instance->m_debug_enabled) TRACE("tracking callback\r\n");
	if(loc->size != sizeof(qapi_Location_t)) {
		if(instance->m_debug_enabled) TRACE("param size missmatch\r\n");
		return;
	}
    if(instance->m_debug_enabled) {
        TRACE("flags: pos=%s alt=%s speed=%s bearing=%s acc=%s vacc=%s sacc=%s bacc=%s\r\n",
            ((loc->flags & QAPI_LOCATION_HAS_LAT_LONG_BIT)?"y":"n"),
            ((loc->flags & QAPI_LOCATION_HAS_ALTITUDE_BIT)?"y":"n"),
            ((loc->flags & QAPI_LOCATION_HAS_SPEED_BIT)?"y":"n"),
            ((loc->flags & QAPI_LOCATION_HAS_BEARING_BIT)?"y":"n"),
            ((loc->flags & QAPI_LOCATION_HAS_ACCURACY_BIT)?"y":"n"),
            ((loc->flags & QAPI_LOCATION_HAS_VERTICAL_ACCURACY_BIT)?"y":"n"),
            ((loc->flags & QAPI_LOCATION_HAS_SPEED_ACCURACY_BIT)?"y":"n"),
            ((loc->flags & QAPI_LOCATION_HAS_BEARING_ACCURACY_BIT)?"y":"n")
        );
        TRACE("timestamp: %d\r\n", (int)(loc->timestamp/1000));
        if(loc->flags & QAPI_LOCATION_HAS_LAT_LONG_BIT) {
            TRACE("position:         %f %f\r\n", loc->latitude, loc->longitude);
        }
        if(loc->flags & QAPI_LOCATION_HAS_ALTITUDE_BIT) {
            TRACE("altitude:         %fm\r\n", loc->altitude);
        }
        if(loc->flags & QAPI_LOCATION_HAS_SPEED_BIT) {
            TRACE("speed:            %fm/s\r\n", loc->speed);
        }
        if(loc->flags & QAPI_LOCATION_HAS_BEARING_BIT) {
            TRACE("bearing:          %f°\r\n", loc->bearing);
        }
        if(loc->flags & QAPI_LOCATION_HAS_ACCURACY_BIT) {
            TRACE("accuracy:         %fm\r\n", loc->accuracy);
        }
        if(loc->flags & QAPI_LOCATION_HAS_VERTICAL_ACCURACY_BIT) {
            TRACE("vertical accuracy:%fm\r\n", loc->verticalAccuracy);
        }
        if(loc->flags & QAPI_LOCATION_HAS_SPEED_ACCURACY_BIT) {
            TRACE("speed accuracy:   %fm\r\n", loc->speedAccuracy);
        }
        if(loc->flags & QAPI_LOCATION_HAS_BEARING_ACCURACY_BIT) {
            TRACE("bearing accuracy: %fm\r\n", loc->bearingAccuracy);
        }
    }

    instance->m_last_location.timestamp = loc->timestamp;
    instance->m_last_location.latitude = loc->latitude;
    instance->m_last_location.longitude = loc->longitude;
    instance->m_last_location.altitude = loc->altitude;
    instance->m_last_location.speed = loc->speed;
    instance->m_last_location.accuracy = loc->accuracy;
	instance->m_flags.set(EVT_FLAG_GOT_FIX);

    if(instance->m_on_location) instance->m_on_location(&instance->m_last_location, instance->m_userdata);
}

void GNSS_Client::Response_Callback(GNSS_Client* instance, uint32_t err, uint32_t id) noexcept
{
    if(instance->m_debug_enabled) TRACE("response callback error=%s, id=%u\r\n", error_map[err], id);
    if(instance->m_session == id) {
        instance->m_last_error = err;
	    instance->m_flags.set(EVT_FLAG_INIT_DONE);
    }
}

void GNSS_Client::Collective_Response_Callback(GNSS_Client* instance, size_t count, uint32_t* err, uint32_t* ids) noexcept
{
    if(instance->m_debug_enabled) TRACE("collective response callback (%d values)\r\n", count);
	for(size_t i = 0; i < count; i++) {
		Response_Callback(instance, err[i], ids[i]);
	}
}

bool GNSS_Client::begin() noexcept
{
    if(m_is_initialized) return true;

    if(m_debug_enabled) TRACE("initialising\r\n");

    if(!m_flags.initialize("GNSS_Client_flags")) {
        TRACE("failed to create event flags\r\n");
        return false;
    }

    AsmBuilder builder(m_callback_wrapper_code, sizeof(m_callback_wrapper_code));
    qapi_Location_Callbacks_t cbs = {};
    cbs.size = sizeof(cbs);
    cbs.capabilitiesCb = (qapi_Capabilities_Callback)m_callback_wrapper_code;
	builder.mov(AsmBuilder::r1, AsmBuilder::r0);                  // mov r1, r0
	builder.mov(AsmBuilder::r0, (uint32_t)this);                   // mov r0, this
	builder.branch(&GNSS_Client::Capabilities_Callback);            // b Callback
    cbs.trackingCb = (qapi_Tracking_Callback)&m_callback_wrapper_code[builder.get_length()];
    builder.sub_reg_i(AsmBuilder::sp, AsmBuilder::sp, 16);        // sub sp, sp, 16
	builder.push(AsmBuilder::r4);				                    // push r4
	builder.push(AsmBuilder::lr);				                    // push lr
	builder.add_reg_i(AsmBuilder::ip, AsmBuilder::sp, 8);         // add ip, sp, 8
	builder.stmia(AsmBuilder::ip, 0x000f);		                    // stm ip, {r0, r1, r2, r3}
	builder.mov(AsmBuilder::r1, AsmBuilder::ip);		            // mov r1, ip
	builder.mov(AsmBuilder::r0, (uint32_t)this);		            // mov r0, #100
	builder.branch_link(&GNSS_Client::Tracking_Callback);	        // bl Callback
	builder.pop(AsmBuilder::lr);	                                // pop lr
	builder.pop(AsmBuilder::r4);		                            // pop r4
	builder.add_reg_i(AsmBuilder::sp, AsmBuilder::sp, 16);	    // add sp, sp, 16
	builder.branch_exchange(AsmBuilder::lr);	                    // bx lr
    cbs.responseCb = (qapi_Response_Callback)&m_callback_wrapper_code[builder.get_length()];
	builder.mov(AsmBuilder::r2,AsmBuilder::r1);                   // mov r2, r1
	builder.mov(AsmBuilder::r1,AsmBuilder::r0);                   // mov r1, r0
	builder.mov(AsmBuilder::r0, (uint32_t)this);                   // mov r0, this
	builder.branch(&GNSS_Client::Response_Callback);                // b Callback
    cbs.collectiveResponseCb = (qapi_Collective_Response_Callback)&m_callback_wrapper_code[builder.get_length()];
	builder.mov(AsmBuilder::r3,AsmBuilder::r2);                   // mov r3, r2
	builder.mov(AsmBuilder::r2,AsmBuilder::r1);                   // mov r2, r1
	builder.mov(AsmBuilder::r1,AsmBuilder::r0);                   // mov r1, r0
	builder.mov(AsmBuilder::r0, (uint32_t)this);                   // mov r0, this
	builder.branch(&GNSS_Client::Collective_Response_Callback);     // b Callback

    assert(builder.get_length() <= sizeof(m_callback_wrapper_code));
    if(m_debug_enabled) TRACE("builder total = %u\r\n", builder.get_length());

    if(m_debug_enabled) TRACE("instance=%x\r\n", this);

    auto res = qapi_Loc_Init(&m_client, &cbs);
    if(res != QAPI_LOCATION_ERROR_SUCCESS) {
        if(m_debug_enabled) TRACE("Failed to init location provider %s\r\n", (res < sizeof(error_map)/sizeof(const char*)) ? error_map[res] : "UNKNOWN");
        return false;
    }

    m_flags.clear(EVT_FLAG_INIT_DONE);

    qapi_Location_Options_t opts = {};
    opts.size = sizeof(opts);
    opts.minInterval = 1;
    res = qapi_Loc_Start_Tracking(m_client, &opts, &m_session);
    if(res != QAPI_LOCATION_ERROR_SUCCESS) {
        if(m_debug_enabled) TRACE("Failed to start tracking %s\r\n", (res < sizeof(error_map)/sizeof(const char*)) ? error_map[res] : "UNKNOWN");
        // TODO: Deinit location
        return false;
    }

    m_flags.get_all(EVT_FLAG_INIT_DONE, true, TX_WAIT_FOREVER);

    if(m_last_error != QAPI_LOCATION_ERROR_SUCCESS) {
        if(m_debug_enabled) TRACE("Failed to start session %s\r\n", (res < sizeof(error_map)/sizeof(const char*)) ? error_map[res] : "UNKNOWN");
        // TODO: Deinit location
        return false;
    }

    m_is_initialized = true;

    return true;
}

bool GNSS_Client::end() noexcept {
    if(!m_is_initialized) return true;
    
    m_flags.clear(EVT_FLAG_INIT_DONE);

    auto res = qapi_Loc_Stop_Tracking(m_client, m_session);
    if(res != QAPI_LOCATION_ERROR_SUCCESS) {
        if(m_debug_enabled) TRACE("Failed to stop tracking %s\r\n", (res < sizeof(error_map)/sizeof(const char*)) ? error_map[res] : "UNKNOWN");
        return false;
    }

    m_flags.get_all(EVT_FLAG_INIT_DONE, true, TX_WAIT_FOREVER);

    if(m_last_error != QAPI_LOCATION_ERROR_SUCCESS) {
        if(m_debug_enabled) TRACE("Failed to end session %s\r\n", (res < sizeof(error_map)/sizeof(const char*)) ? error_map[res] : "UNKNOWN");
        return false;
    }

    res = qapi_Loc_Deinit(m_client);
    if(res != QAPI_LOCATION_ERROR_SUCCESS) {
        if(m_debug_enabled) TRACE("Failed to deinit provide %s\r\n", (res < sizeof(error_map)/sizeof(const char*)) ? error_map[res] : "UNKNOWN");
        return false;
    }
    m_is_initialized = false;
    return true;
}

bool GNSS_Client::await_fix(uint32_t timeout) noexcept {
    if(m_is_initialized!= true) return false;
    return m_flags.get_all(EVT_FLAG_GOT_FIX, false, timeout ? timeout : TX_WAIT_FOREVER);
}

bool GNSS_Client::has_fix() noexcept {
    if(m_is_initialized!= true) return false;
    return m_flags.get_all(EVT_FLAG_GOT_FIX, false, TX_NO_WAIT);
}

bool GNSS_Client::get_last_fix(location* loc) noexcept {
    if(!has_fix()) return false;
    memcpy(loc, &m_last_location, sizeof(location));
    return true;
}