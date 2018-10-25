#ifndef __QAPI_SPI_MASTER_H__
#define __QAPI_SPI_MASTER_H__
/*=================================================================================
 *
 *     SERIAL PERIPHERAL INTERFACE MASTER
 *
 *===============================================================================*/
 /** @file qapi_spi_master.h
 *
 * @addtogroup qapi_spi_master
 * @{
 *
 * @brief Serial Peripheral Interface (SPI)
 *
 * @details SPI is a full duplex communication bus to interface peripherals in several 
 * communication modes as configured by the client software. The SPI driver API
 * provides a high level interface to expose the capabilities of the SPI master.
 *
 * Typical usage:
 * - qapi_SPIM_Open() -- Get a handle to an SPI instance.
 * - qapi_SPIM_Power_On() -- Turn on all resources required for a successful SPI transaction.
 * - qapi_SPIM_Full_Duplex() -- Generic transfer API to perform a transfer on the SPI bus.
 * - qapi_SPIM_Power_Off() -- Turn off all resources set by qapi_SPIM_Power_On().
 * - qapi_SPIM_Close() -- Destroy all objects created by the SPI handle.
 * 
 * A note about SPI power: \n
 * Calling qapi_SPIM_Open() and leaving it open does not drain any power. 
 * If the client is expecting to do several back-to-back SPI transfers, the recommended
 * approach is to call Power_On, perform all transfers, then call Power_Off. Calling 
 * Power_On/Power_Off for every transfer will affect throughput and increase the bus idle period.
 *
 * SPI transfers: \n
 * SPI transfers use BAM (DMA mode), so we expect buffers passed by the client to
 * be uncached RAM addresses. There is no address or length alignment requirement.
 *
 * SPI modes: \n
 * The SPI master supports all four SPI modes, and this can be changed per transfer.
 * See #qapi_SPIM_Config_t for configuration specification details.
 * The driver supports parallel transfers on different SPI instances.
 * 
 * A note about SPI modes: \n
 * Always check the meaning of SPI modes in your 
 * SPI slave specifications. Some manufacturers use different mode meanings.
 * - SPI Mode 0: CPOL = 0, and CPHA = 0
 * - SPI Mode 1: CPOL = 0, and CPHA = 1
 * - SPI Mode 2: CPOL = 1, and CPHA = 0
 * - SPI Mode 3: CPOL = 1, and CPHA = 1
 *
 * @}
 */
 
/*==================================================================================
       Copyright (c) 2017 Qualcomm Technologies, Inc.
                     All Rights Reserved.
                     Confidential and Proprietary - Qualcomm Technologies, Inc.
==================================================================================*/ 

/*==================================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tx/1.0.c3/buses/api/spi/qapi_spi_master.h#1 $

when         who     what, where, why
----------   ---     -----------------------------------------------------------------
04/24/2017   leo    (Tech Comm) Edited/added Doxygen comments and markup.
04/14/2017   ska    Fixed compilation issues for user space
02/19/2017   ska    Fixed compilation issues and added QAPI specific error codes
12/14/2016   rc     Initial version
==================================================================================*/

/*==================================================================================

                               INCLUDE FILES

==================================================================================*/

/*==================================================================================

                                   MACROS

==================================================================================*/


#include "qapi_status.h"
#include "qapi_dam_buses.h"

#define TXM_QAPI_SPI_OPEN        TXM_QAPI_BUSES_SPI_BASE
#define TXM_QAPI_SPI_FULL_DUPLEX TXM_QAPI_BUSES_SPI_BASE + 1
#define TXM_QAPI_SPI_POWER_ON    TXM_QAPI_BUSES_SPI_BASE + 2
#define TXM_QAPI_SPI_POWER_OFF   TXM_QAPI_BUSES_SPI_BASE + 3
#define TXM_QAPI_SPI_CLOSE       TXM_QAPI_BUSES_SPI_BASE + 4

/*
 * Error codes returned by the SPI Master API.
 */
