#ifndef QAPI_ADC_H
#define QAPI_ADC_H
/**
 * @file qapi_adc.h
 *
 * @brief  Contains QAPI driver definitions
 *
 * @addtogroup qapi_adc_apis
 * @{
 *
 * The analog-to-digital converter (ADC) allows an analog signal to be
 * sampled and digitally represented. The SoC features an on-die
 * ADC that supports reading multiple channels. The ADC can perform single-
 * shot and recurring measurements.
 *
 * The ADC is configurable via static parameters. See
 * the ADC tunable board file for the statically defined
 * parameters.
 *
 * This programming interface allows client software to configure
 * channels, perform single readings, set a threshold if the channel
 * is an ADC TM channel before reading the channel, and get ADC data samples.
 * The code snippet below shows an example usage.
 *
 * @code
 *
 *  * The code snippet below demonstrates use of this interface. The example
 *  * below opens ADC to obtain a handle, sets the thresholds if the channel
 *  * is an ADC TM channel, reads each ADC channel, and then closes the handle.
 *
 *   qapi_Status_t status;
 *   qapi_ADC_Handle_t handle;
 *   uint32_t num_channels;
 *   uint32_t channel;
 *   qapi_ADC_Read_Result_t result;
 *   const char Channel_Name;
 *   uint32_t Channel_Name_Size;
 *   qapi_AdcTM_Input_Properties_Type_t Properties_TM;
 *   qapi_Adc_Input_Properties_Type_t Properties;
 *   uint32_t Enable;
 *   const qapi_AdcTM_Request_Params_Type_t  ADC_TM_Params, TM_Params_Type;
 *   const int32 Lower_Tolerance, Higher_Tolerance, Threshold_Desired;
 *   qapi_ADC_Amp_Threshold_t Threshold_Type;
 *   qapi_AdcTM_Range_Type_t ADC_TM_Range;
 *   int32 TM_Threshold_Set;
 *
 *   status = qapi_ADC_Open(&handle, Dummy);
 *   if (status != QAPI_OK) { ... }
 *
 *   //To read ADC channels
 *   status=qapi_ADC_Get_Input_Properties(&handle, Channel_Name, 
 *                                Channel_Name_Size, Properties);
 *   if (status != QAPI_OK) { ... }
 *
 *   // To read and configure ADC TM channels
 *   status=qapi_ADC_TM_Get_Input_Properties(&handle, Channel_Name,
 *                                Channel_Name_Size, Properties_TM);
 *   if (status != QAPI_OK) { ... }
 *   else
 *   {
 *     status=qapi_ADC_Get_Range(&handle, channel, ADC_TM_Range);
 *     if (status != QAPI_OK) { ... }
 *     
 *     status=qapi_ADC_Set_Amp_Threshold(&handle, ADC_TM_Params,
 *              Threshold_Type, Threshold_Desired, TM_Threshold_Set):
 *     if (status != QAPI_OK) { ... }
 *     
 *     //Enable Thresholds (Enable = 1)
 *     status=qapi_ADC_TM_Enable_Thresholds(&handle, Enable, Threshold_Type);
 *     if (status != QAPI_OK) { ... 
 *
 *     status=qapi_ADC_TM_Set_Tolerance(&handle, TM_Params_Type_Ptr,
 *                                     Lower_Tolerance, Higher_Tolerance);
 *     if (status != QAPI_OK) { ... }
 *     
 *     //Disable Thresholds (Enable = 0) 
 *     status=qapi_ADC_TM_Enable_Thresholds(&handle, Enable, Threshold_Type);
 *     if (status != QAPI_OK) { ... }   
 *   }
 *
 *   for (channel = 0; channel < num_channels; channel++)
 *   {
 *      status = qapi_ADC_Read_Channel(handle, channel, &result);
 *      if (status != QAPI_OK) { ... }
 *
 *      // result.microvolts contains the reading
 *   }
 *   status = qapi_ADC_Close(handle, false);
 *   if (status != QAPI_OK) { ... }
 *   handle = NULL;
 *
 * @endcode
 *
 * @}
 */
 /* 
 * Copyright (C) 2017 QUALCOMM Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
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

#include "qapi_adc_types.h"
                                                                                                                           
/*============================================================================
                USER_Mode_DEFS
============================================================================*/

