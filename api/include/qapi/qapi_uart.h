#ifndef __QAPI_UART_H__
#define __QAPI_UART_H__

/**
 * @file qapi_uart.h
 */

/*==================================================================================================
Copyright (c) 2016-2017 Qualcomm Technologies, Inc.
        All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.

==================================================================================================*/
/*==================================================================================================
                                            DESCRIPTION
====================================================================================================

GLOBAL FUNCTIONS:
   qapi_UART_Close
   qapi_UART_Open
   qapi_UART_Receive
   qapi_UART_Transmit
   qapi_UART_Power_On
   qapi_UART_Power_Off
   qapi_UART_Ioctl
==================================================================================================*/
/*==================================================================================================
Edit History

$Header: //components/rel/core.tx/1.0.c3/buses/api/uart/qapi_uart.h#1 $

when       who     what, where, why
--------    ---     --------------------------------------------------------
04/24/2017  leo     (Tech Comm) Edited/added Doxygen comments and markup.
01/14/2017   rc     QAPI support for the userspace
12/14/2016   rc     Initial version

==================================================================================================*/

/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/
#include "qapi_txm_base.h"
#include "qapi_status.h"

#define TXM_QAPI_UART_OPEN              		TXM_QAPI_BUSES_BASE + 1	
#define TXM_QAPI_UART_TRANSMIT          		TXM_QAPI_BUSES_BASE	+ 2
#define TXM_QAPI_UART_RECIEVE          		    TXM_QAPI_BUSES_BASE	+ 3
#define TXM_QAPI_UART_POWER_ON          		TXM_QAPI_BUSES_BASE	+ 4
#define TXM_QAPI_UART_POWER_OFF          		TXM_QAPI_BUSES_BASE	+ 5
#define TXM_QAPI_UART_IOCTL              		TXM_QAPI_BUSES_BASE	+ 6
#define TXM_QAPI_UART_CLOSE         		    TXM_QAPI_BUSES_BASE	+ 7


/*==================================================================================================
                                             ENUMERATIONS
==================================================================================================*/

/** @addtogroup qapi_uart
@{ */

/**
 * UART port ID enumeration. 
 *  
 * This enumeration is used to specify which port is to be opened during the uart_open 
 * call.
 *  
 */
typedef enum
{
    QAPI_UART_PORT_001_E = 0, /**< UART core 01. */
    QAPI_UART_PORT_002_E,     /**< UART core 02. */
    QAPI_UART_PORT_003_E,     /**< UART core 03. */
    QAPI_UART_PORT_004_E,     /**< UART core 04. */
    QAPI_UART_PORT_005_E,     /**< UART core 05. */
    QAPI_UART_PORT_006_E,     /**< UART core 06. */
    QAPI_UART_PORT_007_E,     /**< UART core 07. */
    QAPI_UART_PORT_008_E,     /**< UART core 08. */
    QAPI_UART_PORT_009_E,     /**< UART core 09. */
    QAPI_UART_PORT_010_E,     /**< UART core 10. */
    QAPI_UART_PORT_011_E,     /**< UART core 11. */
    QAPI_UART_PORT_012_E,     /**< UART core 12. */
    QAPI_UART_PORT_013_E,     /**< UART core 13. */	
    QAPI_UART_PORT_014_E,     /**< UART core 14. */	
    QAPI_UART_PORT_015_E,     /**< UART core 15. */	
    QAPI_UART_PORT_016_E,     /**< UART core 16. */	
    QAPI_UART_PORT_017_E,     /**< UART core 17. */	
    QAPI_UART_PORT_018_E,     /**< UART core 18. */	
    QAPI_UART_PORT_019_E,     /**< UART core 19. */	
    QAPI_UART_PORT_020_E,     /**< UART core 20. */	
    QAPI_UART_PORT_021_E,     /**< UART core 21. */	
    QAPI_UART_PORT_022_E,     /**< UART core 22. */	
    QAPI_UART_PORT_023_E,     /**< UART core 23. */	
    QAPI_UART_PORT_024_E,     /**< UART core 24. */	

	QAPI_UART_MAX_PORTS_E,
}qapi_UART_Port_Id_e;

/**
 * UART bits per character configuration enumeration.
 *  
 * Enumeration to specify how many UART bits are to be used per character configuration.
 *  
 */