#define QAPI_SPIM_ERROR                         __QAPI_ERROR(QAPI_MOD_BSP_SPI_MASTER, 1)
#define QAPI_SPIM_ERROR_INVALID_PARAM           __QAPI_ERROR(QAPI_MOD_BSP_SPI_MASTER, 2)
#define QAPI_SPIM_ERROR_MEM_ALLOC               __QAPI_ERROR(QAPI_MOD_BSP_SPI_MASTER, 3)
#define QAPI_SPIM_ERROR_TRANSFER_CONFIG_FAIL    __QAPI_ERROR(QAPI_MOD_BSP_SPI_MASTER, 4)
#define QAPI_SPIM_ERROR_TRANSFER_FAILURE        __QAPI_ERROR(QAPI_MOD_BSP_SPI_MASTER, 5)
#define QAPI_SPIM_ERROR_OPEN_FAILURE            __QAPI_ERROR(QAPI_MOD_BSP_SPI_MASTER, 6)
#define QAPI_SPIM_ERROR_CLOSE_FAILURE   	    __QAPI_ERROR(QAPI_MOD_BSP_SPI_MASTER, 7)
#define QAPI_SPIM_ERROR_POWER_ON_FAILURE        __QAPI_ERROR(QAPI_MOD_BSP_SPI_MASTER, 8)
#define QAPI_SPIM_ERROR_POWER_OFF_FAILURE       __QAPI_ERROR(QAPI_MOD_BSP_SPI_MASTER, 9)

/** @addtogroup qapi_spi_master
@{ */

/*==================================================================================

                               TYPE DEFINITIONS

==================================================================================*/
/**
* SPI callback function type.
*
* This type is used by the client to register its callback notification function. The 
* callback_Ctxt is the context object that will be passed untouched by the SPI Master
* driver to help the client identify which transfer completion instance is being signaled.
*/
typedef void (*qapi_SPIM_Callback_Fn_t) (uint32_t status, void *callback_Ctxt);

/**
* SPI instance enumeration.
*
* This enumeration lists the possible SPI instance indicating which HW SPI master 
* is to be used for the current SPI transaction.
*/

typedef enum
{
    QAPI_SPIM_INSTANCE_1_E = 1, /**< SPIM instance 1. */
    QAPI_SPIM_INSTANCE_2_E,     /**< SPIM instance 2. */
    QAPI_SPIM_INSTANCE_3_E,     /**< SPIM instance 3. */
    QAPI_SPIM_INSTANCE_4_E,     /**< SPIM instance 4. */
    QAPI_SPIM_INSTANCE_5_E,     /**< SPIM instance 5. */
    QAPI_SPIM_INSTANCE_6_E,     /**< SPIM instance 6. */
    QAPI_SPIM_INSTANCE_7_E,     /**< SPIM instance 7. */
    QAPI_SPIM_INSTANCE_8_E,     /**< SPIM instance 8. */
    QAPI_SPIM_INSTANCE_9_E,     /**< SPIM instance 9. */
    QAPI_SPIM_INSTANCE_10_E,    /**< SPIM instance 10. */
    QAPI_SPIM_INSTANCE_11_E,    /**< SPIM instance 11. */
    QAPI_SPIM_INSTANCE_12_E,    /**< SPIM instance 12. */
    QAPI_SPIM_INSTANCE_13_E,    /**< SPIM instance 13. */
    QAPI_SPIM_INSTANCE_14_E,    /**< SPIM instance 14. */
    QAPI_SPIM_INSTANCE_15_E,    /**< SPIM instance 15. */
    QAPI_SPIM_INSTANCE_16_E,    /**< SPIM instance 16. */
    QAPI_SPIM_INSTANCE_17_E,    /**< SPIM instance 17. */
    QAPI_SPIM_INSTANCE_18_E,    /**< SPIM instance 18. */
    QAPI_SPIM_INSTANCE_19_E,    /**< SPIM instance 19. */
    QAPI_SPIM_INSTANCE_20_E,    /**< SPIM instance 20. */
    QAPI_SPIM_INSTANCE_21_E,    /**< SPIM instance 21. */
    QAPI_SPIM_INSTANCE_22_E,    /**< SPIM instance 22. */
    QAPI_SPIM_INSTANCE_23_E,    /**< SPIM instance 23. */
    QAPI_SPIM_INSTANCE_24_E,    /**< SPIM instance 24. */
    QAPI_SPIM_INSTANCE_MAX_E,
} qapi_SPIM_Instance_t;

