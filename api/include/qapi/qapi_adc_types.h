/**
 * @file qapi_adc_types.h
 *
 * @brief Type definitions for ADC QAPIs.
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
2017-04-05   KS    QAPI changes.
2017-03-13   PC    Create.
===========================================================================*/


#ifndef QAPI_ADC_TYPE_H
#define QAPI_ADC_TYPE_H

#include "qapi_txm_base.h"
#include "qapi_status.h"

/*==============================================================================
                              MACROS
=============================================================================*/                                   
 
/* Error Macros defined for QAPI errors */
 
#define ___QAPI_ERROR_ADC(x)  ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BSP_ADC,  x)))

/* Client specified an invalid device index. */
#define QAPI_ERR_INVALID_IDX              ___QAPI_ERROR_ADC(15)

/* Client specified an invalid channel index. */
#define QAPI_ERR_INVALID_CHANNEL_IDX     ___QAPI_ERROR_ADC(16)

/* Device request queue was full. */
#define QAPI_ERR_QUEUE_FULL              ___QAPI_ERROR_ADC(17)

/* There are no free TM client handles. */
#define QAPI_ERR_OUT_OF_TM_CLIENTS       ___QAPI_ERROR_ADC(18)

/* Requested threshold is out of range. */
#define QAPI_ERR_TM_THRESHOLD_OUT_OF_RANGE     ___QAPI_ERROR_ADC(19)

/* Busy monitoring a tolerance. */
#define QAPI_ERR_TM_BUSY                 ___QAPI_ERROR_ADC(20)

/* Unknown error. */
#define QAPI_ERR_UNKNOWN_ADC             ___QAPI_ERROR_ADC(21)

/** @addtogroup qapi_adc_datatypes
@{ */

/* The following macros are ADC channel names that should be passed as inputs
to qapi_ADC_Read_Channel().
*/
                                   
/** Physical units are in millivolts. */
#define ADC_INPUT_BATT_ID          "BATT_ID"

/** Physical units are in degrees C. */
#define ADC_INPUT_PA_THERM         "PA_THERM"

/** Physical units are in degrees C. */
#define ADC_INPUT_PA_THERM1        "PA_THERM1"

/** Physical units are in 0.001 gradients of degrees C. */
#define ADC_INPUT_PMIC_THERM       "PMIC_THERM"

/** Physical units are in millivolts. */
#define ADC_INPUT_VBATT            "VBATT"

/** Physical units are in millivolts. */
#define ADC_INPUT_VPH_PWR          "VPH_PWR"

/** Physical units are in 2^-10 degrees C. */
#define ADC_INPUT_XO_THERM           "XO_THERM"

/** Physical units are in 2^-10 degrees C. */
#define ADC_INPUT_XO_THERM_GPS       "XO_THERM_GPS"

#define ADC_INPUT_MPP6            "MPP6"   //SIMCOM zhangwei 2017-12-29 add external adc at ticket/25

#define ARRAY_LENGTH(a) (sizeof(a) / sizeof((a)[0]))

/*======================================================================
                          TYPEDEFS
 ======================================================================*/


/* Datatypes defined for QAPIs*/
typedef int32_t              qapi_Status_t;
typedef uint16_t             qapi_ADC_Mode_t;
typedef long long            qapi_ADC_Offset_t;

/*=============================================================================
                                   ENUMS
=============================================================================*/


 /*============================================================================
                                  STRUCTURES
============================================================================*/

/** ADC read results.
*/
typedef struct
{
   /*AdcResultStatusType*/unsigned int  eStatus;  /**< Status of the conversion. */
   uint32_t  nToken;       /**< Token that identifies the conversion. */
   uint32_t  nDeviceIdx;   /**< Device index for the conversion. */
   uint32_t  nChannelIdx;  /**< Channel index for the conversion. */
   int32_t   nPhysical;    /**< Result in physical units. Units depends on the BSP. */
   uint32_t  nPercent;     /**< Result as a percentage of the reference voltage used
                                for the conversion: 0 = 0%, 65535 = 100% */
   uint32_t  nMicrovolts;  /**< Result in microvolts. */
   uint32_t  nCode;        /**< Raw ADC code from the hardware. */
} qapi_ADC_Read_Result_t;

