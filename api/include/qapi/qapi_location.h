/* Copyright (c) 2017 Qualcomm Technologies, Inc.
All rights reserved.

Confidential and Proprietary - Qualcomm Technologies, Inc.

*/

/**
 * @file qapi_location.h
 *
 * @details Functions for GNSS location driver
 *
 */

#ifndef _QAPI_LOCATION_H_
#define _QAPI_LOCATION_H_

#include <stdint.h>
#include <stddef.h>
#include "qapi_txm_base.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TXM_QAPI_LOCATION_INIT                      TXM_QAPI_LOCATION_BASE
#define TXM_QAPI_LOCATION_DEINIT                    TXM_QAPI_LOCATION_BASE + 1
#define TXM_QAPI_LOCATION_START_TRACKING            TXM_QAPI_LOCATION_BASE + 2
#define TXM_QAPI_LOCATION_STOP_TRACKING             TXM_QAPI_LOCATION_BASE + 3
#define TXM_QAPI_LOCATION_UPDATE_TRACKING_OPTIONS   TXM_QAPI_LOCATION_BASE + 4
#define TXM_QAPI_LOCATION_START_BATCHING            TXM_QAPI_LOCATION_BASE + 5
#define TXM_QAPI_LOCATION_STOP_BATCHING             TXM_QAPI_LOCATION_BASE + 6
#define TXM_QAPI_LOCATION_UPDATE_BATCHING_OPTIONS   TXM_QAPI_LOCATION_BASE + 7
#define TXM_QAPI_LOCATION_GET_BATCHED_LOCATIONS     TXM_QAPI_LOCATION_BASE + 8
#define TXM_QAPI_LOCATION_ADD_GEOFENCES             TXM_QAPI_LOCATION_BASE + 9
#define TXM_QAPI_LOCATION_REMOVE_GEOFENCES          TXM_QAPI_LOCATION_BASE + 10
#define TXM_QAPI_LOCATION_MODIFY_GEOFENCES          TXM_QAPI_LOCATION_BASE + 11
#define TXM_QAPI_LOCATION_PAUSE_GEOFENCES           TXM_QAPI_LOCATION_BASE + 12
#define TXM_QAPI_LOCATION_RESUME_GEOFENCES          TXM_QAPI_LOCATION_BASE + 13

/** @addtogroup qapi_location
@{ */

 /**
 * GNSS location error codes.
 */
typedef enum {
    QAPI_LOCATION_ERROR_SUCCESS = 0,        /**< Success. */
    QAPI_LOCATION_ERROR_GENERAL_FAILURE,    /**< General failure. */
    QAPI_LOCATION_ERROR_CALLBACK_MISSING,   /**< Callback is missing. */
    QAPI_LOCATION_ERROR_INVALID_PARAMETER,  /**< Invalid parameter. */
    QAPI_LOCATION_ERROR_ID_EXISTS,          /**< ID already exists. */
    QAPI_LOCATION_ERROR_ID_UNKNOWN,         /**< ID is unknown. */
    QAPI_LOCATION_ERROR_ALREADY_STARTED,    /**< Already started. */
    QAPI_LOCATION_ERROR_NOT_INITIALIZED,    /**< Not initialized. */
    QAPI_LOCATION_ERROR_GEOFENCES_AT_MAX,   /**< Maximum number of geofences reached. */
    QAPI_LOCATION_ERROR_NOT_SUPPORTED       /**< Not supported. */
} qapi_Location_Error_t;

typedef uint16_t qapi_Location_Flags_Mask_t;
/**
 * Flags to indicate which values are valid in a location.
 */
typedef enum {
    QAPI_LOCATION_HAS_LAT_LONG_BIT =          (1 << 0),   /**< Location has a valid latitude and longitude. */
    QAPI_LOCATION_HAS_ALTITUDE_BIT =          (1 << 1),   /**< Location has a valid altitude. */
    QAPI_LOCATION_HAS_SPEED_BIT =             (1 << 2),   /**< Location has a valid speed. */
    QAPI_LOCATION_HAS_BEARING_BIT =           (1 << 3),   /**< Location has a valid bearing. */
    QAPI_LOCATION_HAS_ACCURACY_BIT =          (1 << 4),   /**< Location has valid accuracy. */
    QAPI_LOCATION_HAS_VERTICAL_ACCURACY_BIT = (1 << 5),   /**< Location has valid vertical accuracy. */
    QAPI_LOCATION_HAS_SPEED_ACCURACY_BIT =    (1 << 6),   /**< Location has valid speed accuracy. */
    QAPI_LOCATION_HAS_BEARING_ACCURACY_BIT =  (1 << 7),   /**< Location has valid bearing accuracy. */
} qapi_Location_Flags_t;

 /**
 * Flags to indicate Geofence breach status.
 */
