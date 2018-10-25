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
/*    txm_module.h                                        PORTABLE C      */ 
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
/*  06-01-2013     William E. Lamie         Initial Version 5.3           */ 
/*  01-01-2014     William E. Lamie         Modified comment(s),          */ 
/*                                            resulting in version 5.4    */ 
/*  01-01-2016     William E. Lamie         Modified comment(s), and      */ 
/*                                            fixed thread delete macro,  */
/*                                            resulting in version 5.5    */ 
/*  08-15-2016     Scott Larson             Modified comment(s),          */ 
/*                                            added shared memory API,    */ 
/*                                            added module instance       */ 
/*                                            maximum priority API,       */ 
/*                                            resulting in version 5.6    */ 
/*                                                                        */ 
/**************************************************************************/ 

#ifndef TXM_MODULE_H
#define TXM_MODULE_H


/*  Determine if module code is being compiled. If so, disable the remapping 
    of the ThreadX API.  */

#ifdef  TXM_MODULE

#ifndef TX_SOURCE_CODE
#define TX_SOURCE_CODE

/* Include the standard ThreadX API file.  */

#include "tx_api.h"
#undef  TX_SOURCE_CODE

#else 

/* Include the standard ThreadX API file.  */

#include "tx_api.h"
#endif  


/* Determine if NetX Duo is enabled.  */

#ifdef TXM_MODULE_ENABLE_NETX_DUO


#ifndef NX_SOURCE_CODE
#define NX_SOURCE_CODE

/* Include the standard NetX API file.  */

#include "nx_api.h"
#undef  NX_SOURCE_CODE
#else

/* Include the standard NetX API file.  */

#include "nx_api.h"

#endif
#endif


#else

/* Include the standard ThreadX API file.  */

#include "tx_api.h"

#endif

/* Include the module port specific file.  */

#include "txm_module_port.h"


#ifdef FX_FILEX_PRESENT
#include "fx_api.h"
typedef struct _FX_MEDIA { 
  unsigned long long _bSpace[256];
} FX_MEDIA;

#endif


/* Determine if a C++ compiler is being used.  If so, ensure that standard
   C is used to process the API information.  */

#ifdef __cplusplus

