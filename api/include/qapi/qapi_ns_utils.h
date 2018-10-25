/* Copyright (c) 2016-2017 Qualcomm Technologies, Inc.
   All rights reserved.
   Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/* Copyright (c) 2015 Qualcomm Atheros, Inc.
   All rights reserved.
   Qualcomm Atheros Confidential and Proprietary.
*/ 
/**
  @file qapi_ns_utils.h

  @brief 
  Networking Utilities (NS).
*/


#ifndef _QAPI_NS_UTILS_H_
#define _QAPI_NS_UTILS_H_

#include "stdint.h"
#include "qapi/qapi_net_status.h"

#include "qapi_data_txm_base.h"

/* Net QAPI REQUEST ID DEFINES */

#define  TXM_QAPI_NET_GET_ALL_IFNAMES                   TXM_QAPI_NET_BASE + 9
#define  TXM_QAPI_NET_INTERFACE_GET_PHYSICAL_ADDRESS    TXM_QAPI_NET_BASE + 10
#define  TXM_QAPI_NET_INTERFACE_EXIST                   TXM_QAPI_NET_BASE + 11
#define  TXM_QAPI_NET_P_TO_N                            TXM_QAPI_NET_BASE + 12
#define  TXM_QAPI_NET_N_TO_P                            TXM_QAPI_NET_BASE + 13
#define  TXM_QAPI_NET_GET_ADDR                          TXM_QAPI_NET_BASE + 14

/** @file qapi_ns_utils.h
*
* @addtogroup qapi_networking_services
* @{
*
* @brief Utility functions for Networking Services (NS)
*
* @details
*
* @}
*/

/** @addtogroup qapi_networking_services
@{ */

/** Max length for interface name */
#define QAPI_NET_IFNAME_LEN     12

#define QAPI_NET_ICMP_REQUEST_TIMEOUT              -1    /* Ping requet timeout */

#define QAPI_NET_ICMP_BIND_FAILED                  -2    /* Ping source binding failed */

/* ICMP type values */
#define QAPI_NET_ICMP_ECHOREP   0      /* ICMP Echo reply */
#define QAPI_NET_ICMP_DESTIN    3      /* Destination Unreachable */
#define QAPI_NET_ICMP_SOURCEQ   4      /* Source quench */
#define QAPI_NET_ICMP_REDIR     5      /* Redirect */
#define QAPI_NET_ICMP_ECHOREQ   8      /* ICMP Echo request */
#define QAPI_NET_ICMP_TIMEX     11      /* Time exceeded */
#define QAPI_NET_ICMP_PARAM     12      /* Parameter problem */
#define QAPI_NET_ICMP_TIMEREQ   13      /* Timestamp request */
#define QAPI_NET_ICMP_TIMEREP   14      /* Timestamp reply */
#define QAPI_NET_ICMP_INFO      15      /* Information request */

/* Destination unreachable error code */
#define QAPI_NET_ICMP_DESTIN_NETWORK_UNREACHABLE        0    /* Destination network unreachable */
#define QAPI_NET_ICMP_DESTIN_HOST_UNREACHABLE           1    /* Destination host unreachable */
#define QAPI_NET_ICMP_DESTIN_PROTOCOL_UNREACHABLE       2    /* Destination protocol unreachable */
#define QAPI_NET_ICMP_DESTIN_PORT_UNREACHABLE           3    /* Destination port unreachable */
#define QAPI_NET_ICMP_DESTIN_FRAG_REQUIRED              4    /* Fragmentation required, and DF flag set */
#define QAPI_NET_ICMP_DESTIN_SOURCE_ROUTE_FAILED        5    /* Source route failed */
#define QAPI_NET_ICMP_DESTIN_NETWORK_UNKNOWN            6    /* Destination network unknown */
#define QAPI_NET_ICMP_DESTIN_HOST_UNKNOWN               7    /* Destination host unknown */
#define QAPI_NET_ICMP_DESTIN_SOURCE_HOST_ISOLATED       8    /* Source host isolated */
#define QAPI_NET_ICMP_DESTIN_NETWORK_ADMIN_PROHIBIT     9    /* Network administratively prohibited */
#define QAPI_NET_ICMP_DESTIN_HOST_ADMIN_PROHIBIT        10   /* Host administratively prohibited */
#define QAPI_NET_ICMP_DESTIN_NETWORK_UNREACHABLE_TOS    11   /* Network unreachable for ToS */
#define QAPI_NET_ICMP_DESTIN_HOST_UNREACHABLE_TOS       12   /* Host unreachable for ToS */
#define QAPI_NET_ICMP_DESTIN_COMM_ADMIN_PROHIBIT        13   /* Communication administratively prohibited */
#define QAPI_NET_ICMP_DESTIN_HOST_PRECEDENCE_VIOLATION  14   /* Host precedence violation */
#define QAPI_NET_ICMP_DESTIN_PRECEDENCE_CUTOFF_IN_PROG  15   /* Precedence cutoff in effect */

/* Redirect error code */
#define QAPI_NET_ICMP_REDIR_DATAGRAM_NETWORK            0    /* Redirect datagram for the Network */
#define QAPI_NET_ICMP_REDIR_DATAGRAM_HOST               1    /* Redirect datagram for the Host */
#define QAPI_NET_ICMP_REDIR_DATAGRAM_ToS_NETWORK        2    /* Redirect datagram for the ToS & network */
#define QAPI_NET_ICMP_REDIR_DATAGRAM_ToS_HOST           3    /* Redirect datagram for the ToS & host */

/* Time exceeded error code */
#define QAPI_NET_ICMP_TIMEX_TTL_EXPIRED                 0    /* TTL expired in transit */
#define QAPI_NET_ICMP_TIMEX_FRAG_ASSEMBLY_TIME_EXCEEDED 1    /* Fragment reassembly time excedded */

