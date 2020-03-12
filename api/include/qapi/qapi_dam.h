/*
 * =====================================================================================
 *
 *       Filename:  qapi_dam.h
 *
 *    Description:  update dam app 
 *
 *        Version:  1.0
 *        Created:  2017/11/24 15:49:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jumping (apple), zhangping@sim.com
 *   Organization:  www.sim.com
 *
 * =====================================================================================
 */
#include "qapi_txm_base.h"

#ifndef  QAPI_DAM_H
#define  QAPI_DAM_H

#define TXM_QAPI_DAM_UPDATE_APP   TXM_QAPI_DAM_BASE + 1
#define TXM_QAPI_VISUAL_AT_OUTPUT TXM_QAPI_DAM_BASE + 2
#define TXM_QAPI_VISUAL_AT_INPUT  TXM_QAPI_DAM_BASE + 3
#define TXM_QAPI_VISUAL_AT_OPEN  TXM_QAPI_DAM_BASE + 4
#define TXM_QAPI_FORCE_MODEM_SLEEP TXM_QAPI_DAM_BASE + 5

#define TXM_QAPI_SET_DTR_EVENT_CALLBACK TXM_QAPI_DAM_BASE + 6

#ifdef  QAPI_TXM_MODULE
               
/* API Definitions */

#define qapi_DAM_Update_App()\
    ((qapi_FS_Status_t) (_txm_module_kernel_call_dispatcher)(TXM_QAPI_DAM_UPDATE_APP, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#define qapi_DAM_Visual_AT_Output(data, length)\
    ((_txm_module_kernel_call_dispatcher)(TXM_QAPI_VISUAL_AT_OUTPUT, (ULONG) data,(ULONG) length, (ULONG) 0))

#define qapi_DAM_Visual_AT_Input(data, length)\
    ((unsigned short) (_txm_module_kernel_call_dispatcher)(TXM_QAPI_VISUAL_AT_INPUT, (ULONG) data,(ULONG) length, (ULONG) 0))

#define qapi_DAM_Visual_AT_Open(call_back)\
    ((unsigned short) (_txm_module_kernel_call_dispatcher)(TXM_QAPI_VISUAL_AT_OPEN, (ULONG) call_back,(ULONG) 0, (ULONG) 0))
                                                                                                                                                                                                                                           
#define qapi_force_modem_sleep(sleep)\
    ((int) (_txm_module_kernel_call_dispatcher)(TXM_QAPI_FORCE_MODEM_SLEEP, (uint8_t) sleep, (ULONG) 0, (ULONG) 0))
#define qapi_DAM_Set_DTR_Event_Callback(call_back)\
    ((unsigned short) (_txm_module_kernel_call_dispatcher)(TXM_QAPI_SET_DTR_EVENT_CALLBACK, (ULONG) call_back,(ULONG) 0, (ULONG) 0))

#elif defined QAPI_TXM_SOURCE_CODE
    
/*============================================================================
                KERNEL_Mode_DEFS
============================================================================*/

/*============================================================================
                qapi_DAM_Update_App
============================================================================*/
/**
*  @brief Update Dam app
*  before call this interfacce, please put the upate app to  Alternate FS\custapp\cust_app.update
*  and ensure this file is valid dam app.
*   Refer to the doc of "SIM7000 Series_QAPI"
*/
void qapi_DAM_Update_App(void);

/*============================================================================
                qapi_DAM_Visual_AT_Open
============================================================================*/
/**
*  @brief Open Visual AT port.
*
*  @param[int]  if func is not NULL,when visual port recv AT data, func will callback.
*		the type of func is simcom_visual_empty_cb_type
*		typedef void(* simcom_visual_empty_cb_type)(void);
*
*  @return
*   1                -- Call succeeded.
*   0					--Already open by other
*/
uint32 qapi_DAM_Visual_AT_Open(void *func);

/*============================================================================
                qapi_DAM_Visual_AT_Input
============================================================================*/
/**
*  @brief send the AT command at the virtual port .
*
*  @param[int]  data : AT command data
*  @param[int]  length: less than 1500 bytes
*
*  @return
*/
void qapi_DAM_Visual_AT_Input(const unsigned char *data, unsigned short length);

/*============================================================================
                qapi_DAM_Visual_AT_Output
============================================================================*/
/**
*  @brief recv the AT command at the virtual port .
*
*  @param[int]  data :  the buffer to recv data. The buffer need more than 2048 bytes, otherwise data may be lost
*  @param[int]  length: the length of buffer
*
*  @return:  recv data length
*/
unsigned short qapi_DAM_Visual_AT_Output(unsigned char *data, unsigned short length);

/*============================================================================
                qapi_force_modem_sleep
============================================================================*/
/**
*  @brief force the modem go into sleep mode
*
*  @param[int]  sleep :  0, sleep. 1, wakeup
*
*  @return:  0, succeeded. -1, failed
*/
int qapi_force_modem_sleep(uint8 sleep);
/*============================================================================
                qapi_DAM_Set_DTR_Event_Callback
============================================================================*/
/**
*  @brief Set DTR Event callback function.
*
*  @param[int]  if func is not NULL, when the status of DTR pin is changed, the func will be called.
*		the type of func is simcom_dtr_event_cb_type
*		typedef void(* simcom_dtr_event_cb_type)(uint32 dtr_status);
*
*  @return
*   1                -- Call succeeded.
*   0					--Already open by other
*/
void qapi_DAM_Set_DTR_Event_Callback(void *func);
#else   
#error "No QAPI flags defined"
#endif


#endif   
