#ifndef QAPI_PSM_H
#define QAPI_PSM_H 

/**
  @file qapi_psm.h
  @brief    PSM header for dynamic modules to interact with underlying PSM Daemon(Server).

  @details  Refer to psm_test.c for example usage of PSM with DAM

 EXTERNALIZED FUNCTIONS
  none

 INITIALIZATION AND SEQUENCING REQUIREMENTS
  none

 Copyright (c) 2017  by Qualcomm Technologies, Inc.  All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
 ======================================================================*/
/*======================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 * when       who     what, where, why
 * --------   ---     ----------------------------------------------------------
 * 17/03/17   rkr      Initial PSM QAPI
 ======================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#include "qapi_ril_base.h"

#ifdef  QAPI_TXM_MODULE     // USER_MODE_DEFS

typedef unsigned short word;

// PSM's version of the Julian time structure
typedef struct
{
   word year;            // Year [1980..2100]
   word month;           // Month of year [1..12]
   word day;             // Day of month [1..31]
   word hour;            // Hour of day [0..23]
   word minute;          // Minute of hour [0..59]
   word second;          // Second of minute [0..59]
   word day_of_week;     // Day of the week [0..6] Monday..Sunday
} pm_rtc_julian_type;

#else

#include "pmapp_rtc.h"

#endif


#include "qapi_psm_types.h"


// Driver ID defines
#define    TXM_QAPI_PSM_CLIENT_REGISTER      TXM_QAPI_PSM_BASE + 1
#define    TXM_QAPI_PSM_CLIENT_UNREGISTER    TXM_QAPI_PSM_BASE + 2
#define    TXM_QAPI_PSM_CLIENT_ENTER_PSM     TXM_QAPI_PSM_BASE + 3
#define    TXM_QAPI_PSM_CLIENT_ENTER_BACKOFF TXM_QAPI_PSM_BASE + 4
#define    TXM_QAPI_PSM_CLIENT_CANCEL_PSM    TXM_QAPI_PSM_BASE + 5
#define    TXM_QAPI_PSM_CLIENT_LOAD_MODEM    TXM_QAPI_PSM_BASE + 6
#define    TXM_QAPI_PSM_CLIENT_HC_ACK        TXM_QAPI_PSM_BASE + 7

#ifdef  QAPI_TXM_MODULE     // USER_MODE_DEFS

#define    qapi_PSM_Client_Register(a,b)      ((qapi_PSM_Status_t) (_txm_module_system_call12)(TXM_QAPI_PSM_CLIENT_REGISTER       , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define    qapi_PSM_Client_Unregister(a)      ((qapi_PSM_Status_t) (_txm_module_system_call12)(TXM_QAPI_PSM_CLIENT_UNREGISTER     , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define    qapi_PSM_Client_Enter_Psm(a,b)     ((qapi_PSM_Status_t) (_txm_module_system_call12)(TXM_QAPI_PSM_CLIENT_ENTER_PSM      , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define    qapi_PSM_Client_Enter_Backoff(a)   ((qapi_PSM_Status_t) (_txm_module_system_call12)(TXM_QAPI_PSM_CLIENT_ENTER_BACKOFF  , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define    qapi_PSM_Client_Cancel_Psm(a)      ((qapi_PSM_Status_t) (_txm_module_system_call12)(TXM_QAPI_PSM_CLIENT_CANCEL_PSM     , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define    qapi_PSM_Client_Load_Modem(a)      ((qapi_PSM_Status_t) (_txm_module_system_call12)(TXM_QAPI_PSM_CLIENT_LOAD_MODEM     , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define    qapi_PSM_Client_Hc_Ack(a)          ((qapi_PSM_Status_t) (_txm_module_system_call12)(TXM_QAPI_PSM_CLIENT_HC_ACK         , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#else

qapi_Status_t qapi_PSM_Handler(UINT id, UINT a1, UINT a2, UINT a3, UINT a4, UINT a5, UINT a6, UINT a7, UINT a8, UINT a9, UINT a10, UINT a11, UINT a12);


/*============================================================================
                qapi_PSM_Client_Register
============================================================================*/
/**
 *  @brief     Makes the app known to PSM server as a PSM aware application.
 *             This is the first API every PSM aware application need to call.
 *             Every application which needs network related functionality 
 *             should call this API.
 *
 *  @details Registering a client will enable the PSM aware application to vote
 *           for PSM time and readiness when desired. Callback will be used by
 *           PSM Server to inform application about all PSM events.
 *           A maximum of 20 clients can be registered at a time with server.
 *
 *  @param[out] client_id Integer ptr to store id of the registered client.
 *  @param[in] cb_func Callback function of type psm_client_cb_type. Server
 *                     invokes this function to inform client about PSM events.
 *                     PSM Events contain status and reason. Refer to
 *                     psm_status_type_e and psm_reject_reason_type_e.
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 *  - QAPI_ERR_PSM_WRONG_ARGUMENTS -- Any of the arguments are invalid or NULL.
 *  - QAPI_ERR_PSM_GENERIC_FAILURE -- Registration failed because of max client limit(20).
 *  - QAPI_ERR_ESPIPE -- Some file descriptors (like pipes and FIFOs) are not seekable.
 */
qapi_Status_t qapi_PSM_Client_Register(int32_t *client_id, psm_client_cb_type cb_func);