typedef enum {
    QAPI_GEOFENCE_BREACH_ENTER = 0, /**< Entering Geofence breach. */
    QAPI_GEOFENCE_BREACH_EXIT,      /**< Exiting Geofence breach. */
    QAPI_GEOFENCE_BREACH_DWELL_IN,  /**< Dwelling in a breached Geofence. */
    QAPI_GEOFENCE_BREACH_DWELL_OUT, /**< Dwelling outside of a breached Geofence. */
    QAPI_GEOFENCE_BREACH_UNKNOWN,   /**< Breach is unknown. */
} qapi_Geofence_Breach_t;

typedef uint16_t qapi_Geofence_Breach_Mask_t;
/** Flags to indicate Geofence breach mask bit. */
typedef enum {
    QAPI_GEOFENCE_BREACH_ENTER_BIT =     (1 << 0),   /**< Breach enter bit. */
    QAPI_GEOFENCE_BREACH_EXIT_BIT =      (1 << 1),   /**< Breach exit bit. */
    QAPI_GEOFENCE_BREACH_DWELL_IN_BIT =  (1 << 2),   /**< Breach dwell in bit. */
    QAPI_GEOFENCE_BREACH_DWELL_OUT_BIT = (1 << 3),   /**< Breach dwell out bit. */
} qapi_Geofence_Breach_Mask_Bits_t;

typedef uint32_t qapi_Location_Capabilities_Mask_t;
/** Flags to indicate the capabilities bit. */
typedef enum {
    QAPI_LOCATION_CAPABILITIES_TIME_BASED_TRACKING_BIT =     (1 << 0),  /**< Capabilities time-based tracking bit. */
    QAPI_LOCATION_CAPABILITIES_TIME_BASED_BATCHING_BIT =     (1 << 1),  /**< Capabilities time-based batching bit. */
    QAPI_LOCATION_CAPABILITIES_DISTANCE_BASED_TRACKING_BIT = (1 << 2),  /**< Capabilities distance-based tracking bit. */
    QAPI_LOCATION_CAPABILITIES_DISTANCE_BASED_BATCHING_BIT = (1 << 3),  /**< Capabilities distance-based batching bit. */
    QAPI_LOCATION_CAPABILITIES_GEOFENCE_BIT =                (1 << 4),  /**< Capabilities Geofence bit. @newpage */
} qapi_Location_Capabilities_Mask_Bits_t;

/** Structure for location information. */
typedef struct {
    size_t size;                        /**< Size. Set to the size of qapi_Location_t. */
    qapi_Location_Flags_Mask_t flags;   /**< Bitwise OR of qapi_Location_Flags_t. */
    uint64_t timestamp;                 /**< UTC timestamp for a location fix; milliseconds since Jan. 1, 1970. */
    double latitude;                    /**< Latitude in degrees. */
    double longitude;                   /**< Longitude in degrees. */
    double altitude;                    /**< Altitude in meters above the WGS 84 reference ellipsoid. */
    float speed;                        /**< Speed in meters per second. */
    float bearing;                      /**< Bearing in degrees; range: 0 to 360. */
    float accuracy;                     /**< Accuracy in meters. */
    float verticalAccuracy;             /**< Vertical accuracy in meters. */
    float speedAccuracy;                /**< Speed accuracy in meters/second. */
    float bearingAccuracy;              /**< Bearing accuracy in degrees (0 to 359.999). */
} qapi_Location_t;

/** Structure for location options. */
typedef struct {
    size_t size;          /**< Size. Set to the size of #qapi_Location_Options_t. */
    uint32_t minInterval; /**<  There are three different interpretations of this field, 
                                depending if minDistance is 0 or not:
                                1. Time-based tracking (minDistance = 0). minInterval is the minimum 
                                time interval in seconds that must elapse between final position reports.
                                2. Distance-based tracking (minDistance > 0). minInterval is the
                                maximum time period in seconds after the minimum distance
                                criteria has been met within which a location update must be provided. 
                                If set to 0, an ideal value will be assumed by the engine.
                                3. Batching. minInterval is the minimum time interval in seconds that 
                                must elapse between position reports.
                                */
    uint32_t minDistance; /**< Minimum distance in meters that must be traversed between position reports. 
                               Setting this interval to 0 will be a pure time-based tracking/batching.
                               */
} qapi_Location_Options_t;