typedef enum
{
  QAPI_UART_5_BITS_PER_CHAR_E  = 0,  /**< 5 bits per character. */
  QAPI_UART_6_BITS_PER_CHAR_E  = 1,  /**< 6 bits per character. */
  QAPI_UART_7_BITS_PER_CHAR_E  = 2,  /**< 7 bits per character. */
  QAPI_UART_8_BITS_PER_CHAR_E  = 3,  /**< 8 bits per character. */
} qapi_UART_Bits_Per_Char_e;

/**
 * Enumeration for UART number of stop bits configuration.  
 *   
 */
typedef enum
{
  QAPI_UART_0_5_STOP_BITS_E    = 0,  /**< 0.5 stop bits. */
  QAPI_UART_1_0_STOP_BITS_E    = 1,  /**< 1.0 stop bit. */
  QAPI_UART_1_5_STOP_BITS_E    = 2,  /**< 1.5 stop bits. */
  QAPI_UART_2_0_STOP_BITS_E    = 3,  /**< 2.0 stop bits. */
} qapi_UART_Num_Stop_Bits_e;

/**
 * Enumeration for UART parity mode configuration.  
 *   
 */
typedef enum
{
  QAPI_UART_NO_PARITY_E        = 0,  /**< No parity. */ 
  QAPI_UART_ODD_PARITY_E       = 1,  /**< Odd parity. */
  QAPI_UART_EVEN_PARITY_E     = 2,   /**< Even parity. */
  QAPI_UART_SPACE_PARITY_E     = 3,  /**< Space parity. */
} qapi_UART_Parity_Mode_e;

/**
 * IOCTL command ID list of the UART.
 */
typedef enum
{
  QAPI_SET_FLOW_CTRL_E        = 0,  /**< Set auto flow control. */ 
  QAPI_SET_BAUD_RATE_E        = 1,  /**< Set baud rate. */
  QAPI_SET_RTS_CTRL_E         = 2,
} qapi_UART_Ioctl_Command_e;

/**
 * Flow control types for UART. 
 */
typedef enum
{
  QAPI_FCTL_OFF_E,                        /**< Disable flow control */
  QAPI_CTSRFR_AUTO_FCTL_E                /**< Use CTS/RFR flow control with
                                              auto RX RFR signal generation.  */
} QAPI_Flow_Control_Type;


/**
 * Flow control types for UART. 
 */
typedef enum
{
  QAPI_RTS_DEASSERT,  // manually deassert RTS
  QAPI_RTS_ASSERT,    // manually assert RTS
  QAPI_RTS_AUTO,      // RTS automatically controlled by HW (based on level of RX FIFO)
} QAPI_Rts_Control_type;


/**
 * IOCTL command ID list of the UART.
 *
 */
typedef union QAPI_UART_Ioctl_Param
{
  uint32_t                     baud_Rate; /**< Supported baud rates are 115200 bps, 1 Mbps,
                                                       2 Mbps, 3 Mbps, and 4 Mbps. */
  QAPI_Flow_Control_Type       Flow_Control_Type;    /**< Transmit flow control type. */

  QAPI_Rts_Control_type        Rts_Control_type;
} QAPI_UART_Ioctl_Param;

/** @} */ /* end_addtogroup qapi_uart */

/** @addtogroup qapi_uart
@{ */

/**
 * UART handle that is passed to the client when a UART port is opened.
 */
typedef void* qapi_UART_Handle_t;

/**
 * Transmit and receive operation callback type.
 *    
 * @param[in] num_bytes  Number of bytes.
 * @param[out] cb_data   Pointer to the callback data.
 */
typedef void(*qapi_UART_Callback_Fn_t)(uint32_t num_bytes, void *cb_data);

/** @} */ /* end_addtogroup qapi_uart */

/** @addtogroup qapi_uart
@{ */

/** Structure for UART configuration. */
typedef struct
{
   uint32_t                     baud_Rate; /**< Supported baud rates are 115200 bps, 1 Mbps,
                                                       2 Mbps, 3 Mbps, and 4 Mbps. */
   qapi_UART_Parity_Mode_e      parity_Mode; /**< Parity mode. */
   qapi_UART_Num_Stop_Bits_e    num_Stop_Bits; /**< Number of stop bits. */
   qapi_UART_Bits_Per_Char_e    bits_Per_Char; /**< Bits per character. */
   qbool_t                      enable_Loopback; /**< Enable loopback. */
   qbool_t                      enable_Flow_Ctrl; /**< Enable flow control. */
   qapi_UART_Callback_Fn_t         tx_CB_ISR; /**< Transmit callback, called from ISR context. \n
                                                       Be sure not to violate ISR guidelines. \n
                                                       @latexonly \textbf{Note:} @endlatexonly
                                                       Do not call uart_transmit or uart_receive
                                                       APIs from this callback. */
   qapi_UART_Callback_Fn_t         rx_CB_ISR; /**< Receive callback, called from ISR context. \n
                                                       Be sure not to violate ISR guidelines. \n
                                                       @latexonly \textbf{Note:} @endlatexonly
                                                       Do not call uart_transmit or uart_receive
                                                       APIs from this callback. */
}qapi_UART_Open_Config_t;