/*============================================================================
                qapi_PSM_Client_Unregister
============================================================================*/
/**
 *  @brief Unregisters the PSM aware application with the PSM Server.
 *         Callback registered with the Server by the application will no longer
 *         be used to send any messages by the Server.
 *
 *  @details Unregistered applications cannot vote for PSM. Re registration
 *           can be done using qapi_PSM_Client_Register call.
 *           Unregistered PSM aware applications should be prepared for device
 *           shutdown without any further information.
 *
 *  @param[in] client_id Client ID obtained during registration.
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 *  - QAPI_ERR_PSM_APP_NOT_REGISTERED -- Invalid client ID.
 *  - QAPI_ERR_PSM_GENERIC_FAILURE -- Communication failed with Server.
 */
qapi_Status_t qapi_PSM_Client_Unregister(int32_t client_id);

/*============================================================================
                qapi_PSM_Client_Enter_Psm
============================================================================*/
/**
 *  @brief Used by app to notify its desire to enter PSM mode.
 *
 *  @details Application needs to pass active_time in secs, time in PSM mode,
 *           whether next wake up is for measurement purpose or access network.
 *           PSM time can will be accepted in either broken down format or in secs.
 *           PSM Aware application will be blocking PSM entry if this API is not 
 *           called indefinitely.
 *
 *  @param[in] client_id Client ID obtained during registration.
 *  @param[in] psm_info Ptr to a psm_info_type struct consisting of Active Time,
 *             Next Wakeup time(Time in PSM) and next wakeup type.
 *             Based on wakeup type, Server will decide for loading modem as
 *             part of bootup. 
 *             Active time will be overridden to 0 in case the Modem has already sent
 *             AUTOREADY indication to Server.
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 *  - QAPI_ERR_PSM_WRONG_ARGUMENTS -- Any of the arguments are invalid or NULL.
 *  - QAPI_ERR_PSM_APP_NOT_REGISTERED -- Invalid client ID.
 *  - QAPI_ERR_PSM_GENERIC_FAILURE -- Communication failed with Server.
 */
qapi_Status_t qapi_PSM_Client_Enter_Psm(int32_t client_id, psm_info_type *psm_info);

/*============================================================================
                qapi_PSM_Client_Enter_Backoff
============================================================================*/
/**
 *  @brief Used by app to notify its desire to enter PSM mode due to 
 *         Network Out Of Service or MTC server not reachable.
 *
 *  @details Duration for which app want to enter into PSM mode is 
 *           decided by the PSM server based on the NV item configuration.
 *           NV73784 - psm_duration_due_to_oos
 *           In case where there is no PSM aware application registered, Server
 *           will enter device to PSM state independently.
 *           PSM Aware can even decide to use Enter PSM API with desired time
 *           on recieving such status indications.
 *
 *
 *  @param[in] client_id Client ID obtained during registration.
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 *  - QAPI_ERR_PSM_APP_NOT_REGISTERED -- Invalid client ID.
 *  - QAPI_ERR_PSM_GENERIC_FAILURE -- Communication failed with Server.
 */
 qapi_Status_t qapi_PSM_Client_Enter_Backoff(int32_t client_id);

/*============================================================================
                qapi_PSM_Client_Cancel_Psm
============================================================================*/
/**
 *  @brief Withdraw a previous request to enter PSM
 * 
 *
 *  @param[in] client_id Client ID obtained during registration.
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 *  - QAPI_ERR_PSM_APP_NOT_REGISTERED -- Invalid client ID.
 *  - QAPI_ERR_PSM_GENERIC_FAILURE -- Communication failed with Server.
 */
qapi_Status_t qapi_PSM_Client_Cancel_Psm(int32_t client_id);

/*============================================================================
                qapi_PSM_Client_Load_Modem
============================================================================*/
/**
 *  @brief Request the PSM Server to load modem if not already (PIL based flavors only)
 *
 *  @details PSM aware applications can load modem dynamically based upon
 *           use case to save power. Applications will be informed through
 *           callback about modem loading success/failure.
 *           Further, applications can vote for modem loading in next bootup
 *           through the qapi_PSM_Client_Enter_Psm call.
 *
 *  @param[in] client_id Client ID obtained during registration.
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 *  - QAPI_ERR_PSM_APP_NOT_REGISTERED -- Invalid client ID.
 *  - QAPI_ERR_PSM_GENERIC_FAILURE -- Communication failed with Server.
 */
qapi_Status_t qapi_PSM_Client_Load_Modem(int32_t client_id);

/*============================================================================
                qapi_PSM_Client_Hc_Ack
============================================================================*/
/**
 *  @brief Application health check acknowledge API. 
 *         PSM aware applications need to call this API everytime it receives 
 *         PSM_STATUS_HEALTH_CHECK event.
 *
 *  @details This API ensures that every registered PSM aware application is
 *           alive, functioning and not stuck in a deadlock situation.
 *           Periodically, PSM Server uses the callback to send 
 *           PSM_STATUS_HEALTH_CHECK event. Application has to call this API
 *           to acknowledge the working.
 *           On failing to respond to Health Check, it will be treated as a
 *           dead application and vote for PSM on behalf of the dead application
 *           Time in PSM will be as configured in NV Settings.
 *           NV73784 - psm_duration_due_to_oos
 *
 *  @param[in] client_id Client ID obtained during registration.
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 *  - QAPI_ERR_PSM_APP_NOT_REGISTERED -- Invalid client ID.
 *  - QAPI_ERR_PSM_GENERIC_FAILURE -- Communication failed with Server.
 */
qapi_Status_t qapi_PSM_Client_Hc_Ack(int32_t client_id);




#endif

#endif /* QAPI_PSM_H */