/** Structure for Geofence options. */
typedef struct {
    size_t size;                                /**< Size. Set to the size of #qapi_Geofence_Option_t. */
    qapi_Geofence_Breach_Mask_t breachTypeMask; /**< Bitwise OR of #qapi_Geofence_Breach_Mask_Bits_t bits. */
    uint32_t responsiveness;                    /**< Specifies in milliseconds the user-defined rate of detection for a Geofence
                                                     breach. This may impact the time lag between the actual breach event and
                                                     when it is reported. The gap between the actual breach and the time it 
                                                     is reported depends on the user setting. The power implication is 
                                                     inversely proportional to the responsiveness value set by the user.
                                                     The higher the responsiveness value, the lower the power implications, 
                                                     and vice-versa. */
    uint32_t dwellTime;                         /**< Dwell time is the time in milliseconds a user spends in the Geofence before 
                                                     a dwell event is sent. */
} qapi_Geofence_Option_t;

/** Structure for Geofence information. */
typedef struct {
    size_t size;      /**< Size. Set to the size of #qapi_Geofence_Info_t. */
    double latitude;  /**< Latitude of the center of the Geofence in degrees. */
    double longitude; /**< Longitude of the center of the Geofence in degrees. */
    double radius;    /**< Radius of the Geofence in meters. */
} qapi_Geofence_Info_t;

/** Structure for Geofence breach notification. */
typedef struct {
    size_t size;                    /**< Size. Set to the size of #qapi_Geofence_Breach_Notification_t. */
    size_t count;                   /**< Number of IDs in the array. */
    uint32_t* ids;                  /**< Array of IDs that have been breached. */
    qapi_Location_t location;       /**< Location associated with a breach. */
    qapi_Geofence_Breach_t type;    /**< Type of breach. */
    uint64_t timestamp;             /**< Timestamp of the breach. */
} qapi_Geofence_Breach_Notification_t;

/* GNSS Location Callbacks */

/**
* @brief Provides the capabilities of the system.
         It is called once after qapi_Loc_Init() is called.

  @param[in] capabilitiesMask Bitwise OR of #qapi_Location_Capabilities_Mask_Bits_t.

  @return None.
*/
typedef void(*qapi_Capabilities_Callback)(
    qapi_Location_Capabilities_Mask_t capabilitiesMask
);

/**
* @brief Response callback, which is used by all tracking, batching and
         geofence APIs.
         It is called for every tracking, batching and geofence API.

  @param[in] err  #qapi_Location_Error_t associated with the request.
                  If this is not QAPI_LOCATION_ERROR_SUCCESS then id is not valid.
  @param[in] id   ID to be associated with the request.

  @return None.
*/
typedef void(*qapi_Response_Callback)(
    qapi_Location_Error_t err,
    uint32_t id
);

/**
* @brief Collective response callback is used by Geofence APIs.
         It is called for every Geofence API call.

  @param[in] count  Number of locations in arrays.
  @param[in] err    Array of #qapi_Location_Error_t associated with the request.
  @param[in] ids    Array of IDs to be associated with the request.

  @return None.
*/
typedef void(*qapi_Collective_Response_Callback)(
    size_t count,
    qapi_Location_Error_t* err,
    uint32_t* ids
);

/**
* @brief Tracking callback used for the qapi_Loc_Start_Tracking() API.
         This is an optional function and can be NULL.
         It is called when delivering a location in a tracking session.

  @param[in] location  Structure containing information related to the 
                       tracked location.

  @return None.
*/
typedef void(*qapi_Tracking_Callback)(
    qapi_Location_t location
);

/**
* @brief Batching callback used for the qapi_Loc_Start_Batching() API.
         This is an optional function and can be NULL.
         It is called when delivering a location in a batching session.

  @param[in] count     Number of locations in an array.
  @param[in] location  Array of location structures containing information
                       related to the batched locations.

  @return None.
*/
typedef void(*qapi_Batching_Callback)(
    size_t count,
    qapi_Location_t* location
);

/**
* @brief Geofence breach callback used for the qapi_Loc_Add_Geofences() API.
         This is an optional function and can be NULL.
         It is called when any number of geofences have a state change.

  @param[in] geofenceBreachNotification     Breach notification information.

  @return None.
*/
typedef void(*qapi_Geofence_Breach_Callback)(
    qapi_Geofence_Breach_Notification_t geofenceBreachNotification
);