/**
* SPI phase type.
*
* This type defines the clock phase that the client can set in the 
* SPI configuration.
*/
typedef enum 
{
   QAPI_SPIM_MODE_0_E, /**< CPOL = 0, CPHA = 0. */
   QAPI_SPIM_MODE_1_E, /**< CPOL = 0, CPHA = 1. */
   QAPI_SPIM_MODE_2_E,  /**< CPOL = 1, CPHA = 0. */
   QAPI_SPIM_MODE_3_E,  /**< CPOL = 1, CPHA = 1. */
   QAPI_SPIM_MODE_INVALID_E = 0x7FFFFFFF
}qapi_SPIM_Shift_Mode_t;
 
/** SPI chip select ppolarity type.
*/
typedef enum 
{
   QAPI_SPIM_CS_ACTIVE_LOW_E,   /**< During Idle state, the CS line is held low. */
   QAPI_SPIM_CS_ACTIVE_HIGH_E,  /**< During Idle state, the CS line is held high. */
   QAPI_SPIM_CS_ACTIVE_INVALID_E = 0x7FFFFFFF
}qapi_SPIM_CS_Polarity_t;

/*Note - Endian ness - it is unclear  whether we can 
 * support this in all (FIFO/GSI) modes ! */

/** Order in which bytes from Tx/Rx buffer words are put on the bus.
 */
typedef enum
{
    SPI_NATIVE = 0,         /**< Native. */
    SPI_LITTLE_ENDIAN = 0,  /**< Little Endian. */
    SPI_BIG_ENDIAN          /**< Big Endian (network). */
}qapi_SPIM_Byte_Order_t;

/**
* SPI chip select assertion type.
*
* This type defines how the chip select line is configured between N word cycles.
*/
typedef enum 
{
   QAPI_SPIM_CS_DEASSERT_E,/**< CS is deasserted after transferring data for N clock cycles. */
   QAPI_SPIM_CS_KEEP_ASSERTED_E,/**< CS is asserted as long as the core is in the Run state. */
   QAPI_SPIM_CS_MODE_INVALID_E = 0x7FFFFFFF
}qapi_SPIM_CS_Mode_t;

/**
* SPI master configuration.
*
* The SPI master configuration is the collection of settings specified for each SPI
* transfer call to select the various possible SPI transfer parameters.
*/
typedef struct
{
   /* Add note to timing diagram here.*/
   qapi_SPIM_Shift_Mode_t SPIM_Mode;
   /**< SPIM mode type to be used for the SPI core. */
   qapi_SPIM_CS_Polarity_t SPIM_CS_Polarity;
   /**< CS polarity type to be used for the SPI core. */
   qapi_SPIM_Byte_Order_t SPIM_endianness;
   /** Endian-ness type used for the SPI transfer. */
   uint8_t SPIM_Bits_Per_Word;
   /**< SPI bits per word; any value from 3 to 31. */
   uint8_t SPIM_Slave_Index;
   /**< Slave index, beginning at 0 if mulitple SPI devices are connected to the same master. 
   At most 7 slaves are allowed. If an invalid number (7 or higher) is set, the CS 
   signal will not be used. */
   uint32_t Clk_Freq_Hz;
   /**< Host sets the SPI clock frequency closest to the requested frequency. */
   uint8_t CS_Clk_Delay_Cycles;
   /**< Number of clock cycles to wait after asserting CS before starting transfer. */
   uint8_t Inter_Word_Delay_Cycles;
   /**< Number of clock cycles to wait between SPI words. */
   qapi_SPIM_CS_Mode_t SPIM_CS_Mode;
   /**< CS mode to be used for the SPI core. */
   qbool_t loopback_Mode;
   /**< Normally 0. If set, the SPI controller will enable Loopback mode; used primarily for testing. */
} qapi_SPIM_Config_t;

