#ifndef QAPI_ALI_IOT_HAL_H
#define QAPI_ALI_IOT_HAL_H
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

#define TXM_QAPI_IOT_HAL_MUTEXCREATEP                        TXM_QAPI_IOT_HAL_BASE+ 0
#define TXM_QAPI_IOT_HAL_MUTEXDESTROY                        TXM_QAPI_IOT_HAL_BASE+ 1
#define TXM_QAPI_IOT_HAL_MUTEXLOCK                           TXM_QAPI_IOT_HAL_BASE+ 2
#define TXM_QAPI_IOT_HAL_MUTEXUNLOCK                         TXM_QAPI_IOT_HAL_BASE+ 3
#define TXM_QAPI_IOT_HAL_MALLOC                              TXM_QAPI_IOT_HAL_BASE+ 4 
#define TXM_QAPI_IOT_HAL_FREE                                TXM_QAPI_IOT_HAL_BASE+ 5
#define TXM_QAPI_IOT_HAL_UPTIMEMS                            TXM_QAPI_IOT_HAL_BASE+ 6 
#define TXM_QAPI_IOT_HAL_SLEEPMS                             TXM_QAPI_IOT_HAL_BASE+ 7
#define TXM_QAPI_IOT_HAL_GETPARTNERID                        TXM_QAPI_IOT_HAL_BASE+ 8 
#define TXM_QAPI_IOT_HAL_TCP_ESTABLISH                       TXM_QAPI_IOT_HAL_BASE+ 9
#define TXM_QAPI_IOT_HAL_TCP_DESTROY                         TXM_QAPI_IOT_HAL_BASE+ 10
#define TXM_QAPI_IOT_HAL_TCP_WRITE                           TXM_QAPI_IOT_HAL_BASE+ 11
#define TXM_QAPI_IOT_HAL_TCP_READ                            TXM_QAPI_IOT_HAL_BASE+ 12
#define TXM_QAPI_IOT_HAL_SSL_ESTABLISH                       TXM_QAPI_IOT_HAL_BASE+ 13
#define TXM_QAPI_IOT_HAL_SSL_DESTROY                         TXM_QAPI_IOT_HAL_BASE+ 14
#define TXM_QAPI_IOT_HAL_SSL_WRITE                           TXM_QAPI_IOT_HAL_BASE+ 15
#define TXM_QAPI_IOT_HAL_SSL_READ                            TXM_QAPI_IOT_HAL_BASE+ 16 
#define TXM_QAPI_IOT_HAL_UDP_CREATE                          TXM_QAPI_IOT_HAL_BASE+ 17
#define TXM_QAPI_IOT_HAL_UDP_CLOSE                           TXM_QAPI_IOT_HAL_BASE+ 18 
#define TXM_QAPI_IOT_HAL_UDP_WRITE                           TXM_QAPI_IOT_HAL_BASE+ 19
#define TXM_QAPI_IOT_HAL_UDP_READ                            TXM_QAPI_IOT_HAL_BASE+ 20
#define TXM_QAPI_IOT_HAL_UDP_READTIMEOUT                     TXM_QAPI_IOT_HAL_BASE+ 21
#define TXM_QAPI_IOT_HAL_UDP_RESOLVEADDRESS                  TXM_QAPI_IOT_HAL_BASE+ 22
#define TXM_QAPI_IOT_HAL_DTLSSESSION_FREE                    TXM_QAPI_IOT_HAL_BASE+ 23
#define TXM_QAPI_IOT_HAL_DTLSSESSION_INIT                    TXM_QAPI_IOT_HAL_BASE+ 24
#define TXM_QAPI_IOT_HAL_DTLSSESSION_CREATE                  TXM_QAPI_IOT_HAL_BASE+ 25 
#define TXM_QAPI_IOT_HAL_DTLSSESSION_WRITE                   TXM_QAPI_IOT_HAL_BASE+ 26
#define TXM_QAPI_IOT_HAL_DTLSSESSION_READ                    TXM_QAPI_IOT_HAL_BASE+ 27
#if defined QAPI_TXM_MODULE

#define   HAL_MutexCreate()  \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_MUTEXCREATEP,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define     HAL_MutexDestroy(mutex)  \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_MUTEXDESTROY,\
    (ULONG) mutex,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define      HAL_MutexLock(mutex) \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_MUTEXLOCK,\
    (ULONG) mutex,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define    HAL_MutexUnlock(mutex) \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_MUTEXUNLOCK,\
    (ULONG) mutex,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define         HAL_Malloc(size) \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_MALLOC,\
    (ULONG) size,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))
 
