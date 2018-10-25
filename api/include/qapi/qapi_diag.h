#ifndef QAPI_DIAG_H
#define QAPI_DIAG_H 

/** @file qapi_diag.h
*/

/*
Copyright (c) 2017 by Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/*===========================================================================

                            Edit History

  $Header: //components/rel/core.tx/1.0.c3/api/services/qapi_diag.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/06/17   gn      Added control of DIAG_MSG_DISABLE_LVL_MASK for Userspace modules
05/19/17   gn      Header file cleanup
05/04/17   gn      Added Doxgyen comments and markup.
03/24/17   gn      Changes to support DIAG delayed reponses on User space
02/24/17   gn      Changes to support DIAG QAPIs with DAM framework
===========================================================================*/

#include "txm_module.h" 
#include "qapi_types.h" // For qapi_Status_t and other qapi types
#include "qapi_status.h" // For QAPI_ERROR, QAPI_SUCCESS and other status codes
#include "qapi_txm_base.h" // For TXM_QAPI_DIAG_BASE
#include "qapi_diag_codes.h"
#include "qapi_diag_types.h"

/** @addtogroup qapi_diag
@{ */

/** @brief
   Macro to register the user space client's dispatch table with the diagnostics
   packet dispatching service.

   The client must maintain two buffers (inbuf and outbuf) and must pass a
   pointer to these buffers while registering its user table with Diag.
   When the command is received from the tool for the user space client,
   Diag will copy the command to the inbuf of the client and call its handler 
   with the length of the command that was written. The client must copy the
   response of the command to its outbuf and return the length of the response
   that was written or commit the response using qapi_diagpkt_commit with
   IMMEDIATE_RSP_FLAG and return 0.

    @note1hang 
    When a client command handler is processing a response, if qapi_diagpkt_commit
    is used, it returns only 0. For any other valid return length, Diag generates
    a response other than the one that is already committed.

   Parameters:
   - xx_subsysid -- Subsystem ID of the client.
   - xx_entry    -- Client registration table of type diagpkt_user_table_entry_type
                    with the func_ptr field as NULL and user_func_ptr with the
                    command handler.
   - inbuf       -- Client static buffer to which Diag copies the command.
   - inbuf_len   -- Client input static buffer length.
   - outbuf      -- Client static buffer to which which the client is
                    to copy the response to the command.
   - outbuf_len   -- Client output static buffer length.
   
   Returns QAPI status codes (defined in qapi_status.h).
@hideinitializer
*/
#define QAPI_DIAGPKT_DISPATCH_TABLE_REGISTER(xx_subsysid, xx_entry, inbuf, inbuf_len, outbuf, outbuf_len) \
   do { \
	 static diagpkt_master_table_type xx_entry##_table = { \
	  0, 0xFF, xx_subsysid, sizeof (xx_entry) / sizeof (xx_entry[0]), DIAG_APP_PROC, 0, DIAGCOMM_CTRL_NO_PORT, xx_entry \
	 }; \
	 static diagpkt_user_space_table_type xx_entry##_user_table = { \
	 inbuf, inbuf_len, outbuf, outbuf_len \
	 }; \
	 qapi_user_space_tbl_reg_append_proc (&xx_entry##_table, &xx_entry##_user_table); \
   } while (0)

