#ifndef QAPI_DATA_TXM_BASE_H
#define QAPI_DATA_TXM_BASE_H 

/**
  @file qapi_data_txm_base.h 
  @brief  Contains QAPI Driver ID mappings for Dataservices

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
 *  
 *
 *
 * when         who     what, where, why
 * ----------   ---     ------------------------------------------------
 ======================================================================*/
 

#ifdef __cplusplus
extern "C" {
#endif

#include "qapi_txm_base.h"

/*** Maximum IDs for dataservices is defined by macro TXM_QAPI_DATA_SERVICES_NUM_IDS ***/

#define  TXM_QAPI_DSS_BASE                        TXM_QAPI_DATA_SERVICES_BASE
#define  TXM_QAPI_DSS_NUM_IDS                     30

#define  TXM_QAPI_SOCKET_BASE                     TXM_QAPI_DSS_BASE + TXM_QAPI_DSS_NUM_IDS
#define  TXM_QAPI_SOCKET_NUM_IDS                  30

#define  TXM_QAPI_NET_BASE                        TXM_QAPI_SOCKET_BASE + TXM_QAPI_SOCKET_NUM_IDS
#define  TXM_QAPI_NET_NUM_IDS                     30

#define  TXM_QAPI_NET_SSL_BASE                    TXM_QAPI_NET_BASE + TXM_QAPI_NET_NUM_IDS
#define  TXM_QAPI_NET_SSL_NUM_IDS                 20

#define  TXM_QAPI_NET_DNSC_BASE                   TXM_QAPI_NET_SSL_BASE + TXM_QAPI_NET_SSL_NUM_IDS
#define  TXM_QAPI_NET_DNSC_NUM_IDS                20

#define  TXM_QAPI_NET_HTTP_BASE                   TXM_QAPI_NET_DNSC_BASE + TXM_QAPI_NET_DNSC_NUM_IDS
#define  TXM_QAPI_NET_HTTP_NUM_IDS                20

#define  TXM_QAPI_MQTT_BASE                       TXM_QAPI_NET_HTTP_BASE + TXM_QAPI_NET_HTTP_NUM_IDS
#define  TXM_QAPI_MQTT_NUM_IDS                    15

#define TXM_QAPI_DEVICE_INFO_BASE                 TXM_QAPI_MQTT_BASE + TXM_QAPI_MQTT_NUM_IDS
#define TXM_QAPI_DEVICE_INFO_NUM_IDS              5

#define TXM_QAPI_NET_LWM2M_BASE                   TXM_QAPI_DEVICE_INFO_BASE + TXM_QAPI_DEVICE_INFO_NUM_IDS
#define TXM_QAPI_NET_LWM2M_NUM_IDS                20

#define TXM_QAPI_ATFWD_BASE                       TXM_QAPI_NET_LWM2M_BASE + TXM_QAPI_NET_LWM2M_NUM_IDS
#define TXM_QAPI_ATFWD_NUM_IDS                    5

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif /* QAPI_TXM_BASE_H */
