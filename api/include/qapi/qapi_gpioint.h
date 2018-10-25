/*
 * $QAPI_LICENSE_TEXT
 */

#ifndef __QAPI_GPIOINT_H__ // [
#define __QAPI_GPIOINT_H__

/*=================================================================================
 *
 *                       GPIO INTERRUPT CONTROLLER
 *
 *================================================================================*/

/**
 * @file qapi_gpioint.h
 *
 * @brief QAPI GPIO interrupt controller module.
 *
 * @addtogroup qapi_gpioint
 * @{
 *
 * @details The general purpose input/output (GPIO) interrupt controller 
 *          provides an interface for registering for interrupts for a GPIO.
 *          These are generally used for customer-specific use cases in which
 *          an entity external to the chip needs to communicate with the chip.
 *          This can be done by configuring a GPIO as an input and toggling it
 *          externally to the chip. In doing so, this causes a GPIO interrupt
 *          to fire, and software will be invoked to handle it. Additionally,
 *          the register API will allow clients to register their callback, and
 *          the driver will internally configure the hardware to handle the
 *          given trigger type. Clients may also force-trigger the interrupt
 *          by using the trigger API, as well as check if an interrupt is pending
 *          by using the Is_Interrupt_Pending() API. The GPIO interrupt may be
 *          enabled or disabled at any time using the Enable or Disable API.
 *          This ensures that the callback is not removed from the handler,
 *          but the interrupt will be unmasked/masked accordingly.
 *
 * @code
 *    * The code snippet below demonstates the use of this interface. The
 *    * example below includes the qapi_gpioint.h header file. This example
 *    * registers a callback with the GPIO Interrupt driver and manually
 *    * triggers the interrupt. Although this is a manual trigger use-case,
 *    * in practice, the GPIO is usually triggered externally to the chip.
 *    * After triggering the interrupt, it will loop 1000 times and deregister
 *    * the callback from the driver.
 *    *
 *    * This code snippet registers for GPIO 10 specifically and registers
 *    * the callback that will be defined as type qapi_GPIOINT_CB_t.
 *    * The code registers medium priority. It will be a level high trigger
 *    * given the input parameter GPIOINT_TRIGGER_HIGH_LEVEL, meaning that
 *    * when the external signal is high, it will jump to the handler if
 *    * enabled.
 * 
 *
 * qapi_Status_t          nStatus;
 * qapi_Instance_Handle_t pH;
 * uint32_t               nLoopCounter = 0;
 *
 * nStatus = qapi_GPIOINT_Register_Interrupt(&pH,         // Pass in a pointer
 *                                                        // to the handle
 *                                           10,          // GPIO 10 is used
 *                                           pfnCallback, // Callback fn pointer
 *                                           NULL,                       // NULL callback data
 *                                           GPIOINT_TRIGGER_HIGH_LEVEL,
 *                                                        // Level high trigger
 *                                           QAPI_GPIOINT_PRIO_MEDIUM_E,
 *                                                      // Priority of interrupt
 *                                           false );                    // Maskable Interrupt
 * if ( nStatus != QAPI_OK )
 * {
 *   // Error!
 * }
 * 
 * // Trigger interrupt for GPIO 10
 * nStatus = qapi_GPIOINT_Trigger_Interrupt( &pH, 10 );
 * if ( nStatus != QAPI_OK )
 * {
 *   // Error!
 * }
 *
 * while ( nLoopCounter++ < 1000 )
 * {
 * }
 * 
 * // Deregister the GPIO Interrupt
 * nRet = qapi_GPIOINT_Deregister_Interrupt( &pH, 10 );
 * if ( nRet != GPIOINT_SUCCESS )
 * {
 *   // Error!
 * }
 *
 * @endcode
 *
 * @}
 */

/*==================================================================================
       Copyright (c) 2015-2017 Qualcomm Technologies, Inc.
                       All Rights Reserved.
       Confidential and Proprietary - Qualcomm Technologies, Inc.
==================================================================================*/