/** Location callbacks requirements. */
typedef struct {
    size_t size;
    /**< Size. Set to the size of #qapi_Location_Callbacks_t. */
    qapi_Capabilities_Callback      capabilitiesCb;
    /**< Capabilities callback is mandatory. */
    qapi_Response_Callback          responseCb;
    /**< Response callback is mandatory. */
    qapi_Collective_Response_Callback collectiveResponseCb;
    /**< Geofence response callback is mandatory. */
    qapi_Tracking_Callback          trackingCb;
    /**< Tracking callback is optional. */
    qapi_Batching_Callback          batchingCb;
    /**< Batching callback is optional. */
    qapi_Geofence_Breach_Callback   geofenceBreachCb;
    /**< Geofence breach callback is optional. */
} qapi_Location_Callbacks_t;

/** Location client identifier. */
typedef uint32_t qapi_loc_client_id;

#ifdef  QAPI_TXM_MODULE     // USER_MODE_DEFS

#define qapi_Loc_Init(a, b)                            ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_INIT                     , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Loc_Deinit(a)                             ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_DEINIT                   , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Loc_Start_Tracking(a, b, c)               ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_START_TRACKING           , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Loc_Stop_Tracking(a, b)                   ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_STOP_TRACKING            , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Loc_Update_Tracking_Options(a, b, c)      ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_UPDATE_TRACKING_OPTIONS  , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Loc_Start_Batching(a, b, c)               ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_START_BATCHING           , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Loc_Stop_Batching(a, b)                   ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_STOP_BATCHING            , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Loc_Update_Batching_Options(a, b, c)      ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_UPDATE_BATCHING_OPTIONS  , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Loc_Get_Batched_Locations(a, b, c)        ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_GET_BATCHED_LOCATIONS    , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Loc_Add_Geofences(a, b, c, d, e)          ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_ADD_GEOFENCES            , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) e, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Loc_Remove_Geofences(a, b, c)             ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_REMOVE_GEOFENCES         , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Loc_Modify_Geofences(a, b, c, d)          ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_MODIFY_GEOFENCES         , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Loc_Pause_Geofences(a, b, c)              ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_PAUSE_GEOFENCES          , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Loc_Resume_Geofences(a, b, c)             ((UINT) (_txm_module_system_call12)(TXM_QAPI_LOCATION_RESUME_GEOFENCES         , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#else // QAPI_TXM_MODULE

UINT qapi_location_handler(UINT id, UINT a1, UINT a2, UINT a3, UINT a4, UINT a5, UINT a6, UINT a7, UINT a8, UINT a9, UINT a10, UINT a11, UINT a12);

/**
* @brief Initializes a location session and registers the callbacks.

  @param[out] pClientId  Pointer to client ID type, where the unique identifier
                         for this location client is returned.
  @param[in] pCallbacks  Pointer to the structure with the callback
                         functions to be registered.

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_CALLBACK_MISSING -- One of the mandatory
            callback functions is missing. \n
  QAPI_LOCATION_ERROR_GENERAL_FAILURE -- There is an internal error. \n
  QAPI_LOCATION_ERROR_ALREADY_STARTED -- A location session has
            already been initialized.
*/
qapi_Location_Error_t qapi_Loc_Init(
        qapi_loc_client_id* pClientId,
        const qapi_Location_Callbacks_t* pCallbacks);

/**
* @brief De-initializes a location session.

  @param[in] clientId  Client identifier for the location client to be
                       deinitialized.

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_NOT_INITIALIZED -- No location session has
            been initialized.
*/
qapi_Location_Error_t qapi_Loc_Deinit(
        qapi_loc_client_id clientId);

/**
* @brief Starts a tracking session, which returns a 
         session ID that will be used by the other tracking APIs and in 
         the response callback to match the command with a response. Locations are 
         reported on the tracking callback passed in qapi_Loc_Init() periodically
         according to the location options.

  @param[in] clientId     Client identifier for the location client.
  @param[in] pOptions     Pointer to a structure containing the options: 
                          - minInterval -- There are two different interpretations of this field, 
                                depending if minDistance is 0 or not:
                                1. Time-based tracking (minDistance = 0). minInterval is the minimum 
                                time interval in seconds that must elapse between final position reports.
                                2. Distance-based tracking (minDistance > 0). minInterval is the
                                maximum time period in seconds after the minimum distance
                                criteria has been met within which a location update must be provided. 
                                If set to 0, an ideal value will be assumed by the engine.
                          - minDistance -- Minimum distance in meters that must be traversed between position 
                                reports. Setting this interval to 0 will be a pure time-based tracking.
  @param[out] pSessionId   Pointer to the session ID to be returned.

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_NOT_INITIALIZED -- No location session has
            been initialized.
*/
qapi_Location_Error_t qapi_Loc_Start_Tracking(
        qapi_loc_client_id clientId,
        const qapi_Location_Options_t* pOptions,
        uint32_t* pSessionId);

