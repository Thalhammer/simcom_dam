#ifndef QAPI_RIL_BASE_H
#define QAPI_RIL_BASE_H 

/**
  @file qapi_ril_base.h 
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
 * when       who     what, where, why
 * --------   ---     ----------------------------------------------------------
 * 17/03/17   rkr      Initial PSM QAPI

 ======================================================================*/
 

#ifdef __cplusplus
extern "C" {
#endif

#include "qapi_txm_base.h"
#include "qapi/qapi_status.h"
#include <stdint.h>
#include <stddef.h>

/*** Maximum IDs for RIL is defined by macro TXM_QAPI_RIL_NUM_IDS in base txm***/

#define  TXM_QAPI_PSM_BASE                        TXM_QAPI_RIL_BASE
#define  TXM_QAPI_PSM_NUM_IDS                     20

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif /* QAPI_RIL_BASE_H */