/*==================================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tx/1.0.c3/api/systemdrivers/qapi_gpioint.h#1 $

when       who     what, where, why
--------   ---     -----------------------------------------------------------------
04/24/17   leo      (Tech Comm) Edited/added Doxygen comments and markup.
01/04/17   spalepu  Initial revision.
==================================================================================*/


/*==========================================================================

                       INCLUDE FILES FOR MODULE

==========================================================================*/
#include "qapi_types.h"
#include "qapi_status.h"
#include "stdint.h"
#include "qapi_txm_base.h"
/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/

/** @addtogroup qapi_gpioint
@{ */

/** 
 * GPIO interrupt trigger type enumeration for supported triggers.
 */
typedef enum {
  QAPI_GPIOINT_TRIGGER_LEVEL_HIGH_E,    /**< Level triggered active high. */
  QAPI_GPIOINT_TRIGGER_LEVEL_LOW_E,     /**< Level triggered active low. */
  QAPI_GPIOINT_TRIGGER_EDGE_RISING_E,   /**< Rising edge triggered. */
  QAPI_GPIOINT_TRIGGER_EDGE_FALLING_E,  /**< Falling edge triggered. */
  QAPI_GPIOINT_TRIGGER_EDGE_DUAL_E,     /**< Dual edge triggered. @newpage */
  QAPI_GPIOINT_TRIGGER_MAX_E
} qapi_GPIOINT_Trigger_e;


/** 
 * GPIO interrupt priority selection. The priority can determine how the
 * interrupt is configured internally. 
 */
typedef enum {
  QAPI_GPIOINT_PRIO_HIGHEST_E,  /**< Highest priority. */
  QAPI_GPIOINT_PRIO_HIGH_E,     /**< Medium-high priority. */
  QAPI_GPIOINT_PRIO_MEDIUM_E,   /**< Medium priority. */
  QAPI_GPIOINT_PRIO_LOW_E,      /**< Medium-low priority. */
  QAPI_GPIOINT_PRIO_LOWEST_E,   /**< Highest priority. */
  QAPI_GPIOINT_PRIO_MAX_E
} qapi_GPIOINT_Priority_e;


/** 
 * GPIO interrupt callback data type.
 *
 * This is the data type of the 
 *          argument passed into the callback that is registered
 * with the GPIO interrupt module. The value to pass
 *          will be given by the client at registration time.
 */
typedef uint32_t qapi_GPIOINT_Callback_Data_t;

/** 
 * GPIO interrupt callback function definition.
 *
 * GPIO interrupt clients will pass a function pointer of
 *          this format into the registration API.
 */
typedef void ( *qapi_GPIOINT_CB_t )( qapi_GPIOINT_Callback_Data_t );

/** 
 * GPIO interrupt handle definition.
 */
typedef void* qapi_Instance_Handle_t;


/** @} */ /* end_addtogroup qapi_gpioint */

/** @addtogroup qapi_gpioint
@{ */

// Driver ID defines

#define  TXM_QAPI_GPIOINT_REGISTER_INTERRUPT         TXM_QAPI_GPIO_INT_BASE
#define  TXM_QAPI_GPIOINT_DEREGISTER_INTERRUPT       TXM_QAPI_GPIO_INT_BASE + 1
#define  TXM_QAPI_GPIOINT_SET_TRIGGER                TXM_QAPI_GPIO_INT_BASE + 2
#define  TXM_QAPI_GPIOINT_ENABLE_INTERRUPT           TXM_QAPI_GPIO_INT_BASE + 3
#define  TXM_QAPI_GPIOINT_DISABLE_INTERRUPT          TXM_QAPI_GPIO_INT_BASE + 4
#define  TXM_QAPI_GPIOINT_TRIGGER_INTERRUPT          TXM_QAPI_GPIO_INT_BASE + 5
#define  TXM_QAPI_GPIOINT_IS_INTERRUPT_PENDING       TXM_QAPI_GPIO_INT_BASE + 6

#ifdef  QAPI_TXM_MODULE     // USER_MODE_DEFS