/**
* SPI transfer type.
*
* This type specifies the address and length of the buffer for an SPI transaction.
*/
typedef struct
{
   uint8_t *tx_buf;
   /**< Buffer address for transmitting data. */
   uint8_t *rx_buf;
   /**< Buffer address for receiving data. */
   uint32_t len; 
   /**< Size in bytes. No alignment requirements; the arbitrary length data can be transferred. */
}qapi_SPIM_Descriptor_t;

/** @} */ /* end_addtogroup qapi_spi_master */

#ifdef QAPI_TXM_SOURCE_CODE      // KERNEL_MODE_DEFS
/*==================================================================================

                            FUNCTION DECLARATIONS

==================================================================================*/

/** @addtogroup qapi_spi_master
@{ */

/*==================================================================================
  FUNCTION      qapi_SPIM_Open
==================================================================================*/
/**
*  Initializes the SPI Master.
*
*  This function initializes internal data structures along with associated
*  static data. In any operating mode, this function should be called before
*  calling any other SPI master API.
*
*  @param[in]  instance    SPI instance specified by #qapi_SPIM_Instance_t.
*  @param[out] spi_Handle  Pointer to a location in which to store the driver handle.
*
*  @return
*  QAPI_OK                           -- Module initialized successfully. \n
*  QAPI_SPIM_ERROR_INVALID_PARAM     -- Invalid instance or handle parameter. \n
*  QAPI_SPIM_ERROR_MEM_ALLOC         -- Could not allocate space for driver structures. \n
*  QAPI_SPIM_ERR_INTERRUPT_REGISTER  -- Could not register for an interrupt.
*/
qapi_Status_t qapi_SPIM_Open (qapi_SPIM_Instance_t instance, void **spi_Handle);

/*==================================================================================
  FUNCTION      qapi_SPIM_Power_On
==================================================================================*/
/**
*  Enables the SPI Hardware resources for an SPI transaction.
*
*  This function enables all resources required for a successful SPI transaction. This 
*  includes clocks, power resources and pin multiplex functions. This function should 
*  be called before a transfer or a batch of SPI transfers.
* 
*  @param[in] spi_Handle  Driver handle returned by qapi_SPIM_Open().
*
*  @return
*  QAPI_OK                             -- SPI master enabled successfully. \n
*  QAPI_SPIM_ERROR_INVALID_PARAM       -- Invalid handle parameter. \n
*  QAPI_SPIM_ERROR_CLK_ENABLE_FAIL     -- Could not enable clocks or NPA. \n
*  QAPI_SPIM_ERROR_GPIO_ENABLE_FAIL    -- Could not enable GPIOs.
*/
qapi_Status_t qapi_SPIM_Power_On (void *spi_Handle);

/*==================================================================================
  FUNCTION      qapi_SPIM_Power_Off
==================================================================================*/
/**
*  Disables the SPI Hardware resources for an SPI transaction.
*
*  This function turns off all resources used by the SPI master. This includes clocks, 
*  power resources, and GPIOs. This function should be called to put the SPI master
*  in its lowest possible power state.
* 
*  @param[in] spi_Handle  Driver handle returned by qapi_SPIM_Open().
*
*  @return
*  QAPI_OK                             -- SPI master disabled successfully. \n
*  QAPI_SPIM_ERROR_INVALID_PARAM       -- Invalid handle parameter. \n
*  QAPI_SPIM_ERROR_CLK_DISABLE_FAIL    -- Could not disable clocks or NPA. \n
*  QAPI_SPIM_ERROR_GPIO_DISABLE_FAIL   -- Could not disable GPIOs.
*/
qapi_Status_t qapi_SPIM_Power_Off (void *spi_Handle);

