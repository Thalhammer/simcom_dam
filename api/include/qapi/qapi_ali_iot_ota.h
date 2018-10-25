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



#ifndef __QAPI_ALI_IOT_OTA_H__
#define __QAPI_ALI_IOT_OTA_H__
#if defined(__cplusplus)
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

#define OTA_CH_SIGNAL_MQTT      (1)
#define OTA_CH_SIGNAL_COAP      (0)
#define OTA_CH_FETCH_HTTP       (1)


typedef enum {

    IOT_OTAE_GENERAL = -1,
    IOT_OTAE_INVALID_PARAM = -2,
    IOT_OTAE_INVALID_STATE = -3,
    IOT_OTAE_STR_TOO_LONG = -4,
    IOT_OTAE_FETCH_FAILED = -5,
    IOT_OTAE_NOMEM = -6,
    IOT_OTAE_OSC_FAILED = -7,
    IOT_OTAE_NONE = 0,

} IOT_OTA_Err_t;


//State of OTA
typedef enum {
    IOT_OTAS_UNINITED = 0,  //Uninitialized State
    IOT_OTAS_INITED,        //Initialized State
    IOT_OTAS_FETCHING,      //Fetching firmware
    IOT_OTAS_FETCHED        //Fetching firmware finish
} IOT_OTA_State_t;


//Progress of OTA
typedef enum {

    /* Burn firmware file failed */
    IOT_OTAP_BURN_FAILED = -4,

    /* Check firmware file failed */
    IOT_OTAP_CHECK_FALIED = -3,

    /* Fetch firmware file failed */
    IOT_OTAP_FETCH_FAILED = -2,

    /* Initialized failed */
    IOT_OTAP_GENERAL_FAILED = -1,


    /* [0, 100], percentage of fetch progress */

    /* The minimum percentage of fetch progress */
    IOT_OTAP_FETCH_PERCENTAGE_MIN = 0,

    /* The maximum percentage of fetch progress */
    IOT_OTAP_FETCH_PERCENTAGE_MAX = 100

} IOT_OTA_Progress_t;