#define     HAL_Free(ptr)  \
	( (_txm_module_system_call12)( TXM_QAPI_IOT_HAL_FREE,\
    (ULONG) ptr,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define      HAL_UptimeMs()  \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_UPTIMEMS,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))
 
#define    	HAL_SleepMs(ms) \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_SLEEPMS ,\
    (ULONG) ms,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define     HAL_GetPartnerID(pid_str)  \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_GETPARTNERID ,\
    (ULONG) pid_str,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))
 
#define     HAL_TCP_Establish(host, port)  \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_TCP_ESTABLISH ,\
    (ULONG) host,(ULONG) port, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define   HAL_TCP_Destroy( fd )     \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_TCP_DESTROY,\
    (ULONG) fd,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define   HAL_TCP_Write(fd,buf,len,timeout_ms) \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_TCP_WRITE,\
    (ULONG) fd,(ULONG) buf, (ULONG) len, (ULONG) timeout_ms,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define   HAL_TCP_Read( fd,buf,len,timeout_ms)    \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_TCP_READ ,\
    (ULONG) fd,(ULONG) buf, (ULONG) len, (ULONG) timeout_ms,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define     HAL_SSL_Establish(host,port,ca_crt,ca_crt_len)  \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_SSL_ESTABLISH ,\
    (ULONG) host,(ULONG) port, (ULONG) ca_crt, (ULONG) ca_crt_len,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define   HAL_SSL_Destroy( handle)   \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_SSL_DESTROY,\
    (ULONG) handle,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define    HAL_SSL_Write(handle, buf,len,timeout_ms) \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_SSL_WRITE,\
    (ULONG) handle,(ULONG) buf, (ULONG) len, (ULONG) timeout_ms,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define     HAL_SSL_Read(handle, buf, len,timeout_ms)       \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_SSL_READ,\
    (ULONG) handle,(ULONG)buf, (ULONG) len, (ULONG) timeout_ms,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))
 
#define    HAL_UDP_create(p_socket)       \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_UDP_CREATE,\
    (ULONG) p_socket,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define     HAL_UDP_close(p_socket)  \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_UDP_CLOSE,\
    (ULONG) p_socket,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))
 
#define    HAL_UDP_write(p_socket,p_remote,p_data,datalen)    \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_UDP_WRITE,\
    (ULONG) p_socket,(ULONG) p_remote, (ULONG) p_data, (ULONG) datalen,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define  HAL_UDP_read(p_socket,p_remote,p_data,datalen)            \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_UDP_READ,\
    (ULONG) p_socket,(ULONG) p_remote, (ULONG)p_remote, (ULONG) datalen,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define  HAL_UDP_readTimeout(p_socket,p_remote,p_data,datalen,timeout )   \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_UDP_READTIMEOUT,\
    (ULONG) p_socket,(ULONG) p_remote, (ULONG) p_data, (ULONG) datalen,(ULONG) timeout,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define      HAL_UDP_resolveAddress(p_host,addr)       \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_UDP_RESOLVEADDRESS,\
    (ULONG) p_host,(ULONG) addr, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define       HAL_DTLSSession_free(context)    \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_DTLSSESSION_FREE,\
    (ULONG) context,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define    HAL_DTLSSession_init() \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_DTLSSESSION_INIT,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define       HAL_DTLSSession_create(context, p_options)  \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_DTLSSESSION_CREATE,\
    (ULONG) context,(ULONG) p_options, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))
 
#define   HAL_DTLSSession_write(context,p_data,p_datalen)  \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_DTLSSESSION_WRITE,\
    (ULONG) context,(ULONG) p_data, (ULONG) p_datalen, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define   HAL_DTLSSession_read(context,p_data,p_datalen,timeout)  \
	( (_txm_module_system_call12)(TXM_QAPI_IOT_HAL_DTLSSESSION_READ,\
    (ULONG) context,(ULONG) p_data, (ULONG) p_datalen, (ULONG) timeout,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#elif defined QAPI_TXM_SOURCE_CODE
#else

  #error "No QAPI flags defined"

#endif

#endif /** QAPI_ALI_IOT_HAL_H */