/**
* @brief Stops a tracking session associated with the id 
         parameter

  @param[in] clientId   Client identifier for the location client.
  @param[in] sessionId  ID of the session to be stopped.

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_NOT_INITIALIZED -- No location session has
            been initialized.
*/
qapi_Location_Error_t qapi_Loc_Stop_Tracking(
        qapi_loc_client_id clientId,
        uint32_t sessionId);

/**
* @brief Changes the location options of a 
         tracking session associated with the id parameter.

  @param[in] clientId   Client identifier for the location client.
  @param[in] sessionId  ID of the session to be changed.
  @param[in] pOptions   Pointer to a structure containing the options:
                          - minInterval -- There are two different interpretations of this field, 
                                depending if minDistance is 0 or not:
                                1. Time-based tracking (minDistance = 0). minInterval is the minimum 
                                time interval in milliseconds that must elapse between final position reports.
                                2. Distance-based tracking (minDistance > 0). minInterval is the
                                maximum time period in milliseconds after the minimum distance
                                criteria has been met within which a location update must be provided. 
                                If set to 0, an ideal value will be assumed by the engine.
                          - minDistance -- Minimum distance in meters that must be traversed between position 
                                reports. Setting this interval to 0 will be a pure time-based tracking.@tablebulletend

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_NOT_INITIALIZED -- No location session has
            been initialized.
*/
qapi_Location_Error_t qapi_Loc_Update_Tracking_Options(
        qapi_loc_client_id clientId,
        uint32_t sessionId,
        const qapi_Location_Options_t* pOptions);

/**
* @brief Starts a batching session, which returns a 
         session ID that will be used by the other batching APIs and in 
         the response callback to match the command with a response.
         
         Locations are 
         reported on the batching callback passed in qapi_Loc_Init() periodically
         according to the location options. A batching session starts tracking on
         the low power processor and delivers them in batches by the 
         batching callback when the batch is full or when qapi_Loc_Get_Batched_Locations() 
         is called. This allows for the processor that calls this API to sleep 
         when the low power processor can batch locations in the background and 
         wake up the processor calling the API only when the batch is full, 
         thus saving power.

  @param[in] clientId    Client identifier for the location client.
  @param[in] pOptions    Pointer to a structure containing the options:
                          - minInterval -- minInterval is the minimum time interval in milliseconds that 
                                must elapse between position reports.
                          - minDistance -- Minimum distance in meters that must be traversed between 
                                position reports.@tablebulletend
  @param[out] pSessionId  Pointer to the session ID to be returned.

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_NOT_INITIALIZED -- No location session has
            been initialized.
*/
qapi_Location_Error_t qapi_Loc_Start_Batching(
        qapi_loc_client_id clientId,
        const qapi_Location_Options_t* pOptions,
        uint32_t* pSessionId);

/**
* @brief Stops a batching session associated with the id
         parameter.

  @param[in] clientId   Client identifier for the location client.
  @param[in] sessionId  ID of the session to be stopped.

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_NOT_INITIALIZED -- No location session has
            been initialized.
*/
qapi_Location_Error_t qapi_Loc_Stop_Batching(
        qapi_loc_client_id clientId,
        uint32_t sessionId);

/**
* @brief Changes the location options of a 
         batching session associated with the id parameter.

  @param[in] clientId   Client identifier for the location client.
  @param[in] sessionId  ID of the session to be changed.
  @param[in] pOptions   Pointer to a structure containing the options:
                          - minInterval -- minInterval is the minimum time interval in milliseconds that 
                                must elapse between position reports.
                          - minDistance -- Minimum distance in meters that must be traversed between 
                                position reports.@tablebulletend

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_NOT_INITIALIZED -- No location session has
            been initialized.
*/
qapi_Location_Error_t qapi_Loc_Update_Batching_Options(
        qapi_loc_client_id clientId,
        uint32_t sessionId,
        const qapi_Location_Options_t* pOptions);