/** @} */ /* end_addtogroup qapi_uart */


#ifdef  QAPI_TXM_MODULE     /* USER_MODE_DEFS*/
#define qapi_UART_Close(handle)          (UINT) _txm_module_system_call4( \
                                                                    TXM_QAPI_UART_CLOSE, \
                                                                    (ULONG) handle, (ULONG) 0,\
                                                                    (ULONG) 0, (ULONG) 0)
#define qapi_UART_Open(handle, id, config)  ((UINT) (_txm_module_system_call4)(TXM_QAPI_UART_OPEN, (ULONG) handle, (ULONG) id,(ULONG) config, (ULONG) 0))	

#define qapi_UART_Receive(handle,buf, buf_Size,  cb_Data) \
                                                            (UINT) _txm_module_system_call4( \
                                                                    TXM_QAPI_UART_RECIEVE, \
                                                                    (ULONG) handle, (ULONG) buf,\
                                                                    (ULONG) buf_Size, (ULONG) cb_Data)
#define qapi_UART_Transmit( handle, buf, buf_Size,  cb_Data) ((UINT) (_txm_module_system_call4)( TXM_QAPI_UART_TRANSMIT, (ULONG) handle, (ULONG) buf,(ULONG) buf_Size, (ULONG) cb_Data))
#define qapi_UART_Power_On( handle)       (UINT) _txm_module_system_call4( \
                                                                    TXM_QAPI_UART_POWER_ON, \
                                                                    (ULONG) handle, (ULONG) 0,\
                                                                    (ULONG) 0, (ULONG) 0)	
#define qapi_UART_Power_Off( handle)      (UINT) _txm_module_system_call4( \
                                                                    TXM_QAPI_UART_POWER_OFF, \
                                                                    (ULONG) handle, (ULONG) 0,\
                                                                    (ULONG) 0, (ULONG) 0)
#define qapi_UART_Ioctl( handle,ioctl_Command,ioctl_Param) \
                                                            (UINT) _txm_module_system_call4( \
                                                                     TXM_QAPI_UART_IOCTL, \
                                                                    (ULONG) handle, (ULONG) ioctl_Command,\
                                                                    (ULONG) ioctl_Param, (ULONG) 0);

#elif defined QAPI_TXM_SOURCE_CODE      // KERNEL_MODE_DEFS
/*==================================================================================================
                                        FUNCTION PROTOTYPES
==================================================================================================*/
/** @addtogroup qapi_uart
@{ */

/**
 * Closes the UART port.
 *
 * Releases clock, interrupt, and GPIO handles related to this UART and
 *          cancels any pending transfers.
 * 
 * @note1hang Do not call this API from ISR context.
 * 
 * @param[in] handle      UART handle provided by qapi_UART_Open().
 * 
 * @return
 * QAPI_OK      Port close successful. \n
 * QAPI_ERROR   Port close failed.
 * 
 */

qapi_Status_t qapi_UART_Close
(  
   qapi_UART_Handle_t handle
);

/**
 * Initializes the UART port.
 *
 * Opens the UART port and configures the corresponding clocks, interrupts, and GPIO.
 * 
 * @note1hang Do not call this API from ISR context.
 * 
 * @param[in] handle  UART handle. 
 * @param[in] id      ID of the port to be opened.
 * @param[in] config  Structure that holds all configuration data.
 *  
 * @return 
 * QAPI_OK      Port open successful. \n
 * QAPI_ERROR   Port open failed.
 *  
 *  
 */

qapi_Status_t qapi_UART_Open
(
   qapi_UART_Handle_t*        handle, 
   qapi_UART_Port_Id_e        id, 
   qapi_UART_Open_Config_t*   config
);

