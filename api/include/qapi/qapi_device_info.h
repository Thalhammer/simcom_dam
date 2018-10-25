/**
  @file qapi_device_info.h

 EXTERNALIZED FUNCTIONS
  none

 INITIALIZATION AND SEQUENCING REQUIREMENTS
  none
*/

/*
 Copyright (c) 2017  Qualcomm Technologies, Inc.  All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
 ======================================================================*/
/*======================================================================
 *
 *        EDIT HISTORY FOR FILE
 *
 *	 This section contains comments describing changes made to the
 *	 module. Notice that changes are listed in reverse chronological
 *	 order.
 *
 *	
 *
 *
 * when 		who 	what, where, why
 * ---------- 	---   ------------------------------------------------
 * 2017-04-25   leo   (Tech Comm) Edited/added Doxygen comments and markup.
 ======================================================================*/
 
#ifndef _QAPI_DEVICE_INFO_H
#define _QAPI_DEVICE_INFO_H

#include "qapi/qapi_data_txm_base.h"
#include "qapi/qapi_status.h"
#include <stdbool.h>

#define  TXM_QAPI_DEVICE_INFO_INIT               TXM_QAPI_DEVICE_INFO_BASE + 1
#define  TXM_QAPI_DEVICE_INFO_GET                TXM_QAPI_DEVICE_INFO_BASE + 2
#define  TXM_QAPI_DEVICE_INFO_RELEASE            TXM_QAPI_DEVICE_INFO_BASE + 3
#define  TXM_QAPI_DEVICE_INFO_SET_CB             TXM_QAPI_DEVICE_INFO_BASE + 4
#define  TXM_QAPI_DEVICE_INFO_RESET              TXM_QAPI_DEVICE_INFO_BASE + 5

/** @addtogroup qapi_device_info
@{ */

/** Device information types. */
typedef enum {

 QAPI_DEVICE_INFO_BUILD_ID_E,
 /**< Device BUILD_ID. */
 QAPI_DEVICE_INFO_IMEI_E,
 /**< Device IMEI. */
 QAPI_DEVICE_INFO_IMSI_E,
 /**< UIM IMSI. */
 QAPI_DEVICE_INFO_OS_VERSION_E,
 /**< Device OS version. */
 QAPI_DEVICE_INFO_MANUFACTURER_E,
 /**< Device manufacturer. */
 QAPI_DEVICE_INFO_MODEL_ID_E,
 /**< Device model ID. */
 QAPI_DEVICE_INFO_BATTERY_STATUS_E,
 /**< Device battery status. */
 QAPI_DEVICE_INFO_BATTERY_PERCENTAGE_E,
 /**< Device battery percentage. */
 QAPI_DEIVCE_INFO_TIME_ZONE_E,
 /**< Device time zone. */
 QAPI_DEIVCE_INFO_ICCID_E,
 /**< Device ICCID. */
 QAPI_DEVICE_INFO_4G_SIG_STRENGTH_E,
 /**< Network signal strength. */
 QAPI_DEVICE_INFO_BASE_STATION_ID_E,
 /**< Network base station ID. */
 QAPI_DEVICE_INFO_MCC_E,
 /**< Network MCC. */
 QAPI_DEVICE_INFO_MNC_E,
 /**< Network MNC. */
 QAPI_DEVICE_INFO_SERVICE_STATE_E,
 /**< Network service status. */
 QAPI_DEVICE_INFO_MDN_E,
 /**< Deivce MDN. */
 QAPI_DEVICE_INFO_TAC_E,
 /**< Network tracking area code. */
 QAPI_DEVICE_INFO_CELL_ID_E,
 /**< Network cell ID. */
 QAPI_DEVICE_INFO_RCCS_E,
 /**< Network RRC state. */
 QAPI_DEVICE_INFO_EMMS_E,
 /**< Network EMM state. */
 DEPRACATED1,
 /** <Info to keep numbering of enum same> */
 QAPI_DEVICE_INFO_SERVING_PCI_E,
 /**< Network serving cell PCI. */
 QAPI_DEVICE_INFO_SERVING_RSRQ_E,
 /**< Serving cell RSRQ. */
 QAPI_DEVICE_INFO_SERVING_EARFCN_E,
 /**< Serving cell EARFCN. */
 DEPRACATED2,
 /** <Info to keep numbering of enum same> */
 DEPRACATED3,
 /** <Info to keep numbering of enum same> */
 DEPRACATED4,
 /** <Info to keep numbering of enum same> */
 DEPRACATED5,
 /** <Info to keep numbering of enum same> */
 DEPRACATED6,
 /** <Info to keep numbering of enum same> */
 QAPI_DEVICE_INFO_NETWORK_IND_E,
 /**< Network indication */
 QAPI_DEVICE_INFO_ROAMING_E,
 /**< Roaming status. */
 QAPI_DEVICE_INFO_LAST_POWER_ON_E,
 /**< Last power on time. */
 QAPI_DEVICE_INFO_CHIPID_STRING_E,
 /**< Chipset name. */
 QAPI_DEVICE_INFO_APN_PROFILE_INDEX_E,
  /** < APN Profile Index > */
 QAPI_DEVICE_INFO_SIM_STATE_E
 /** < SIM State */
} qapi_Device_Info_ID_t;