/**
* @brief Gets a number of locations that are 
         currently stored or batched on the low power processor, delivered by 
         the batching callback passed to qapi_Loc_Init(). Locations are then 
         deleted from the batch stored on the low power processor.

  @param[in] clientId   Client identifier for the location client.
  @param[in] sessionId  ID of the session for which the number of locations is requested.
  @param[in] count      Number of requested locations. The client can set this to 
                        MAXINT to get all the batched locations. If set to 0 no location
                        will be present in the callback function.

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_NOT_INITIALIZED -- No location session has
            been initialized.
*/
qapi_Location_Error_t qapi_Loc_Get_Batched_Locations(
        qapi_loc_client_id clientId,
        uint32_t sessionId,
        size_t count);

/**
* @brief Adds a specified number of Geofences and returns an 
         array of Geofence IDs that will be used by the other Geofence APIs, 
         as well as in the Geofence response callback to match the command with 
         a response. The Geofence breach callback delivers the status of each
         Geofence according to the Geofence options for each.

  @param[in] clientId  Client identifier for the location client.
  @param[in] count     Number of Geofences to be added.
  @param[in] pOptions  Array of structures containing the options:
                       - breachTypeMask -- Bitwise OR of GeofenceBreachTypeMask bits
                       - responsiveness in milliseconds
                       - dwellTime in seconds
  @param[in] pInfo     Array of structures containing the data:
                       - Latitude of the center of the Geofence in degrees 
                       - Longitude of the center of the Geofence in degrees
                       - Radius of the Geofence in meters
  @param[out] pIdArray  Array of IDs of Geofences to be returned.

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_NOT_INITIALIZED -- No location session has
            been initialized.
*/
qapi_Location_Error_t qapi_Loc_Add_Geofences(
        qapi_loc_client_id clientId,
        size_t count,
        const qapi_Geofence_Option_t* pOptions,
        const qapi_Geofence_Info_t* pInfo,
        uint32_t** pIdArray);

/**
* @brief Removes a specified number of Geofences.

  @param[in] clientId  Client identifier for the location client.
  @param[in] count     Number of Geofences to be removed.
  @param[in] pIDs      Array of IDs of the Geofences to be removed.

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_NOT_INITIALIZED -- No location session has
            been initialized.
*/
qapi_Location_Error_t qapi_Loc_Remove_Geofences(
        qapi_loc_client_id clientId,
        size_t count,
        const uint32_t* pIDs);

/**
* @brief Modifies a specified number of Geofences.

  @param[in] clientId  Client identifier for the location client.
  @param[in] count     Number of Geofences to be modified.
  @param[in] pIDs      Array of IDs of the Geofences to be modified.
  @param[in] options  Array of structures containing the options:
                       - breachTypeMask -- Bitwise OR of GeofenceBreachTypeMask bits
                       - responsiveness in milliseconds
                       - dwellTime in seconds @tablebulletend

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_NOT_INITIALIZED -- No location session has
            been initialized.
*/
qapi_Location_Error_t qapi_Loc_Modify_Geofences(
        qapi_loc_client_id clientId,
        size_t count,
        const uint32_t* pIDs,
        const qapi_Geofence_Option_t* options);

/**
* @brief Pauses a specified number of Geofences, which is 
         similar to qapi_Loc_Remove_Geofences() except that they can be resumed 
         at any time.

  @param[in] clientId  Client identifier for the location client.
  @param[in] count     Number of Geofences to be paused.
  @param[in] pIDs      Array of IDs of the Geofences to be paused.

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_NOT_INITIALIZED -- No location session has
            been initialized.
*/
qapi_Location_Error_t qapi_Loc_Pause_Geofences(
        qapi_loc_client_id clientId,
        size_t count,
        const uint32_t* pIDs);

/**
* @brief Resumes a specified number of Geofences that are 
         paused.

  @param[in] clientId  Client identifier for the location client.
  @param[in] count     Number of Geofences to be resumed.
  @param[in] pIDs      Array of IDs of the Geofences to be resumed.

  @return
  QAPI_LOCATION_ERROR_SUCCESS -- The operation was successful. \n
  QAPI_LOCATION_ERROR_NOT_INITIALIZED -- No location session has
            been initialized.
*/
qapi_Location_Error_t qapi_Loc_Resume_Geofences(
        qapi_loc_client_id clientId,
        size_t count,
        const uint32_t* pIDs);

#endif // QAPI_TXM_MODULE

/** @} */ /* end_addtogroup qapi_location */

#ifdef __cplusplus
}
#endif

#endif /* _QAPI_LOCATION_H_ */
