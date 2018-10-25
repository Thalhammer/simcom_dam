/**
  @file qapi_atfwd.h

 EXTERNALIZED FUNCTIONS
  none

 INITIALIZATION AND SEQUENCING REQUIREMENTS
  none
*/

/*
 Copyright (c) 2017  Qualcomm Technologies, Inc.  All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
 ======================================================================*/
/*======================================================================
 *
 *        EDIT HISTORY FOR FILE
 *
 *	 This section contains comments describing changes made to the
 *	 module. Notice that changes are listed in reverse chronological
 *	 order.
 *
 *	
 *
 *
 * when 		who 	what, where, why
 * ---------- 	---   ------------------------------------------------
 * 2017-04-25   leo   (Tech Comm) Edited/added Doxygen comments and markup.
 ======================================================================*/
 
#ifndef _QAPI_ATFWD
#define _QAPI_ATFWD

#include "at_fwd_ext_api.h"
#include "qapi_tsens_types.h"
#include "qapi_status.h"
#include "qapi_data_txm_base.h"

/* ATFWD QAPI REQUEST ID DEFINES */
#define  TXM_QAPI_ATFWD_REG_CB                            TXM_QAPI_ATFWD_BASE + 1
#define  TXM_QAPI_ATFWD_DEREG_CB                          TXM_QAPI_ATFWD_BASE + 2
#define  TXM_QAPI_ATFWD_SEND_RESP_CB                      TXM_QAPI_ATFWD_BASE + 3
#define  TXM_QAPI_ATFWD_SEND_URC_RESP_CB                  TXM_QAPI_ATFWD_BASE + 4


#ifdef  QAPI_TXM_MODULE     // USER_MODE_DEFS

#define qapi_atfwd_reg(a,b)                                   ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_ATFWD_REG_CB             , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_atfwd_dereg(a)                                   ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_ATFWD_DEREG_CB             , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_atfwd_send_resp(a,b,c)                           ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_ATFWD_SEND_RESP_CB               , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_atfwd_send_urc_resp(a,b)                         ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_ATFWD_SEND_URC_RESP_CB                , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))


#else

qapi_Status_t qapi_ATFWD_Handler(UINT id, UINT a1, UINT a2, UINT a3, UINT a4, UINT a5, UINT a6, UINT a7, UINT a8, UINT a9, UINT a10, UINT a11, UINT a12);


/*=======================================================
 * QAPI ATFWD APIs                             *
 =======================================================*/


/** @ingroup qapi_atfwd_reg
 *
 * @brief Register the new custom AT Commands along with respective callbacks.
 *
 * @details
 *
 * @param[in] name  pointer to AT Commands string
 *
 * @param[in] atfwd_callback  pointer to the callback corresponding to the AT Commands.
 * 
 * @return On success, QAPI_OK is returned. On error, -QAPI_ERROR is returned.
 *
 */

qapi_Status_t qapi_atfwd_reg(char *name, at_fwd_cb_type atfwd_callback);


/** @ingroup qapi_atfwd_dereg
 *
 * @brief De-Register AT Commands 
 *
 * @details
 *
 * @param[in] name  pointer to AT Commands List
 *
 * @return On success, QAPI_OK is returned. On error, -QAPI_ERROR is returned.
 *
 */

qapi_Status_t qapi_atfwd_dereg(char *name);


/** @ingroup qapi_atfwd_send_resp
 *
 * @brief Send Response
 *
 * @details
 *
 * @param[in] atcmd_name  pointer to the particular atcmd to which this response corresponds to
 *
 * @param[in] buf  pointer to the buffer containing the response 
 *
 * @param[in] result   0 : Result ERROR. This is to be set in case of ERROR or CME ERROR. 
 *                                       The response buffer contains the entire details. 
 *                     1 : Result OK.    This is to be set if the final response  must send 
 *                                       an OK result code to the terminal. 
 *
 * @return On success, QAPI_OK is returned. On error, -QAPI_ERROR is returned.
 *
 */

qapi_Status_t qapi_atfwd_send_resp(char *atcmd_name, char *buf, uint32_t result);


/** @ingroup qapi_atfwd_send_urc_resp
 *
 * @brief Send URC Response
 *
 * @details
 *
 * @param[in] atcmd_name pointer to the particular atcmd to which this response corresponds to
 *
 * @param[in] at_urc  pointer to the buffer containing the response 
 *
 * @return On success, QAPI_OK is returned. On error, -QAPI_ERROR is returned.
 *
 */

qapi_Status_t qapi_atfwd_send_urc_resp(char *atcmd_name, char *at_urc);

#endif

#endif
