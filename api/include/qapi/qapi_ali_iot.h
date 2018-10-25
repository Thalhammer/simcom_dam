#ifndef QAPI_ALI_IOT_H
#define QAPI_ALI_IOT_H
/*
 * Copyright (c) 2014-2016 Alibaba Group. All rights reserved.
 * License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#if defined QAPI_TXM_MODULE
#include "qapi_ali_iot_txm_base.h"
#elif defined QAPI_TXM_SOURCE_CODE
#include "iot_ali/qapi_ali_iot_txm_base.h"
#endif
                                                                                                                           
#include <stdbool.h>

typedef enum _IOT_LogLevel {
    IOT_LOG_EMERG = 0,
    IOT_LOG_CRIT,
    IOT_LOG_ERROR,
    IOT_LOG_WARNING,
    IOT_LOG_INFO,
    IOT_LOG_DEBUG,
} IOT_LogLevel;

/*============================================================================
                USER_Mode_DEFS
============================================================================*/

                 /* Driver ID defines */

#define  TXM_QAPI_IOT_COAP_INIT                              TXM_QAPI_IOT_BASE  
#define  TXM_QAPI_IOT_COAP_DEINIT                            TXM_QAPI_IOT_BASE + 1
#define  TXM_QAPI_IOT_COAP_DEVICE_NAME_AUTH                  TXM_QAPI_IOT_BASE + 2
#define  TXM_QAPI_IOT_COAP_YIELD                             TXM_QAPI_IOT_BASE + 3
#define  TXM_QAPI_IOT_COAP_SEND_MESSAGE                      TXM_QAPI_IOT_BASE + 4
#define  TXM_QAPI_IOT_COAP_GET_MESSAGE_PAYLOAD               TXM_QAPI_IOT_BASE + 5
#define  TXM_QAPI_IOT_COAP_GET_MESSAGE_CODE                  TXM_QAPI_IOT_BASE + 6

#define  TXM_QAPI_IOT_MQTT_CONSTRUCT                         TXM_QAPI_IOT_BASE + 7
#define  TXM_QAPI_IOT_MQTT_DESTROY                           TXM_QAPI_IOT_BASE + 8
#define  TXM_QAPI_IOT_MQTT_YIELD                             TXM_QAPI_IOT_BASE + 9
#define  TXM_QAPI_IOT_MQTT_CHECK_STATE_NORMAL                TXM_QAPI_IOT_BASE + 10
#define  TXM_QAPI_IOT_MQTT_SUBSCRIBE                         TXM_QAPI_IOT_BASE + 11
#define  TXM_QAPI_IOT_MQTT_UNSUBSCRIBE                       TXM_QAPI_IOT_BASE + 12
#define  TXM_QAPI_IOT_MQTT_PUBLISH                           TXM_QAPI_IOT_BASE + 13
#define  TXM_QAPI_IOT_SETUP_CONNINFO                         TXM_QAPI_IOT_BASE + 14
#define  TXM_QAPI_IOT_OPEN_LOG                               TXM_QAPI_IOT_BASE + 15
#define  TXM_QAPI_IOT_CLOSE_LOG                              TXM_QAPI_IOT_BASE + 16
#define  TXM_QAPI_IOT_SET_LOG_LEVEL                          TXM_QAPI_IOT_BASE + 17
#define  TXM_QAPI_IOT_DUMP_MEMORY_STATS                      TXM_QAPI_IOT_BASE + 18

/*SIMCOM zhangwei 2017-10-26 add ota qapi and HAL base index  begin*/
#define   TXM_QAPI_IOT_OTA_INIT                       		TXM_QAPI_IOT_BASE + 21
#define   TXM_QAPI_IOT_OTA_DEINIT                   		TXM_QAPI_IOT_BASE + 22
#define   TXM_QAPI_IOT_OTA_REPORTVERSION           			TXM_QAPI_IOT_BASE + 23
#define   TXM_QAPI_IOT_OTA_REPORTPROGRESS          			TXM_QAPI_IOT_BASE + 24
#define   TXM_QAPI_IOT_OTA_ISFETCHING             			TXM_QAPI_IOT_BASE + 25
#define   TXM_QAPI_IOT_OTA_ISFETCHFINISH         			TXM_QAPI_IOT_BASE + 26
#define   TXM_QAPI_IOT_OTA_FETCHYIELD         				TXM_QAPI_IOT_BASE + 27
#define   TXM_QAPI_IOT_OTA_IOCTL             				TXM_QAPI_IOT_BASE + 28
#define   TXM_QAPI_IOT_OTA_GETLASTERROR             		TXM_QAPI_IOT_BASE + 29


/*SIMCOM zhangwei 2017-10-19 fixed bug end*/
/*SIMCOM zhangwei 2017-10-26 add ota qapi and HAL base index  end*/
#if defined QAPI_TXM_MODULE

#define IOT_SetupConnInfo(product_key, device_name, device_secret, info_ptr)\
    ((int) (_txm_module_system_call12)(TXM_QAPI_IOT_SETUP_CONNINFO,\
    (ULONG) product_key,(ULONG) device_name, (ULONG) device_secret, (ULONG) info_ptr,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define IOT_OpenLog(ident)\
    ( (_txm_module_system_call12)(TXM_QAPI_IOT_OPEN_LOG,\
    (ULONG) ident,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define IOT_CloseLog()\
    ( (_txm_module_system_call12)(TXM_QAPI_IOT_CLOSE_LOG,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define IOT_SetLogLevel(level)\
    ( (_txm_module_system_call12)(TXM_QAPI_IOT_SET_LOG_LEVEL,\
    (ULONG) level,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define IOT_DumpMemoryStats(level)\
    ( (_txm_module_system_call12)(TXM_QAPI_IOT_DUMP_MEMORY_STATS,\
    (ULONG) level,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))



/*SIMCOM zhangwei 2017-10-19 fixed bug end*/
#elif defined QAPI_TXM_SOURCE_CODE

void    IOT_OpenLog(const char *ident);
void    IOT_CloseLog(void);
void    IOT_SetLogLevel(IOT_LogLevel level);
void    IOT_DumpMemoryStats(IOT_LogLevel level);
int     IOT_SetupConnInfo(const char *product_key,
                          const char *device_name,
                          const char *device_secret,
                          void **info_ptr);

#else

  #error "No QAPI flags defined"

#endif

#include "qapi_ali_iot_ota.h" /*SIMCOM zhangwei 2017-10-24 fixed bug end*/
#include "qapi_ali_iot_coap.h"
#include "qapi_ali_iot_mqtt.h"
#include "qapi_ali_iot_device.h"
#endif /** QAPI_ALI_IOT_H */




