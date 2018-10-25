#ifndef __QAPI_TLMM__
#define __QAPI_TLMM__
/**
 * @file qapi_tlmm.h 
 * 
 * @brief Pin Mode Mux (PMM)
 *
 * @addtogroup qapi_tlmm
 * @{
 * 
 * @details Modern SoCs pack a lot of functionality but are often pin-limited
 *          owing to their shrinking size. This limitation is overcome by
 *          incorporating hardware to flexibly mux several different
 *          functionalities on a given physical pin under software control.
 *
 *          This module exposes an interface allowing its clients to manage
 *          desired functionalities on a set of physical GPIO pins on the SoC.
 *          The most common usage of this interface is to configure pins for
 *          discrete inputs or outputs to implement handshakes with external
 *          peripherals, sensors, or actuators.
 *
 *          The code snippet below shows an example usage of the programming
 *          interface. The module requires clients to use physical pin numbers
 *          on the SoC. Consult the hardware schematic or use a device
 *          configuration database to determine the proper pin number.
 *
 *
 * @code
 *    * The code snippet below demonstrates usage of the PMM interface. The 
 *    * example below configures SoC pin-13 to be a discrete GPIO configured
 *    * as an input with a pull-down. Note that drive strength is defaulted
 *    * to be QAPI_GPIO_2MA_E, even though it is not applicable for pins
 *    * configured as discrete inputs.
 *
 *    qapi_GPIO_ID_t     gpio_id;
 *    qapi_TLMM_Config_t tlmm_config;
 *    qapi_Status_t      status = QAPI_OK;
 *
 *    tlmm_config.pin = 13;
 *    tlmm_config.func = 1                 // Using the functionality tied to
 *                                         // pin mux value 1
 *    tlmm_config.dir = QAPI_GPIO_INPUT_E;
 *    tlmm_config.pull = QAPI_GPIO_PULL_DOWN_E;
 *    tlmm_config.drive = QAPI_GPIO_2MA_E; // drive is for output pins, specify
 *                                         // the default here
 *
 *    status = qapi_TLMM_Get_Gpio_ID( &tlmm_config, &gpio_id);
 *
 *    if (status == QAPI_OK)
 *    {
 *      status = qapi_TLMM_Config_Gpio(gpio_id, &tlmm_config);
 *
 *      if (status != QAPI_OK)
 *      {
 *        // Handle failed case here
 *      }
 *    } 
 *
 * @endcode
 * @}
 * @newpage */

/*==========================================================================
       Copyright (c) 2015-2017 Qualcomm Technologies, Inc.
                       All Rights Reserved.
       Confidential and Proprietary - Qualcomm Technologies, Inc.
===========================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tx/1.0.c3/api/systemdrivers/qapi_tlmm.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/04/17   spalepu Initial version.
===========================================================================*/


/*==========================================================================

                       INCLUDE FILES FOR MODULE

==========================================================================*/
 #include "qapi_types.h"
 #include "qapi_status.h"
 #include "stdint.h"
 #include "qapi_txm_base.h"
/*==========================================================================

                      PUBLIC GPIO CONFIGURATION MACROS

==========================================================================*/

/** @addtogroup qapi_tlmm
@{ */

/** 
 * @brief Pin direction enumeration. 
 *   
 * @details The enumeration is used to specify the direction when configuring
 *          a GPIO pin.
 */
typedef enum
{ 
  QAPI_GPIO_INPUT_E  = 0, /**< Specify the pin as an input to the SoC. */
  QAPI_GPIO_OUTPUT_E = 1, /**< Specify the pin as an output to the SoC. */

  QAPI_GPIO_INVALID_DIR_E = 0x7fffffff /* Placeholder - Do not use */

}qapi_GPIO_Direction_t;


/** 
  @brief GPIO pin pull type.
    
  @details This enumeration specifies the type of pull (if any) to use when
           specifying the configuration for a GPIO pin.
*/
typedef enum
{
  QAPI_GPIO_NO_PULL_E    = 0x0, /**< Specify no pull. */
  QAPI_GPIO_PULL_DOWN_E  = 0x1, /**< Pull the GPIO down. */
  QAPI_GPIO_KEEPER_E  = 0x2,    /**< Keep the GPIO as it is. */
  QAPI_GPIO_PULL_UP_E    = 0x3, /**< Pull the GPIO up. */

  QAPI_GPIO_INVALID_PULL_E = 0x7fffffff /* Placeholder - Do not use */

}qapi_GPIO_Pull_t;