/* Driver ID defines */

#define  TXM_QAPI_ADC_OPEN                  TXM_QAPI_ADC_BASE
#define  TXM_QAPI_ADC_CLOSE                 TXM_QAPI_ADC_BASE + 1
#define  TXM_QAPI_ADC_GET_INPUT_PROP        TXM_QAPI_ADC_BASE + 2
#define  TXM_QAPI_ADC_READ_CHNL             TXM_QAPI_ADC_BASE + 3
#define  TXM_QAPI_ADC_TM_GET_INPUT_PROP     TXM_QAPI_ADC_BASE + 4
#define  TXM_QAPI_ADC_GET_RANGE             TXM_QAPI_ADC_BASE + 5
#define  TXM_QAPI_ADC_SET_AMP_THRESHOLD     TXM_QAPI_ADC_BASE + 6
#define  TXM_QAPI_ADC_TM_ENABLE_THRESHOLDS  TXM_QAPI_ADC_BASE + 7
#define  TXM_QAPI_ADC_TM_SET_TOLERANCE      TXM_QAPI_ADC_BASE + 8


#ifdef  QAPI_TXM_MODULE
               
/* API Definitions */

#define qapi_ADC_Open(Handle, Attributes)\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_ADC_OPEN,\
    (ULONG) Handle, (ULONG) Attributes, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define qapi_ADC_Get_Input_Properties(Handle, Channel_Name_Ptr,\
    Channel_Name_Size, Properties_Ptr)\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_ADC_GET_INPUT_PROP,\
    (ULONG) Handle, (ULONG) Channel_Name_Ptr, (ULONG) Channel_Name_Size,\
    (ULONG) Properties_Ptr, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0, (ULONG) 0, (ULONG) 0))

#define qapi_ADC_Read_Channel(Handle, Input_Prop_Ptr, Result_Ptr)\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_ADC_READ_CHNL,\
    (ULONG) Handle, (ULONG) Input_Prop_Ptr, (ULONG) Result_Ptr, (ULONG) 0,\
    (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0))

#define qapi_ADC_TM_Get_Input_Properties(Handle, Channel_Name_Ptr,\
    Channel_Name_Size, Properties_Ptr)\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_ADC_TM_GET_INPUT_PROP,\
    (ULONG) Handle, (ULONG) Channel_Name_Ptr, (ULONG) Channel_Name_Size,\
    (ULONG) Properties_Ptr, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0, (ULONG) 0, (ULONG) 0))

#define qapi_ADC_Get_Range(Handle, Input_Prop_Ptr, Range_Ptr)\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_ADC_GET_RANGE,\
    (ULONG) Handle, (ULONG) Input_Prop_Ptr, (ULONG) Range_Ptr, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define qapi_ADC_Set_Amp_Threshold(Handle, Params_Ptr, Threshold_Type, \
      Threshold_Desired_Ptr, Threshold_Set_Ptr)\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_ADC_SET_AMP_THRESHOLD,\
    (ULONG) Handle, (ULONG) Params_Ptr, (ULONG) Threshold_Type, \
    (ULONG) Threshold_Desired_Ptr, (ULONG) Threshold_Set_Ptr, (ULONG) 0,\
    (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#define qapi_ADC_TM_Enable_Thresholds(Handle, Enable, Threshold_Type)\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_ADC_TM_ENABLE_THRESHOLDS,\
    (ULONG) Handle, (ULONG) Enable, (ULONG) Threshold_Type, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define qapi_ADC_TM_Set_Tolerance(Handle, Params_Type_Ptr, \
      Lower_Tolerance_Ptr, Higher_Tolerance_Ptr)\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_ADC_TM_SET_TOLERANCE,\
    (ULONG) Handle, (ULONG) Params_Type_Ptr, (ULONG) Lower_Tolerance_Ptr, \
    (ULONG) Higher_Tolerance_Ptr, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#define qapi_ADC_Close(Handle, keep_enabled)\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_ADC_CLOSE,\
    (ULONG) Handle, (ULONG) keep_enabled, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))
                                                                                                                                                                                                                                                                                                               

