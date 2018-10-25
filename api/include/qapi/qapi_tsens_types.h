/**
 * qapi_tsens_types.h
 *
 * Type definitions for Temperature Sensor QAPIs.
*/

/*
 *
 * Copyright (C) 2017 Qualcomm Technologies, Inc.
 * All rights reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2017-04-10   KS    QAPI changes.
2017-03-13   PC    Create.

===========================================================================*/


#ifndef QAPI_TSENS_TYPE_H
#define QAPI_TSENS_TYPE_H

#include "qapi_txm_base.h"
#include "qapi_status.h"

/*==============================================================================
                              MACROS
=============================================================================*/                                   
 
/* QAPI TSENS Macros */
 
/* Error macros defined for QAPI errors. */
#define ___QAPI_ERROR_TSENS(x)  ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BSP_TSENS,  x)))

/* TSENS hardware sensor is not calibrated. */
#define QAPI_ERR_INVALID_CALIB        ___QAPI_ERROR_TSENS(16)

/* TSENS sensor is not available. */
#define QAPI_ERR_DEAD_SENSOR          ___QAPI_ERROR_TSENS(17)

/* Unknown error. */
#define QAPI_ERR_UNKNOWN_TSENS        ___QAPI_ERROR_TSENS(21)



/*======================================================================
                          TYPEDEFS
 ======================================================================*/

/* Datatypes defined for QAPIs*/
typedef int32_t              qapi_Status_t;
typedef uint16_t             qapi_TSENS_Mode_t;

/*=============================================================================
                                   ENUMS
=============================================================================*/

/*============================================================================
                                  STRUCTURES
============================================================================*/

/** @addtogroup qapi_tsens_datatypes
@{ */

/** Enumeration of TSENS temperature thresholds. */
typedef enum
{
   QAPIS_TSENS_THRESHOLD_LOWER = 0,  /**< Lower threshold. */
   QAPIS_TSENS_THRESHOLD_UPPER,      /**< Upper threshold. */
   QAPIS_TSENS_NUM_THRESHOLDS        /**< Number of thresholds. */
} qapi_TSENS_ThresholdType_t;

/** TSENS callback payload type structure. */
typedef struct
{
   qapi_TSENS_ThresholdType_t eThreshold;  /**< Type of threshold that was triggered. */
   uint32_t uSensor;                       /**< Sensor that was triggered. */
   int32_t nTriggeredDegC;                 /**< Temperature value that was triggered. */
}  qapi_TSENS_CallbackPayloadType_t;

/** TSENS callback function type. */
typedef void (*QAPI_Tsens_Threshold_Cb_Type)
(
   void *pCtxt,
   const qapi_TSENS_CallbackPayloadType_t *pPayload
);

/** TSENS temperature result structure. */
typedef struct
{
   int32_t deg_c;      /**< Temperature in degrees Celsius. @newpagetable */
} qapi_TSENS_Result_t;

/** TSENS handler type. */
typedef void *qapi_TSENS_Handle_t;

/** @} */ /* end_addtogroup qapi_tsens_datatypes */
#endif /** QAPI_TSENS_TYPE_H*/