/* Yes, C++ compiler is present.  Use standard C.  */
extern   "C" {

#endif


/* Define the Module ID, which is used to indicate a module is valid.  */

#define TXM_MODULE_ID                                       0x4D4F4455


/* Define valid module states.  */

#define TXM_MODULE_LOADED                                   1
#define TXM_MODULE_STARTED                                  2
#define TXM_MODULE_STOPPING                                 3
#define TXM_MODULE_STOPPED                                  4
#define TXM_MODULE_UNLOADED                                 5


/* Define module manager error codes.  */

#define TXM_MODULE_ALIGNMENT_ERROR                          0xF0
#define TXM_MODULE_ALREADY_LOADED                           0xF1
#define TXM_MODULE_INVALID                                  0xF2
#define TXM_MODULE_INVALID_PROPERTIES                       0xF3
#define TXM_MODULE_INVALID_MEMORY                           0xF4
#define TXM_MODULE_INVALID_CALLBACK                         0xF5


/* Define the data area alignment mask, must be a power of 2.  */

#ifndef TXM_MODULE_DATA_ALIGNMENT
#define TXM_MODULE_DATA_ALIGNMENT                           4
#endif


/* Define the code area alignment mask, must be a power of 2.  */

#ifndef TXM_MODULE_CODE_ALIGNMENT
#define TXM_MODULE_CODE_ALIGNMENT                           4
#endif


/* Define module timeout for waiting for module to finish.  */

#ifndef TXM_MODULE_TIMEOUT
#define TXM_MODULE_TIMEOUT                                  100
#endif


/* Define module thread time-slice default.  */

#ifndef TXM_MODULE_TIME_SLICE
#define TXM_MODULE_TIME_SLICE                               4
#endif


/* Define maximum number of active module callbacks that can be handled at the 
   same time.  Valid values are 16, 32, 64, and 128.  */
   
#ifndef TXM_MODULE_MAX_CALLBACKS
#define TXM_MODULE_MAX_CALLBACKS                            16
#endif

#if TXM_MODULE_MAX_CALLBACKS != 16
#if TXM_MODULE_MAX_CALLBACKS != 32
#if TXM_MODULE_MAX_CALLBACKS != 64
#if TXM_MODULE_MAX_CALLBACKS != 128
#error "Invalid number of callbacks!  "
#endif
#endif
#endif
#endif


/* Define each module's callback queue message size. This is used to hold callback request message.  */

#ifndef TXM_MODULE_CALLBACKS_MESSAGE_SIZE
#define TXM_MODULE_CALLBACKS_MESSAGE_SIZE                   8       /* 8 32-bit words, or 32-byte messages.  */   
#endif


/* Define each module's callback queue depth. This is used to queue up incoming call back requests.  */

#ifndef TXM_MODULE_CALLBACKS_QUEUE_DEPTH
#define TXM_MODULE_CALLBACKS_QUEUE_DEPTH                    8       /* Number queued callback requests.  */   
#endif


/* Define the module manager thread's stack size.  */

#ifndef TXM_MODULE_MANAGER_THREAD_STACK_SIZE
#define TXM_MODULE_MANAGER_THREAD_STACK_SIZE                1024
#endif


/* Define the module manager thread's priority.  */

#ifndef TXM_MODULE_MANAGER_THREAD_PRIORITY
#define TXM_MODULE_MANAGER_THREAD_PRIORITY                  1
#endif


/* Define the module's callback handler thread's stack size.  */

#ifndef TXM_MODULE_CALLBACK_THREAD_STACK_SIZE
#define TXM_MODULE_CALLBACK_THREAD_STACK_SIZE                1024
#endif


/* Define object types for object search requests.  */

#define TXM_BLOCK_POOL_OBJECT                               1
#define TXM_BYTE_POOL_OBJECT                                2
#define TXM_EVENT_FLAGS_OBJECT                              3
#define TXM_MUTEX_OBJECT                                    4
#define TXM_QUEUE_OBJECT                                    5
#define TXM_SEMAPHORE_OBJECT                                6
#define TXM_THREAD_OBJECT                                   7
#define TXM_TIMER_OBJECT                                    8
#define TXM_IP_OBJECT                                       9
#define TXM_PACKET_POOL_OBJECT                              10
#define TXM_UDP_SOCKET_OBJECT                               11
#define TXM_TCP_SOCKET_OBJECT                               12


/* Define callback types.  */

#define TXM_TIMER_CALLBACK                                  0
#define TXM_EVENTS_SET_CALLBACK                             1
#define TXM_QUEUE_SEND_CALLBACK                             2
#define TXM_SEMAPHORE_PUT_CALLBACK                          3
#define TXM_THREAD_ENTRY_EXIT_CALLBACK                      4
#define TXM_ARP_RESPONSE_CALLBACK                           5
#define TXM_IP_ADDRESS_CHANGE_NOTIFY_CALLBACK               6
#define TXM_TCP_LISTEN_CALLBACK                             7
#define TXM_TCP_URGENT_DATA_CALLBACK                        8
#define TXM_TCP_DISCONNECT_CALLBACK                         9
#define TXM_TCP_SOCKET_RECEIVE_CALLBACK                     10
#define TXM_TCP_WINDOW_UPDATE_CALLBACK                      11
#define TXM_UDP_SOCKET_RECEIVE_CALLBACK                     12


/* Determine the ThreadX kernel API call IDs.  */

#define TXM_BLOCK_ALLOCATE_CALL                             1
#define TXM_BLOCK_POOL_CREATE_CALL                          2
#define TXM_BLOCK_POOL_DELETE_CALL                          3
#define TXM_BLOCK_POOL_INFO_GET_CALL                        4
#define TXM_BLOCK_POOL_PERFORMANCE_INFO_GET_CALL            5
#define TXM_BLOCK_POOL_PERFORMANCE_SYSTEM_INFO_GET_CALL     6
#define TXM_BLOCK_POOL_PRIORITIZE_CALL                      7
#define TXM_BLOCK_RELEASE_CALL                              8
#define TXM_BYTE_ALLOCATE_CALL                              9
#define TXM_BYTE_POOL_CREATE_CALL                           10
#define TXM_BYTE_POOL_DELETE_CALL                           11
#define TXM_BYTE_POOL_INFO_GET_CALL                         12
#define TXM_BYTE_POOL_PERFORMANCE_INFO_GET_CALL             13
#define TXM_BYTE_POOL_PERFORMANCE_SYSTEM_INFO_GET_CALL      14
#define TXM_BYTE_POOL_PRIORITIZE_CALL                       15
#define TXM_BYTE_RELEASE_CALL                               16
#define TXM_EVENT_FLAGS_CREATE_CALL                         17
#define TXM_EVENT_FLAGS_DELETE_CALL                         18
#define TXM_EVENT_FLAGS_GET_CALL                            19
#define TXM_EVENT_FLAGS_INFO_GET_CALL                       20
#define TXM_EVENT_FLAGS_PERFORMANCE_INFO_GET_CALL           21
#define TXM_EVENT_FLAGS_PERFORMANCE_SYSTEM_INFO_GET_CALL    22
#define TXM_EVENT_FLAGS_SET_CALL                            23
#define TXM_EVENT_FLAGS_SET_NOTIFY_CALL                     24
#define TXM_INTERRUPT_CONTROL_CALL                          25
#define TXM_MUTEX_CREATE_CALL                               26
#define TXM_MUTEX_DELETE_CALL                               27
#define TXM_MUTEX_GET_CALL                                  28
#define TXM_MUTEX_INFO_GET_CALL                             29
#define TXM_MUTEX_PERFORMANCE_INFO_GET_CALL                 30
#define TXM_MUTEX_PERFORMANCE_SYSTEM_INFO_GET_CALL          31
#define TXM_MUTEX_PRIORITIZE_CALL                           32
#define TXM_MUTEX_PUT_CALL                                  33
#define TXM_QUEUE_CREATE_CALL                               34
#define TXM_QUEUE_DELETE_CALL                               35
#define TXM_QUEUE_FLUSH_CALL                                36
#define TXM_QUEUE_FRONT_SEND_CALL                           37
#define TXM_QUEUE_INFO_GET_CALL                             38
#define TXM_QUEUE_PERFORMANCE_INFO_GET_CALL                 39
#define TXM_QUEUE_PERFORMANCE_SYSTEM_INFO_GET_CALL          40
#define TXM_QUEUE_PRIORITIZE_CALL                           41
#define TXM_QUEUE_RECEIVE_CALL                              42
#define TXM_QUEUE_SEND_CALL                                 43
#define TXM_QUEUE_SEND_NOTIFY_CALL                          44
#define TXM_SEMAPHORE_CEILING_PUT_CALL                      45
#define TXM_SEMAPHORE_CREATE_CALL                           46
#define TXM_SEMAPHORE_DELETE_CALL                           47
#define TXM_SEMAPHORE_GET_CALL                              48
#define TXM_SEMAPHORE_INFO_GET_CALL                         49
#define TXM_SEMAPHORE_PERFORMANCE_INFO_GET_CALL             50
#define TXM_SEMAPHORE_PERFORMANCE_SYSTEM_INFO_GET_CALL      51
#define TXM_SEMAPHORE_PRIORITIZE_CALL                       52
#define TXM_SEMAPHORE_PUT_CALL                              53
#define TXM_SEMAPHORE_PUT_NOTIFY_CALL                       54
#define TXM_THREAD_CREATE_CALL                              55
#define TXM_THREAD_DELETE_CALL                              56
#define TXM_THREAD_ENTRY_EXIT_NOTIFY_CALL                   57
#define TXM_THREAD_IDENTIFY_CALL                            58
#define TXM_THREAD_INFO_GET_CALL                            59
#define TXM_THREAD_PERFORMANCE_INFO_GET_CALL                60
#define TXM_THREAD_PERFORMANCE_SYSTEM_INFO_GET_CALL         61
#define TXM_THREAD_PREEMPTION_CHANGE_CALL                   62
#define TXM_THREAD_PRIORITY_CHANGE_CALL                     63
#define TXM_THREAD_RELINQUISH_CALL                          64
#define TXM_THREAD_RESET_CALL                               65
#define TXM_THREAD_RESUME_CALL                              66
#define TXM_THREAD_SLEEP_CALL                               67
#define TXM_THREAD_STACK_ERROR_NOTIFY_CALL                  68
#define TXM_THREAD_SUSPEND_CALL                             69
#define TXM_THREAD_TERMINATE_CALL                           70
#define TXM_THREAD_TIME_SLICE_CHANGE_CALL                   71
#define TXM_THREAD_WAIT_ABORT_CALL                          72
#define TXM_TIME_GET_CALL                                   73
#define TXM_TIME_SET_CALL                                   74
#define TXM_TIMER_ACTIVATE_CALL                             75
#define TXM_TIMER_CHANGE_CALL                               76
#define TXM_TIMER_CREATE_CALL                               77
#define TXM_TIMER_DEACTIVATE_CALL                           78
#define TXM_TIMER_DELETE_CALL                               79
#define TXM_TIMER_INFO_GET_CALL                             80
#define TXM_TIMER_PERFORMANCE_INFO_GET_CALL                 81
#define TXM_TIMER_PERFORMANCE_SYSTEM_INFO_GET_CALL          82
#define TXM_TRACE_ENABLE_CALL                               83
#define TXM_TRACE_EVENT_FILTER_CALL                         84
#define TXM_TRACE_EVENT_UNFILTER_CALL                       85
#define TXM_TRACE_DISABLE_CALL                              86
#define TXM_TRACE_ISR_ENTER_INSERT_CALL                     87
#define TXM_TRACE_ISR_EXIT_INSERT_CALL                      88
#define TXM_TRACE_BUFFER_FULL_NOTIFY_CALL                   89
#define TXM_TRACE_USER_EVENT_INSERT_CALL                    90
#define TXM_THREAD_SYSTEM_SUSPEND_CALL                      91
#define TXM_MODULE_OBJECT_POINTER_GET_CALL                  92
#define TXM_MODULE_OBJECT_ALLOCATE_CALL                     93
#define TXM_MODULE_OBJECT_DEALLOCATE_CALL                   94


/* Determine the NetX TCP/IP API call IDs.  */

#define TXM_ARP_DYNAMIC_ENTRIES_INVALIDATE_CALL             100
#define TXM_ARP_DYNAMIC_ENTRY_SET_CALL                      101
#define TXM_ARP_ENABLE_CALL                                 102
#define TXM_ARP_GRATUITOUS_SEND_CALL                        103
#define TXM_ARP_HARDWARE_ADDRESS_FIND_CALL                  104
#define TXM_ARP_INFO_GET_CALL                               105
#define TXM_ARP_IP_ADDRESS_FIND_CALL                        106
#define TXM_ARP_STATIC_ENTRIES_DELETE_CALL                  107
#define TXM_ARP_STATIC_ENTRY_CREATE_CALL                    108
#define TXM_ARP_STATIC_ENTRY_DELETE_CALL                    109
#define TXM_ICMP_ENABLE_CALL                                110
#define TXM_ICMP_INFO_GET_CALL                              111
#define TXM_ICMP_PING_CALL                                  112
#define TXM_ICMP_RESERVED_CALL                              113
#define TXM_IGMP_ENABLE_CALL                                114
#define TXM_IGMP_INFO_GET_CALL                              115
#define TXM_IGMP_LOOPBACK_DISABLE_CALL                      116
#define TXM_IGMP_LOOPBACK_ENABLE_CALL                       117
#define TXM_IGMP_MULTICAST_JOIN_CALL                        118
#define TXM_IGMP_MULTICAST_INTERFACE_JOIN_CALL              119
#define TXM_IGMP_MULTICAST_LEAVE_CALL                       120
#define TXM_IP_ADDRESS_CHANGE_NOTIFY_CALL                   121
#define TXM_IP_ADDRESS_GET_CALL                             122
#define TXM_IP_ADDRESS_SET_CALL                             123
#define TXM_IP_INTERFACE_ADDRESS_GET_CALL                   124
#define TXM_IP_INTERFACE_ADDRESS_SET_CALL                   125
#define TXM_IP_INTERFACE_INFO_GET_CALL                      126
#define TXM_IP_CREATE_CALL                                  127
#define TXM_IP_DELETE_CALL                                  128
#define TXM_IP_DRIVER_DIRECT_COMMAND_CALL                   129
#define TXM_IP_DRIVER_INTERFACE_DIRECT_COMMAND_CALL         130
#define TXM_IP_FORWARDING_DISABLE_CALL                      131
#define TXM_IP_FORWARDING_ENABLE_CALL                       132
#define TXM_IP_FRAGMENT_DISABLE_CALL                        133
#define TXM_IP_FRAGMENT_ENABLE_CALL                         134
#define TXM_IP_GATEWAY_ADDRESS_SET_CALL                     135
#define TXM_IP_INFO_GET_CALL                                136
#define TXM_IP_INTERFACE_ATTACH_CALL                        137
#define TXM_IP_INTERFACE_STATUS_CHECK_CALL                  138
#define TXM_IP_MAX_PAYLOAD_SIZE_FIND_CALL                   139
#define TXM_IP_RAW_PACKET_DISABLE_CALL                      140
#define TXM_IP_RAW_PACKET_ENABLE_CALL                       141
#define TXM_IP_RAW_PACKET_RECEIVE_CALL                      142
#define TXM_IP_RAW_PACKET_SEND_CALL                         143
#define TXM_IP_RAW_PACKET_SOURCE_SEND_CALL                  144
#define TXM_IP_STATIC_ROUTE_ADD_CALL                        145
#define TXM_IP_STATIC_ROUTE_DELETE_CALL                     146
#define TXM_IP_STATUS_CHECK_CALL                            147
#define TXM_PACKET_ALLOCATE_CALL                            148
#define TXM_PACKET_COPY_CALL                                149
#define TXM_PACKET_DATA_APPEND_CALL                         150
#define TXM_PACKET_DATA_EXTRACT_OFFSET_CALL                 151
#define TXM_PACKET_DATA_RETRIEVE_CALL                       152
#define TXM_PACKET_LENGTH_GET_CALL                          153
#define TXM_PACKET_POOL_CREATE_CALL                         154
#define TXM_PACKET_POOL_DELETE_CALL                         155
#define TXM_PACKET_POOL_INFO_GET_CALL                       156
#define TXM_PACKET_RELEASE_CALL                             157
#define TXM_PACKET_TRANSMIT_RELEASE_CALL                    158
#define TXM_RARP_DISABLE_CALL                               159
#define TXM_RARP_ENABLE_CALL                                160
#define TXM_RARP_INFO_GET_CALL                              161
#define TXM_SYSTEM_INITIALIZE_CALL                          162
#define TXM_TCP_CLIENT_SOCKET_BIND_CALL                     163
#define TXM_TCP_CLIENT_SOCKET_CONNECT_CALL                  164
#define TXM_TCP_CLIENT_SOCKET_PORT_GET_CALL                 165
#define TXM_TCP_CLIENT_SOCKET_UNBIND_CALL                   166
#define TXM_TCP_ENABLE_CALL                                 167
#define TXM_TCP_FREE_PORT_FIND_CALL                         168
#define TXM_TCP_INFO_GET_CALL                               169
#define TXM_TCP_SERVER_SOCKET_ACCEPT_CALL                   170
#define TXM_TCP_SERVER_SOCKET_LISTEN_CALL                   171
#define TXM_TCP_SERVER_SOCKET_RELISTEN_CALL                 172
#define TXM_TCP_SERVER_SOCKET_UNACCEPT_CALL                 173
#define TXM_TCP_SERVER_SOCKET_UNLISTEN_CALL                 174
#define TXM_TCP_SOCKET_BYTES_AVAILABLE_CALL                 175
#define TXM_TCP_SOCKET_CREATE_CALL                          176
#define TXM_TCP_SOCKET_DELETE_CALL                          177
#define TXM_TCP_SOCKET_DISCONNECT_CALL                      178
#define TXM_TCP_SOCKET_INFO_GET_CALL                        179
#define TXM_TCP_SOCKET_MSS_GET_CALL                         180
#define TXM_TCP_SOCKET_MSS_PEER_GET_CALL                    181
#define TXM_TCP_SOCKET_MSS_SET_CALL                         182
#define TXM_TCP_SOCKET_PEER_INFO_GET_CALL                   183
#define TXM_TCP_SOCKET_RECEIVE_CALL                         184
#define TXM_TCP_SOCKET_RECEIVE_NOTIFY_CALL                  185
#define TXM_TCP_SOCKET_SEND_CALL                            186
#define TXM_TCP_SOCKET_STATE_WAIT_CALL                      187
#define TXM_TCP_SOCKET_TRANSMIT_CONFIGURE_CALL              188
#define TXM_TCP_SOCKET_WINDOW_UPDATE_NOFITY_SET_CALL        189
#define TXM_UDP_ENABLE_CALL                                 190
#define TXM_UDP_FREE_PORT_FIND_CALL                         191
#define TXM_UPD_INFO_GET_CALL                               192
#define TXM_UDP_PACKET_INFO_EXTRACT_CALL                    193
#define TXM_UDP_SOCKET_BIND_CALL                            194
#define TXM_UDP_SOCKET_BYTES_AVAILABLE_CALL                 195
#define TXM_UDP_SOCKET_CHECKSUM_DISABLE_CALL                196
#define TXM_UDP_SOCKET_CHECKSUM_ENABLE_CALL                 197
#define TXM_UDP_SOCKET_CREATE_CALL                          198
#define TXM_UDP_SOCKET_DELETE_CALL                          199
#define TXM_UDP_SOCKET_INFO_GET_CALL                        200
#define TXM_UDP_SOCKET_PORT_GET_CALL                        201
#define TXM_UDP_SOCKET_RECEIVE_CALL                         202
#define TXM_UDP_SOCKET_RECEIVE_NOTIFY_CALL                  203
#define TXM_UDP_SOCKET_SEND_CALL                            204
#define TXM_UDP_SOCKET_SOURCE_SEND_CALL                     205
#define TXM_UDP_SOCKET_UNBIND_CALL                          206
#define TXM_UDP_SOURCE_EXTRACT_CALL                         207
#define TXM_DUO_ICMP_ENABLE_CALL                            208
#define TXM_DUO_ICMP_INTERFACE_PING_CALL                    209
#define TXM_DUO_ICMP_PING_CALL                              210
#define TXM_DUO_IP_RAW_PACKET_SOURCE_SEND_CALL              211
#define TXM_DUO_IP_RAW_PACKET_SEND_CALL                     212
#define TXM_DUO_IPV6_ADDRESS_DELETE_CALL                    213
#define TXM_DUO_IPV6_ADDRESS_GET_CALL                       214
#define TXM_DUO_IPV6_ADDRESS_SET_CALL                       215
#define TXM_DUO_IPV6_DEFAULT_ROUTER_ADD_CALL                216
#define TXM_DUO_IPV6_DEFAULT_ROUTER_DELETE_CALL             217
#define TXM_DUO_IPV6_DEFAULT_ROUTER_GET_CALL                218
#define TXM_DUO_IPV6_ENABLE_CALL                            219
#define TXM_DUO_ND_CACHE_ENTRY_DELETE_CALL                  220
#define TXM_DUO_ND_CACHE_ENTRY_SET_CALL                     221
#define TXM_DUO_ND_CACHE_HARDWARE_ADDRESS_FIND_CALL         222
#define TXM_DUO_ND_CACHE_INVALIDATE_CALL                    223
#define TXM_DUO_ND_CACHE_IP_ADDRESS_FIND_CALL               224
#define TXM_DUO_TCP_CLIENT_SOCKET_CONNECT_CALL              225
#define TXM_DUO_TCP_SOCKET_PEER_INFO_GET_CALL               226
#define TXM_DUO_UDP_PACKET_INFO_EXTRACT_CALL                227
#define TXM_DUO_UDP_SOURCE_EXTRACT_CALL                     228
#define TXM_DUO_UDP_SOCKET_INTERFACE_SEND_CALL              230
#define TXM_DUO_UDP_SOCKET_SEND_CALL                        231

#define TXM_NETX_IP_INTERNAL_PACKET_DEFERRED_RECEIVE_CALL   240
#define TXM_NETX_ARP_INTERNAL_PACKET_DEFERRED_RECEIVE_CALL  241
#define TXM_NETX_RARP_INTERNAL_PACKET_DEFERRED_RECEIVE_CALL 242


/* Determine the application's IDs for calling application code in the resident area.  */

#define TXM_APPLICATION_REQUEST_ID_BASE                     0x10000


/* Define the overlay for the module's preamble.  */

typedef struct TXM_MODULE_PREAMBLE_STRUCT
{
                                                                        /* Offset        Size            Meaning                                */
    ULONG               txm_module_preamble_id;                         /*     0          4        Download Module ID (0x54584D44)              */
    ULONG               txm_module_preamble_version_major;              /*     4          4        Major Version ID                             */
    ULONG               txm_module_preamble_version_minor;              /*     8          4        Minor Version ID                             */
    ULONG               txm_module_preamble_preamble_size;              /*    12          4        Module Preamble Size, in 32-bit words        */
    ULONG               txm_module_preamble_application_module_id;      /*    16          4        Module ID (application defined)              */
    ULONG               txm_module_preamble_property_flags;             /*    20          4        Properties Bit Map                           */
    ULONG               txm_module_preamble_shell_entry_function;       /*    24          4        Module shell Entry Function                  */
    ULONG               txm_module_preamble_start_function;             /*    28          4        Module Thread Start Function                 */
    ULONG               txm_module_preamble_stop_function;              /*    32          4        Module Thread Stop Function                  */ 
    ULONG               txm_module_preamble_start_stop_priority;        /*    36          4        Module Start/Stop Thread Priority            */
    ULONG               txm_module_preamble_start_stop_stack_size;      /*    40          4        Module Start/Stop Thread Priority            */
    ULONG               txm_module_preamble_callback_function;          /*    44          4        Module Callback Thread Function              */
    ULONG               txm_module_preamble_callback_priority;          /*    48          4        Module Callback Thread Priority              */
    ULONG               txm_module_preamble_callback_stack_size;        /*    52          4        Module Callback Thread Stack Size            */
    ULONG               txm_module_preamble_code_size;                  /*    56          4        Module Instruction Area Size                 */
    ULONG               txm_module_preamble_data_size;                  /*    60          4        Module Data Area Size                        */
    ULONG               txm_module_preamble_reserved_0;                 /*    64          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_1;                 /*    68          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_2;                 /*    72          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_3;                 /*    76          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_4;                 /*    80          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_5;                 /*    84          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_6;                 /*    88          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_7;                 /*    92          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_8;                 /*    96          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_9;                 /*   100          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_10;                /*   104          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_11;                /*   108          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_12;                /*   112          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_13;                /*   116          4        Reserved                                     */
    ULONG               txm_module_preamble_reserved_14;                /*   120          4        Reserved                                     */
    ULONG               txm_module_preamble_checksum;                   /*   124          4        Module Instruction Area Checksum [Optional]  */

} TXM_MODULE_PREAMBLE;


struct TXM_MODULE_ALLOCATED_OBJECT_STRUCT;

/* Define the module's instance for the manager.  */

typedef struct TXM_MODULE_INSTANCE_STRUCT
{
    ULONG               txm_module_instance_id;
    CHAR                *txm_module_instance_name;
    ULONG               txm_module_instance_state;
    ULONG               txm_module_instance_property_flags;
    VOID                *txm_module_instance_code_allocation_ptr;
    ULONG               txm_module_instance_code_allocation_size;
    VOID                *txm_module_instance_code_start;
    VOID                *txm_module_instance_code_end;
    ULONG               txm_module_instance_code_size;
    VOID                *txm_module_instance_data_allocation_ptr;
    ULONG               txm_module_instance_data_allocation_size;
    VOID                *txm_module_instance_data_start;
    VOID                *txm_module_instance_data_end;
    VOID                *txm_module_instance_module_data_base_address;
    ULONG               txm_module_instance_data_size;
    ULONG               txm_module_instance_total_ram_usage;
    VOID                *txm_module_instance_start_stop_stack_start_address;
    VOID                *txm_module_instance_start_stop_stack_end_address;
    VOID                *txm_module_instance_callback_stack_start_address;
    VOID                *txm_module_instance_callback_stack_end_address;
    TXM_MODULE_PREAMBLE *txm_module_instance_preamble_ptr;
    VOID                (*txm_module_instance_shell_entry_function)(TX_THREAD *, struct TXM_MODULE_INSTANCE_STRUCT *);
    VOID                (*txm_module_instance_start_thread_entry)(ULONG);
    VOID                (*txm_module_instance_stop_thread_entry)(ULONG);
    VOID                (*txm_module_instance_callback_request_thread_entry)(ULONG);
    TX_THREAD           txm_module_instance_start_stop_thread;
    TX_THREAD           txm_module_instance_callback_request_thread;
    TX_QUEUE            txm_module_instance_callback_request_queue;
    ULONG               txm_module_instance_callback_request_queue_area[TXM_MODULE_CALLBACKS_QUEUE_DEPTH * TXM_MODULE_CALLBACKS_MESSAGE_SIZE];
    ULONG               txm_module_instance_start_stop_stack_size;
    ULONG               txm_module_instance_start_stop_priority;
    ULONG               txm_module_instance_callback_stack_size;
    ULONG               txm_module_instance_callback_priority;
    ULONG               txm_module_instance_application_module_id;
    ULONG               txm_module_instance_callbacks_requested;
    ULONG               txm_module_instance_callbacks_completed;
    UINT                txm_module_instance_maximum_priority;
    
    /* Define the port extention to the module manager structure.  */
    TXM_MODULE_MANAGER_PORT_EXTENSION

    /* Define the head pointer of the list of objects allocated by the module.  */
    struct TXM_MODULE_ALLOCATED_OBJECT_STRUCT
                        *txm_module_instance_object_list_head;
    ULONG               txm_module_instance_object_list_count;

    struct TXM_MODULE_INSTANCE_STRUCT
                        *txm_module_instance_loaded_next,
                        *txm_module_instance_loaded_previous;  
} TXM_MODULE_INSTANCE;


/* Define the thread entry information structure. This structure is placed on the thread's stack such that the 
   module's _txm_thread_shell_entry function does not need to access anything in the thread control block.  */
   
typedef struct TXM_MODULE_THREAD_ENTRY_INFO_STRUCT
{
    TX_THREAD           *txm_module_thread_entry_info_thread;
    TXM_MODULE_INSTANCE *txm_module_thread_entry_info_module;
    VOID                *txm_module_thread_entry_info_data_base_address;     /* Don't move this, referenced in stack build to setup module data base register. */
    VOID                *txm_module_thread_entry_info_code_base_address;
    VOID               (*txm_module_thread_entry_info_entry)(ULONG);
    ULONG                txm_module_thread_entry_info_parameter;
    VOID               (*txm_module_thread_entry_info_exit_notify)(struct TX_THREAD_STRUCT *, UINT);
    UINT                 txm_module_thread_entry_info_start_thread;
    TX_THREAD           *txm_module_thread_entry_info_callback_request_thread;
    TX_QUEUE            *txm_module_thread_entry_info_callback_request_queue;
    TX_QUEUE            *txm_module_thread_entry_info_callback_response_queue;
    ULONG               (*txm_module_thread_entry_info_kernel_call_dispatcher)(ULONG kernel_request, ULONG param_1, ULONG param_2, ULONG param_3);
} TXM_MODULE_THREAD_ENTRY_INFO;


/* Define the callback control structure. Each module application callback is dynamically allocated one of 
   these structures in order to process the callback.  */
   
typedef struct TXM_MODULE_CALLBACK_STRUCT
{
    UINT                txm_module_callback_index;
    ULONG               txm_module_callback_activation_id;
    UINT                txm_module_callback_activated;
    UINT                txm_module_callback_response_pending;
    TXM_MODULE_INSTANCE *txm_module_callback_module_instance;
    UINT                txm_module_callback_pending_calls;    
    VOID                *txm_module_callback_application_function;
    ULONG               txm_module_callback_type;
    VOID                *txm_module_callback_object_ptr;
    ULONG               txm_module_callback_id;
    ULONG               txm_module_callback_param_1;
    ULONG               txm_module_callback_param_2;
    struct TXM_MODULE_CALLBACK_STRUCT
                        *txm_module_callback_next,
                        *txm_module_callback_previous;  
} TXM_MODULE_CALLBACK;


/* Define the callback notification structure used to communicate between the module's callback handling thread
   and the module manager.  */

typedef struct TXM_MODULE_CALLBACK_NOTIFY_STRUCT
{
    TXM_MODULE_CALLBACK *txm_module_callback_notify_callback;
    VOID                *txm_module_callback_notify_application_function;
    ULONG               txm_module_callback_notify_param_1;
    ULONG               txm_module_callback_notify_param_2;
    ULONG               txm_module_callback_notify_type;
    ULONG               txm_module_callback_notify_activation_id;
    ULONG               txm_module_callback_notify_reserved1;
    ULONG               txm_module_callback_notify_reserved2;
} TXM_MODULE_CALLBACK_NOTIFY;


/* Define the linked-list structure used to maintain the module's object allocation.  */

typedef struct TXM_MODULE_ALLOCATED_OBJECT_STRUCT
{

    TXM_MODULE_INSTANCE *txm_module_allocated_object_module_instance;
    struct TXM_MODULE_ALLOCATED_OBJECT_STRUCT
                        *txm_module_allocated_object_next,
                        *txm_module_allocated_object_previous;
    ULONG               txm_module_object_type;
} TXM_MODULE_ALLOCATED_OBJECT;                  


/*  Determine if module code is being compiled. If so, remap the ThreadX API to 
    the module shell functions that will go through the module <-> module manager
    interface.  */

#ifdef TXM_MODULE


/* Define the external reference to the module manager kernel dispatcher function pointer. This is supplied to the module by the module
   manager when the module is created and started.  */

extern ULONG (*_txm_module_kernel_call_dispatcher)(ULONG type, ULONG param_1, ULONG param_2, ULONG param3);


/* Define the system call functions that assist on calls with larger numbers of parameters.  */

ULONG  _txm_module_system_call4( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4);
ULONG  _txm_module_system_call5( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5);
ULONG  _txm_module_system_call6( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6);
ULONG  _txm_module_system_call7( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7);
ULONG  _txm_module_system_call8( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8);
ULONG  _txm_module_system_call9( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9);
ULONG  _txm_module_system_call10(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9, ULONG param_10);
ULONG  _txm_module_system_call11(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9, ULONG param_10, ULONG param_11);
ULONG  _txm_module_system_call12(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9, ULONG param_10, ULONG param_11, ULONG param12);


/* Module code is present.  Define all ThreadX APIs to calls to the module manager dispatcher.  */

#define tx_block_allocate(p, b, w)                                      ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_BLOCK_ALLOCATE_CALL, (ULONG) p, (ULONG) b, (ULONG) w))
#define tx_block_pool_create(p,n,b,s,l)                                 ((UINT) _txm_module_system_call6(TXM_BLOCK_POOL_CREATE_CALL, (ULONG) p, (ULONG) n, (ULONG) b, (ULONG) s, (ULONG) l, sizeof(TX_BLOCK_POOL)))
#define tx_block_pool_delete(p)                                         ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_BLOCK_POOL_DELETE_CALL, (ULONG) p, (ULONG) 0, (ULONG) 0))
#define tx_block_pool_info_get(p,n,a,t,f,s,o)                           ((UINT) _txm_module_system_call7(TXM_BLOCK_POOL_INFO_GET_CALL, (ULONG) p, (ULONG) n, (ULONG) a, (ULONG) t, (ULONG) f, (ULONG) s, (ULONG) o))
#define tx_block_pool_performance_info_get(p,a,r,s,t)                   ((UINT) _txm_module_system_call5(TXM_BLOCK_POOL_PERFORMANCE_INFO_GET_CALL, (ULONG) p, (ULONG) a, (ULONG) r, (ULONG) s, (ULONG) t))
#define tx_block_pool_performance_system_info_get(a,r,s,t)              ((UINT) _txm_module_system_call4(TXM_BLOCK_POOL_PERFORMANCE_SYSTEM_INFO_GET_CALL, (ULONG) a, (ULONG) r, (ULONG) s, (ULONG) t))

#define tx_block_pool_prioritize(p)                                     ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_BLOCK_POOL_PRIORITIZE_CALL, (ULONG) p, (ULONG) 0, (ULONG) 0))
#define tx_block_release(b)                                             ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_BLOCK_RELEASE_CALL, (ULONG) b, (ULONG) 0, (ULONG) 0))
#define tx_byte_allocate(p,m,s,w)                                       ((UINT) _txm_module_system_call4(TXM_BYTE_ALLOCATE_CALL, (ULONG) p, (ULONG) m, (ULONG) s, (ULONG) w))
#define tx_byte_pool_create(p,n,s,l)                                    ((UINT) _txm_module_system_call5(TXM_BYTE_POOL_CREATE_CALL, (ULONG) p, (ULONG) n, (ULONG) s, (ULONG) l, sizeof(TX_BYTE_POOL)))
#define tx_byte_pool_delete(p)                                          ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_BYTE_POOL_DELETE_CALL, (ULONG) p, (ULONG) 0, (ULONG) 0))
#define tx_byte_pool_info_get(p,n,a,f,s,c,o)                            ((UINT) _txm_module_system_call7(TXM_BYTE_POOL_INFO_GET_CALL, (ULONG) p, (ULONG) n, (ULONG) a, (ULONG) f, (ULONG) s, (ULONG) c, (ULONG) o))
#define tx_byte_pool_performance_info_get(p,a,r,f,m,s,u,t)              ((UINT) _txm_module_system_call8(TXM_BYTE_POOL_PERFORMANCE_INFO_GET_CALL, (ULONG) p, (ULONG) a, (ULONG) r, (ULONG) f, (ULONG) m, (ULONG) s, (ULONG) u, (ULONG) t))
#define tx_byte_pool_performance_system_info_get(a,r,f,m,s,u,t)         ((UINT) _txm_module_system_call7(TXM_BYTE_POOL_PERFORMANCE_SYSTEM_INFO_GET_CALL, (ULONG) a, (ULONG) r, (ULONG) f, (ULONG) m, (ULONG) s, (ULONG) u, (ULONG) t))
#define tx_byte_pool_prioritize(p)                                      ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_BYTE_POOL_PRIORITIZE_CALL, (ULONG) p, (ULONG) 0, (ULONG) 0))
#define tx_byte_release(b)                                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_BYTE_RELEASE_CALL, (ULONG) b, (ULONG) 0, (ULONG) 0))

#define tx_event_flags_create(g,n)                                      ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_EVENT_FLAGS_CREATE_CALL, (ULONG) g, (ULONG) n, (ULONG) sizeof(TX_EVENT_FLAGS_GROUP)))
#define tx_event_flags_delete(g)                                        ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_EVENT_FLAGS_DELETE_CALL, (ULONG) g, (ULONG) 0, (ULONG) 0))
#define tx_event_flags_get(g,r,o,a,w)                                   ((UINT) _txm_module_system_call5(TXM_EVENT_FLAGS_GET_CALL, (ULONG) g, (ULONG) r, (ULONG) o, (ULONG) a, (ULONG) w))
#define tx_event_flags_info_get(g,n,c,f,s,x)                            ((UINT) _txm_module_system_call6(TXM_EVENT_FLAGS_INFO_GET_CALL, (ULONG) g, (ULONG) n, (ULONG) c, (ULONG) f, (ULONG) s, (ULONG) x))
#define tx_event_flags_performance_info_get(g,s,t,u,m)                  ((UINT) _txm_module_system_call5(TXM_EVENT_FLAGS_PERFORMANCE_INFO_GET_CALL, (ULONG) g, (ULONG) s, (ULONG) t, (ULONG) u, (ULONG) m))
#define tx_event_flags_performance_system_info_get(s,g,u,t)             ((UINT) _txm_module_system_call4(TXM_EVENT_FLAGS_PERFORMANCE_SYSTEM_INFO_GET_CALL, (ULONG) s, (ULONG) g, (ULONG) u, (ULONG) t))
#define tx_event_flags_set(g,f,s)                                       ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_EVENT_FLAGS_SET_CALL, (ULONG) g, (ULONG) f, (ULONG) s))
#define tx_event_flags_set_notify(g,n)                                  ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_EVENT_FLAGS_SET_NOTIFY_CALL, (ULONG) g, (ULONG) n, (ULONG) 0))

#define tx_interrupt_control(n)                                         ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_INTERRUPT_CONTROL_CALL, (ULONG) n, (ULONG) 0, (ULONG) 0))

#define tx_mutex_create(m,n,i)                                          ((UINT) _txm_module_system_call4(TXM_MUTEX_CREATE_CALL, (ULONG) m, (ULONG) n, (ULONG) i, (ULONG) sizeof(TX_MUTEX)))
#define tx_mutex_delete(m)                                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_MUTEX_DELETE_CALL, (ULONG) m, (ULONG) 0, (ULONG) 0))
#define tx_mutex_get(m,w)                                               ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_MUTEX_GET_CALL, (ULONG) m, (ULONG) w, (ULONG) 0))
#define tx_mutex_info_get(m,n,c,o,f,u,x)                                ((UINT) _txm_module_system_call7(TXM_MUTEX_INFO_GET_CALL, (ULONG) m, (ULONG) n, (ULONG) c, (ULONG) o, (ULONG) f, (ULONG) u, (ULONG) x))
#define tx_mutex_performance_info_get(m,p,g,s,t,i,h)                    ((UINT) _txm_module_system_call7(TXM_MUTEX_PERFORMANCE_INFO_GET_CALL, (ULONG) m, (ULONG) p, (ULONG) g, (ULONG) s, (ULONG) t, (ULONG) i, (ULONG) h))
#define tx_mutex_performance_system_info_get(p,g,s,t,i,h)               ((UINT) _txm_module_system_call6(TXM_MUTEX_PERFORMANCE_SYSTEM_INFO_GET_CALL, (ULONG) p, (ULONG) g, (ULONG) s, (ULONG) t, (ULONG) i, (ULONG) h))
#define tx_mutex_prioritize(m)                                          ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_MUTEX_PRIORITIZE_CALL, (ULONG) m, (ULONG) 0, (ULONG) 0))
#define tx_mutex_put(m)                                                 ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_MUTEX_PUT_CALL, (ULONG) m, (ULONG) 0, (ULONG) 0))

#define tx_queue_create(q,n,m,s,l)                                      ((UINT) _txm_module_system_call6(TXM_QUEUE_CREATE_CALL, (ULONG) q, (ULONG) n, (ULONG) m, (ULONG) s, (ULONG) l, sizeof(TX_QUEUE)))
#define tx_queue_delete(q)                                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_QUEUE_DELETE_CALL, (ULONG) q, (ULONG) 0, (ULONG) 0))
#define tx_queue_flush(q)                                               ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_QUEUE_FLUSH_CALL, (ULONG) q, (ULONG) 0, (ULONG) 0))
#define tx_queue_info_get(q,n,e,a,f,s,x)                                ((UINT) _txm_module_system_call7(TXM_QUEUE_INFO_GET_CALL, (ULONG) q, (ULONG) n, (ULONG) e, (ULONG) a, (ULONG) f, (ULONG) s, (ULONG) x))
#define tx_queue_performance_info_get(q,s,r,e,f,u,t)                    ((UINT) _txm_module_system_call7(TXM_QUEUE_PERFORMANCE_INFO_GET_CALL, (ULONG) q, (ULONG) s, (ULONG) r, (ULONG) e, (ULONG) f, (ULONG) u, (ULONG) t))
#define tx_queue_performance_system_info_get(s,r,e,f,u,t)               ((UINT) _txm_module_system_call6(TXM_QUEUE_PERFORMANCE_SYSTEM_INFO_GET_CALL, (ULONG) s, (ULONG) r, (ULONG) e, (ULONG) f, (ULONG) u, (ULONG) t))
#define tx_queue_receive(q,d,w)                                         ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_QUEUE_RECEIVE_CALL, (ULONG) q, (ULONG) d, (ULONG) w))
#define tx_queue_send(q,s,w)                                            ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_QUEUE_SEND_CALL, (ULONG) q, (ULONG) s, (ULONG) w))
#define tx_queue_send_notify(q,n)                                       ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_QUEUE_SEND_NOTIFY_CALL, (ULONG) q, (ULONG) n, (ULONG) 0))
#define tx_queue_front_send(q,s,w)                                      ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_QUEUE_FRONT_SEND_CALL, (ULONG) q, (ULONG) s, (ULONG) w))
#define tx_queue_prioritize(q)                                          ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_QUEUE_PRIORITIZE_CALL, (ULONG) q, (ULONG) 0, (ULONG) 0))

#define tx_semaphore_ceiling_put(s,c)                                   ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_SEMAPHORE_CEILING_PUT_CALL, (ULONG) s, (ULONG) c, (ULONG) 0))
#define tx_semaphore_create(s,n,i)                                      ((UINT) _txm_module_system_call4(TXM_SEMAPHORE_CREATE_CALL, (ULONG) s, (ULONG) n, (ULONG) i, (ULONG) sizeof(TX_SEMAPHORE)))
#define tx_semaphore_delete(s)                                          ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_SEMAPHORE_DELETE_CALL, (ULONG) s, (ULONG) 0, (ULONG) 0))
#define tx_semaphore_get(s,w)                                           ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_SEMAPHORE_GET_CALL, (ULONG) s, (ULONG) w, (ULONG) 0))
#define tx_semaphore_info_get(s,n,c,f,u,x)                              ((UINT) _txm_module_system_call6(TXM_SEMAPHORE_INFO_GET_CALL, (ULONG) s, (ULONG) n, (ULONG) c, (ULONG) f, (ULONG) u, (ULONG) x))
#define tx_semaphore_performance_info_get(s,p,g,u,t)                    ((UINT) _txm_module_system_call5(TXM_SEMAPHORE_PERFORMANCE_INFO_GET_CALL, (ULONG) s, (ULONG) p, (ULONG) g, (ULONG) u, (ULONG) t))
#define tx_semaphore_performance_system_info_get(p,g,u,t)               ((UINT) _txm_module_system_call4(TXM_SEMAPHORE_PERFORMANCE_SYSTEM_INFO_GET_CALL, (ULONG) p, (ULONG) g, (ULONG) u, (ULONG) t))
#define tx_semaphore_prioritize(s)                                      ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_SEMAPHORE_PRIORITIZE_CALL, (ULONG) s, (ULONG) 0, (ULONG) 0))
#define tx_semaphore_put(s)                                             ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_SEMAPHORE_PUT_CALL, (ULONG) s, (ULONG) 0, (ULONG) 0))
#define tx_semaphore_put_notify(s,n)                                    ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_SEMAPHORE_PUT_NOTIFY_CALL, (ULONG) s, (ULONG) n, (ULONG) 0))

#define tx_thread_create(t,n,e,i,s,l,p,r,c,a)                           ((UINT) _txm_module_system_call11(TXM_THREAD_CREATE_CALL, (ULONG) t, (ULONG) n, (ULONG) e, (ULONG) i, (ULONG) s, (ULONG) l, (ULONG) p, (ULONG) r, (ULONG) c, (ULONG) a, (ULONG) sizeof(TX_THREAD)))
#define tx_thread_delete(t)                                             ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_DELETE_CALL, (ULONG) t, (ULONG) 0, (ULONG) 0))
#define tx_thread_entry_exit_notify(t,n)                                ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_ENTRY_EXIT_NOTIFY_CALL, (ULONG) t, (ULONG) n, (ULONG) 0))
#define tx_thread_identify()                                            ((TX_THREAD *) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_IDENTIFY_CALL, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define tx_thread_info_get(t,n,s,r,p,h,i,x,u)                           ((UINT) _txm_module_system_call9(TXM_THREAD_INFO_GET_CALL, (ULONG) t, (ULONG) n, (ULONG) s, (ULONG) r, (ULONG) p, (ULONG) h, (ULONG) i, (ULONG) x, (ULONG) u))
#define tx_thread_performance_info_get(t,r,s,o,i,v,l,q,u,w,y)           ((UINT) _txm_module_system_call11(TXM_THREAD_PERFORMANCE_INFO_GET_CALL, (ULONG) t, (ULONG) r, (ULONG) s, (ULONG) o, (ULONG) i, (ULONG) v, (ULONG) l, (ULONG) q, (ULONG) u, (ULONG) w, (ULONG) y))
#define tx_thread_performance_system_info_get(r,s,o,i,v,l,q,u,w,d,e)    ((UINT) _txm_module_system_call11(TXM_THREAD_PERFORMANCE_SYSTEM_INFO_GET_CALL, (ULONG) r, (ULONG) s, (ULONG) o, (ULONG) i, (ULONG) v, (ULONG) l, (ULONG) q, (ULONG) u, (ULONG) w, (ULONG) d, (ULONG) e))
#define tx_thread_preemption_change(t,n,o)                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_PREEMPTION_CHANGE_CALL, (ULONG) t, (ULONG) n, (ULONG) o))
#define tx_thread_priority_change(t,n,o)                                ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_PRIORITY_CHANGE_CALL, (ULONG) t, (ULONG) n, (ULONG) o))
#define tx_thread_relinquish()                                          ((VOID) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_RELINQUISH_CALL, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define tx_thread_reset(t)                                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_RESET_CALL, (ULONG) t, (ULONG) 0, (ULONG) 0))
#define tx_thread_resume(t)                                             ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_RESUME_CALL, (ULONG) t, (ULONG) 0, (ULONG) 0))
#define tx_thread_sleep(c)                                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_SLEEP_CALL, (ULONG) c, (ULONG) 0, (ULONG) 0))
#define tx_thread_stack_error_notify(n)                                 ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_STACK_ERROR_NOTIFY_CALL, (ULONG) n, (ULONG) 0, (ULONG) 0))
#define tx_thread_suspend(t)                                            ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_SUSPEND_CALL, (ULONG) t, (ULONG) 0, (ULONG) 0))
#define tx_thread_terminate(t)                                          ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_TERMINATE_CALL, (ULONG) t, (ULONG) 0, (ULONG) 0))
#define tx_thread_time_slice_change(t,n,o)                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_TIME_SLICE_CHANGE_CALL, (ULONG) t, (ULONG) n, (ULONG) o))
#define tx_thread_wait_abort(t)                                         ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_WAIT_ABORT_CALL, (ULONG) t, (ULONG) 0, (ULONG) 0))

#define tx_time_get()                                                   ((ULONG) (_txm_module_kernel_call_dispatcher)(TXM_TIME_GET_CALL, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define tx_time_set(t)                                                  ((VOID) (_txm_module_kernel_call_dispatcher)(TXM_TIME_SET_CALL, (ULONG) t, (ULONG) 0, (ULONG) 0))
#define tx_timer_activate(t)                                            ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TIMER_ACTIVATE_CALL, (ULONG) t, (ULONG) 0, (ULONG) 0))
#define tx_timer_change(t,i,r)                                          ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TIMER_CHANGE_CALL, (ULONG) t, (ULONG) i, (ULONG) r))
#define tx_timer_create(t,n,e,i,j,k,a)                                  ((UINT) _txm_module_system_call8(TXM_TIMER_CREATE_CALL, (ULONG) t, (ULONG) n, (ULONG) e, (ULONG) i, (ULONG) j, (ULONG) k, (ULONG) a, (ULONG) sizeof(TX_TIMER)))
#define tx_timer_deactivate(t)                                          ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TIMER_DEACTIVATE_CALL, (ULONG) t, (ULONG) 0, (ULONG) 0))
#define tx_timer_delete(t)                                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TIMER_DELETE_CALL, (ULONG) t, (ULONG) 0, (ULONG) 0))
#define tx_timer_info_get(t,n,a,r,s,x)                                  ((UINT) _txm_module_system_call6(TXM_TIMER_INFO_GET_CALL, (ULONG) t, (ULONG) n, (ULONG) a, (ULONG) r, (ULONG) s, (ULONG) x))
#define tx_timer_performance_info_get(t,a,r,d,x,j)                      ((UINT) _txm_module_system_call6(TXM_TIMER_PERFORMANCE_INFO_GET_CALL, (ULONG) t, (ULONG) a, (ULONG) r, (ULONG) d, (ULONG) x, (ULONG) j))
#define tx_timer_performance_system_info_get(a,r,d,x,j)                 ((UINT) _txm_module_system_call5(TXM_TIMER_PERFORMANCE_SYSTEM_INFO_GET_CALL,(ULONG) a, (ULONG) r, (ULONG) d, (ULONG) x, (ULONG) j))

#define tx_trace_enable(s,z,r)                                          ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TRACE_ENABLE_CALL, (ULONG) s, (ULONG) z, (ULONG) r))
#define tx_trace_event_filter(f)                                        ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TRACE_EVENT_FILTER_CALL, (ULONG) f, (ULONG) 0, (ULONG) 0))
#define tx_trace_event_unfilter(u)                                      ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TRACE_EVENT_UNFILTER_CALL, (ULONG) u, (ULONG) 0, (ULONG) 0))
#define tx_trace_disable()                                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TRACE_DISABLE_CALL, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define tx_trace_isr_enter_insert(i)                                    ((VOID) (_txm_module_kernel_call_dispatcher)(TXM_TRACE_ISR_ENTER_CALL, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define tx_trace_isr_exit_insert(i)                                     ((VOID) (_txm_module_kernel_call_dispatcher)(TXM_TRACE_ISR_EXIT_CALL, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define tx_trace_buffer_full_notify(n)                                  ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TRACE_BUFFER_FULL_NOTIFY_CALL, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define tx_trace_user_event_insert(i,a,b,c,d)                           ((UINT) _txm_module_system_call5(TXM_TRACE_USER_EVENT_INSERT_CALL,(ULONG) i, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d))

#define txm_module_thread_system_suspend(t)                             ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_THREAD_SYSTEM_SUSPEND_CALL, (ULONG) t, (ULONG) 0, (ULONG) 0))
#define txm_module_object_pointer_get(o,n,p)                            ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_MODULE_OBJECT_POINTER_GET_CALL, (ULONG) o, (ULONG) n, (ULONG) p))
#define txm_module_object_allocate(o,s)                                 ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_MODULE_OBJECT_ALLOCATE_CALL, (ULONG) o, (ULONG) s, (ULONG) 0))
#define txm_module_object_deallocate(o)                                 ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_MODULE_OBJECT_DEALLOCATE_CALL, (ULONG) o, (ULONG) 0, (ULONG) 0))
#define txm_module_application_request(i,a,b,c)                         ((UINT) (_txm_module_kernel_call_dispatcher)((ULONG) TXM_APPLICATION_REQUEST_ID_BASE+i, (ULONG) a, (ULONG) b, (ULONG) c))

#define nx_arp_dynamic_entries_invalidate(i)                            ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_ARP_DYNAMIC_ENTRIES_INVALIDATE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_arp_dynamic_entry_set(i,a,m,l)                               ((UINT) _txm_module_system_call4(TXM_ARP_DYNAMIC_ENTRY_SET_CALL, (ULONG) i, (ULONG) a, (ULONG) m, (ULONG) l))
#define nx_arp_enable(i,c,s)                                            ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_ARP_ENABLE_CALL, (ULONG) i, (ULONG) c, (ULONG) s))
#define nx_arp_gratuitous_send(i,r)                                     ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_ARP_GRATUITOUS_SEND_CALL, (ULONG) i, (ULONG) r, (ULONG) 0))
#define nx_arp_hardware_address_find(i,a,m,l)                           ((UINT) _txm_module_system_call4(TXM_ARP_HARDWARE_ADDRESS_FIND_CALL, (ULONG) i, (ULONG) a, (ULONG) m, (ULONG) l))
#define nx_arp_info_get(i,r,c,s,e,d,t,g,v)                              ((UINT) _txm_module_system_call9(TXM_ARP_INFO_GET_CALL, (ULONG) i, (ULONG) r, (ULONG) c, (ULONG) s, (ULONG) e, (ULONG) d, (ULONG) t, (ULONG) g, (ULONG) v))
#define nx_arp_ip_address_find(i,a,m,l)                                 ((UINT) _txm_module_system_call4(TXM_ARP_IP_ADDRESS_FIND_CALL, (ULONG) i, (ULONG) a, (ULONG) m, (ULONG) l))
#define nx_arp_static_entries_delete(i)                                 ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_ARP_STATIC_ENTRIES_DELETE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_arp_static_entry_create(i,a,m,l)                             ((UINT) _txm_module_system_call4(TXM_ARP_STATIC_ENTRY_CREATE_CALL, (ULONG) i, (ULONG) a, (ULONG) m, (ULONG) l))
#define nx_arp_static_entry_delete(i,a,m,l)                             ((UINT) _txm_module_system_call4(TXM_ARP_STATIC_ENTRY_DELETE_CALL, (ULONG) i, (ULONG) a, (ULONG) m, (ULONG) l))
#define nx_icmp_enable(i)                                               ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_ICMP_ENABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_icmp_info_get(i,p,t,g,r,c,u)                                 ((UINT) _txm_module_system_call7(TXM_ICMP_INFO_GET_CALL, (ULONG) i, (ULONG) p, (ULONG) t, (ULONG) g, (ULONG) r, (ULONG) c, (ULONG) u))
#define nx_icmp_ping(i,a,d,s,r,w)                                       ((UINT) _txm_module_system_call6(TXM_ICMP_PING_CALL, (ULONG) i, (ULONG) a, (ULONG) d, (ULONG) s, (ULONG) r, (ULONG) w))
#define nx_igmp_enable(i)                                               ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IGMP_ENABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_igmp_info_get(i,r,q,c,g)                                     ((UINT) _txm_module_system_call5(TXM_IGMP_INFO_GET_CALL, (ULONG) i, (ULONG) r, (ULONG) q, (ULONG) c, (ULONG) g))
#define nx_igmp_loopback_disable(i)                                     ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IGMP_LOOPBACK_DISABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_igmp_loopback_enable(i)                                      ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IGMP_LOOPBACK_ENABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_igmp_multicast_join(i,g)                                     ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IGMP_MULTICAST_JOIN_CALL, (ULONG) i, (ULONG) g, (ULONG) 0))
#define nx_igmp_multicast_interface_join(i,g,n)                         ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IGMP_MULTICAST_INTERFACE_JOIN_CALL, (ULONG) i, (ULONG) g, (ULONG) n))
#define nx_igmp_multicast_leave(i,g)                                    ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IGMP_MULTICAST_LEAVE_CALL, (ULONG) i, (ULONG) g, (ULONG) 0))
#define nx_ip_address_change_notify(i,a,d)                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_ADDRESS_CHANGE_NOTIFY_CALL, (ULONG) i, (ULONG) a, (ULONG) d))
#define nx_ip_address_get(i,a,n)                                        ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_ADDRESS_GET_CALL, (ULONG) i, (ULONG) a, (ULONG) n))
#define nx_ip_address_set(i,a,n)                                        ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_ADDRESS_SET_CALL, (ULONG) i, (ULONG) a, (ULONG) n))
#define nx_ip_interface_address_get(i,n,a,m)                            ((UINT) _txm_module_system_call4(TXM_IP_INTERFACE_ADDRESS_GET_CALL, (ULONG) i, (ULONG) n, (ULONG) a, (ULONG) m))
#define nx_ip_interface_address_set(i,n,a,m)                            ((UINT) _txm_module_system_call4(TXM_IP_INTERFACE_ADDRESS_SET_CALL, (ULONG) i, (ULONG) n, (ULONG) a, (ULONG) m))
#define nx_ip_interface_info_get(i,n,f,a,t,s,m,l)                       ((UINT) _txm_module_system_call8(TXM_IP_INTERFACE_INFO_GET_CALL, (ULONG) i, (ULONG) n, (ULONG) f, (ULONG) a, (ULONG) t, (ULONG) s, (ULONG) m, (ULONG) l))
#define nx_ip_create(i,n,a,m,p,d,z,s,t)                                 ((UINT) _txm_module_system_call10(TXM_IP_CREATE_CALL, (ULONG) i, (ULONG) n, (ULONG) a, (ULONG) m, (ULONG) p, (ULONG) d, (ULONG) z, (ULONG) s, (ULONG) t, (ULONG) sizeof(NX_IP)))
#define nx_ip_delete(i)                                                 ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_DELETE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_ip_driver_direct_command(i,c,r)                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_DRIVER_DIRECT_COMMAND_CALL, (ULONG) i, (ULONG) c, (ULONG) r))
#define nx_ip_driver_interface_direct_command(i,c,f,r)                  ((UINT) _txm_module_system_call4(TXM_IP_DRIVER_INTERFACE_DIRECT_COMMAND_CALL, (ULONG) i, (ULONG) c, (ULONG) f, (ULONG) r))
#define nx_ip_forwarding_disable(i)                                     ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_FORWARDING_DISABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_ip_forwarding_enable(i)                                      ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_FORWARDING_ENABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_ip_fragment_disable(i)                                       ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_FRAGMENT_DISABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_ip_fragment_enable(i)                                        ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_FRAGMENT_ENABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_ip_gateway_address_set(i,a)                                  ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_GATEWAY_ADDRESS_SET_CALL, (ULONG) i, (ULONG) a, (ULONG) 0))
#define nx_ip_info_get(i,t,b,r,l,v,d,c,o,f,e)                           ((UINT) _txm_module_system_call11(TXM_IP_INFO_GET_CALL, (ULONG) i, (ULONG) t, (ULONG) b, (ULONG) r, (ULONG) l, (ULONG) v, (ULONG) d, (ULONG) c, (ULONG) o, (ULONG) f, (ULONG) e))
#define nx_ip_interface_attach(i,n,a,m,l)                               ((UINT) _txm_module_system_call5(TXM_IP_INTERFACE_ATTACH_CALL,(ULONG) i, (ULONG) n, (ULONG) a, (ULONG) m, (ULONG) l))
#define nx_ip_interface_status_check(i,n,s,a,w)                         ((UINT) _txm_module_system_call5(TXM_IP_INTERFACE_STATUS_CHECK_CALL,(ULONG) i, (ULONG) n, (ULONG) s, (ULONG) a, (ULONG) w))
#define nx_ip_max_payload_size_find(i,d,f,s,p,r,o,y)                    ((UINT) _txm_module_system_call8(TXM_IP_MAX_PAYLOAD_SIZE_FIND_CALL, (ULONG) i, (ULONG) d, (ULONG) f, (ULONG) s, (ULONG) p, (ULONG) r, (ULONG) o, (ULONG) y))
#define nx_ip_raw_packet_disable(i)                                     ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_RAW_PACKET_DISABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_ip_raw_packet_enable(i)                                      ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_RAW_PACKET_ENABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_ip_raw_packet_receive(i,p,w)                                 ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_RAW_PACKET_RECEIVE_CALL, (ULONG) i, (ULONG) p, (ULONG) w))
#define nx_ip_raw_packet_send(i,p,d,t)                                  ((UINT) _txm_module_system_call4(TXM_IP_RAW_PACKET_SEND_CALL, (ULONG) i, (ULONG) &p, (ULONG) d, (ULONG) t))
#define nx_ip_raw_packet_source_send(i,p,d,f,t)                         ((UINT) _txm_module_system_call5(TXM_IP_RAW_PACKET_SOURCE_SEND_CALL,(ULONG) i, (ULONG) &p, (ULONG) d, (ULONG) f, (ULONG) t))
#define nx_ip_static_route_add(i,a,m,h)                                 ((UINT) _txm_module_system_call4(TXM_IP_STATIC_ROUTE_ADD_CALL, (ULONG) i, (ULONG) a, (ULONG) m, (ULONG) h))
#define nx_ip_static_route_delete(i,n,m)                                ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_IP_STATIC_ROUTE_DELETE_CALL, (ULONG) i, (ULONG) n, (ULONG) m))
#define nx_ip_status_check(i,s,a,w)                                     ((UINT) _txm_module_system_call4(TXM_IP_STATUS_CHECK_CALL, (ULONG) i, (ULONG) s, (ULONG) a, (ULONG) w))

#define nx_packet_allocate(p,t,e,w)                                     ((UINT) _txm_module_system_call4(TXM_PACKET_ALLOCATE_CALL, (ULONG) p, (ULONG) t, (ULONG) e, (ULONG) w))
#define nx_packet_copy(p,n,t,w)                                         ((UINT) _txm_module_system_call4(TXM_PACKET_COPY_CALL, (ULONG) p, (ULONG) n, (ULONG) t, (ULONG) w))
#define nx_packet_data_append(p,d,s,t,w)                                ((UINT) _txm_module_system_call5(TXM_PACKET_DATA_APPEND_CALL,(ULONG) p, (ULONG) d, (ULONG) s, (ULONG) t, (ULONG) w))
#define nx_packet_data_extract_offset(p,o,b,l,y)                        ((UINT) _txm_module_system_call5(TXM_PACKET_DATA_EXTRACT_OFFSET_CALL,(ULONG) p, (ULONG) o, (ULONG) b, (ULONG) l, (ULONG) y))
#define nx_packet_data_retrieve(p,b,c)                                  ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_PACKET_DATA_RETRIEVE_CALL, (ULONG) p, (ULONG) b, (ULONG) c))
#define nx_packet_length_get(p,l)                                       ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_PACKET_LENGTH_GET_CALL, (ULONG) p, (ULONG) l, (ULONG) 0))
#define nx_packet_pool_create(p,n,y,m,s)                                ((UINT) _txm_module_system_call6(TXM_PACKET_POOL_CREATE_CALL, (ULONG) p, (ULONG) n, (ULONG) y, (ULONG) m, (ULONG) s, (ULONG) sizeof(NX_PACKET_POOL)))
#define nx_packet_pool_delete(p)                                        ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_PACKET_POOL_DELETE_CALL, (ULONG) p, (ULONG) 0, (ULONG) 0))
#define nx_packet_pool_info_get(p,t,f,e,s,i)                            ((UINT) _txm_module_system_call6(TXM_PACKET_POOL_INFO_GET_CALL, (ULONG) p, (ULONG) t, (ULONG) f, (ULONG) e, (ULONG) s, (ULONG) i))
#define nx_packet_release(p)                                            ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_PACKET_RELEASE_CALL, (ULONG) &p, (ULONG) 0, (ULONG) 0))
#define nx_packet_transmit_release(p)                                   ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_PACKET_TRANSMIT_RELEASE_CALL, (ULONG) &p, (ULONG) 0, (ULONG) 0))

#define nx_rarp_disable(i)                                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_RARP_DISABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_rarp_enable(i)                                               ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_RARP_ENABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_rarp_info_get(i,r,p,z)                                       ((UINT) _txm_module_system_call4(TXM_RARP_INFO_GET_CALL, (ULONG) i, (ULONG) r, (ULONG) p, (ULONG) z))

#define nx_system_initialize()                                          ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_SYSTEM_INITIALIZE_CALL, (ULONG) 0, (ULONG) 0, (ULONG) 0)) 

#define nx_tcp_client_socket_bind(s,p,w)                                ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_CLIENT_SOCKET_BIND_CALL, (ULONG) s, (ULONG) p, (ULONG) w))
#define nx_tcp_client_socket_connect(s,i,p,w)                           ((UINT) _txm_module_system_call4(TXM_TCP_CLIENT_SOCKET_CONNECT_CALL, (ULONG) s, (ULONG) i, (ULONG) p, (ULONG) w))
#define nx_tcp_client_socket_port_get(s,p)                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_CLIENT_SOCKET_PORT_GET_CALL, (ULONG) s, (ULONG) p, (ULONG) 0))
#define nx_tcp_client_socket_unbind(s)                                  ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_CLIENT_SOCKET_UNBIND_CALL, (ULONG) s, (ULONG) 0, (ULONG) 0))
#define nx_tcp_enable(i)                                                ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_ENABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_tcp_free_port_find(i,p,f)                                    ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_FREE_PORT_FIND_CALL, (ULONG) i, (ULONG) p, (ULONG) f))
#define nx_tcp_info_get(i,s,b,r,y,x,d,c,o,n,v,t)                        ((UINT) _txm_module_system_call12(TXM_TCP_INFO_GET_CALL, (ULONG) i, (ULONG) s, (ULONG) b, (ULONG) r, (ULONG) y, (ULONG) x, (ULONG) d, (ULONG) c, (ULONG) o, (ULONG) n, (ULONG) v, (ULONG) t))
#define nx_tcp_server_socket_accept(s,w)                                ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SERVER_SOCKET_ACCEPT_CALL, (ULONG) s, (ULONG) w, (ULONG) 0))
#define nx_tcp_server_socket_listen(i,p,s,l,v)                          ((UINT) _txm_module_system_call5(TXM_TCP_SERVER_SOCKET_LISTEN_CALL,(ULONG) i, (ULONG) p, (ULONG) s, (ULONG) l, (ULONG) v))
#define nx_tcp_server_socket_relisten(i,p,s)                            ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SERVER_SOCKET_RELISTEN_CALL, (ULONG) i, (ULONG) p, (ULONG) s))
#define nx_tcp_server_socket_unaccept(s)                                ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SERVER_SOCKET_UNACCEPT_CALL, (ULONG) s, (ULONG) 0, (ULONG) 0))
#define nx_tcp_server_socket_unlisten(i,p)                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SERVER_SOCKET_UNLISTEN_CALL, (ULONG) i, (ULONG) p, (ULONG) 0))
#define nx_tcp_socket_bytes_available(s,b)                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SOCKET_BYTES_AVAILABLE_CALL, (ULONG) s, (ULONG) b, (ULONG) 0))
#define nx_tcp_socket_create(i,s,n,t,f,m,w,u,d)                         ((UINT) _txm_module_system_call10(TXM_TCP_SOCKET_CREATE_CALL, (ULONG) i, (ULONG) s, (ULONG) n, (ULONG) t, (ULONG) f, (ULONG) m, (ULONG) w, (ULONG) u, (ULONG) d, (ULONG) sizeof(NX_TCP_SOCKET)))
#define nx_tcp_socket_delete(s)                                         ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SOCKET_DELETE_CALL, (ULONG) s, (ULONG) 0, (ULONG) 0))
#define nx_tcp_socket_disconnect(s,w)                                   ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SOCKET_DISCONNECT_CALL, (ULONG) s, (ULONG) w, (ULONG) 0))
#define nx_tcp_socket_info_get(s,p,b,k,r,n,q,c,a,d,w,i)                 ((UINT) _txm_module_system_call12(TXM_TCP_SOCKET_INFO_GET_CALL, (ULONG) s, (ULONG) p, (ULONG) b, (ULONG) k, (ULONG) r, (ULONG) n, (ULONG) q, (ULONG) c, (ULONG) a, (ULONG) d, (ULONG) w, (ULONG) i))
#define nx_tcp_socket_mss_get(s,m)                                      ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SOCKET_MSS_GET_CALL, (ULONG) s, (ULONG) m, (ULONG) 0))
#define nx_tcp_socket_mss_peer_get(s,p)                                 ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SOCKET_MSS_PEER_GET_CALL, (ULONG) s, (ULONG) p, (ULONG) 0))
#define nx_tcp_socket_mss_set(s,m)                                      ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SOCKET_MSS_SET_CALL, (ULONG) s, (ULONG) m, (ULONG) 0))
#define nx_tcp_socket_peer_info_get(s,p,e)                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SOCKET_PEER_INFO_GET_CALL, (ULONG) s, (ULONG) p, (ULONG) e))
#define nx_tcp_socket_receive(s,p,w)                                    ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SOCKET_RECEIVE_CALL, (ULONG) s, (ULONG) p, (ULONG) w))
#define nx_tcp_socket_receive_notify(s,n)                               ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SOCKET_RECEIVE_NOTIFY_CALL, (ULONG) s, (ULONG) n, (ULONG) 0))
#define nx_tcp_socket_send(s,p,w)                                       ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SOCKET_SEND_CALL, (ULONG) s, (ULONG) &p, (ULONG) w))
#define nx_tcp_socket_state_wait(s,d,w)                                 ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SOCKET_STATE_WAIT_CALL, (ULONG) s, (ULONG) d, (ULONG) w))
#define nx_tcp_socket_transmit_configure(s,m,t,x,o)                     ((UINT) _txm_module_system_call5(TXM_TCP_SOCKET_TRANSMIT_CONFIGURE_CALL,(ULONG) s, (ULONG) m, (ULONG) t, (ULONG) x, (ULONG) o))
#define nx_tcp_socket_window_update_notify_set(s,n)                     ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_TCP_SOCKET_WINDOW_UPDATE_NOFITY_SET_CALL, (ULONG) s, (ULONG) n, (ULONG) 0))

#define nx_udp_enable(i)                                                ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_UDP_ENABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nx_udp_free_port_find(i,p,f)                                    ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_UDP_FREE_PORT_FIND_CALL, (ULONG) i, (ULONG) p, (ULONG) f))
#define nx_udp_info_get(i,p,s,r,u,v,d,c)                                ((UINT) _txm_module_system_call8(TXM_UPD_INFO_GET_CALL, (ULONG) i, (ULONG) p, (ULONG) s, (ULONG) r, (ULONG) u, (ULONG) v, (ULONG) d, (ULONG) c))
#define nx_udp_packet_info_extract(p,i,a,o,f)                           ((UINT) _txm_module_system_call5(TXM_UDP_PACKET_INFO_EXTRACT_CALL,(ULONG) p, (ULONG) i, (ULONG) a, (ULONG) o, (ULONG) f))
#define nx_udp_socket_bind(s,p,w)                                       ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_UDP_SOCKET_BIND_CALL, (ULONG) s, (ULONG) p, (ULONG) w))
#define nx_udp_socket_bytes_available(s,b)                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_UDP_SOCKET_BYTES_AVAILABLE_CALL, (ULONG) s, (ULONG) b, (ULONG) 0))
#define nx_udp_socket_checksum_disable(s)                               ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_UDP_SOCKET_CHECKSUM_DISABLE_CALL, (ULONG) s, (ULONG) 0, (ULONG) 0))
#define nx_udp_socket_checksum_enable(s)                                ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_UDP_SOCKET_CHECKSUM_ENABLE_CALL, (ULONG) s, (ULONG) 0, (ULONG) 0))
#define nx_udp_socket_create(i,s,n,t,f,m,q)                             ((UINT) _txm_module_system_call8(TXM_UDP_SOCKET_CREATE_CALL, (ULONG) i, (ULONG) s, (ULONG) n, (ULONG) t, (ULONG) f, (ULONG) m, (ULONG) q, (ULONG) sizeof(NX_UDP_SOCKET)))
#define nx_udp_socket_delete(s)                                         ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_UDP_SOCKET_DELETE_CALL, (ULONG) s, (ULONG) 0, (ULONG) 0))
#define nx_udp_socket_info_get(s,p,t,r,b,q,e,c)                         ((UINT) _txm_module_system_call8(TXM_UDP_SOCKET_INFO_GET_CALL, (ULONG) s, (ULONG) p, (ULONG) t, (ULONG) r, (ULONG) b, (ULONG) q, (ULONG) e, (ULONG) c))
#define nx_udp_socket_port_get(s,p)                                     ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_UDP_SOCKET_PORT_GET_CALL, (ULONG) s, (ULONG) p, (ULONG) 0))
#define nx_udp_socket_receive(s,p,w)                                    ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_UDP_SOCKET_RECEIVE_CALL, (ULONG) s, (ULONG) p, (ULONG) w))
#define nx_udp_socket_receive_notify(s,n)                               ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_UDP_SOCKET_RECEIVE_NOTIFY_CALL, (ULONG) s, (ULONG) n, (ULONG) 0))
#define nx_udp_socket_send(s,p,i,o)                                     ((UINT) _txm_module_system_call4(TXM_UDP_SOCKET_SEND_CALL, (ULONG) s, (ULONG) &p, (ULONG) i, (ULONG) o))
#define nx_udp_socket_source_send(s,p,i,o,a)                            ((UINT) _txm_module_system_call5(TXM_UDP_SOCKET_SOURCE_SEND_CALL,(ULONG) s, (ULONG) &p, (ULONG) i, (ULONG) o, (ULONG) a))
#define nx_udp_socket_unbind(s)                                         ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_UDP_SOCKET_UNBIND_CALL, (ULONG) s, (ULONG) 0, (ULONG) 0))
#define nx_udp_source_extract(p,i,o)                                    ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_UDP_SOURCE_EXTRACT_CALL, (ULONG) p, (ULONG) i, (ULONG) o))

#define nxd_icmp_enable(i)                                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_DUO_ICMP_ENABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nxd_icmp_interface_ping(i,a,s,d,z,r,w)                          ((UINT) _txm_module_system_call7(TXM_DUO_ICMP_INTERFACE_PING_CALL, (ULONG) i, (ULONG) a, (ULONG) s, (ULONG) d, (ULONG) z, (ULONG) r, (ULONG) w))
#define nxd_icmp_ping(i,a,d,z,r,w)                                      ((UINT) _txm_module_system_call6(TXM_DUO_ICMP_PING_CALL, (ULONG) i, (ULONG) a, (ULONG) d, (ULONG) z, (ULONG) r, (ULONG) w))
#define nxd_ip_raw_packet_send(i,p,d,f,t,l,s)                           ((UINT) _txm_module_system_call7(TXM_DUO_IP_RAW_PACKET_SEND_CALL, (ULONG) i, (ULONG) &p, (ULONG) d, (ULONG) f, (ULONG) o, (ULONG) t), (ULONG) s)
#define nxd_ip_raw_packet_source_send(i,p,d,f,o,t,s)                    ((UINT) _txm_module_system_call7(TXM_DUO_IP_RAW_PACKET_SOURCE_SEND_CALL,(ULONG) i, (ULONG) &p, (ULONG) d, (ULONG) f, (ULONG) o), (UINT) t, (ULONG) s)
#define nxd_ipv6_address_delete(i,a)                                    ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_DUO_IPV6_ADDRESS_DELETE_CALL, (ULONG) i, (ULONG) a, (ULONG) 0))
#define nxd_ipv6_address_get(i,a,p,e,x)                                 ((UINT) _txm_module_system_call5(TXM_DUO_IPV6_ADDRESS_GET_CALL,(ULONG) i, (ULONG) a, (ULONG) p, (ULONG) e, (ULONG) x))
#define nxd_ipv6_address_set(i,f,a,p,n)                                 ((UINT) _txm_module_system_call5(TXM_DUO_IPV6_ADDRESS_SET_CALL,(ULONG) i, (ULONG) f, (ULONG) a, (ULONG) p, (ULONG) n))
#define nxd_ipv6_default_router_add(i,r,o,f)                            ((UINT) _txm_module_system_call4(TXM_DUO_IPV6_DEFAULT_ROUTER_ADD_CALL, (ULONG) i, (ULONG) r, (ULONG) o, (ULONG) f))
#define nxd_ipv6_default_router_delete(i,r)                             ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_DUO_IPV6_DEFAULT_ROUTER_DELETE_CALL, (ULONG) i, (ULONG) r, (ULONG) 0))
#define nxd_ipv6_default_router_get(i,n,r,l,x)                          ((UINT) _txm_module_system_call5(TXM_DUO_IPV6_DEFAULT_ROUTER_GET_CALL,(ULONG) i, (ULONG) n, (ULONG) r, (ULONG) l, (ULONG) x))
#define nxd_ipv6_enable(i)                                              ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_DUO_IPV6_ENABLE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nxd_nd_cache_entry_delete(i,d)                                  ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_DUO_ND_CACHE_ENTRY_DELETE_CALL, (ULONG) i, (ULONG) d, (ULONG) 0))
#define nxd_nd_cache_entry_set(i,d,f,m)                                 ((UINT) _txm_module_system_call4(TXM_DUO_ND_CACHE_ENTRY_SET_CALL, (ULONG) i, (ULONG) d, (ULONG) f, (ULONG) m))
#define nxd_nd_cache_hardware_address_find(i,a,m,l,f)                   ((UINT) _txm_module_system_call5(TXM_DUO_ND_CACHE_HARDWARE_ADDRESS_FIND_CALL,(ULONG) i, (ULONG) a, (ULONG) m, (ULONG) l, (ULONG) f))
#define nxd_nd_cache_invalidate(i)                                      ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_DUO_ND_CACHE_INVALIDATE_CALL, (ULONG) i, (ULONG) 0, (ULONG) 0))
#define nxd_nd_cache_ip_address_find(i,a,m,l,f)                         ((UINT) _txm_module_system_call5(TXM_DUO_ND_CACHE_IP_ADDRESS_FIND_CALL,(ULONG) i, (ULONG) a, (ULONG) m, (ULONG) l, (ULONG) f))
#define nxd_tcp_client_socket_connect(s,i,p,w)                          ((UINT) _txm_module_system_call4(TXM_DUO_TCP_CLIENT_SOCKET_CONNECT_CALL, (ULONG) s, (ULONG) i, (ULONG) p, (ULONG) w))
#define nxd_tcp_socket_peer_info_get(s,p,e)                             ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_DUO_TCP_SOCKET_PEER_INFO_GET_CALL, (ULONG) s, (ULONG) p, (ULONG) e))
#define nxd_udp_packet_info_extract(p,a,o,r,i)                          ((UINT) _txm_module_system_call5(TXM_DUO_UDP_PACKET_INFO_EXTRACT_CALL,(ULONG) p, (ULONG) a, (ULONG) o, (ULONG) r, (ULONG) i))
#define nxd_udp_source_extract(p,a,o)                                   ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_DUO_UDP_SOURCE_EXTRACT_CALL, (ULONG) p, (ULONG) a, (ULONG) o))
#define nxd_udp_socket_interface_send(s,p,a,o,i)                        ((UINT) _txm_module_system_call5(TXM_DUO_UDP_SOCKET_INTERFACE_SEND_CALL, (ULONG) s, (ULONG) p, (ULONG) a, (ULONG) o, (ULONG) i))
#define nxd_udp_socket_send(s,p,a,o)                                    ((UINT) _txm_module_system_call4(TXM_DUO_UDP_SOCKET_SEND_CALL, (ULONG) s, (ULONG) &p, (ULONG) a, (ULONG) o))

#ifdef TXM_MODULE_ENABLE_NETX_DUO
#define _nx_ip_packet_deferred_receive(i,p)                             ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_NETX_IP_INTERNAL_PACKET_DEFERRED_RECEIVE_CALL, (ULONG) i, (ULONG) p, (ULONG) 0))
#define _nx_arp_packet_deferred_receive(i,p)                            ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_NETX_ARP_INTERNAL_PACKET_DEFERRED_RECEIVE_CALL, (ULONG) i, (ULONG) p, (ULONG) 0))
#define _nx_rarp_packet_deferred_receive(i,p)                           ((UINT) (_txm_module_kernel_call_dispatcher)(TXM_NETX_RARP_INTERNAL_PACKET_DEFERRED_RECEIVE_CALL, (ULONG) i, (ULONG) p, (ULONG) 0))
#endif

#define nxd_ipv6_global_address_set(i,a,p)                              ((UINT) _txm_module_system_call5(TXM_DUO_IPV6_ADDRESS_SET_CALL,(ULONG) i, (ULONG) 0, (ULONG) a, (ULONG) p, (ULONG) NX_NULL))


/* Define specific module function prototypes.  */

VOID  _txm_module_callback_request_thread_entry(ULONG id);
VOID  _txm_module_thread_shell_entry(TX_THREAD *thread_ptr, TXM_MODULE_THREAD_ENTRY_INFO *thread_info);


/* Define the module's thread shell entry function macros.  */

#define TXM_THREAD_COMPLETED_EXTENSION(a)
#define TXM_THREAD_STATE_CHANGE(a, b)

#else


/* Map the module manager APIs just in case this is being included from the module manager in the
   resident portion of the application.  */
   
#define txm_module_manager_initialize                   _txm_module_manager_initialize
#define txm_module_manager_in_place_load                _txm_module_manager_in_place_load
#define txm_module_manager_file_load                    _txm_module_manager_file_load
#define txm_module_manager_memory_load                  _txm_module_manager_memory_load
#define txm_module_manager_object_pointer_get           _txm_module_manager_object_pointer_get
#define txm_module_manager_object_pool_create           _txm_module_manager_object_pool_create
#define txm_module_manager_start                        _txm_module_manager_start
#define txm_module_manager_stop                         _txm_module_manager_stop
#define txm_module_manager_unload                       _txm_module_manager_unload
#define txm_module_manager_maximum_module_priority_set  _txm_module_manager_maximum_module_priority_set
#define txm_module_manager_external_memory_enable       _txm_module_manager_external_memory_enable

/* Define external variables used by module manager functions.  */

#ifndef TX_MODULE_MANAGER_INIT
extern ULONG                                        _txm_module_manager_properties_supported;
extern ULONG                                        _txm_module_manager_properties_required;
extern TX_BYTE_POOL                                 _txm_module_manager_byte_pool;
extern TX_BYTE_POOL                                 _txm_module_manager_object_pool;
extern UINT                                         _txm_module_manager_object_pool_created;
extern TXM_MODULE_INSTANCE                          *_txm_module_manager_loaded_list_ptr;
extern ULONG                                        _txm_module_manger_loaded_count;
extern UINT                                         _txm_module_manager_ready;
extern TX_MUTEX                                     _txm_module_manager_mutex;
extern TX_THREAD                                    _txm_module_manager_callback_response_thread;
extern UCHAR                                        _txm_module_manager_callback_response_thread_stack[TXM_MODULE_MANAGER_THREAD_STACK_SIZE];
extern TX_QUEUE                                     _txm_module_manager_callback_response_queue;
extern ULONG                                        _txm_module_manager_callback_response_queue_area[TXM_MODULE_CALLBACKS_QUEUE_DEPTH*TXM_MODULE_CALLBACKS_MESSAGE_SIZE];
extern ULONG                                        _txm_module_manager_callback_total_activated_count;
extern ULONG                                        _txm_module_manager_callback_activated_count;
extern ULONG                                        _txm_module_manager_callback_maximum_activated_count;
extern ULONG                                        _txm_module_manager_callback_error_count;
extern TXM_MODULE_CALLBACK                          *_txm_module_manager_callback_available_ptr;
extern TXM_MODULE_CALLBACK                          *_txm_module_manager_callback_activated_ptr;
extern TXM_MODULE_CALLBACK                          _txm_module_manager_callback_array[TXM_MODULE_MAX_CALLBACKS];
extern VOID                                         *_txm_module_manager_callback_handler_array[TXM_MODULE_MAX_CALLBACKS];
#endif

/* Define internal module manager function prototypes.  */

UINT  _txm_module_manager_application_request(ULONG request, ULONG param_1, ULONG param_2, ULONG param_3);
VOID  _txm_module_manager_callback_configure(UINT type, VOID *object_ptr, ULONG id, VOID *application_callback, VOID **manager_callback);
VOID  _txm_module_manager_callback_deactivate(TXM_MODULE_CALLBACK *callback_instance);
VOID  _txm_module_manager_callback_response_thread_entry(ULONG id);
VOID  _txm_module_manager_callback_transfer(ULONG index, ULONG param_1, ULONG param_2);
#ifdef FX_FILEX_PRESENT
UINT  _txm_module_manager_file_load(TXM_MODULE_INSTANCE *module_instance, CHAR *module_name, FX_MEDIA *media_ptr, CHAR *file_name);
#endif
UINT  _txm_module_manager_initialize(VOID *module_memory_start, ULONG module_memory_size);
UINT  _txm_module_manager_in_place_load(TXM_MODULE_INSTANCE *module_instance, CHAR *name, VOID *module_location);
ULONG _txm_module_manager_kernel_dispatch(ULONG request, ULONG param_1, ULONG param_2, ULONG param3);
UINT  _txm_module_manager_object_pointer_get(UINT object_type, CHAR *name, VOID **object_ptr);
UINT  _txm_module_manager_object_pool_create(VOID *object_memory, ULONG object_memory_size);
UINT  _txm_module_manager_memory_load(TXM_MODULE_INSTANCE *module_instance, CHAR *module_name, VOID *module_location);
UINT  _txm_module_manager_start(TXM_MODULE_INSTANCE *module_instance);
UINT  _txm_module_manager_stop(TXM_MODULE_INSTANCE *module_instance);
UINT  _txm_module_manager_thread_create(TX_THREAD *thread_ptr, CHAR *name, VOID (*shell_function)(TX_THREAD *, TXM_MODULE_INSTANCE *), 
                               VOID (*entry_function)(ULONG), ULONG entry_input,
                               VOID *stack_start, ULONG stack_size, UINT priority, UINT preempt_threshold,
                               ULONG time_slice, UINT auto_start, TXM_MODULE_INSTANCE *module_instance);
VOID  _txm_module_manager_name_build(CHAR *module_name, CHAR *thread_name, CHAR *combined_name);
VOID  _txm_module_manager_thread_stack_build(TX_THREAD *thread_ptr, VOID (*shell_function)(TX_THREAD *, TXM_MODULE_INSTANCE *));
UINT  _txm_module_manager_unload(TXM_MODULE_INSTANCE *module_instance);
ULONG _txm_module_manager_user_mode_entry(ULONG request, ULONG param_1, ULONG param_2, ULONG param3);
UINT  _txm_module_manager_maximum_module_priority_set(TXM_MODULE_INSTANCE *module_instance, UINT priority);
UINT  _txm_module_manager_external_memory_enable(TXM_MODULE_INSTANCE *module_instance, VOID *start_address, ULONG length, UINT attributes);

/* Define port specific module manager prototypes.  */

TXM_MODULE_MANAGER_ADDITIONAL_PROTOTYPES

#endif


/* Determine if a C++ compiler is being used.  If so, complete the standard
   C conditional started above.  */
#ifdef __cplusplus
        }
#endif

#endif