/**
 * Queues the buffer provided for receiving the data.
 *
 * This is an asynchronous call. rx_cb_isr is called when the Rx transfer completes.
 * The buffer is owned by the UART driver until rx_cb_isr is called.
 * 
 * There must always be a pending Rx. The UART hardware has a limited buffer
 * (FIFO), and if there is no software buffer available for HS-UART,
 * the flow control will de-assert the RFR line.
 * 
 * Call uart_receive immediately after uart_open to queue a buffer.
 * After every rx_cb_isr, from a different non-ISR thread, queue the next transfer.
 * 
 * There can be a maximum of two buffers queued at a time.
 * 
 * @note1hang Do not call this API from ISR context.
 * 
 * @param[in] handle       UART handle provided by qapi_UART_Open().
 * @param[in] buf          Buffer to be filled with data.
 * @param[in] buf_Size     Buffer size. Must be @ge 4 and a multiple of 4. 
 * @param[in] cb_Data      Callback data to be passed when rx_cb_isr is called 
 *                         during Rx completion.
 *  
 * @return 
 * QAPI_OK      Queuing of the receive buffer was successful. \n
 * QAPI_ERROR   Queuing of the receive buffer failed.
 *  
 */

qapi_Status_t qapi_UART_Receive
(
   qapi_UART_Handle_t   handle,
   char*                buf, 
   uint32_t             buf_Size, 
   void*                cb_Data
);

/**
 * Transmits data from a specified buffer.
 *
 * This is an asynchronous call. The buffer is queued for Tx, and when transmit is completed,
 * tx_cb_isr is called.
 * 
 * The buffer is owned by the UART driver until tx_cb_isr is called.
 * 
 * @note1hang Do not call this API from ISR context.
 *
 * @param[in] handle         UART handle provided by qapi_UART_Open().
 * @param[in] buf            Buffer with data for transmit. 
 * @param[in] bytes_To_Tx    Bytes of data to transmit.
 * @param[in] cb_Data        Callback data to be passed when tx_cb_isr is called 
 *                           during Tx completion. 
 *  
 * @return 
 * QAPI_OK      Queuing of the transmit buffer was successful. \n
 * QAPI_ERROR   Queuing of the transmit buffer failed. 
 *  
 */

qapi_Status_t qapi_UART_Transmit
(
   qapi_UART_Handle_t handle, 
   char* buf, 
   uint32_t bytes_To_Tx, 
   void* cb_Data
);

/*==================================================================================
  FUNCTION      qapi_UART_Power_On
==================================================================================*/
/**
*  Enables the UART hardware resources for a UART transaction.
*
*  This function enables all resources required for a successful UART transaction. This 
*  includes clocks, power resources, and pin multiplex functions. This function should 
*  be called before a transfer or a batch of UART transfers.
* 
*  @param[in] UART_Handle  Driver handle returned by qapi_UART_Open().
*
*  @return
*  QAPI_OK      UART powered on successfully. \n
*  QAPI_ERROR   UART power on is failed. 
*/
qapi_Status_t
qapi_UART_Power_On
(
    qapi_UART_Handle_t UART_Handle
);

/*==================================================================================
  FUNCTION      qapi_UART_Power_Off
==================================================================================*/
/**
*  Disables the UART hardware resources for a UART transaction.
*
*  This function turns off all resources used by the UART master. This includes clocks, 
*  power resources, and GPIOs. This function should be called to put the UART master
*  in its lowest possible power state.
* 
*  @param[in] UART_Handle  Driver handle returned by qapi_UART_Open().
*
*  @return
*  QAPI_OK      UART powered off successfully. \n
*  QAPI_ERROR   UART power off is failed.
*/
qapi_Status_t 
qapi_UART_Power_Off 
(
    qapi_UART_Handle_t UART_Handle
);
/*==================================================================================
  FUNCTION      qapi_UART_Ioctl
==================================================================================*/
/**
*  Controls the UART configurations for a UART transaction.
*
*  This function controls the UART configurations apart from the IO operations, which 
*  cannot be achieved through standard APIs.
* 
*  @param[in] handle         Driver handle returned by qapi_UART_Open().
*  @param[in] ioctl_Command  Pass the commands listed with #qapi_UART_Ioctl_Command_e.
*  @param[in] ioctl_Param    Pass the argument associated with #qapi_UART_Ioctl_Command_e.
*
*  @return
*  QAPI_OK      UART IOCTL configuration is successfull. \n
*  QAPI_ERROR   UART IOCTL configuration is failed.
*/
qapi_Status_t qapi_UART_Ioctl
(    
 qapi_UART_Handle_t handle,
 qapi_UART_Ioctl_Command_e ioctl_Command,
  void *ioctl_Param
);

/** @} */ /* end_addtogroup qapi_uart */
#else   /* DEF_END */

#error "No QAPI flags defined"

#endif /* END OF QAPI_TXM_MODULE */

#endif /*__QAPI_UART_H__*/