#elif defined QAPI_TXM_SOURCE_CODE
    
/*============================================================================
                KERNEL_Mode_DEFS
============================================================================*/

/** @addtogroup qapi_adc_apis	
@{ */

/*============================================================================
                qapi_ADC_Open
============================================================================*/
/**
*  @brief Opens the ADC for use by a software client.
*
*  @details ADC clients values can only be read after successfully opening ADC.
*
*  @param[out] handle      Pointer to an ADC handle.
*  @param[in]  Attributes  Reserved parameter.
*
*  @return
*  - QAPI_OK                -- Call succeeded.
*  - QAPI_ERROR             -- Call failed.
*  - QAPI_ERR_INVALID_PARAM -- Invalid parameters were specified.
*  - QAPI_ERR_NO_MEMORY     -- No memory available to support this operation.
*  - QAPI_ERR_NO_RESOURCE   -- No more handles are available.
*/
qapi_Status_t qapi_ADC_Open
(
   qapi_ADC_Handle_t *Handle,
   uint32_t Attributes   
);


/*============================================================================
                qapi_ADC_Get_Input_Properties
============================================================================*/
/**
*  Gets the ADC channel configuration.
*
*  This function is used to get properties of ADC channels.
*
*  @param[in]  Handle           Handle provided by qapi_ADC_Open().
*  @param[in]  Channel_Name_Ptr Pointer to ADC channel name pointer.
*  @param[in]  Channel_Name_Size Size of channel name string.
*  @param[out] Properties_Ptr   ADC channel configuration.
*
*  @return
*  - QAPI_OK                -- Call succeeded.
*  - QAPI_ERROR             -- Call failed.
*  - QAPI_ERR_INVALID_PARAM -- Invalid parameters were specified.
*/
qapi_Status_t qapi_ADC_Get_Input_Properties
(
   qapi_ADC_Handle_t Handle,
   const char *Channel_Name_Ptr,
   uint32_t Channel_Name_Size,
   qapi_Adc_Input_Properties_Type_t *Properties_Ptr
);

/*============================================================================
                qapi_ADC_Read_Channel
============================================================================*/
/**
*  Reads an ADC channel.
*
*  This function performs a blocking ADC read for the device and channel
*  specified by the client in pAdcInputProps.
*
*  @param[in]  Handle           Handle provided by qapi_ADC_Open().
*  @param[in]  Input_Prop_Ptr   Properties pointer of channel provided by
*                                qapi_ADC_Get_Input_Properties().
*  @param[out] Result_Ptr       ADC reading result structure.
*
*  @return
*  - QAPI_OK                -- Call succeeded.
*  - QAPI_ERROR             -- Call failed.
*  - QAPI_ERR_INVALID_PARAM -- Invalid parameters were specified.
*/
qapi_Status_t qapi_ADC_Read_Channel
(
   qapi_ADC_Handle_t Handle,
   const qapi_Adc_Input_Properties_Type_t *Input_Prop_Ptr,
   qapi_ADC_Read_Result_t *Result_Ptr
);