/** @brief
    Macro to register the user space client's dispatch table of the delayed
    responses type with the diagnostics packet dispatching service.

    The client must maintain two buffers (inbuf and outbuf) and must pass
    the pointers to these buffers while registering its user table with Diag.

    When the command is received from the tool for the user space client,
    Diag copies the command to inbuf of the client and call its handler 
    with the length of the command written. The client must copy the response
    to its outbuf and commit the immediate response using qapi_diagpkt_commit
    with IMMEDIATE_RSP_FLAG. Subsequent delayed responses must be committed
    using qapi_diagpkt_commit with DELAYED_RSP_FLAG.

    @note1hang
    When a client command handler is processing a response, if qapi_diagpkt_commit
    is used, it returns only 0. For any other valid return length, Diag generates
    a response other than the one that is already committed.

    Parameters:
    - xx_cmdcode  -- Set to DIAG_SUBSYS_CMD_VER_2_F to specify that
                     the table is being registered for delayed response
                     functionality.
    - xx_subsysid -- Subsystem ID of the client.
    - xx_entry    -- Client registration table of type diagpkt_user_table_entry_type
                     with the func_ptr field as NULL and user_func_ptr
                     with the command handler.
    - inbuf       -- Client static buffer to which Diag copies the command.
    - inbuf_len   -- Client input static buffer length.
    - outbuf      -- Client static buffer to which which the client is to
                     copy the response to the command.
    - outbuf_len  -- Client output static buffer length.
   
    Returns QAPI status codes (defined in qapi_status.h).
@hideinitializer
*/
 #define QAPI_DIAGPKT_DISPATCH_TABLE_REGISTER_V2_DELAY(xx_cmdcode, xx_subsysid, xx_entry, inbuf, inbuf_len, outbuf, outbuf_len) \
   do { \
	 static diagpkt_master_table_type xx_entry##_table = { \
	  1, DIAG_SUBSYS_CMD_VER_2_F, xx_subsysid, sizeof (xx_entry) / sizeof (xx_entry[0]), DIAG_APP_PROC, 0, DIAGCOMM_CTRL_NO_PORT, xx_entry \
	 }; \
	 static diagpkt_user_space_table_type xx_entry##_user_table = { \
	 inbuf, inbuf_len, outbuf, outbuf_len \
	 }; \
	 qapi_user_space_tbl_reg_append_proc (&xx_entry##_table, &xx_entry##_user_table); \
   } while (0)	 