/** ADC input properties.
*/
typedef struct
{
   uint32_t  nDeviceIdx;   /**< Device index. */
   uint32_t  nChannelIdx;  /**< Channel index. */
} qapi_Adc_Input_Properties_Type_t;

/** ADC TM input properties.
*/
typedef struct
{
   uint32_t  nDeviceIdx;   /**< Device index. */
   uint32_t  nChannelIdx;  /**< Channel index. */
} qapi_AdcTM_Input_Properties_Type_t;



typedef void *qapi_ADC_Handle_t;


typedef struct AdcDevCtxt AdcHandleType;

/**
* ADC amplitude threshold types that can be configured to be
*          monitored using qapi_ADC_Set_Threshold().
*/
typedef enum
{
   QAPI_ADC_THRESHOLD_LOWER_E,   /**< Lower threshold. */
   QAPI_ADC_THRESHOLD_HIGHER_E,  /**< Higher threshold. */
   QAPI_ADC_THRESHOLD_INVALID_E = 0x7fffffff  /* Force enum to 32-bit */
} qapi_ADC_Amp_Threshold_t;


/**
* ADC range structure.
*/
typedef struct
{
   int32_t min_uv;  /**< Minimum value in microvolts. */
   int32_t max_uv;  /**< Maximum value in microvolts. */
} qapi_ADC_Range_t;

/**
* ADC amplitude threshold result structure.
*/
typedef struct
{
   uint32_t channel;                    /**< Channel that was triggered. */
   qapi_ADC_Amp_Threshold_t threshold;  /**< Threshold that was triggered. */
} qapi_ADC_Threshold_Result_t;

/**
* ADC device properties structure.
*/
typedef struct
{
   uint32_t uNumChannels;      /**< Number of ADC channels. */
} qapi_ADC_Device_Properties_t;

/**
*  Callback invoked when an amplitude threshold is crossed.
*
*  Once the threshold is crossed, it must be re-armed or it will
*           not trigger again.
*
*  @param[in] ctxt    Context specified when setting the threshold.
*  @param[in] result  Threshold crossing result.
*
*  @return
*  None.
*/
typedef void (*qapi_ADC_Threshold_CB_t)
(
   void *ctxt,
   const qapi_ADC_Threshold_Result_t *result
);

/**
* ADC TM callback payload structure
*/
typedef struct
{
   qapi_ADC_Amp_Threshold_t eThresholdTriggered;   /**< Type of threshold that triggered. */
   uint32_t uTMChannelIdx;                     /**< TM channel index. */
   int32_t nPhysicalTriggered;                 /**< Physical value that triggered. */
} qapi_AdcTM_Callback_Payload_Type_t;

/**
*  Callback invoked when an amplitude threshold is crossed.
*
*  Once the threshold is crossed, it must be re-armed or it will
*           not trigger again.
*
*  @param[in] ctxt    Context specified when setting the threshold.
*  @param[in] result  Threshold crossing result.
*
*  @return
*  None.
*/
typedef void (*qapi_AdcTM_Threshold_Cb_Type)
(
   void *ctxt,
   const qapi_ADC_Threshold_Result_t *result
);

/**
* ADC TM channel range structure.
*/
typedef struct
{
   int32_t nPhysicalMin;   /**< Minimum threshold in physical units. */
   int32_t nPhysicalMax;   /**< Maximum threshold in physical units. */
} qapi_AdcTM_Range_Type_t;

/**
* ADC TM request parameters structure.
*/
typedef struct
{
   qapi_Adc_Input_Properties_Type_t adcTMInputProps; /**< ADC channel input properties. */
   qapi_AdcTM_Threshold_Cb_Type pfnAdcTMThresholdCb; /**< Amplitude threshold callback type. */
   void *pCtxt;                                      /**< Context specified when setting the threshold. */
} qapi_AdcTM_Request_Params_Type_t;

/** @} */ /* end_addtogroup qapi_adc_datatypes */
#endif /** QAPI_ADC_TYPE_H*/