/*============================================================================
                qapi_ADC_TM_Get_Input_Properties
============================================================================*/
/**
*  Gets the ADC TM channel configuration.
*
*  @param[in]  Handle           Handle provided by qapi_ADC_Open().
*  @param[in]  Channel_Name_Ptr  Pointer to the ADC TM channel name pointer.
*  @param[in]  Channel_Name_Size Size of channel name string.
*  @param[out] Properties_Ptr   ADC TM channel configuration.
*
*  @return
*  - QAPI_OK                -- Call succeeded.
*  - QAPI_ERROR             -- Call failed.
*  - QAPI_ERR_INVALID_PARAM -- Invalid parameters were specified.
*/
qapi_Status_t qapi_ADC_TM_Get_Input_Properties
(
   qapi_ADC_Handle_t Handle,
   const char *Channel_Name_Ptr,
   uint32_t Channel_Name_Size,
   qapi_AdcTM_Input_Properties_Type_t *Properties_Ptr
);

/*============================================================================
                qapi_ADC_TMGet_Range
============================================================================*/
/**
*  Gets the ADC TM channels range of operation.
*
*  This function gets the minimum and maximum physical value that can be set
*  as a threshold for a given VADC TM channel.
*
*  @param[in]  Handle           Handle provided by qapi_ADC_Open().
*  @param[in]  In_Properties_Ptr  Properties pointer of the channel provided by
*                                qapi_ADC_TM_Get_Input_Properties().
*  @param[out] ADC_TM_Range_Ptr   Pointer to the channel range.
*
*  @return
*  - QAPI_OK                -- Call succeeded.
*  - QAPI_ERROR             -- Call failed.
*  - QAPI_ERR_INVALID_PARAM -- Invalid parameters were specified.
*/
qapi_Status_t qapi_ADC_Get_Range
(
   qapi_ADC_Handle_t Handle,
   const qapi_AdcTM_Input_Properties_Type_t *In_Properties_Ptr,
   qapi_AdcTM_Range_Type_t *ADC_TM_Range_Ptr
);

/*============================================================================
                qapi_ADC_Set_Amp_Threshold
============================================================================*/
/**
*  Sets the threshold-related configuration for ADC TM channels.
*
*  The threshold event is triggered once when the threshold is crossed:
*       - ADC_TM_THRESHOLD_LOWER: current reading <= *Threshold_Desired_Ptr
*       - ADC_TM_THRESHOLD_HIGHER: current reading >= *Threshold_Desired_Ptr
*
*   After the event is triggered, the threshold will not trigger the event again
*   and will be in a triggered state until the client calls qapi_ADC_Set_Amp_Threshold()
*   to set a new threshold.
*
*  Note that thresholds can be disabled/re-enabled on a per client basis by calling
*  qapi_ADC_Clear_Amp_Threshold(). Thresholds are enabled by default, but calling
*  qapi_ADC_Clear_Amp_Threshold() does not automatically re-enable them if they were
*  previously disabled by a call to qapi_ADC_Clear_Amp_Threshold().
*
*  @param[in]  Handle                   Handle provided by qapi_ADC_Open().
*  @param[in]  ADC_TM_Params_Ptr        Pointer to the threshold parameters.
*  @param[in]  Threshold_Type           Type of threshold.
*  @param[in]  Threshold_Desired_Ptr    Pointer to desired threshold value.
*  @param[out] TM_Threshold_Set_Ptr     Pointer to threshold value actually set.
*
*  @return
*  - QAPI_OK                -- Call succeeded.
*  - QAPI_ERROR             -- Call failed.
*  - QAPI_ERR_INVALID_PARAM -- Invalid parameters were specified.
*/
qapi_Status_t qapi_ADC_Set_Amp_Threshold
(
   qapi_ADC_Handle_t Handle,
   const qapi_AdcTM_Request_Params_Type_t * ADC_TM_Params_Ptr,
   qapi_ADC_Amp_Threshold_t Threshold_Type,
   const int32_t *Threshold_Desired_Ptr,
   int32_t *TM_Threshold_Set_Ptr
);

