
/* Copyright (c) 2016-2017 Qualcomm Technologies, Inc.
   All rights reserved.
   Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/* Copyright (c) 2015 Qualcomm Atheros, Inc.
   All rights reserved.
   Qualcomm Atheros Confidential and Proprietary.
*/ 

/**
  @file qapi_ns_gen_v6.h

  @brief 
  IPv6 Networking Services (NS).
*/




#ifndef _QAPI_NS_GEN_V6_H_
#define _QAPI_NS_GEN_V6_H_

#include "stdint.h"
#include "qapi/qapi_types.h"
#include "qapi/qapi_netservices.h"
#include "qapi_status.h"


/* Net QAPI REQUEST ID DEFINES */

#define  TXM_QAPI_NET_IPV6_GET_ADDRESS                  TXM_QAPI_NET_BASE + 4
#define  TXM_QAPI_NET_PING6                             TXM_QAPI_NET_BASE + 5
#define  TXM_QAPI_NET_IPV6_ROUTE                        TXM_QAPI_NET_BASE + 6
#define  TXM_QAPI_NET_IPV6_CONFIG_ROUTER_PREFIX         TXM_QAPI_NET_BASE + 7
#define  TXM_QAPI_NET_IPV6_GET_SCOPE_ID                 TXM_QAPI_NET_BASE + 8
#define  TXM_QAPI_NET_PING6_2                           TXM_QAPI_NET_BASE + 22

/** @addtogroup qapi_net_services_datatypes
@{ */

/**
 * Checks whether the IPv6 address is link local.
 *
 * This macro returns 1 if the passed IPv6 address is link local.
 * Link local address format is fe80::/64. The
 * first 10 bits of the address are 1111111010, followed by
 * 54 zeros, followed by 64 bits of the interface identifier.
 *
 * @param[in] ipv6_Address    IPv6 address to check.
 *
 * @return    1 if the IPv6 address is link local, or 0 otherwise.
 *
 */

#define QAPI_IS_IPV6_LINK_LOCAL(ipv6_Address) \
       ((ipv6_Address != NULL) && \
        (((uint8_t *)ipv6_Address)[0] == 0xfe) && \
        (((uint8_t *)ipv6_Address)[1] == 0x80) && \
        (((uint8_t *)ipv6_Address)[2] == 0x0) && \
        (((uint8_t *)ipv6_Address)[3] == 0x0) && \
        (((uint8_t *)ipv6_Address)[4] == 0x0) && \
        (((uint8_t *)ipv6_Address)[5] == 0x0) && \
        (((uint8_t *)ipv6_Address)[6] == 0x0) && \
        (((uint8_t *)ipv6_Address)[7] == 0x0))

/**
 * Checks whether the IPv6 address is multicast.
 *
 * @param[in] ipv6_Address    IPv6 address to check.
 *
 * @return    1 if the IPv6 address is multicast, 0 otherwise.
 *
 */
#define QAPI_IS_IPV6_MULTICAST(ipv6_Address) \
	(ipv6_Address[0] == 0xff)

#define IF_NAMELEN   20        /* default max length for iface names */

/**
 * @brief IPv6 Ping input
 */
typedef struct qapi_Net_Ping_V6_s
{
   uint8_t ipv6_addr[16];
   /**< Destination to ping */

   uint8_t ipv6_src[16];
   /**< Source address */

   uint32_t size;
   /**< Packet size */

   uint32_t timeout;
   /**< Timeout value (in ms)*/

   char  *ifname;
   /**< Interface name*/

} qapi_Net_Ping_V6_t;

typedef struct
{
    uint8_t  ipv6RouteDest[16];
    /**< Destination IPv6 address of this route. */

    uint32_t ipv6RoutePfxLength;
    /**< Indicates the prefix length of the destination address. */

    uint8_t  ipv6RouteNextHop[16];
    /**< Address of the next system en route. */

    uint32_t ipv6RouteProtocol;
    /**< Routing mechanism via which this route was learned. */

    uint32_t ipv6RouteIfIndex;
    /**< Index value that uniquely identifies the local interface through
         which the next hop of this route should be reached. */

    char     ifName[IF_NAMELEN];
    /**< Textual name of the interface. */

} qapi_Net_IPv6_Route_t;

/** Maximum IPv6 routing configurations. */
#define QAPI_NET_IPV6_MAX_ROUTES    (3)

/** IPv6 routing objects list.  */
typedef struct
{
    uint32_t                route_Count;
    /**< Number of qapi_Net_IPv6_Route_t in the routing table */

    qapi_Net_IPv6_Route_t   route[QAPI_NET_IPV6_MAX_ROUTES];
    /**< Array of type qapi_Net_IPv6_Route_t. */

} qapi_Net_IPv6_Route_List_t;

/** @} */ /* end_addtogroup qapi_net_services_datatypes */

#ifdef  QAPI_TXM_MODULE     // USER_MODE_DEFS

#define qapi_Net_IPv6_Get_Address(a,b,c,d,e,f,g,h,i)         ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_NET_IPV6_GET_ADDRESS            , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) e, (ULONG) f, (ULONG) g, (ULONG) h, (ULONG) i, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_Ping6(a,b,c)                                ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_NET_PING6                       , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_IPv6_Route(a,b,c,d,e,f)                     ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_NET_IPV6_ROUTE                  , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) e, (ULONG) f, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_IPv6_Config_Router_Prefix(a,b,c,d,e)        ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_NET_IPV6_CONFIG_ROUTER_PREFIX   , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) e, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_IPv6_Get_Scope_ID(a,b)                      ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_NET_IPV6_GET_SCOPE_ID           , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_Ping6_2(a,b)                                ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_NET_PING6_2                     , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#else

