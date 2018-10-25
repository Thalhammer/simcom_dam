#ifndef QAPI_TXM_BASE_H
#define QAPI_TXM_BASE_H 

/**
  @file qapi_txm_base.h 
  @brief  Contains QAPI/ThreadX modules Driver ID mappings

 EXTERNALIZED FUNCTIONS
  none

 INITIALIZATION AND SEQUENCING REQUIREMENTS
  none

 Copyright (c) 2017  by Qualcomm Technologies, Inc.  All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
 ======================================================================*/
/*======================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *  
 *
 *
 * when         who     what, where, why
 * ----------   ---     ------------------------------------------------
 * 2017-01-20   c_sbegum  Add Header file, with initial QAPI TXM defines
 ======================================================================*/
 

#ifdef __cplusplus
extern "C" {
#endif

#include "txm_module.h"

/* this is used when no extra arguments need to be passed through kernel dispatcher*/
#define QAPI_NULL_EXTRA_ARG	0x4E415247

#define  TXM_QAPI_ID_START                        TXM_APPLICATION_REQUEST_ID_BASE

#define  TXM_QAPI_ID_END                          TXM_QAPI_ID_START + TXM_QAPI_MAX_NUM_IDS

// *NOT TO BE CHANGED* or else it may impact system functionality
// API ID base and limit definitions for OEM APIs
#define  TXM_QC_OEM_API_BASE		TXM_APPLICATION_REQUEST_ID_BASE + 0x10000
#define  TXM_QC_OEM_API_MAX_IDS		0x10000
#define  TXM_QC_OEM_API_END			TXM_QC_OEM_API_BASE + TXM_QC_OEM_API_MAX_IDS
// OEM API ID base and limit definition ends

/*** DO NOT MODIFY anything above this line ***/

#define  TXM_QAPI_MAX_NUM_IDS                     (TXM_QAPI_LOCATION_NUM_IDS + \
                                                   TXM_QAPI_QCCI_NUM_IDS + \
                                                   TXM_QAPI_DIAG_NUM_IDS + \
                                                   TXM_QAPI_TIMERS_NUM_IDS + \
                                                   TXM_QAPI_FS_NUM_IDS + \
                                                   TXM_QAPI_TLMM_NUM_IDS + \
                                                   TXM_QAPI_GPIO_INT_NUM_IDS + \
                                                   TXM_QAPI_ADC_NUM_IDS + \
                                                   TXM_QAPI_TSENS_NUM_IDS + \
                                                   TXM_QAPI_DATA_SERVICES_NUM_IDS + \
                                                   TXM_QAPI_BUSES_NUM_IDS + \
                                                   TXM_QAPI_FTL_NUM_IDS + \
                                                   TXM_QAPI_USB_NUM_IDS + \
                                                   TXM_QAPI_RIL_NUM_IDS + \
                                                   TXM_QAPI_PMIC_NUM_IDS + \
                                                   TXM_QURT_TIMETICK_NUM_IDS)

#define  TXM_QAPI_LOCATION_BASE                   TXM_QAPI_ID_START
#define  TXM_QAPI_LOCATION_NUM_IDS                50

#define  TXM_QAPI_QCCI_BASE                       TXM_QAPI_LOCATION_BASE + TXM_QAPI_LOCATION_NUM_IDS
#define  TXM_QAPI_QCCI_NUM_IDS                    100

#define  TXM_QAPI_DIAG_BASE                       TXM_QAPI_QCCI_BASE + TXM_QAPI_QCCI_NUM_IDS
#define  TXM_QAPI_DIAG_NUM_IDS                    100

#define  TXM_QAPI_TIMERS_BASE                     TXM_QAPI_DIAG_BASE + TXM_QAPI_DIAG_NUM_IDS
#define  TXM_QAPI_TIMERS_NUM_IDS                  50

#define  TXM_QAPI_FS_BASE                         TXM_QAPI_TIMERS_BASE + TXM_QAPI_TIMERS_NUM_IDS
#define  TXM_QAPI_FS_NUM_IDS                      100

#define  TXM_QAPI_TLMM_BASE                       TXM_QAPI_FS_BASE + TXM_QAPI_FS_NUM_IDS
#define  TXM_QAPI_TLMM_NUM_IDS                    50

#define  TXM_QAPI_GPIO_INT_BASE                   TXM_QAPI_TLMM_BASE + TXM_QAPI_TLMM_NUM_IDS
#define  TXM_QAPI_GPIO_INT_NUM_IDS                50

#define  TXM_QAPI_ADC_BASE                        TXM_QAPI_GPIO_INT_BASE + TXM_QAPI_GPIO_INT_NUM_IDS
#define  TXM_QAPI_ADC_NUM_IDS                     50

#define  TXM_QAPI_TSENS_BASE                      TXM_QAPI_ADC_BASE + TXM_QAPI_ADC_NUM_IDS
#define  TXM_QAPI_TSENS_NUM_IDS                   50

#define  TXM_QAPI_DATA_SERVICES_BASE              TXM_QAPI_TSENS_BASE + TXM_QAPI_TSENS_NUM_IDS
#define  TXM_QAPI_DATA_SERVICES_NUM_IDS           300

#define  TXM_QAPI_BUSES_BASE                      TXM_QAPI_DATA_SERVICES_BASE + TXM_QAPI_DATA_SERVICES_NUM_IDS
#define  TXM_QAPI_BUSES_NUM_IDS                   100

#define  TXM_QAPI_FTL_BASE                        TXM_QAPI_BUSES_BASE + TXM_QAPI_BUSES_NUM_IDS
#define  TXM_QAPI_FTL_NUM_IDS                     25

#define  TXM_QAPI_USB_BASE                        TXM_QAPI_FTL_BASE + TXM_QAPI_FTL_NUM_IDS
#define  TXM_QAPI_USB_NUM_IDS                     25

#define  TXM_QAPI_RIL_BASE                        TXM_QAPI_USB_BASE + TXM_QAPI_USB_NUM_IDS
#define  TXM_QAPI_RIL_NUM_IDS                     50

#define  TXM_QAPI_PMIC_BASE                       TXM_QAPI_RIL_BASE + TXM_QAPI_RIL_NUM_IDS
#define  TXM_QAPI_PMIC_NUM_IDS                    25

#define  TXM_QURT_TIMETICK_BASE                   TXM_QAPI_PMIC_BASE + TXM_QAPI_PMIC_NUM_IDS
#define  TXM_QURT_TIMETICK_NUM_IDS                10

#define  TXM_QAPI_DAM_BASE                        TXM_QC_OEM_API_BASE
#define  TXM_QAPI_DAM_NUM_IDS                     50
#define  TXM_QAPI_IOT_BASE                        (TXM_QAPI_DAM_BASE+TXM_QAPI_DAM_NUM_IDS)                       
#define  TXM_QAPI_IOT_NUM_IDS                     100
#define  TXM_QAPI_IOT_HAL_BASE                    (TXM_QAPI_IOT_BASE +TXM_QAPI_IOT_NUM_IDS)
#define  TXM_QAPI_IOT_HAL_NUM_IDS                 100

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif /* QAPI_TXM_BASE_H */