/** 
  @brief GPIO pin drive strength. 
    
  @details This enumeration specifies the drive strength to use when specifying 
           the configuration of a GPIO pin. 
*/
typedef enum
{
  QAPI_GPIO_2MA_E     = 0,    /**< Specify a 2 mA drive. */
  QAPI_GPIO_4MA_E     = 0x1,  /**< Specify a 4 mA drive. */
  QAPI_GPIO_6MA_E     = 0x2,  /**< Specify a 6 mA drive. */
  QAPI_GPIO_8MA_E     = 0x3,  /**< Specify an 8 mA drive. */
  QAPI_GPIO_10MA_E    = 0x4,  /**< Specify a 10 mA drive. */
  QAPI_GPIO_12MA_E    = 0x5,  /**< Specify a 12 mA drive. */
  QAPI_GPIO_14MA_E    = 0x6,  /**< Specify a 14 mA drive. */
  QAPI_GPIO_16MA_E    = 0x7,  /**< Specify a 16 mA drive. */

  QAPI_GPIO_INVALID_STRENGTH_E = 0x7fffffff /* Placeholder - Do not use */

}qapi_GPIO_Drive_t;


/**
  @brief GPIO output state specification.
    
  @details This enumeration specifies the value to write to a GPIO pin configured as 
           an output. This functionality is also known as <i>bit banging</i>.
*/

typedef enum
{
  QAPI_GPIO_LOW_VALUE_E,     /**< Drive the output LOW. */
  QAPI_GPIO_HIGH_VALUE_E,    /**< Drive the output HIGH. */

  QAPI_GPIO_INVALID_VALUE_E = 0x7fffffff /* Placeholder - Do not use */

}qapi_GPIO_Value_t;


/*==========================================================================

                      PUBLIC DATA STRUCTURES

==========================================================================*/




/**
  @brief GPIO configuration.
    
  @details This structure is used to specify the configuration for a GPIO on the SoC.
           The GPIO can be configured as an Input or Output, which can be
           driven High or Low by the software. The interface also allows the
    SoC pins to be configured for alternate functionality.
*/
 typedef struct
 {
  uint32_t              pin;    /**< Physical pin number. */
  uint32_t              func;   /**< Pin function select. */
  qapi_GPIO_Direction_t dir;    /**< Direction (input or output). */
  qapi_GPIO_Pull_t      pull;   /**< Pull value. */
  qapi_GPIO_Drive_t     drive;  /**< Drive strength. */

 }qapi_TLMM_Config_t;

/**
* @brief SoC pin access ID.
*
* @details Unique ID provided by the module to the client. Clients must pass this
*          ID as a token with subsequent calls. Note that clients
*          should cache the ID. 
*/
typedef uint16_t qapi_GPIO_ID_t;


// Driver ID defines

#define  TXM_QAPI_TLMM_GET_GPIO           TXM_QAPI_TLMM_BASE
#define  TXM_QAPI_TLMM_RELEASE_GPIO       TXM_QAPI_TLMM_BASE + 1
#define  TXM_QAPI_TLMM_CONFIG_GPIO        TXM_QAPI_TLMM_BASE + 2
#define  TXM_QAPI_TLMM_DRIVE_GPIO         TXM_QAPI_TLMM_BASE + 3
#define  TXM_QAPI_TLMM_READ_GPIO          TXM_QAPI_TLMM_BASE + 4

#ifdef  QAPI_TXM_MODULE     // USER_MODE_DEFS

#define qapi_TLMM_Get_Gpio_ID(a,b)  ((UINT) (_txm_module_system_call12)(TXM_QAPI_TLMM_GET_GPIO , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_TLMM_Release_Gpio_ID(a,b)   ((UINT) (_txm_module_system_call12)(TXM_QAPI_TLMM_RELEASE_GPIO     , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_TLMM_Config_Gpio(a,b)   ((UINT) (_txm_module_system_call12)(TXM_QAPI_TLMM_CONFIG_GPIO     , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_TLMM_Drive_Gpio(a,b,c)   ((UINT) (_txm_module_system_call12)(TXM_QAPI_TLMM_DRIVE_GPIO     , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_TLMM_Read_Gpio(a,b,c)   ((UINT) (_txm_module_system_call12)(TXM_QAPI_TLMM_READ_GPIO     , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#elif defined QAPI_TXM_SOURCE_CODE      // KERNEL_MODE_DEFS

#include "qurt_txm_qapi_fwk.h"
 
