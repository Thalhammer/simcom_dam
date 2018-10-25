/**************************************************************************/
/*                                                                        */ 
/*            Copyright (c) 1996-2016 by Express Logic Inc.               */ 
/*                                                                        */ 
/*  This software is copyrighted by and is the sole property of Express   */ 
/*  Logic, Inc.  All rights, title, ownership, or other interests         */ 
/*  in the software remain the property of Express Logic, Inc.  This      */ 
/*  software may only be used in accordance with the corresponding        */ 
/*  license agreement.  Any unauthorized use, duplication, transmission,  */ 
/*  distribution, or disclosure of this software is expressly forbidden.  */ 
/*                                                                        */
/*  This Copyright notice may not be removed or modified without prior    */ 
/*  written consent of Express Logic, Inc.                                */ 
/*                                                                        */ 
/*  Express Logic, Inc. reserves the right to modify this software        */ 
/*  without notice.                                                       */ 
/*                                                                        */ 
/*  Express Logic, Inc.                     info@expresslogic.com         */
/*  11423 West Bernardo Court               http://www.expresslogic.com   */
/*  San Diego, CA  92127                                                  */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */ 
/** ThreadX Component                                                     */
/**                                                                       */
/**   Module Interface (API)                                              */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/**************************************************************************/ 
/*                                                                        */ 
/*  APPLICATION INTERFACE DEFINITION                       RELEASE        */ 
/*                                                                        */ 
/*    txm_module_port.h                                 Cortex-A7/ARM     */ 
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    William E. Lamie, Express Logic, Inc.                               */ 
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This file defines the basic module constants, interface structures, */ 
/*    and function prototypes.                                            */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  03-01-2017     William E. Lamie         Initial Version 5.6           */ 
/*                                                                        */ 
/**************************************************************************/ 

#ifndef TXM_MODULE_PORT_H
#define TXM_MODULE_PORT_H

/* It is assumed that the base ThreadX tx_port.h file has been modified to add the 
  following extensions to the ThreadX thread control block (this code should replace
  the corresponding macro define in tx_port.h):

#define TX_THREAD_EXTENSION_2                   VOID    *tx_thread_module_instance_ptr;       \
                                                VOID    *tx_thread_module_entry_info_ptr;     
*/


/* Define constants specific to the tools the module can be built with for this particular modules port.  */

#define TXM_MODULE_IAR_COMPILER                 0x00000000
#define TXM_MODULE_RVDS_COMPILER                0x01000000
#define TXM_MODULE_GNU_COMPILER                 0x02000000
#define TXM_MODULE_COMPILER_MASK                0xFF000000
#define TXM_MODULE_OPTIONS_MASK                 0x000000FF


/* Define the properties for this particular module port.  */

#define TXM_MODULE_USER_MODE                    0x00000000

/* Define the minimum stack available for a module thread on this processor.
   If the size available during dispatch is less than this value, dispatch will return an error.  */
#ifndef TXM_MODULE_MINIMUM_STACK_AVAILABLE
#define TXM_MODULE_MINIMUM_STACK_AVAILABLE      64
#endif

/* Define the supported options for this module.   */

#define TXM_MODULE_MANAGER_SUPPORTED_OPTIONS    0
#define TXM_MODULE_MANAGER_REQUIRED_OPTIONS     0


/* Define offset adjustments according to the compiler used to build the module.  */

#define TXM_MODULE_IAR_SHELL_ADJUST             24
#define TXM_MODULE_IAR_START_ADJUST             28
#define TXM_MODULE_IAR_STOP_ADJUST              32
#define TXM_MODULE_IAR_CALLBACK_ADJUST          44

#define TXM_MODULE_RVDS_SHELL_ADJUST            0
#define TXM_MODULE_RVDS_START_ADJUST            0
#define TXM_MODULE_RVDS_STOP_ADJUST             0
#define TXM_MODULE_RVDS_CALLBACK_ADJUST         0

#define TXM_MODULE_GNU_SHELL_ADJUST             24
#define TXM_MODULE_GNU_START_ADJUST             28
#define TXM_MODULE_GNU_STOP_ADJUST              32
#define TXM_MODULE_GNU_CALLBACK_ADJUST          44


/* Define other module port-specific constants.  */


/* QC port start */
#ifndef TX_DAM_QC_CUSTOMIZATIONS
#define TX_DAM_QC_CUSTOMIZATIONS
#endif

#ifdef TX_DAM_QC_CUSTOMIZATIONS

#ifdef TXM_MODULE_REQUIRE_LOCAL_OBJECT_MEMORY
#undef TXM_MODULE_REQUIRE_LOCAL_OBJECT_MEMORY
#endif

#define TXM_MODULE_CODE_ALIGNMENT 0x1000

/* Define the port-extensions to the module manager instance structure.  */
#define TXM_MODULE_MANAGER_PORT_EXTENSION                                           \
 VOID *txm_module_instance_virt_base;                                               \
 VOID *txm_module_instance_phys_base;