/*==================================================================================
  FUNCTION      qapi_SPIM_Full_Duplex
==================================================================================*/
/**
*  Performs a data transfer over the SPI bus.
*
*  This function performs an asynchronous transfer over the SPI bus. Transfers can be 
*  one-directional or bi-directional. A callback is generated upon transfer completion.
* 
*  @param[in] spi_Handle  Driver handle returned by qapi_SPIM_Open().
*  @param[in] config      Pointer to the SPI configuration structure described by
                          #qapi_SPIM_Config_t.
*  @param[in] desc        Pointer to the structure described by
                          #qapi_SPIM_Descriptor_t. The descriptor can have NULL Tx OR
                          Rx buffers if a half duplex transfer is selected.
*  @param[in] num_Descriptors  Number of descriptor pointers the client wants to process.
*  @param[in] c_Fn        Callback function to be invoked when the SPI transfer 
                          completes succesfully or with an error.
*  @param[in] c_Ctxt      Pointer to a client object that will be returned as an
                          argument to c_Fn.
*  @param[in] get_timestamp Boolean variable to indicate if tranasaction timestamp needs to be provided
						  this is not supporeted for QUPv2 version.
*  @return
*  QAPI_OK                             -- SPI master enabled successfully. \n
*  QAPI_SPIM_ERROR_INVALID_PARAM       -- One or more invalid parameters. \n
*  QAPI_SPIM_ERROR_QUP_STATE_INVALID   -- SPI or BAM hardware is in a bad state. \n
*  QAPI_SPIM_ERROR_TRANSFER_TIMEOUT    -- Transfer timed out.
*/
qapi_Status_t qapi_SPIM_Full_Duplex (void *spi_Handle, qapi_SPIM_Config_t *config, 
                                     qapi_SPIM_Descriptor_t *desc, uint32_t num_Descriptors,
									 qapi_SPIM_Callback_Fn_t c_Fn, void *c_Ctxt, qbool_t get_timestamp);

/*==================================================================================
  FUNCTION      qapi_SPIM_Close
==================================================================================*/
/**
*  Closes the SPI master.
*
*  This function frees all internal data structures and closes the SPI master interface.
*  The handle returned by qapi_SPIM_Open() is then rendered invalid.
*
*  @param[in] spi_handle  Driver handle returned by qapi_SPIM_Open().
*
*  @return
*  QAPI_OK                             -- SPI driver closed successfully.
*/
qapi_Status_t qapi_SPIM_Close (void *spi_handle);



#elif defined  QAPI_TXM_MODULE     // USER_MODE_DEFS
#define qapi_SPIM_Open(instance, spi_Handle)  \
                                                                    (UINT) _txm_module_system_call4( \
                                                                    TXM_QAPI_SPI_OPEN, \
																	(ULONG) instance, \
																	(ULONG) spi_Handle,(ULONG) 0, (ULONG) 0)
#define qapi_SPIM_Power_On(spi_Handle)       \
                                                                    (UINT) _txm_module_system_call4( \
                                                                    TXM_QAPI_SPI_POWER_ON, \
                                                                    (ULONG) spi_Handle,(ULONG) 0, (ULONG) 0, \
                                                                    (ULONG) 0)	
#define qapi_SPIM_Power_Off(spi_Handle)      \
                                                                    (UINT) _txm_module_system_call4( \
                                                                    TXM_QAPI_SPI_POWER_OFF, \
                                                                    (ULONG) spi_Handle,(ULONG) 0,(ULONG) 0, \
                                                                    (ULONG) 0)
#define qapi_SPIM_Full_Duplex(spi_Handle, config, desc, \
                               num_Descriptors, c_Fn, c_Ctxt, \
                               get_timestamp) \
                                                                    (UINT) _txm_module_system_call7( \
                                                                    TXM_QAPI_SPI_FULL_DUPLEX, \
                                                                    (ULONG)spi_Handle, (ULONG)config, \
                                                                    (ULONG)desc, (ULONG) num_Descriptors, \
									                                (ULONG) c_Fn, (ULONG)c_Ctxt, (ULONG) get_timestamp)																		
#define qapi_SPIM_Close(spi_handle)          \
                                                                   (UINT) _txm_module_system_call4( \
                                                                    TXM_QAPI_SPI_CLOSE, \
                                                                    (ULONG) spi_Handle, (ULONG) 0,(ULONG) 0, \
                                                                    (ULONG) 0)	


/** @} */ /* end_addtogroup qapi_spi_master */
#else   // DEF_END

#error "No QAPI flags defined"

#endif // DEF end for QAPI_TXM_MODULE or QAPI_TXM_SOURCE_CODE

/** @} */ /* end_addtogroup qapi_spi_master */

#endif	
