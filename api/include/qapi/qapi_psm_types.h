/***********************************************************************
 * qapi_psm_types.h
 *
 * Copyright (C) 2017 QUALCOMM Technologies, Inc.
 *
 * Type definitions for PSM Client QAPIs.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2017-03-17   rkr    Create.

===========================================================================*/


#ifndef QAPI_PSM_TYPES_H
#define QAPI_PSM_TYPES_H

#include "qapi_status.h"


/*==============================================================================
                              MACROS
=============================================================================*/


/**=============================================================================
                                   ENUMS
=============================================================================*/

/** @addtogroup psm_enums
    @{
  */

typedef enum {
    PSM_STATUS_NONE,
    PSM_STATUS_REJECT,            /**< PSM enter request is rejected */
    PSM_STATUS_READY,             /**< Ready to enter into PSM mode. */
    PSM_STATUS_NOT_READY,         /**< Not ready to enter PSM. */
    PSM_STATUS_COMPLETE,          /**< Entered into PSM mode, system might shutdown any time. */
    PSM_STATUS_DISCONNECTED,      /**< PSM Server is down. */
    PSM_STATUS_MODEM_LOADED,      /**< Modem is loaded as part of boot up. */
    PSM_STATUS_MODEM_NOT_LOADED,  /**< Modem is not loaded as part of boot up.*/
    PSM_STATUS_NW_OOS,            /** < Network is OOS. */
    PSM_STATUS_NW_LIMITED_SERVICE,/**< Network is Limited Service. */
    PSM_STATUS_HEALTH_CHECK,      /**< Application health check.*/
    PSM_STATUS_FEATURE_ENABLED,   /**< Feature is dynamically enabled.*/
    PSM_STATUS_FEATURE_DISABLED,  /**< Feature is dynamically disabled.*/
    PSM_STATUS_MAX
} psm_status_type_e;

/**
    @}
  */

/** @addtogroup psm_enums
    @{
  */
typedef enum {
    PSM_REJECT_REASON_NONE,                /**< Reject reason None.*/
    PSM_REJECT_REASON_NOT_ENABLED,         /**< PSM feature is not enabled. */
    PSM_REJECT_REASON_MODEM_NOT_READY,     /**< Modem is not ready to enter into PSM mode.*/
    PSM_REJECT_REASON_DURATION_TOO_SHORT,  /**< PSM duration is too short to enter into PSM mode.*/
    PSM_REJECT_REASON_MAX
} psm_reject_reason_type_e;

/**
    @}
  */

/** @addtogroup psm_enums
    @{
  */
typedef enum {
    PSM_ERR_NONE,                  /**< Success. */
    PSM_ERR_FAIL,                  /**< Failure.*/
    PSM_ERR_GENERIC_FAILURE,       /**< Miscellaneous failure.*/
    PSM_ERR_APP_NOT_REGISTERED,    /**< Application is not registered with PSM Server.*/
    PSM_ERR_WRONG_ARGUMENTS,       /**< Wrong input arguments.*/
    PSM_ERR_IPC_FAILURE,           /**< Failure to communicate with PSM server.*/
} psm_error_type_e;
/**
    @}
  */

/** @addtogroup psm_enums
    @{
  */

typedef enum {
    PSM_TIME_IN_TM,        /**< Specify time in broken down format.*/
    PSM_TIME_IN_SECS       /**< Specify time in seconds.*/
} psm_time_format_type_e;

/**
    @}
  */

/** @addtogroup psm_enums
    @{
  */

typedef enum {
    PSM_WAKEUP_MEASUREMENT_ONLY,        /**< Next wake up from PSM is for measurement purpose only.*/
    PSM_WAKEUP_MEASUREMENT_NW_ACCESS    /**< Next wake up from PSM is for measurement and network access.*/
} psm_wakeup_type_e;

/**
    @}
  */

 /**============================================================================
                                  STRUCTURES
============================================================================*/

/** @addtogroup psm_aggregates
    @{
  */
typedef struct {
    psm_time_format_type_e  time_format_flag;       /**< Time format. see #psm_time_format_type. */
    pm_rtc_julian_type      wakeup_time;            /**< Time in broken down format if time_format_flag is set to PSM_TIME_IN_TM */
    int                     psm_duration_in_secs;   /**< Time in seconds if if time_format_flag is set to PSM_TIME_IN_SECS.*/
}psm_time_info_type;

/**
    @}
  */


/** @addtogroup psm_aggregates
    @{
  */

typedef struct {
    int                 active_time_in_secs;  /**< Active time is the duration PSM server has to wait before entering
    into PSM mode. Purpose of this time is to give chance for MTC server to react.*/
    psm_wakeup_type_e   psm_wakeup_type;      /**< Next wake up from PSM mode is for
    measurement purpose or measurement and network access. */
    psm_time_info_type  psm_time_info;        /**< PSM time information. see #psm_time_info_type.*/
}psm_info_type;


/**
    @}
  */

/** @addtogroup psm_aggregates
    @{
  */

typedef struct  {
    int   client_id; /**< Client id. */
    int   status;    /**< PSM status. see #psm_status_type_e. */
    int   reason;    /**< PSM reject reason. see #psm_reject_reason_type_e.*/
}psm_status_msg_type;

/**
    @}
  */
    





/**======================================================================
                          TYPEDEFS
 ======================================================================*/

/* PSM status call back type.*/
typedef void (*psm_client_cb_type)(psm_status_msg_type *);

/* PSM timer expiry call back type.*/
typedef void (*psm_util_timer_expiry_cb_type)(void *, size_t);

typedef int32_t qapi_PSM_Status_t;

#endif /** QAPI_PSM_TYPES_H*/