/* Parameter problem error code */
#define QAPI_NET_ICMP_PARAM_POINTER_ERROR               0    /* Pointer indicates the error */
#define QAPI_NET_ICMP_PARAM_REQUIRE_PARAM_MISSING       1    /* Missing a required option */
#define QAPI_NET_ICMP_PARAM_BAD_LENGTH                  2    /* Bad length */

/**
 * @brief Network Interface object
 */
typedef struct
{
    uint32_t if_Index;
    /**< ifIndex in rfc1213-mib2 which ranges from 1 to the returned
         value of qapi_Net_Get_Number_of_Interfaces() if value is >= 1 */

    char     interface_Name[QAPI_NET_IFNAME_LEN];  /* null terminated name */
    /**< Interface name (null terminated) */

    qbool_t  if_Is_Up;
    /**< true if interface is "up", false if interface is not "up" (e.g. down, testing) */

} qapi_Net_Ifnameindex_t;

#ifdef  QAPI_TXM_MODULE     // USER_MODE_DEFS

#define qapi_Net_Get_All_Ifnames(a)                          ((UINT)         (_txm_module_system_call12)(TXM_QAPI_NET_GET_ALL_IFNAMES                 , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_Interface_Get_Physical_Address(a,b,c)       ((UINT)         (_txm_module_system_call12)(TXM_QAPI_NET_INTERFACE_GET_PHYSICAL_ADDRESS  , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_Interface_Exist(a)                          ((qbool_t)      (_txm_module_system_call12)(TXM_QAPI_NET_INTERFACE_EXIST                 , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define inet_pton(a,b,c)                                     ((UINT)         (_txm_module_system_call12)(TXM_QAPI_NET_P_TO_N                          , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define inet_ntop(a,b,c,d)                                   ((const char *) (_txm_module_system_call12)(TXM_QAPI_NET_N_TO_P                     , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define inet_addr(a)                                         ((UINT)         (_txm_module_system_call12)(TXM_QAPI_NET_GET_ADDR                   , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#else


/**
 * @brief Retrieve textual names of all network interfaces
 *
 * @details
 *
 * @param[out]  ifname_index    Array to contain the retrieved info
 *
 * @return       Number of network interfaces
 */
int32_t qapi_Net_Get_All_Ifnames(qapi_Net_Ifnameindex_t *if_Name_Index);

/**
 * @brief Parse the passed address string into an IPv4/IPv6 address
 *
 * @details
 *
 * @param[in]   af      Address family. AF_INET for IPv4, AF_INET6 for IPv6
 *
 * @param[in]   src     IPv4 or IPv6 address string (null-terminated)
 *
 * @param[out]  dst     Resulting IPv4/IPv6 address
 *
 * @return      0 if OK, 1 if bad address format, -1 if af is not AF_INET or AF_INET6
 */
int32_t inet_pton(int32_t af, const char *src, void *dst);

/**
 * @brief Format an IPv4/IPv6 address into a null-terminated string 
 *
 * @details
 *
 * @param[in]   af      Address family. AF_INET for IPv4, AF_INET6 for IPv6
 *
 * @param[in]   src     Pointer to IPv4 or IPv6 address
 *
 * @param[out]  dst     Pointer to output buffer to contain IPv4/IPv6 address string
 *
 * @param[out]  size    Size of output buffer in bytes
 *
 * @return      Pointer to resulting string if OK, else NULL
 */
const char *inet_ntop(int32_t af, const void *src, char *dst, size_t size);

/** 
 * @brief Retrieves the physical address and physical address length of an
 *        interface.
 *
 * @details This function retrieves the physical address and physical address
 * length for the interface.  Please note that all arguments must NOT be 0.
 * Please also note that this function does NOT allocate space for the address,
 * and therefore the caller must NOT free it.
 *
 * @code
 *      int status;
 *      const char * address = 0;
 *      uint32_t address_length = 0;
 *      status = qapi_Net_Interface_Get_Physical_Address(interface_name, &address, &address_length);
 *      if ( status == 0 ) {
 *              // at this point address contains the physical address and
 *              // address_length contains the physical address length
 *              // address[0] is the MSB of the physical address
 *      }
 * @endcode
 *
 * @param[in]      interface_name    The name of the interface for which to
 *                                   retrive physical address and or physical
 *                                   address length.
 * @param[out]     address      Pointer where to save the address of the buffer
 *                              containing the physical address.
 * @param[out]     address_Len  Pointer where to store the physical address length.
 *
 * @return       0 on success, or a negative error code on failure.
 *
 */
int32_t qapi_Net_Interface_Get_Physical_Address(const char * interface_Name, const uint8_t ** address, uint32_t * address_Len);

/** 
 * @brief Check if the interface exists or not
 *
 * @code
 *      int exist;
 *
 *      exist = qapi_Net_Interface_Exist("rmnet_data0");
 *      if ( exist == 1 )
 *      {
 *          printf("rmnet_data0 exists\r\n");
 *      }
 * @endcode
 *
 * @param[in]      interface_name    The name of the interface for which to
 *                                   check if it exists or not.
 *
 * @return       0 if NOT exist or 1 if the interface does exist
 *
 */
qbool_t qapi_Net_Interface_Exist(const char * interface_Name);

/** @} */ /* end_addtogroup qapi_networking_services */

#endif

/**
 * @brief Ping response structure
 */
typedef struct qapi_Ping_Info_Resp_s
{
  int ptype;
  /**< ICMP type for ping */

  int pcode;
  /**< ICMP code for ping */

  char perror[128];
  /**< Response description for ping */

}qapi_Ping_Info_Resp_t;


#endif /* _QAPI_NS_UTILS_H_ */