/** Device information response types. */
typedef enum {
 QAPI_DEVICE_INFO_TYPE_BOOLEAN_E,
 /**< Response type is Boolean. */
 QAPI_DEVICE_INFO_TYPE_INTEGER_E,
 /**< Response type is integer. */
 QAPI_DEVICE_INFO_TYPE_BUFFER_E,
 /**< Response type is buffer. */
} qapi_Device_Info_Type_t;

/*========================================================
 * Device Info structure                               *
 ========================================================*/

/** Maximum size of #qapi_Device_Info_t valuebuf. */
#define QAPI_DEVICE_INFO_BUF_SIZE 128

/**
 @brief QAPI device information structure.
*/
typedef struct {
  qapi_Device_Info_ID_t id; /**< Required information ID. */
  qapi_Device_Info_Type_t info_type; /**< Response type. */
  union {
    struct {
      char buf[QAPI_DEVICE_INFO_BUF_SIZE]; /**< Response buffer. */
      uint32_t len; /**< Length of the response string. @newpagetable */
    }valuebuf;    /**< Union of buffer values. */
    int valueint; /**< Response integer value. */
    bool valuebool; /**< Response Boolean value.*/
  }u;
}qapi_Device_Info_t;

#ifdef  QAPI_TXM_MODULE

#define qapi_Device_Info_Init()                 ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_DEVICE_INFO_INIT,    (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Device_Info_Get(a, b)              ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_DEVICE_INFO_GET,     (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Device_Info_Release()              ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_DEVICE_INFO_RELEASE, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Device_Info_Set_Callback(a, b)     ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_DEVICE_INFO_SET_CB,  (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Device_Info_Reset()                  ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_DEVICE_INFO_RESET,   (ULONG)0, (ULONG)0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#else

UINT qapi_Device_Info_Handler(UINT id, UINT a, UINT b, UINT c, UINT d, UINT e, UINT f, UINT g, UINT h, UINT i, UINT j, UINT k, UINT l);

/*====================================================
 * QAPI Device Info Callback                         *
 ====================================================*/
typedef void (*qapi_Device_Info_Callback_t)(const qapi_Device_Info_t *info);

/*=======================================================
 * QAPI Device Info APIs                             *
 =======================================================*/

/**
 * @brief Initializes the device information context.
 *
 * This function must be called before invoking other qapi_Device_Info APIs.
 *
 * @return QAPI_OK on success, QAPI_ERROR on failure.
 */
qapi_Status_t qapi_Device_Info_Init(void);

/**
 * @brief Gets the device information for specified ID.
 *
 * @param[in] id     Information ID.
 * @param[out] info  Information received for the specified ID.
 *
 * @return QAPI_OK on success, QAPI_ERROR on failure.
 *
 * @dependencies
 * Before calling this API, qapi_Device_Info_Init() must have been called.
 */
qapi_Status_t qapi_Device_Info_Get(qapi_Device_Info_ID_t id, qapi_Device_Info_t *info);

/**
 * @brief Sets a device information callback.
 *
 * @param[in] id        Information ID.
 * @param[in] callback  Callback to be registered.
 *
 * @return QAPI_OK on success, QAPI_ERROR on failure.
 *
 * @dependencies
 * Before calling this API, qapi_Device_Info_Init() must have been called.
 */
qapi_Status_t qapi_Device_Info_Set_Callback(qapi_Device_Info_ID_t id, qapi_Device_Info_Callback_t callback);

/**
 * @brief Releases the device information context.
 *
 * @return QAPI_OK on success, QAPI_ERROR on failure.
 *
 * @dependencies
 * Before calling this API, qapi_Device_Info_Init() must have been called.
 */
qapi_Status_t qapi_Device_Info_Release(void);

/**
 * @brief Resets the device.
 *
 * @return QAPI_OK on success, QAPI_ERROR on failure.
 */
qapi_Status_t qapi_Device_Info_Reset(void);

#endif

/** @} */ /* end_addtogroup qapi_device_info */

#endif