/** @ingroup qapi_Net_Ping6
 *
 * Sends an IPv6 ping request.
 *
 * @param[in] ipv6_addr    IPv6 address to which to send a ping.
 * @param[in] size         Number of data bytes to send.
 * @param[in] ifname       Pointer to the interface name; the interface name is 
                           required when pinging an IPv6 link-local address.
 *
 * @return 
 * - 0 -- Ping response is received.
 * - 1 -- Ping request timed out.
 * - -1 -- Error.
 */
qapi_Status_t qapi_Net_Ping6(uint8_t ipv6_Addr[16], uint32_t size, const char * interface_Name);

/**
 * @brief Send an IPv6 ping request
 *
 * @param[in]      ping6_buf    Pointer to IPv6 ping structure. The structure will
                                take IPv6 address to send ping to, IPv6 address 
                                to send ping via this source, Number of data bytes
                                to send, Ping request timeout value (in ms) and 
                                when pinging IPv6 link-local address interface 
                                name is required.
 * @param[out]     ping_resp    Store ping response code and type for ICMP echo response received.
 *
 * @return QAPI_OK:       successful ping response is received.
 *         QAPI_ERROR:    error and response buffer is filled with error code.
 */

qapi_Status_t qapi_Net_Ping6_2(qapi_Net_Ping_V6_t *ping6_buf, qapi_Ping_Info_Resp_t *ping_resp);

/** @ingroup qapi_Net_IPv6_Get_Address
 * 
 * Gets the IPv6 addresses of an interface.
 *
 * @param[in] interface_Name               Pointer to the name of the network interface.
 * @param[in] link_Local                   Pointer to the first global unicast address.
 * @param[in] global                       Pointer to the link-local unicast address.
 * @param[in] default_Gateway              Pointer to the default gateway address.
 * @param[in] global_Second                Pointer to the second global unicast address.
 * @param[in] link_Local_Prefix            Pointer to the prefix length of the link-local address.
 * @param[in] global_Prefix                Pointer to the prefix length of the first global address.
 * @param[in] default_Gateway_Prefix       Pointer to the prefix length of the default gateway address.
 * @param[in] global_Second_Prefix         Pointer to the prefix length of the second global address.
 *
 * @return On success, 0 is returned. On error, -1 is returned.
 */

qapi_Status_t qapi_Net_IPv6_Get_Address(
                const char *interface_Name,
                uint8_t *link_Local,
                uint8_t *global,
                uint8_t *default_Gateway,
                uint8_t *global_Second,
                uint32_t *link_Local_Prefix,
                uint32_t *global_Prefix,
                uint32_t *default_Gateway_Prefix,
                uint32_t *global_Second_Prefix);

/** @cond */

/* Adds a new entry to the prefixes to be advertised by the router.
 *
 * @param[in] interface_Name             Pointer to the name of the network interface.
 * @param[in] ipv6_Addr                  Pointer to the ipv6RouteDest value.
 * @param[in] prefix_Length              Prefix length (1 to 128).
 * @param[in] preferred_Lifetime         Preferred lifetime in seconds.
 * @param[in] valid_Lifetime             Valid lifetime in seconds.
 *
 * @return On success, 0 is returned. On error, -1 is returned.
 */

qapi_Status_t qapi_Net_IPv6_Config_Router_Prefix(
                const char *interface_Name,
                uint8_t *ipv6_Addr,
                uint32_t prefix_Length,
                uint32_t preferred_Lifetime,
                uint32_t valid_Lifetime);

/** @endcond */

/** @ingroup qapi_Net_IPv6_Route
 * 
 * Adds, deletes, or queries the IPv6 route.
 *
 * @param[in] interface_Name    Pointer to the name of the network interface.
 * @param[in] cmd   Command mode. Possible values are: \n
 *                  - QAPI_NET_ROUTE_ADD_E (0) -- Add route
 *                  - QAPI_NET_ROUTE_DEL_E (1) -- Delete route
 *                  - QAPI_NET_ROUTE_SHOW_E (2) -- Show route @tablebulletend
 * @param[in] ipv6_Addr        Pointer to the IPv6 address.
 * @param[in] prefix_Length    Pointer to the IPv6 prefix length.
 * @param[in] next_Hop         Pointer to the IPv6 gateway address.
 * @param[in] route_List       Pointer to the buffer containing a list of routes, 
 *                             returned with the QAPI_NET_ROUTE_SHOW_E command.
 *
 * @return On success, 0 is returned. On error, -1 is returned.
 */

qapi_Status_t qapi_Net_IPv6_Route(
                const char *interface_Name,
                qapi_Net_Route_Command_t cmd,
                uint8_t *ipv6_Addr,
                uint32_t *prefix_Length,
                uint8_t *next_Hop,
                qapi_Net_IPv6_Route_List_t *route_List);

/** @ingroup qapi_Net_IPv6_Get_Scope_ID
 *
 * Returns the scope ID for the interface.
 *
 * When using link-local addressing with the IPv6 protocol, the scope ID must be specified 
 * along with the destination address. The application should use this function to retrieve a scope ID
 * based on the interface name.
 *
 * @param[in]      interface_Name    Pointer to the name of the interface for which to
 *                                   retrieve the scope ID.
 * @param[out]     scope_ID          Pointer to the location store the scope ID.
 *
 * @return         
 * 0 on success, or a negative error code.
 *
 */

qapi_Status_t qapi_Net_IPv6_Get_Scope_ID(const char *interface_Name, int32_t *scope_ID);

#endif

#endif /* _QAPI_NS_GEN_V6_H_ */