#else

/* Define the port-extensions to the module manager instance structure.  */
#define TXM_MODULE_MANAGER_PORT_EXTENSION                                           \

#endif
/* QC port end */

/* Define the macro to check the stack available in dispatch.  */
#define TXM_MODULE_MANAGER_CHECK_STACK_AVAILABLE                                    \
    ULONG stack_available;                                                          \
    stack_available =  __current_sp();                                              \
    stack_available -= (ULONG)_tx_thread_current_ptr->tx_thread_stack_start;        \
    if((stack_available < TXM_MODULE_MINIMUM_STACK_AVAILABLE) ||                    \
       (stack_available > _tx_thread_current_ptr->tx_thread_stack_size))            \
    {                                                                               \
        return(TX_SIZE_ERROR);                                                      \
    }


/* Define the macro to check the module version ID.  */

#define TXM_MODULE_MANAGER_CHECK_PROPERTIES(properties)                             \
        if ((properties & _txm_module_manager_properties_supported) != (properties))\
        {                                                                           \
            _tx_mutex_put(&_txm_module_manager_mutex);                              \
            return(TXM_MODULE_INVALID_PROPERTIES);                                  \
        }                                                                           \
        if ((_txm_module_manager_properties_required & properties) != _txm_module_manager_properties_required) \
        {                                                                           \
            _tx_mutex_put(&_txm_module_manager_mutex);                              \
            return(TXM_MODULE_INVALID_PROPERTIES);                                  \
        }                                                                           


/* Define the macro to check the code alignment.  */

#define TXM_MODULE_MANAGER_CHECK_CODE_ALIGNMENT(module_location, code_alignment)    _txm_module_manager_alignment_adjust(module_preamble, &code_size, &code_alignment, &data_size, &data_alignment);


/* Define the macro to adjust the alignment and size for code/data areas.  */

#define TXM_MODULE_MANAGER_ALIGNMENT_ADJUST(module_preamble, code_size, code_alignment, data_size, data_alignment)   


/* Define the macro to adjust the symbols in the module preamble.  */

#define TXM_MODULE_MANAGER_CALCULATE_ADJUSTMENTS(properties, shell_function_adjust, start_function_adjust, stop_function_adjust, callback_function_adjust) \
    if ((properties & TXM_MODULE_COMPILER_MASK) == TXM_MODULE_IAR_COMPILER)         \
    {                                                                               \
        shell_function_adjust =     TXM_MODULE_IAR_SHELL_ADJUST;                    \
        start_function_adjust =     TXM_MODULE_IAR_START_ADJUST;                    \
        stop_function_adjust =      TXM_MODULE_IAR_STOP_ADJUST;                     \
        callback_function_adjust =  TXM_MODULE_IAR_CALLBACK_ADJUST;                 \
    }                                                                               \
    else if ((properties & TXM_MODULE_COMPILER_MASK) == TXM_MODULE_RVDS_COMPILER)   \
    {                                                                               \
        shell_function_adjust =     TXM_MODULE_RVDS_SHELL_ADJUST;                   \
        start_function_adjust =     TXM_MODULE_RVDS_START_ADJUST;                   \
        stop_function_adjust =      TXM_MODULE_RVDS_STOP_ADJUST;                    \
        callback_function_adjust =  TXM_MODULE_RVDS_CALLBACK_ADJUST;                \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        shell_function_adjust =     TXM_MODULE_GNU_SHELL_ADJUST;                    \
        start_function_adjust =     TXM_MODULE_GNU_START_ADJUST;                    \
        stop_function_adjust =      TXM_MODULE_GNU_STOP_ADJUST;                     \
        callback_function_adjust =  TXM_MODULE_GNU_CALLBACK_ADJUST;                 \
    }


/* Define the macro to populate the thread control block with module port-specific information.  */

#define TXM_MODULE_MANAGER_THREAD_SETUP(thread_ptr, module_instance)                                                            \
        thread_entry_info -> txm_module_thread_entry_info_kernel_call_dispatcher =   _txm_module_manager_kernel_dispatch;       


/* Define the macro to populate the module control block with module port-specific information.
   For this port - nothing needs to be done.
*/
#define TXM_MODULE_MANAGER_MODULE_SETUP(module_instance) 


/* Define some internal prototypes to this module port.  */

#define TXM_MODULE_MANAGER_ADDITIONAL_PROTOTYPES    \
void  _txm_module_manager_alignment_adjust(TXM_MODULE_PREAMBLE *module_preamble, ULONG *code_size, ULONG *code_alignment, ULONG *data_size, ULONG *data_alignment); 


#define TXM_MODULE_MANAGER_VERSION_ID   \
CHAR                            _txm_module_manager_version_id[] =  \
                                    "Copyright (c) 1996-2016 Express Logic Inc. * ThreadX Module Cortex-A7/ARM Version 5.6 *";

#endif