/* ============================================================================
*  Function : qapi_TLMM_Get_Gpio_ID
* ============================================================================*/
/**
  @brief Gets a unique access ID.
 
  @details This function provides a unique access ID for a specified GPIO. This is
           required in order to access GPIO configuration APIs.

  @param[in] qapi_TLMM_Config  Pointer to the pin configuration data.
  @param[in] qapi_GPIO_ID      Pointer to a location in which to store the access ID.
    
  @return
  QAPI_OK -- Pin GPIO ID was successfully created. \n
  QAPI_ERR -- Pin GPIO is currently in use or not programmable.
    
*/

qapi_Status_t qapi_TLMM_Get_Gpio_ID
(
  qapi_TLMM_Config_t* qapi_TLMM_Config,
  qapi_GPIO_ID_t*     qapi_GPIO_ID
);


/* ============================================================================
*  Function : qapi_TLMM_Release_Gpio_ID
* ============================================================================*/
/**
  @brief Releases an SoC pin.
 
  @details This function allows a client to relinquish the lock on a GPIO pin. It
           facilitates sharing of a pin between two drivers in different system
       modes where each driver may need to reconfigure the pin. Using this
      function is not required unless such a condition dictates.

  @param[in]  qapi_TLMM_Config   Pointer to pin configuration data.
  @param[in]  qapi_GPIO_ID       Pin access ID retrieved from the qapi_TLMM_Get_Gpio_ID() call.
    
  @return
  QAPI_OK  -- Pin was released successfully. \n
  QAPI_ERR -- Pin could not be released.
    
*/
qapi_Status_t qapi_TLMM_Release_Gpio_ID
(
  qapi_TLMM_Config_t* qapi_TLMM_Config,
  qapi_GPIO_ID_t      qapi_GPIO_ID
);


/* ============================================================================
*  Function : qapi_TLMM_Config_Gpio
* ============================================================================*/
/**
  @brief Changes the SoC pin configuration
 
  @details This function configures an SoC pin based on a set of fields specified
           in the configuration structure reference passed in as a parameter.
 
  @param[in] qapi_GPIO_ID      Pin access ID retrieved from the qapi_TLMM_Get_Gpio_ID() call.
  @param[in] qapi_TLMM_Config  Pin configuration to use.
    
  @return
  QAPI_OK  -- Pin was configured successfully. \n
  QAPI_ERR -- Pin could not be configured.
*/
qapi_Status_t qapi_TLMM_Config_Gpio
(
  qapi_GPIO_ID_t      qapi_GPIO_ID,
  qapi_TLMM_Config_t* qapi_TLMM_Config
);


/* ============================================================================
*  Function : qapi_TLMM_Drive_Gpio
* ============================================================================*/
/**
  @brief Sets the state of an SoC pin configured as an output GPIO.
 
  @details This function drives the output of an SoC pin that has been configured as
           a generic output GPIO to a specified value.
 
  @param[in] qapi_GPIO_ID  Pin access ID retrieved from the qapi_TLMM_Get_Gpio_ID() call.
  @param[in] pin           SoC pin number to configure.
  @param[in] value         Output value.
    
  @return
  QAPI_OK  -- Operation completed successfully. \n
  QAPI_ERR -- Operation failed.
*/
qapi_Status_t qapi_TLMM_Drive_Gpio
(
  qapi_GPIO_ID_t    qapi_GPIO_ID,
  uint32_t          pin,
  qapi_GPIO_Value_t value
);


/* ============================================================================
*  Function : qapi_TLMM_Read_Gpio
* ============================================================================*/
/**
  @brief Reads the state of an SoC pin configured as an input GPIO.
 
  @param[in] qapi_GPIO_ID  Pin access ID retrieved from the qapi_TLMM_Get_Gpio_ID() call.
  @param[in] pin           SoC pin number to configure.
  @param[out] qapi_GPIO_Value  GIPO pin value.
    
  @return
  QAPI_GPIO_HIGH_VALUE -- Read value was HIGH. \n
  QAPI_GPIO_LOW_VALUE  -- Read value was LOW.
*/
qapi_Status_t qapi_TLMM_Read_Gpio
(
  qapi_GPIO_ID_t qapi_GPIO_ID,
  uint32_t       pin,
  qapi_GPIO_Value_t* qapi_GPIO_Value
);

#else   // DEF_END

#error "No QAPI flags defined"

#endif


/** @} */ /* end_addtogroup qapi_tlmm */

 #endif /* __QAPI_TLMM__ */