/** @brief
    Macro to log a client's printf_stype messages with 0 to 9 parameters.

    Parameters:
    - xx_ss_id   -- Subsystem ID of the client.
    - xx_ss_mask -- Subystem mask for this message (represents the logging level).
    - xx_fmt     -- Format string.
    - xx_args    -- Integer arguments.

    Returns QAPI status codes (defined in qapi_status.h).
@hideinitializer
*/
#define QAPI_MSG(xx_ss_id, xx_ss_mask, xx_fmt, ...) \
  do { \
    if (xx_ss_mask & (MSG_BUILD_MASK_## xx_ss_id)) { \
	  XX_MSG_CONST (xx_ss_id, xx_ss_mask, xx_fmt); \
      qapi_msg_send (&xx_msg_const, MSG_NARG(xx_fmt, ## __VA_ARGS__), ## __VA_ARGS__); \
    } \
  } while (0) \

/** @brief
    Macro to log a client's sprintf_stype messages with 0 to 9 parameters.

    Parameters:
    - xx_ss_id   -- Subsystem ID of the client.
    - xx_ss_mask -- Subystem mask for this message (represents the logging level).
    - xx_fmt     -- Format string.
    - xx_args    -- Arguments (integer or string type).

    Returns QAPI status codes (defined in qapi_status.h).
@hideinitializer
*/
#define QAPI_MSG_SPRINTF(xx_ss_id, xx_ss_mask, xx_fmt, ...) \
	  do { \
		if (xx_ss_mask & (MSG_BUILD_MASK_## xx_ss_id)) { \
		  XX_MSG_CONST (xx_ss_id, xx_ss_mask, xx_fmt); \
		  qapi_msg_sprintf (&xx_msg_const, MSG_NARG(xx_fmt, ## __VA_ARGS__), ## __VA_ARGS__); \
		} \
	  } while (0) \

#ifdef  QAPI_TXM_MODULE     // USER_MODE_DEFS

/* For modules, change the following macro appropriately to control DIAG message levels. */
#define DIAG_MSG_DISABLE_LVL_MASK 0

#include "msg_mask.h"
#include "msgcfg.h"
#include "msgtgt.h"

/** @brief 
   Internal QAPI to register a command table with Diag -- not to be used directly. Use 
   QAPI_DIAGPKT_DISPATCH_TABLE_REGISTER or QAPI_DIAGPKT_DISPATCH_TABLE_REGISTER_V2_DELAY
   to register. See the qapi_user_space_tbl_reg_append_proc() API for details.
*/
#define qapi_user_space_tbl_reg_append_proc(tbl_ptr, user_space_tbl_ptr) \
((qapi_Status_t) (_txm_module_system_call4) (TXM_QAPI_DIAG_DISPATCH_TABLE_REGISTER, (uint32_t)tbl_ptr, (uint32_t)user_space_tbl_ptr, (uint32_t)0, (uint32_t) 0))

/** @brief 
   Gets the delayed response ID for the client. See the qapi_diagpkt_get_next_delayed_rsp_id() API
   for details.
*/
#define qapi_diagpkt_get_next_delayed_rsp_id(delayed_rsp_id) \
((qapi_Status_t) (_txm_module_system_call4) (TXM_QAPI_DIAGPKT_GET_NEXT_DELAYED_RSP_ID, (uint32_t)delayed_rsp_id, (uint32_t)0, (uint32_t)0, (uint32_t) 0))

/** @brief 
   Commits the reponse packet. Use IMMEDIATE_RSP_FLAG for immediate
   responses, DELAYED_RSP_FLAG for delayed responses, and any other error code
   to report an error. qapi_diagpkt_commit returns QAPI_ERROR code if the commit
   is not successful. See the qapi_diagpkt_commit() API for details.
*/
#define qapi_diagpkt_commit(outbuf, rsp_len, rsp_flag) \
((qapi_Status_t) (_txm_module_system_call4) (TXM_QAPI_DIAGPKT_COMMIT, (uint32_t)outbuf, (uint32_t)rsp_len, (uint32_t)rsp_flag, (uint32_t) 0))

/** @brief
    Logs an accumlated log entry. Header contents must be assigned by the
    caller before calling this function. Therefore, qapi_log_set_code(),
    qapi_log_set_length(), and qapi_log_set_timestamp() must be used before this call. 
    See the qapi_log_submit() API for details.
*/
#define qapi_log_submit(ptr) \
((qapi_Status_t) (_txm_module_system_call4) (TXM_QAPI_DIAG_LOG_SUBMIT, (uint32_t)ptr, (uint32_t) 0, (uint32_t) 0, (uint32_t) 0))

/** @brief
    Sets the length field in the specified log record.
    See the qapi_log_set_length() API for details.
*/
#define qapi_log_set_length(ptr, length) \
((qapi_Status_t) (_txm_module_system_call4) (TXM_QAPI_DIAG_LOG_SET_LENGTH, (uint32_t)ptr, (uint32_t)length, (uint32_t) 0, (uint32_t) 0))

/** @brief
    Sets the code field in the specified log record.
    See the qapi_log_set_code() API for details.
*/
#define qapi_log_set_code(ptr, code) \
((qapi_Status_t) (_txm_module_system_call4) (TXM_QAPI_DIAG_LOG_SET_CODE, (uint32_t)ptr, (uint32_t)code, (uint32_t) 0, (uint32_t) 0))

/** @brief
    Sets the timestamp field in the specified log record.
    See the qapi_log_set_timestamp() API for details.
*/
#define qapi_log_set_timestamp(plog_hdr_ptr) \
((qapi_Status_t) (_txm_module_system_call4) (TXM_QAPI_DIAG_LOG_SET_TIMESTAMP, (uint32_t)plog_hdr_ptr, (uint32_t) 0, (uint32_t) 0, (uint32_t) 0))

/** @brief
    Checks whether a particular code is enabled for logging.
    See the qapi_log_status() API for details.
*/
#define qapi_log_status(code) \
((qapi_Status_t) (_txm_module_system_call4) (TXM_QAPI_DIAG_LOG_STATUS, (uint32_t)code, (uint32_t) 0, (uint32_t) 0, (uint32_t) 0))

/** @brief
    Reports an event without a payload.
    See the qapi_event_report() API for details.
*/
#define qapi_event_report(event_id) \
((qapi_Status_t) (_txm_module_system_call4) (TXM_QAPI_DIAG_EVENT_REPORT, (uint32_t)event_id, (uint32_t) 0, (uint32_t) 0, (uint32_t) 0))

/** @brief
    Reports an event with a payload.
    See the qapi_event_report_payload() API for details.
*/
#define qapi_event_report_payload(event_id, length, data) \
((qapi_Status_t) (_txm_module_system_call4) (TXM_QAPI_DIAG_EVENT_REPORT_PAYLOAD, (uint32_t)event_id, (uint32_t)length, (uint32_t)data, (uint32_t) 0))

/** @brief
    Internal API to build a diagnostic message. Not to be used directly.
    See the qapi_msg_send() API for details.
*/
#define qapi_msg_send(const_blk, num_args, ...) \
((qapi_Status_t) (_txm_module_system_call11) (TXM_QAPI_DIAG_MSG, (uint32_t)const_blk,(uint32_t)num_args, \
(uint32_t)GET_ARG(1, ## __VA_ARGS__ , PAD()), (uint32_t)GET_ARG(2, ## __VA_ARGS__ , PAD()), (uint32_t)GET_ARG(3, ## __VA_ARGS__ , PAD()),(uint32_t)GET_ARG(4, ## __VA_ARGS__ , PAD()), \
(uint32_t)GET_ARG(5, ## __VA_ARGS__ , PAD()), (uint32_t)GET_ARG(6, ## __VA_ARGS__ , PAD()),(uint32_t)GET_ARG(7, ## __VA_ARGS__ , PAD()), (uint32_t)GET_ARG(8, ## __VA_ARGS__ , PAD()), \
(uint32_t)GET_ARG(9, ## __VA_ARGS__ , PAD())))

/** @brief
    Internal API to build a sprintf diagnostic message. Not to be used directly.
    Use QAPI_MSG_SPRINTF for any number of arguments from 0 to 9.
    See the qapi_msg_sprintf() API for details.
*/
#define qapi_msg_sprintf(const_blk, num_args, ...) \
((qapi_Status_t) (_txm_module_system_call11) (TXM_QAPI_DIAG_MSG_SPRINTF, (uint32_t)const_blk, (uint32_t)num_args, \
(uint32_t)GET_ARG(1, ## __VA_ARGS__ , PAD()), (uint32_t)GET_ARG(2, ## __VA_ARGS__ , PAD()), (uint32_t)GET_ARG(3, ## __VA_ARGS__ , PAD()),(uint32_t)GET_ARG(4, ## __VA_ARGS__ , PAD()), \
(uint32_t)GET_ARG(5, ## __VA_ARGS__ , PAD()), (uint32_t)GET_ARG(6, ## __VA_ARGS__ , PAD()),(uint32_t)GET_ARG(7, ## __VA_ARGS__ , PAD()), (uint32_t)GET_ARG(8, ## __VA_ARGS__ , PAD()), \
(uint32_t)GET_ARG(9, ## __VA_ARGS__ , PAD())))


#elif defined QAPI_TXM_SOURCE_CODE    // KERNEL_MODE_DEFS

#include "diag.h"
#include "comdef.h"
#include "event_defs.h"
#include "event.h"
#include "diagcmd.h"
#include "diagpkt.h"
#include "log.h"
#include "msg.h"
#include "qurt_txm_qapi_fwk.h" // For TXM system calls
/* @brief
    Handler to be registered with a DAM framework. For any user space Diag QAPI
    call, this handler will be invoked by the kernel dispatcher with the TXM ID
    of the call and arguments.

    @param[in] request_ID  DIAG TXM ID.
    @param[in] arg1        Argument 1.
    @param[in] arg2        Argument 2.
    @param[in] arg3        Argument 3.
    @param[in] arg4        Argument 4.
    @param[in] arg5        Argument 5.
    @param[in] arg6        Argument 6.
    @param[in] arg7        Argument 7.
    @param[in] arg8        Argument 8.
    @param[in] arg9        Argument 9.
    @param[in] arg10       Argument 10.
    @param[in] arg11       Argument 11.
    @param[in] arg12       Argument 12.

    @return  QAPI status codes (defined in qapi_status.h).
*/
qapi_Status_t qapi_diag_handler(uint32_t request_ID, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5, uint32_t arg6, uint32_t arg7, uint32_t arg8, uint32_t arg9, uint32_t arg10, uint32_t arg11, uint32_t arg12);

/** @brief 
    Registers the user table given to the diagpkt master table and creates a
    new entry in diagpkt_user_space_table with user_space_tbl_ptr. Updates the
    port field of the master table entry with the index of its entry in
    diagpkt_user_space_table.
   
    @param[in] tbl_ptr             Structure for the diagnostics packet service
                                   master table to hold the client's table
                                   entries when the clients registers with the
                                   diagnostics packet services.
    @param[in] user_space_tbl_ptr  Structure for the diagnostics packet service
                                   user space table to hold the client's buffer
                                   details when the client registers with the
                                   diagnostics packet services.

    @return  QAPI status; see @xhyperref{hdr:QAPIStatust,QAPI Status Codes}.
*/
qapi_Status_t qapi_user_space_tbl_reg_append_proc(diagpkt_master_table_type * tbl_ptr, diagpkt_user_space_table_type *user_space_tbl_ptr);

/** @brief 
    Gets a unique delayed response ID that is to be used for the set of delayed
    responses generated for a single command.
   
    @param[in] delayed_rsp_id  Address of the variable that will be updated
                               with the delayed response ID from Diag.

   @return  QAPI status; see @xhyperref{hdr:QAPIStatust,QAPI Status Codes}.
*/
qapi_Status_t qapi_diagpkt_get_next_delayed_rsp_id(uint16_t* delayed_rsp_id);

/** @brief 
    Processes the user space client's response and commits the response if all
    the sanity checks are passed. In the case of a failure, it generates an
    error response.

    @param[in] outbuf    Client static buffer to which the client is to copy the
                         response to the command.
    @param[in] rsp_len   Length of the response copied to outbuf.
    @param[in] rsp_flag  Flag that respresents the type of response (immediate or
                         delayed) or any error code.

    @return  QAPI status; see @xhyperref{hdr:QAPIStatust,QAPI Status Codes}.
*/
qapi_Status_t qapi_diagpkt_commit(uint32_t* outbuf, uint32_t rsp_len, uint32_t rsp_flag);

/** @brief
    Internal API that is not to be used by clients directly. Use the QAPI_MSG()
    macro to log a debug message. There are also arguments under a va_args
    parameter (integer type) that are not shown in the protocol.

    @param[in] const_blk  Constant information stored for a message.
    @param[in] num_args   Number of arguments for the message.

    @return  QAPI status; see @xhyperref{hdr:QAPIStatust,QAPI Status Codes}.
*/
qapi_Status_t qapi_msg_send(const msg_const_type * const_blk, uint32_t num_args, ...);

/** @brief
    Internal API is not to be used by clients directly. Use the
    QAPI_MSG_SPRINTF() macro to log a debug message. There are also arguments
    under a va_args parameter (integer or string type) that are not shown in
    the protocol.

    @param[in] const_blk  Constant information stored for a message.
    @param[in] num_args   Number of arguments for the message.

    @return  QAPI status; see @xhyperref{hdr:QAPIStatust,QAPI Status Codes}.
*/
qapi_Status_t qapi_msg_sprintf(const msg_const_type * const_blk, uint32_t num_args,...);

/** @brief
    Logs an accumlated log entry. Header contents must be assigned by the
    caller before calling this function. Therefore, qapi_log_set_code(),
    qapi_log_set_length(), and qapi_log_set_timestamp() must be used before
    this call

    @param[in] ptr  Pointer to the client-allocated log packet.

    @return  QAPI status; see @xhyperref{hdr:QAPIStatust,QAPI Status Codes}.
*/
qapi_Status_t qapi_log_submit(void* ptr);

/** @brief
    Sets the length field in the specified log record.

    @param[in] ptr     Pointer to the client-allocated log packet.
    @param[in] length  Length of the client-allocated log packet.

    @return  QAPI status; see @xhyperref{hdr:QAPIStatust,QAPI Status Codes}.
*/
qapi_Status_t qapi_log_set_length(void* ptr, log_code_type length);

/** @brief
    Sets the code field in the specified log record.

    @param[in] ptr   Pointer to the client-allocated log packet.
    @param[in] code  Log code of the client-allocated log packet.

    @return  QAPI status; see @xhyperref{hdr:QAPIStatust,QAPI Status Codes}.
*/
qapi_Status_t qapi_log_set_code(void* ptr, log_code_type code);

/** @brief
    Sets the timestamp field in the specified log record.

    @param[in] plog_hdr_ptr  Pointer to the client-allocated log packet.

    @return  QAPI status; see @xhyperref{hdr:QAPIStatust,QAPI Status Codes}.
*/
qapi_Status_t qapi_log_set_timestamp(void* plog_hdr_ptr);

/** @brief
    Checks whether a particular code is enabled for logging.

    @param[in] code  Log code of the client-allocated log packet.

    @return  QAPI status; see @xhyperref{hdr:QAPIStatust,QAPI Status Codes}.
*/
qapi_Status_t qapi_log_status(log_code_type code);

/** @brief
    Reports an event without a payload.

    @param[in] event_id  Event ID of the event to be reported.

    @return  QAPI status; see @xhyperref{hdr:QAPIStatust,QAPI Status Codes}.
*/
qapi_Status_t qapi_event_report(event_id_enum_type event_id);

/** @brief
    Reports an event with a payload.

    @param[in] event_id  Event ID of the event to be reported.
    @param[in] length    Length of the event to be reported.
    @param[in] data      Payload of the event to be reported.

    @return  QAPI status; see @xhyperref{hdr:QAPIStatust,QAPI Status Codes}.
*/
qapi_Status_t qapi_event_report_payload(event_id_enum_type event_id, uint8_t length, void* data);

#endif

/** @} */ /* end_addtogroup qapi_diag */

#endif /* QAPI_DIAG_TXM_H */
