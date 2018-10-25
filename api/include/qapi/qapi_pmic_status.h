/**
 * @file qapi_pmic_status.h
 *
 * @brief Error codes define for PMIC module.
 */
/*
 * Copyright (C) 2017 QUALCOMM Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when         who   what, where, why
----------   ---   ---------------------------------------------------------
12/20/17     kcs     Created a new QAPI error code for Batt absent (CR-2138435).
07/11/17     kcs     Create.
===========================================================================*/


#ifndef QAPI_PMIC_STATUS_H
#define QAPI_PMIC_STATUS_H

#include "qapi_txm_base.h"
#include "qapi_status.h"

/*==============================================================================
                              MACROS
=============================================================================*/                                   
 
/* Error Macros defined for QAPI errors */
 
#define ___QAPI_ERROR_PMIC(x)  ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BSP_PMIC,  x)))

/* For battery absent */
#define QAPI_ERR_BATT_ABSENT              ___QAPI_ERROR_PMIC(1)

/** @} */ /* end of qapi_pmic_status header file */
#endif /** QAPI_PMIC_STATUS_H*/