#define qapi_GPIOINT_Register_Interrupt(a,b,c,d,e,f,g)  ((UINT) (_txm_module_system_call12)(TXM_QAPI_GPIOINT_REGISTER_INTERRUPT , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) e, (ULONG) f, (ULONG) g, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_GPIOINT_Deregister_Interrupt(a,b)   ((UINT) (_txm_module_system_call12)(TXM_QAPI_GPIOINT_DEREGISTER_INTERRUPT, (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_GPIOINT_Set_Trigger(a,b,c)   ((UINT) (_txm_module_system_call12)(TXM_QAPI_GPIOINT_SET_TRIGGER     , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_GPIOINT_Enable_Interrupt(a,b)   ((UINT) (_txm_module_system_call12)(TXM_QAPI_GPIOINT_ENABLE_INTERRUPT     , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_GPIOINT_Disable_Interrupt(a,b)   ((UINT) (_txm_module_system_call12)(TXM_QAPI_GPIOINT_DISABLE_INTERRUPT    , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_GPIOINT_Trigger_Interrupt(a,b)   ((UINT) (_txm_module_system_call12)(TXM_QAPI_GPIOINT_TRIGGER_INTERRUPT    , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_GPIOINT_Is_Interrupt_Pending(a,b,c)   ((UINT) (_txm_module_system_call12)(TXM_QAPI_GPIOINT_IS_INTERRUPT_PENDING , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#elif defined QAPI_TXM_SOURCE_CODE      // KERNEL_MODE_DEFS

#include "qurt_txm_qapi_fwk.h"

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/


 
/** 
 * Registers a callback for a GPIO interrupt.
 *
 * Registers a callback function with the GPIO 
 *          interrupt controller and enables the interrupt.
 * This function configures and routes the interrupt
 * accordingly, as well as enabling it in the underlying
 *          layers.
 *
 * @param[in]    pH           Input handle to the client context.
 * @param[in]    nGpio        GPIO number to configure for an 
 *                            interrupt.
 * @param[in]    pfnCallback  Callback function pointer.
 * @param[in]    nData        Callback data.
 * @param[in]    eTrigger     Trigger type for the interrupt.
 * @param[in]    ePriority    Priority enumeration to determine
 *                            the configuration of the GPIO interrupt.
 * @param[in]    bNmi         Boolean value to select whether or not the
 *                            GPIO interrupt is nonmaskable to the CPU.
 * @return
 * - QAPI_ERR_INVALID_PARAM -- There is an issue with one of the input parameters.
 * - QAPI_ERROR             -- Error in internal registration. 
 * - QAPI_OK                -- Successfully registered.
 * 
 * @note1hang 
 * QAPI_ERROR may be returned if there is an invalid handle or 
 * an incorrect or invalid GPIO is being used. 
 */
qapi_Status_t qapi_GPIOINT_Register_Interrupt
(
  qapi_Instance_Handle_t       *pH,
  uint32_t                      nGpio,
  qapi_GPIOINT_CB_t             pfnCallback,
  qapi_GPIOINT_Callback_Data_t  nData,
  qapi_GPIOINT_Trigger_e        eTrigger,
  qapi_GPIOINT_Priority_e       ePriority,
  qbool_t                       bNmi
);

/** 
 * Deregisters a callback function from the GPIO 
 *          interrupt controller and disables the interrupt.
 * This function deconfigures the interrupt
 * accordingly, as well as disabling it in the underlying
 *          layers.
 *
 * @param[in]    pH           Input handle to the client context.
 * @param[in]    nGpio        GPIO number to deconfigure.
 * 
 * @return 
 * - QAPI_ERROR -- Error in internal deregistration.
 * - QAPI_OK    -- Successfully deregistered. 
 *
 * @note1hang 
 * QAPI_ERROR may be returned if there is an invalid handle or 
 * an incorrect or invalid GPIO is being used. 
 *  
 */
qapi_Status_t qapi_GPIOINT_Deregister_Interrupt
(
  qapi_Instance_Handle_t *pH,
  uint32_t                nGpio
);

