
#ifndef __QAPI_PMAPP_VBATT_H__
#define __QAPI_PMAPP_VBATT_H__

/*===========================================================================
              QAPI P M   VBATT   A P P   H E A D E R   F I L E

===========================================================================*/
/**
 * @file qapi_pmapp_vbatt.h
 *
 * @addtogroup qapi_pmapp_vbatt
 * @{ 
 *
 * @brief 
 *
 * @details This module provides the definations to get the battery Status Information.
 * 
 *
 * @}
 *  
 */

/*===========================================================================
  Copyright (c) 2017 QUALCOMM Technologies, Inc.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 
============================================================================*/


/*=============================================================================
                            EDIT HISTORY FOR File

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header:

when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/29/17   kcs     created
=============================================================================*/

/* =========================================================================
                         INCLUDE FILES
========================================================================= */
#ifdef __cplusplus
extern "C" {
#endif


#include "qapi_pmic_status.h"
#include "qapi_txm_base.h"
#include "com_dtypes.h"

#define TXM_QAPI_PM_VBATT_BASE  TXM_QAPI_PMIC_BASE + 10

/* =========================================================================
                       USER_Mode_DEFS
========================================================================= */

// Driver ID defines
#define  TXM_QAPI_PMIC_VBATT_GET_BATTERY_STATUS      TXM_QAPI_PM_VBATT_BASE + 1


/* =========================================================================
                         TYPE DEFINITIONS
========================================================================= */

#ifdef  QAPI_TXM_MODULE

// API Definitions 
#define qapi_Pmapp_Vbatt_Get_Battery_Status(batt_stat)\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_PMIC_VBATT_GET_BATTERY_STATUS,\
    (ULONG) batt_stat,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

	
#elif defined QAPI_TXM_SOURCE_CODE
	

/*===========================================================================
                   KERNEL_Mode_DEFS
===========================================================================*/

/*===========================================================================
FUNCTION   qapi_Pmapp_Vbatt_Get_Battery_Status                            

DESCRIPTION
   This function is used for getting the battery percentage.

PARAMETERS
  uint8* batt_status - Buffer to get the battery percentage.

RETURN VALUE
   Type: qapi_Status_t
   - Possible values:
     - QAPI_OK                        -->  Operation succeeded
	 - QAPI_ERR_INVALID_PARAM         -->  Invalid Parameter
     - QAPI_ERR_NOT_SUPPORTED         -->  Feature_Not_Supported
	 - QAPI_ERROR					  -->  For Any Other Errors

===========================================================================*/
qapi_Status_t
qapi_Pmapp_Vbatt_Get_Battery_Status(uint8* batt_status);
/*~ FUNCTION qapi_Pmapp_Vbatt_Get_Battery_Status */

#else   // DEF_END

#error "No QAPI flags defined"

#endif
#ifdef __cplusplus
} /* closing brace for extern "C" */

#endif

#endif /* __QAPI_PMAPP_VBATT_H__  */