typedef enum {

    IOT_OTAG_FETCHED_SIZE,     //option for get already fetched size
    IOT_OTAG_FILE_SIZE,        //size of file
    IOT_OTAG_MD5SUM,           //md5 in string format
    IOT_OTAG_VERSION,          //version in string format
    IOT_OTAG_CHECK_FIRMWARE    //Check firmware is valid or not

} IOT_OTA_CmdType_t;
#if defined QAPI_TXM_MODULE
 #define IOT_OTA_Init(product_key, device_name,ch_signal)\
    ( (_txm_module_system_call12)(TXM_QAPI_IOT_OTA_INIT,\
    (ULONG) product_key,(ULONG) device_name, (ULONG) ch_signal, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

 #define IOT_OTA_Deinit(handle)\
    ( (_txm_module_system_call12)(TXM_QAPI_IOT_OTA_DEINIT,\
    (ULONG) handle,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

 #define IOT_OTA_ReportVersion(handle,version)\
    ( (_txm_module_system_call12)(TXM_QAPI_IOT_OTA_REPORTVERSION,\
    (ULONG) handle,(ULONG) version, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))
/*SIMCOM zhangwei 2018-01-11 fixed iot qapi bug  at ticket/26 begin*/
 #define IOT_OTA_ReportProgress(handle,progress,msg)\
    ( (_txm_module_kernel_call_dispatcher)( TXM_QAPI_IOT_OTA_REPORTPROGRESS,\
    (ULONG) handle,(ULONG) progress, (ULONG) msg, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))
/*SIMCOM zhangwei 2018-01-11 fixed iot qapi bug  at ticket/26 end*/

 #define IOT_OTA_IsFetching(handle)\
    ( (_txm_module_system_call12)( TXM_QAPI_IOT_OTA_ISFETCHING ,\
    (ULONG) handle,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

 #define IOT_OTA_IsFetchFinish(handle)\
    ( (_txm_module_system_call12)(TXM_QAPI_IOT_OTA_ISFETCHFINISH,\
    (ULONG) handle,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

 #define IOT_OTA_FetchYield(handle, buf, buf_len, timeout_s)\
    ( (_txm_module_system_call12)(TXM_QAPI_IOT_OTA_FETCHYIELD,\
    (ULONG) handle,(ULONG) buf, (ULONG) buf_len, (ULONG) timeout_s,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

 #define IOT_OTA_Ioctl(handle,type,buf, buf_len)\
    ( (_txm_module_system_call12)(TXM_QAPI_IOT_OTA_FETCHYIELD,\
    (ULONG) handle,(ULONG) type, (ULONG) buf, (ULONG) buf_len,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

 #define OTA_Err_t IOT_OTA_GetLastError(handle)\
    ( (_txm_module_system_call12)(TXM_QAPI_IOT_OTA_GETLASTERROR,\
    (ULONG) handle,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#elif defined QAPI_TXM_SOURCE_CODE

/**
 * @brief Initialize OTA module, and return handle.
 *        The MQTT client must be construct before calling this interface.
 *
 * @param [in] product_key, specify the product key.
 * @param [in] device_name, specify the device name.
 * @param [in] ch_signal, specify the signal channel.
 *
 * @return 0, successful; -1, failed.
 */
void *IOT_OTA_Init(const char *product_key, const char *device_name, void *ch_signal);


/**
 * @brief Deinitialize OTA module specified by the @handle, and release the related resource.
 *        You must call this interface to release resource if reboot is not invoked after downloading.
 *
 * @param [in] handle, specify the OTA module.
 *
 * @return 0, successful; < 0, failed, the value is error code.
 */
int IOT_OTA_Deinit(void *handle);


/**
 * @brief Report firmware version information to OTA server (optional).
 *        NOTE: please
 *
 * @param [in] handle, specify the OTA module.
 * @param [in] version, specify the firmware version in string format.
 *
 * @return 0, successful; < 0, failed, the value is error code.
 */
int IOT_OTA_ReportVersion(void *handle, const char *version);


/**
 * @brief Report detail progress to OTA server (optional).
 *        NOTE: please
 *
 * @param [in] handle, specify the OTA module.
 * @param [in] progress, specify the progress defined by @IOT_OTA_Progress_t.
 * @param [in] msg, detail progress information in string.
 *
 * @return 0, successful; < 0, failed, the value is error code.
 */
int IOT_OTA_ReportProgress(void *handle, IOT_OTA_Progress_t progress, const char *msg);


/**
 * @brief Check whether is on fetching state
 *
 * @param [in] handle, specify the OTA module.
 *
 * @return true, yes; false, no.
 */
bool IOT_OTA_IsFetching(void *handle);


/**
 * @brief Check whether is on end-of-fetch state.
 *
 * @param [in] handle, specify the OTA module.
 *
 * @return true, yes; -1, false.
 */
bool IOT_OTA_IsFetchFinish(void *handle);


/**
 * @brief fetch firmware from remote server with specific timeout value.
 *        NOTE: If you want to download more faster, the bigger @buf should be given.
 *
 * @param [in] handle, specify the OTA module.
 * @param [out] buf, specify the space for storing firmware data.
 * @param [in] buf_len, specify the length of @buf in bytes.
 * @param [in] timeout_s, specify the timeout value in second.
 *
 * @return
   @verbatim
        < 0 : error occur.
          0 : No any data be downloaded in @timeout_ms timeout period.
   (0, len] : The length of data be downloaded in @timeout_ms timeout period in bytes.
   @endverbatim
 */
int IOT_OTA_FetchYield(void *handle, char *buf, uint32_t buf_len, uint32_t timeout_s);


/**
 * @brief Get OTA information specified by @type.
 *        By this interface, you can get information like state, size of file, md5 of file, etc.
 *
 * @param [in] handle, handle of the specific OTA
 * @param [in] type, specify what information you want, see detail @IOT_OTA_CmdType_t
 * @param [inout] buf, specify buffer for data exchange
 * @param [in] buf_len, specify the length of @buf in byte.
   @verbatim
      NOTE:
      1) When @type is IOT_OTAG_FETCHED_SIZE, @buf should be pointer of uint32_t, and @buf_len should be 4.
      2) When @type is IOT_OTAG_FILE_SIZE, @buf should be pointer of uint32_t, and @buf_len should be 4.
      3) When @type is IOT_OTAG_MD5SUM, @buf should be a buffer, and @buf_len should be 33.
      4) When @type is IOT_OTAG_VERSION, @buf should be a buffer, and @buf_len should be OTA_VERSION_LEN_MAX.
      5) When @type is IOT_OTAG_CHECK_FIRMWARE, @buf should be pointer of uint32_t, and @buf_len should be 4.
         0, firmware is invalid; 1, firmware is valid. 
   @endverbatim
 *
 * @return 0, successful; < 0, failed, the value is error code.
 */
int IOT_OTA_Ioctl(void *handle, IOT_OTA_CmdType_t type, void *buf, size_t buf_len);


/**
 * @brief Get last error code.
 *
 * @param [in] handle, specify the OTA module.
 *
 * @return The error code.
 */
IOT_OTA_Err_t IOT_OTA_GetLastError(void *handle);

#else

  #error "No QAPI flags defined"

#endif

#endif /*__QAPI_ALI_IOT_OTA_H__*/