/** 
 * Dynamically sets the trigger type of a registered GPIO
 *        interrupt.
 *
 * This function configures the underlying layer to capture an 
 * interrupt with a given trigger type. This function is
 * only to be used on a currently registered GPIO
 * interrupt and will change the trigger at runtime.
 *
 * @param[in]    pH           Input handle to the client context.
 * @param[in]    nGpio        GPIO number in which to set the trigger.
 * @param[in]    eTrigger     Trigger type to configure.
 * 
 * @return
 * - QAPI_ERR_INVALID_PARAM -- eTrigger parameter is invalid.
 * - QAPI_ERROR             -- Internal error in setting trigger. 
 * - QAPI_OK                -- Successfully set the trigger. 
 *
 * @note1hang 
 * QAPI_ERROR may be returned if there is an invalid handle or 
 * an incorrect or invalid GPIO is being used. 
 */
qapi_Status_t qapi_GPIOINT_Set_Trigger
(
  qapi_Instance_Handle_t *pH,
  uint32_t                nGpio,
  qapi_GPIOINT_Trigger_e  eTrigger
);

/** 
 * Enables a currently disabled and registered GPIO 
 *        interrupt.
 *
 * This is used primarily to unmask interrupts.
 *
 * @param[in]    pH           Input handle to the client context.
 * @param[in]    nGpio        GPIO number to enable.
 * 
 * @return
 * - QAPI_ERROR -- Internal error in enabling interrupt.
 * - QAPI_OK    -- Successfully enabled interrupt. 
 *
 * @note1hang 
 * QAPI_ERROR may be returned if there is an invalid handle or 
 * an incorrect or invalid GPIO is being used. 
 */
qapi_Status_t qapi_GPIOINT_Enable_Interrupt
(
  qapi_Instance_Handle_t *pH,
  uint32_t                nGpio
);

/** 
 * Disables a currently enabled and registered GPIO 
 *        interrupt.
 *
 * This is used primarily to mask interrupts, still being able to capture them,
 * but not have the callback called.
 *
 * @param[in]    pH           Input handle to the client context.
 * @param[in]    nGpio        GPIO number to disable.
 * 
 * @return
 * - QAPI_ERROR -- Internal error in disabling interrupt.
 * - QAPI_OK    -- Successfully disabled interrupt. 
 *
 * @note1hang 
 * QAPI_ERROR may be returned if there is an invalid handle or 
 * an incorrect or invalid GPIO is being used. 
 */
qapi_Status_t qapi_GPIOINT_Disable_Interrupt
(
  qapi_Instance_Handle_t *pH,
  uint32_t                nGpio
);

/** 
 * Manually triggers a GPIO interrupt by writing to the appropriate register.
 *
 * @param[in]    pH           Input handle to the client context.
 * @param[in]    nGpio        GPIO number to trigger.
 * 
 * @return
 * - QAPI_ERROR -- Internal error in triggering interrupt. 
 * - QAPI_OK    -- Successfully triggered interrupt. 
 *
 * @note1hang 
 * QAPI_ERROR may be returned if there is an invalid handle or 
 * an incorrect or invalid GPIO is being used. 
 */
qapi_Status_t qapi_GPIOINT_Trigger_Interrupt
(
  qapi_Instance_Handle_t *pH,
  uint32_t                nGpio
);

/** 
 * Queries to see if an interrupt is pending in the hardware by reading the
 * appropriate register.
 *
 * @param[in]    pH           Input handle to the client context.
 * @param[in]    nGpio        GPIO number to trigger.
 * @param[out]   pbIsPending  Boolean value for whether or not the 
 *                            interrupt is pending in hardware.
 * 
 * @return
 * - QAPI_ERR_INVALID_PARAM -- pbIsPending pointer is NULL.
 * - QAPI_ERROR             -- Internal error in checking pending. 
 * - QAPI_OK                -- Successfully checked pending status.
 *  
 * @note1hang 
 * QAPI_ERROR may be returned if there is an invalid handle or 
 * an incorrect or invalid GPIO is being used. 
 */
qapi_Status_t qapi_GPIOINT_Is_Interrupt_Pending
(
  qapi_Instance_Handle_t *pH,
  uint32_t                nGpio,
  qbool_t                *pbIsPending
);

#else   // DEF_END

#error "No QAPI flags defined"

#endif

/** @} */ /* end_addtogroup qapi_gpioint */

#endif // ] #ifndef __QAPI_GPIOINT_H__