/*============================================================================
                qapi_ADC_Clear_Amp_Threshold
============================================================================*/
/**
*  Enables or Disables thresholds on ADC TM channel. By default, thresholds
*  are enabled.
*
*  Thresholds are not monitored while the they are disabled,
*  and any threshold crossings that occurred while the thresholds were disabled
*  are ignored.
*
*  Threshold values and event handles set by qapi_ADC_Set_Amp_Threshold() are 
*  retained while thresholds are disabled.
*
*  @param[in] Handle           Handle provided by qapi_ADC_Open().
*  @param[in] Enable           Enable or disable thresholds.
*  @param[in] Threshold_Type   Type of threshold.
*
*  @return
*  - QAPI_OK                -- Call succeeded.
*  - QAPI_ERROR             -- Call failed.
*  - QAPI_ERR_INVALID_PARAM -- Invalid parameters were specified.
*/
qapi_Status_t qapi_ADC_TM_Enable_Thresholds
(
   qapi_ADC_Handle_t Handle,
   uint32_t Enable,
   qapi_ADC_Amp_Threshold_t Threshold_Type
);


/*============================================================================
                qapi_ADC_TM_Set_Tolerance
============================================================================*/
/**
*  Sets thresholds based on an allowable tolerance or delta.
*
*  This API allows clients to specify a tolerance for how much the measurement
*  can change before being notified, e.g., notify when XO_THERM changes by 0.02
*  degrees C. Thresholds are set based on the current measurement value +/- the
*  allowable delta.
*
*  Once the tolerance has been reached or exceeded, the ADC notifies the client and
*  automatically sets new thresholds for the tolerance. Clients must clear the
*  tolerances for the ADC to stop monitoring. Tolerances can be cleared by setting
*  a NULL value.
*
*  Clients can set or clear either a low tolerance, high tolerance, or both during
*  the same function call. If the client is already monitoring a tolerance,
*  setting a new tolerance results in an update to the previously set tolerance,
*  i.e., the new tolerance replaces the old tolerance.
*
*  A client can set either a threshold or a tolerance on any one measurement, but not
*  both at the same time. To allow a threshold to be set after registering a
*  tolerance, the tolerance must be cleared by passing in NULL parameters for the
*  tolerances.
*
*  The client event is triggered when the tolerance is met or exceeded:
*     - Lower: The event triggers when the current_value <= original_value - tolerance
*     - Upper: The event triggers when the current_value >= original_value + tolerance
*
*  @param[in] Handle            Handle provided by qapi_ADC_Open().
*  @param[in] TM_Params_Type    Pointer to threshold configuration of ADCM TM channel.
*  @param[in] Lower_Tolerance   Pointer to lower tolerance.
*  @param[in] Higher_Tolerance  Pointer to higher tolerance.
*
*  @return
*  - QAPI_OK                -- Call succeeded.
*  - QAPI_ERROR             -- Call failed.
*  - QAPI_ERR_INVALID_PARAM -- Invalid parameters were specified.
*/
qapi_Status_t qapi_ADC_TM_Set_Tolerance
(
   qapi_ADC_Handle_t Handle,
   const qapi_AdcTM_Request_Params_Type_t * TM_Params_Type,
   const int32_t *Lower_Tolerance,
   const int32_t *Higher_Tolerance
);

/*============================================================================
                qapi_ADC_Close
============================================================================*/
/**
*  Closes a handle to the ADC when a software client is done with it.
*
*  @param[in] Handle         Handle provided by qapi_ADC_Open().
*  @param[in] keep_enabled   Reserved parameter.
*
*  @return
*  - QAPI_OK                -- Call succeeded.
*  - QAPI_ERROR             -- Call failed.
*  - QAPI_ERR_INVALID_PARAM -- Invalid parameters were specified.
*/
qapi_Status_t qapi_ADC_Close
(
   qapi_ADC_Handle_t Handle,
   qbool_t keep_enabled
);


#else   

  #error "No QAPI flags defined"

#endif

/** @} */ /* end_addtogroup qapi_adc_apis */

#endif /** QAPI_ADC_H */
