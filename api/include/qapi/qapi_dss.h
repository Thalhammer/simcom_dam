/**
  @file 
  qapi_dss.h

  @brief
  DSS header to interact with underlying data control plane.
*/
  
/*===========================================================================

  Copyright (c) 2017 Qualcomm Technologies, Inc. All Rights Reserved

  Confidential and Proprietary - Qualcomm Technologies, Inc.

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies, Inc.
===========================================================================*/

/*======================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *	 This section contains comments describing changes made to the
 *	 module. Notice that changes are listed in reverse chronological
 *	 order.
 *
 *	
 *
 *
 * when                  who         what, where, why
 * ---------- 	--- 		------------------------------------------------
 ======================================================================*/
 

#ifdef __cplusplus
extern "C" {
#endif

#ifndef QAPI_DSS_H
#define QAPI_DSS_H 

#include <stdint.h>
#include "qapi_status.h"

#include "qapi_data_txm_base.h"

/* DSS QAPI REQUEST ID DEFINES */
#define  TXM_QAPI_DSS_INIT                         TXM_QAPI_DSS_BASE + 1
#define  TXM_QAPI_DSS_RELEASE                      TXM_QAPI_DSS_BASE + 2
#define  TXM_QAPI_DSS_GET_DATA_SRVC_HNDL           TXM_QAPI_DSS_BASE + 3
#define  TXM_QAPI_DSS_REL_DATA_SRVC_HNDL           TXM_QAPI_DSS_BASE + 4
#define  TXM_QAPI_DSS_SET_DATA_CALL_PARAM          TXM_QAPI_DSS_BASE + 5
#define  TXM_QAPI_DSS_START_DATA_CALL              TXM_QAPI_DSS_BASE + 6
#define  TXM_QAPI_DSS_STOP_DATA_CALL               TXM_QAPI_DSS_BASE + 7
#define  TXM_QAPI_DSS_GET_PKT_STATS                TXM_QAPI_DSS_BASE + 8
#define  TXM_QAPI_DSS_RESET_PKT_STATS              TXM_QAPI_DSS_BASE + 9
#define  TXM_QAPI_DSS_GET_CALL_END_REASON          TXM_QAPI_DSS_BASE + 10
#define  TXM_QAPI_DSS_GET_CALL_TECH                TXM_QAPI_DSS_BASE + 11
#define  TXM_QAPI_DSS_GET_CURRENT_DATA_BEARER_TECH TXM_QAPI_DSS_BASE + 12
#define  TXM_QAPI_DSS_GET_DEVICE_NAME              TXM_QAPI_DSS_BASE + 13
#define  TXM_QAPI_DSS_GET_QMI_PORT_NAME            TXM_QAPI_DSS_BASE + 14
#define  TXM_QAPI_DSS_GET_IP_ADDR_COUNT            TXM_QAPI_DSS_BASE + 15
#define  TXM_QAPI_DSS_GET_IP_ADDR                  TXM_QAPI_DSS_BASE + 16
#define  TXM_QAPI_DSS_GET_LINK_MTU                 TXM_QAPI_DSS_BASE + 17
#define  TXM_QAPI_DSS_GET_IP_ADDR_PER_FAMILY       TXM_QAPI_DSS_BASE + 18
#define  TXM_QAPI_DSS_SEND_NIPD_DATA               TXM_QAPI_DSS_BASE + 19
#define  TXM_QAPI_DSS_ADD_MO_EX_IP_FILTERS         TXM_QAPI_DSS_BASE + 20
#define  TXM_QAPI_DSS_DEL_MO_EX_IP_FILTERS         TXM_QAPI_DSS_BASE + 21


typedef void * qapi_DSS_Hndl_t;

/** @addtogroup qapi_dss_datatypes
@{ */

/** @name Unique Radio Technology Bitmasks
@{ */

#define QAPI_DSS_RADIO_TECH_UNKNOWN 0x00000000                 /**< Technology Unknown. */
#define QAPI_DSS_RADIO_TECH_MIN     0x00000001                 /**< Start. */
#define QAPI_DSS_RADIO_TECH_UMTS    QAPI_DSS_RADIO_TECH_MIN    /**< UMTS. */
#define QAPI_DSS_RADIO_TECH_CDMA    0x00000002                 /**< CDMA. */
#define QAPI_DSS_RADIO_TECH_1X      0x00000004                 /**< 1X. */
#define QAPI_DSS_RADIO_TECH_DO      0x00000008                 /**< DO. */
#define QAPI_DSS_RADIO_TECH_LTE     0x00000010                 /**< LTE. */
#define QAPI_DSS_RADIO_TECH_TDSCDMA 0x00000020                 /**< TDSCDMA. */

/** @} */ /* end_namegroup */

/** @name Supported Radio Technologies
@{ */

#define QAPI_DSS_RADIO_TECH_MAX 6

/** @} */ /* end_namegroup */

/** @name Extended Radio Technology
@{ */

#define QAPI_DSS_EXT_RADIO_TECH_UNKNOWN  0x00
#define QAPI_DSS_EXT_RADIO_TECH_MIN      0x01 
#define QAPI_DSS_EXT_RADIO_TECH_NONIP    QAPI_DSS_EXT_RADIO_TECH_MIN

/** @} */ /* end_namegroup */

/** @name Supported Extended Radio Technologies
@{ */

#define QAPI_DSS_EXT_RADIO_TECH_MAX 1   

/** @} */ /* end_namegroup */

/** @name MO Exception Data  
@{ */
 
#define QAPI_DSS_MO_EXCEPTION_NONE       0x00    /**< None. */
#define QAPI_DSS_MO_EXCEPTION_IP_DATA    0x01    /**< MO Exception IP Data. */
#define QAPI_DSS_MO_EXCEPTION_NONIP_DATA 0x02    /**< MO Exception Non-IP Data. */

/** @} */ /* end_namegroup */

/** @name Call Information
@{ */

#define QAPI_DSS_CALL_INFO_USERNAME_MAX_LEN  127  /**< Maxiumum Length of username. */
#define QAPI_DSS_CALL_INFO_PASSWORD_MAX_LEN  127  /**< Maxiumum Length of Password. */
#define QAPI_DSS_CALL_INFO_APN_MAX_LEN       150  /**< Maxiumum Length of APN. */

/** @} */ /* end_namegroup */

/** @name Device Name
          For example, rmnet_sdioxx, rmnet_xx.
@{ */

#define QAPI_DSS_CALL_INFO_DEVICE_NAME_MAX_LEN 12  /**< Maxiumum Length of device name. */

/** @} */ /* end_namegroup */

/** @name Maximum Client Handles Supported
@{ */

#define QAPI_DSS_MAX_DATA_CALLS 20

/** @} */ /* end_namegroup */

/** @name QAPI_DSS Error Codes
@{ */

#define QAPI_DSS_SUCCESS   0   /**< Indicates that the operation was successful. */
#define QAPI_DSS_ERROR    -1   /**< Indicates that the operation was not successful. */

/** @} */ /* end_namegroup */

/** @name IP Versions
@{ */

#define QAPI_DSS_IP_VERSION_4    4
#define QAPI_DSS_IP_VERSION_6    6
#define QAPI_DSS_IP_VERSION_4_6 10

/** @} */ /* end_namegroup */

/** @name Supported Modes of Operation
@{ */

#define QAPI_DSS_MODE_GENERAL 0

/** @} */ /* end_namegroup */

/** @name Maximum supported MO exception filters
@{ */

#define QAPI_DSS_MAX_EXCEPTION_FILTERS 255

/** @} */ /* end_namegroup */

/** @name Maximum IPv6 address length 
@{ */

#define QAPI_DSS_IPV6_ADDR_LEN 16

/** @} */ /* end_namegroup */


/** @name MO exception data filter error mask 
@{ */

typedef uint64_t qapi_DSS_MO_Filter_Error_Mask_t;
#define QAPI_DSS_FILTER_PARAM_NONE_V01            0x00000000 /**< No errors. */
#define QAPI_DSS_FILTER_PARAM_IP_VERSION_V01      0x00000001 /**< IP version. */
#define QAPI_DSS_FILTER_PARAM_IPV4_SRC_ADDR_V01   0x00000002 /**< IPv4 source address. */
#define QAPI_DSS_FILTER_PARAM_IPV4_DEST_ADDR_V01  0x00000004 /**< IPv4 destination address. */
#define QAPI_DSS_FILTER_PARAM_IPV4_TOS_V01        0x00000008 /**< IPv4 type of service. */
#define QAPI_DSS_FILTER_PARAM_IPV6_SRC_ADDR_V01   0x00000010 /**< IPv6 source address. */
#define QAPI_DSS_FILTER_PARAM_IPV6_DEST_ADDR_V01  0x00000020 /**< IPv6 destination address. */
#define QAPI_DSS_FILTER_PARAM_IPV6_TRF_CLS_V01    0x00000040 /**< IPv6 traffic class. */
#define QAPI_DSS_FILTER_PARAM_IPV6_FLOW_LABEL_V01 0x00000080 /**< IPv6 flow label. */
#define QAPI_DSS_FILTER_PARAM_XPORT_PROT_V01      0x00000100 /**< Transport protocol. */
#define QAPI_DSS_FILTER_PARAM_TCP_SRC_PORT_V01    0x00000200 /**< TCP source port. */
#define QAPI_DSS_FILTER_PARAM_TCP_DEST_PORT_V01   0x00000400 /**< TCP destination port. */
#define QAPI_DSS_FILTER_PARAM_UDP_SRC_PORT_V01    0x00000800 /**< UDP source port. */
#define QAPI_DSS_FILTER_PARAM_UDP_DEST_PORT_V01   0x00001000 /**< UDP destination port. */
#define QAPI_DSS_FILTER_PARAM_ICMP_TYPE_V01       0x00002000 /**< ICMP type. */
#define QAPI_DSS_FILTER_PARAM_ICMP_CODE_V01       0x00004000 /**< ICMP code. */
#define QAPI_DSS_FILTER_PARAM_ESP_SPI_V01         0x00008000 /**< Encapsulating SPI. */
#define QAPI_DSS_FILTER_PARAM_AH_SPI_V01          0x00010000 /**< Authentication header SPI. */

/** @} */ /* end_namegroup */

/** @name MO exception data IPv4 filter mask 
@{ */

typedef uint64_t qapi_DSS_IPv4_Filter_Mask_t;
#define QAPI_DSS_IPV4_FILTER_MASK_NONE            0x00000000 /**< No parameters */
#define QAPI_DSS_IPV4_FILTER_MASK_SRC_ADDR        0x00000001 /**< IPv4 source address */
#define QAPI_DSS_IPV4_FILTER_MASK_DEST_ADDR       0x00000002 /**< IPv4 destination address */
#define QAPI_DSS_IPV4_FILTER_MASK_TOS             0x00000004 /**< IPv4 traffic class */

/** @} */ /* end_namegroup */

/** @name MO exception data IPv6 filter mask 
@{ */

typedef uint64_t qapi_DSS_IPv6_Filter_Mask_t;
#define QAPI_DSS_IPV6_FILTER_MASK_NONE            0x00000000 /**< No parameters */
#define QAPI_DSS_IPV6_FILTER_MASK_SRC_ADDR        0x00000001 /**< IPv6 source address */
#define QAPI_DSS_IPV6_FILTER_MASK_DEST_ADDR       0x00000002 /**< IPv6 destination address */
#define QAPI_DSS_IPV6_FILTER_MASK_TRAFFIC_CLASS   0x00000004 /**< IPv6 traffic class */
#define QAPI_DSS_IPV6_FILTER_MASK_FLOW_LABEL      0x00000008 /**< IPv6 flow label */

/** @} */ /* end_namegroup */

/** @name Transport port filter mask information
@{ */

typedef uint64_t qapi_DSS_Port_Info_Filter_Mask_t;
#define QAPI_DSS_PORT_INFO_FILTER_MASK_NONE       0x00000000 /**< No parameters */
#define QAPI_DSS_PORT_INFO_FILTER_MASK_SRC_PORT   0x00000001 /**< Source port */
#define QAPI_DSS_PORT_INFO_FILTER_MASK_DEST_PORT  0x00000002 /**< Destination port */

/** @} */ /* end_namegroup */

/** @name ICMP filter mask information
@{ */

typedef uint64_t qapi_DSS_ICMP_Info_Filter_Mask_t;
#define QAPI_DSS_ICMP_FILTER_MASK_NONE            0x00000000 /**< No parameters */
#define QAPI_DSS_ICMP_FILTER_MASK_MSG_TYPE        0x00000001 /**< Message type */
#define QAPI_DSS_ICMP_FILTER_MASK_MSG_CODE        0x00000002 /**< Message code */ 

/** @} */ /* end_namegroup */

/** @name IPSec filter mask information 
@{ */

typedef uint64_t qapi_DSS_IPSec_Info_Filter_Mask_t;
#define QAPI_DSS_IPSEC_FILTER_MASK_NONE           0x00000000 /**< No parameters */
#define QAPI_DSS_IPSEC_FILTER_MASK_SPI            0x00000001 /**< Security parameter index */

/** @} */ /* end_namegroup */

/** Authentication preference for a PDP connection. */
typedef enum qapi_DSS_Auth_Pref_e
{
  QAPI_DSS_AUTH_PREF_PAP_CHAP_NOT_ALLOWED_E = 0x00,  /**< Neither of the authentication protocols (PAP, CHAP) are allowed. */
  QAPI_DSS_AUTH_PREF_PAP_ONLY_ALLOWED_E,             /**< Only PAP authentication protocol is allowed. */
  QAPI_DSS_AUTH_PREF_CHAP_ONLY_ALLOWED_E,            /**< Only CHAP authentication protocol is allowed. */
  QAPI_DSS_AUTH_PREF_PAP_CHAP_BOTH_ALLOWED_E         /**< Both PAP and CHAP authentication protocols are allowed. */
} /** @cond */qapi_DSS_Auth_Pref_t/** @endcond */;
	
/** Call end reason type. */
typedef enum qapi_DSS_CE_Reason_Type_e
{
  QAPI_DSS_CE_TYPE_UNINIT_E  = -2,                 /**< No specific call end reason was received from the modem. */
  QAPI_DSS_CE_TYPE_INVALID_E = 0XFF,               /**< No valid call end reason was received. */
  QAPI_DSS_CE_TYPE_MOBILE_IP_E = 0x01,             /**< Mobile IP error. */
  QAPI_DSS_CE_TYPE_INTERNAL_E = 0x02,              /**< Data services internal error was sent by the modem. */
  QAPI_DSS_CE_TYPE_CALL_MANAGER_DEFINED_E = 0x03,  /**< Modem Protocol internal error. */
  QAPI_DSS_CE_TYPE_3GPP_SPEC_DEFINED_E = 0x06,     /**< 3GPP specification defined error. */
  QAPI_DSS_CE_TYPE_PPP_E = 0x07,                   /**< Error during PPP negotiation. */
  QAPI_DSS_CE_TYPE_EHRPD_E = 0x08,                 /**< Error during EHRPD. */
  QAPI_DSS_CE_TYPE_IPV6_E = 0x09                   /**< Error during IPV6 configuration. */
} /** @cond */qapi_DSS_CE_Reason_Type_t/** @endcond */;

/** Call parameter identifier.  */
typedef enum qapi_DSS_Call_Info_Enum_e
{
  QAPI_DSS_CALL_INFO_MIN_E = 0x00,
  QAPI_DSS_CALL_INFO_UMTS_PROFILE_IDX_E,   /**< UMTS profile ID. */
  QAPI_DSS_CALL_INFO_APN_NAME_E,           /**< APN name. */
  QAPI_DSS_CALL_INFO_USERNAME_E,           /**< APN user name. */
  QAPI_DSS_CALL_INFO_PASSWORD_E,           /**< APN password. */
  QAPI_DSS_CALL_INFO_AUTH_PREF_E,          /**< Authentication preference. */
  QAPI_DSS_CALL_INFO_CDMA_PROFILE_IDX_E,   /**< CDMA profile ID. */
  QAPI_DSS_CALL_INFO_TECH_PREF_E,          /**< Technology preference. */
  QAPI_DSS_CALL_INFO_IP_VERSION_E,         /**< Preferred IP family for the call. */
  QAPI_DSS_CALL_INFO_EXT_TECH_E,           /**< Extended technology preference. */
  QAPI_DSS_CALL_INFO_MO_EXCEPTION_DATA_E,  /**< MO exception data. */
  QAPI_DSS_CALL_INFO_MAX_E
} /** @cond */qapi_DSS_Call_Param_Identifier_t/** @endcond */;

/*
   QAPI_DSS event names.
   Event names are sent along with the registered user callback 
*/
typedef enum qapi_DSS_Net_Evt_e
{
  QAPI_DSS_EVT_INVALID_E = 0x00,   /**< Invalid event. */
  QAPI_DSS_EVT_NET_IS_CONN_E,      /**< Call connected. */
  QAPI_DSS_EVT_NET_NO_NET_E,       /**< Call disconnected. */
  QAPI_DSS_EVT_NET_RECONFIGURED_E, /**< Call reconfigured. */
  QAPI_DSS_EVT_NET_NEWADDR_E,      /**< New address generated. */
  QAPI_DSS_EVT_NET_DELADDR_E,      /**< Delete generated. */
  QAPI_DSS_EVT_NIPD_DL_DATA_E,
  QAPI_DSS_EVT_MAX_E
} /** @cond */qapi_DSS_Net_Evt_t/** @endcond */;

/* IP families. */
typedef enum qapi_DSS_IP_Family_e
{
  QAPI_DSS_IP_FAMILY_V4_E = 0x00, /**< IPV4 address family. */
  QAPI_DSS_IP_FAMILY_V6_E,        /**< IPV6 address family. */
  QAPI_DSS_NON_IP_FAMILY_E,       /**< Non-IP family. */    
  QAPI_DSS_NUM_IP_FAMILIES_E
} /** @cond */qapi_DSS_IP_Family_t/** @endcond */;

/** Bearer technology types. */

typedef enum qapi_DSS_Data_Bearer_Tech_e
{
  QAPI_DSS_DATA_BEARER_TECH_UNKNOWN_E = 0x00,/**< Unknown bearer. */
  /* CDMA related data bearer technologies */
  QAPI_DSS_DATA_BEARER_TECH_CDMA_1X_E,       /**< 1X technology. */
  QAPI_DSS_DATA_BEARER_TECH_EVDO_REV0_E,     /**< CDMA Rev 0. */
  QAPI_DSS_DATA_BEARER_TECH_EVDO_REVA_E,     /**< CDMA Rev A. */
  QAPI_DSS_DATA_BEARER_TECH_EVDO_REVB_E,     /**< CDMA Rev B. */
  QAPI_DSS_DATA_BEARER_TECH_EHRPD_E,         /**< EHRPD. */
  QAPI_DSS_DATA_BEARER_TECH_FMC_E,           /**< Fixed mobile convergence. */
  QAPI_DSS_DATA_BEARER_TECH_HRPD_E,          /**< HRPD. */
  QAPI_DSS_DATA_BEARER_TECH_3GPP2_WLAN_E,    /**< IWLAN. */
  /* UMTS related data bearer technologies */
  QAPI_DSS_DATA_BEARER_TECH_WCDMA_E,         /**< WCDMA. */
  QAPI_DSS_DATA_BEARER_TECH_GPRS_E,          /**< GPRS. */
  QAPI_DSS_DATA_BEARER_TECH_HSDPA_E,         /**< HSDPA. */
  QAPI_DSS_DATA_BEARER_TECH_HSUPA_E,         /**< HSUPA. */
  QAPI_DSS_DATA_BEARER_TECH_EDGE_E,          /**< EDGE. */
  QAPI_DSS_DATA_BEARER_TECH_LTE_E,           /**< LTE. */
  QAPI_DSS_DATA_BEARER_TECH_HSDPA_PLUS_E,    /**< HSDPA+. */
  QAPI_DSS_DATA_BEARER_TECH_DC_HSDPA_PLUS_E, /**< DC HSDPA+. */
  QAPI_DSS_DATA_BEARER_TECH_HSPA_E,          /**< HSPA. */
  QAPI_DSS_DATA_BEARER_TECH_64_QAM_E,        /**< 64 QAM.  */
  QAPI_DSS_DATA_BEARER_TECH_TDSCDMA_E,       /**< TD-SCDMA. */
  QAPI_DSS_DATA_BEARER_TECH_GSM_E,           /**< GSM. */
  QAPI_DSS_DATA_BEARER_TECH_3GPP_WLAN_E,     /**< IWLAN. */  
  QAPI_DSS_DATA_BEARER_TECH_MAX_E
} /** @cond */qapi_DSS_Data_Bearer_Tech_t/** @endcond */;

/** Call technology. */
typedef enum qapi_DSS_Call_Tech_Type_e
{
  QAPI_DSS_CALL_TECH_INVALID_E = 0x00, /**< Invalid technology. */
  QAPI_DSS_CALL_TECH_CDMA_E,           /**< CDMA. */
  QAPI_DSS_CALL_TECH_UMTS_E           /**< UMTS. */
} /** @cond */qapi_DSS_Call_Tech_Type_t/** @endcond */;

/** MO exception data transport protocol information */
typedef enum qapi_DSS_XPORT_Protocol_e
{
  QAPI_DSS_XPORT_PROTO_NONE    = 0x00, /**< No transport protocol */
  QAPI_DSS_XPORT_PROTO_ICMP    = 0x01, /**< Internet Control Messaging Protocol */
  QAPI_DSS_XPORT_PROTO_TCP     = 0x06, /**< Transmission Control Protocol */
  QAPI_DSS_XPORT_PROTO_UDP     = 0x11, /**< User Datagram Protocol */
  QAPI_DSS_XPORT_PROTO_ESP     = 0x32, /**< Encapsulating Security Payload protocol */
  QAPI_DSS_XPORT_PROTO_AH      = 0x33, /**< Authentication Header protocol */
  QAPI_DSS_XPORT_PROTO_ICMP6   = 0x3A, /**< ICMPv6 protocol */
  QAPI_DSS_XPORT_PROTO_TCPUDP  = 0xFF, /**< TCP and UDP protocol; only applicable for remote socket requests */
} /** @cond */qapi_DSS_XPORT_Protocol_t/** @endcond */;

/** Call end (CE) reason. */
typedef struct qapi_DSS_CE_Reason_s
{
  qapi_DSS_CE_Reason_Type_t reason_type; /**<  Discriminator for reason codes. */
  int reason_code;                       /**<  Overloaded cause codes discriminated by reason type. */
} /** @cond */qapi_DSS_CE_Reason_t/** @endcond */;

/* Specifies call parameter values  */
typedef struct qapi_DSS_Call_Param_Value_s
{
  char *buf_val;  /**<  Pointer to the buffer containing the parameter value that is to be set. */
  int   num_val;  /**<  Size of the parameter buffer. */
} /** @cond */qapi_DSS_Call_Param_Value_t/** @endcond */;

/* Structure used to represent the IP address */
typedef struct qapi_DSS_Addr_s
{
  char valid_addr; /**< Indicates whether a valid address is available. */   
  union qapi_dss_ip_address_u /** Union of DSS IP addresses. */
  {
    uint32_t v4;            /**< Used to access the IPv4 address. */
    uint64_t v6_addr64[2];  /**< Used to access the IPv6 address. */
    uint32_t v6_addr32[4];  /**< Used to access the IPv6 address as four 32-bit integers. */
    uint16_t v6_addr16[8];  /**< Used to access octets of the IPv6 address. */
    uint8_t  v6_addr8[16];  /**< Used to access octets of the IPv6 address as 16 8-bit integers. */
  } addr;
} /** @cond */qapi_DSS_Addr_t/** @endcond */;

/** IP address-related information. */
typedef struct qapi_DSS_Addr_Info_s
{
  qapi_DSS_Addr_t   iface_addr_s; /**< Network interface address. */
  unsigned int      iface_mask;   /**< Interface subnet mask. */
  qapi_DSS_Addr_t   gtwy_addr_s;  /**< Gateway server address. */
  unsigned int      gtwy_mask;    /**< Gateway subnet mask. */
  qapi_DSS_Addr_t   dnsp_addr_s;  /**< Primary DNS server address. */  
  qapi_DSS_Addr_t   dnss_addr_s;  /**< Secondary DNS server address. */
} /** @cond */qapi_DSS_Addr_Info_t/** @endcond */;

/** Packet statistics. */
typedef struct qapi_DSS_Data_Pkt_Stats_s
{
  unsigned long pkts_tx;          /**< Number of packets transmitted. */
  unsigned long pkts_rx;          /**< Number of packets received. */
  long long     bytes_tx;         /**< Number of bytes transmitted. */
  long long     bytes_rx;         /**< Number of bytes received. */
  unsigned long pkts_dropped_tx;  /**< Number of transmit packets dropped. */
  unsigned long pkts_dropped_rx;  /**< Number of receive packets dropped. */
} /** @cond */qapi_DSS_Data_Pkt_Stats_t/** @endcond */;

/** Event payload sent with event callback */
typedef struct qapi_DSS_Evt_Payload_s
{
  uint8_t *data;
  uint32_t data_len;
} /** @cond */qapi_DSS_Evt_Payload_t/** @endcond */;

/** IPv4 address filter type */
typedef struct qapi_DSS_IPv4_Filter_Address_Type_s
{
  uint32_t ipv4_addr; /**< IPv4 address. */
  uint32_t subnet_mask; /**< IPv4 subnet mask. */
} /** @cond */qapi_DSS_IPv4_Filter_Address_Type_t/** @endcond */;

/** IPv4 TOS filter type */
typedef struct qapi_DSS_IPv4_Filter_TOS_Type_s
{
  uint8_t val;  /**< Type of service value. */
  uint8_t mask; /**< Type of service mask. */
} /** @cond */qapi_DSS_IPv4_Filter_TOS_Type_t/** @endcond */;

/** IPv4 filter rule info */ 
typedef struct qapi_DSS_IPv4_Filter_Info_s 
{
  qapi_DSS_IPv4_Filter_Mask_t valid_params; /**< Bit mask denote which parameters contain valid values */
  qapi_DSS_IPv4_Filter_Address_Type_t src_addr; /**< IPv4 source address */
  qapi_DSS_IPv4_Filter_Address_Type_t dest_addr; /**< IPv4 destination address */
  qapi_DSS_IPv4_Filter_TOS_Type_t tos; /**< IPv4 type of service */
} /** @cond */qapi_DSS_IPv4_Filter_Info_t/** @endcond */;

/** IPv6 address filter type */
typedef struct qapi_DSS_IPv6_Filter_Address_Type_s 
{
  uint8_t ipv6_address[QAPI_DSS_IPV6_ADDR_LEN]; /**< IPv6 address */
  uint8_t prefix_len; /**< IPv6 address prefix length. */
} /** @cond */qapi_DSS_IPv6_Filter_Address_Type_t/** @endcond */;

/* IPv6 traffic class filter type */
typedef struct qapi_DSS_IPv6_Filter_Traffic_Type_s
{
  uint8_t val;  /**< Traffic class value */
  uint8_t mask; /**< Traffic class mask */
} /** @cond */qapi_DSS_IPv6_Filter_Traffic_Type_t/** @endcond */;

/** IPv6 filter rule info */ 
typedef struct qapi_DSS_IPv6_Filter_Info_s 
{
  qapi_DSS_IPv6_Filter_Mask_t valid_params; /**< Bit mask denote which parameters contain valid values */
  qapi_DSS_IPv6_Filter_Address_Type_t src_addr; /**< IPv6 source address */
  qapi_DSS_IPv6_Filter_Address_Type_t dest_addr; /**< IPv6 destination address */
  qapi_DSS_IPv6_Filter_Traffic_Type_t trf_cls; /**< IPv6 traffic class */
  uint32_t flow_label; /**<IPv6 flow label */
} /** @cond */qapi_DSS_IPv6_Filter_Info_t/** @endcond */; 

/** Internet protocol filter rule parameters */
typedef struct qapi_DSS_IP_Header_Filters_s
{
  uint8_t ip_version;
  /**< Depending on the IP version set, either the IPv4 or the IPv6 information is valid. Values:\n
      - QAPI_DSS_IP_VERSION_4 (0x04)   --  IPv4 
      - QAPI_DSS_IP_VERSION_6 (0x06)   --  IPv6 
   */
  qapi_DSS_IPv4_Filter_Info_t v4_info; /**< Filter parameters for IPv4 */
  qapi_DSS_IPv6_Filter_Info_t v6_info; /**< Filter parameters for IPv6 */
} /** @cond */qapi_DSS_IP_Header_Filters_t/** @endcond */; 

typedef struct qapi_DSS_Port_Type_s
{
  uint16_t port; /**< Port */
  uint16_t range; /**< Range */
} /** @cond */qapi_DSS_Port_Type_t/** @endcond */; 

/** TCP and UDP port filter rule parameters */
typedef struct qapi_DSS_Port_Filter_Info_s 
{
  qapi_DSS_Port_Info_Filter_Mask_t valid_params; /**< Bit mask denotes which parameters contain valid values */
  qapi_DSS_Port_Type_t src_port_info; /**< Source port information. */
  qapi_DSS_Port_Type_t dest_port_info; /**< Destination port information. */
} /** @cond */qapi_DSS_Port_Filter_Info_t/** @endcond */;

/* ICMP filter rule parameters */
typedef struct qapi_DSS_ICMP_Info_Filter_Type_s
{
  qapi_DSS_ICMP_Info_Filter_Mask_t valid_params; /**< Bit mask denotes which parameters contain valid values */
  uint8_t type; /**< ICMP type */
  uint8_t code; /**< ICMP code */
} /** @cond */qapi_DSS_ICMP_Info_Filter_Type_t/** @endcond */;   

/* IPSec filter rule parameters */
typedef struct qapi_DSS_IPSec_Info_Filter_Type_s
{
  qapi_DSS_IPSec_Info_Filter_Mask_t valid_params; /**< Bit mask denotes which parameters contain valid values */
  uint32_t spi;   /**<   Security parameter index for IPSec */
} /** @cond */qapi_DSS_IPSec_Info_Filter_Type_t/** @endcond */;  

/** Transport protocol filter rule parameters */
typedef struct qapi_DSS_Xport_Header_Filters_s 
{
  qapi_DSS_XPORT_Protocol_t xport_protocol;
  /**< Depending on the value in xport_protocol, only one field of icmp_info, tcp_info, 
       udp_info, esp_info, or ah_info is valid. QAPI_DSS_XPORT_PROTO_NONE implies that 
       no transport level protocol parameters are valid */
  qapi_DSS_Port_Filter_Info_t tcp_info; /**< Filter parameters for TCP */
  qapi_DSS_Port_Filter_Info_t udp_info; /**< Filter parameters for UDP */
  qapi_DSS_ICMP_Info_Filter_Type_t icmp_info; /**< Filter parameters for ICMP */
  qapi_DSS_IPSec_Info_Filter_Type_t esp_info; /**< Filter parameters for ESP */
  qapi_DSS_IPSec_Info_Filter_Type_t ah_info; /**< Filter parameters for AH */
} /** @cond */qapi_DSS_Xport_Header_Filters_t/** @endcond */;

/** MO exception data filter rules */
typedef struct qapi_DSS_Filter_Rule_Type_s 
{
  qapi_DSS_IP_Header_Filters_t ip_info; /**< Internet protocol filter parameters */
  qapi_DSS_Xport_Header_Filters_t xport_info; /**< Transport level protocol filter parameters */
} /** @cond */qapi_DSS_Filter_Rule_Type_t/** @endcond */; 

/** Adds MO exception data filters request. */
typedef struct qapi_DSS_Add_MO_Exception_Filters_Req_s
{
  uint8_t filter_rules_valid;  /**< Set to true if filter rules is being passed */
  uint32_t filter_rules_len;   /**< Set to # of elements in filter rules */
  qapi_DSS_Filter_Rule_Type_t filter_rules[QAPI_DSS_MAX_EXCEPTION_FILTERS];  /**< List of filter rules */
} /** @cond */qapi_DSS_Add_MO_Exception_Filters_Req_t/** @endcond */;
	
/** Adds MO exception data filters response. */
typedef struct qapi_DSS_Add_MO_Exception_Filters_Rsp_s
{
  uint8_t filter_handles_valid;  /**< Set to true if filter handles is being passed */
  uint32_t filter_handles_len;   /**< Set to # of elements in filter handles */
  uint32_t filter_handles[QAPI_DSS_MAX_EXCEPTION_FILTERS]; /**< List of handles that uniquely identifies added filter rules */
  uint8_t filter_rule_error_valid;  /**< Set to true if filter rule error is being passed */
  uint32_t filter_rule_error_len;  /**< Set to # of elements in filter rule error */
  qapi_DSS_MO_Filter_Error_Mask_t filter_rule_error[QAPI_DSS_MAX_EXCEPTION_FILTERS]; /**< Error mask list for filter rule errors */ 
}/** @cond */qapi_DSS_Add_MO_Exception_Filters_Rsp_t/** @endcond */;

/** Remove MO exception data filters. */
typedef struct qapi_DSS_Remove_MO_Exceptional_Filters_s
{
  uint32_t filter_handles_len;  /**< Set to # of elements in filter handles */
  uint32_t filter_handles[QAPI_DSS_MAX_EXCEPTION_FILTERS];  /**< List of handles to the filter rules to remove */
} /** @cond */qapi_DSS_Remove_MO_Exception_Filters_t/** @endcond */;

/** @} */ /* end_addtogroup qapi_dss_datatypes */

/** @addtogroup qapi_dss_typedefs
@{ */

/** Callback function prototype for DSS events.

   @param[in] hndl Handle to which this event is associated.
   @param[in] user_data Application-provided user data.
   @param[in] evt Event identifier.
   @param[in] payload_ptr Pointer to associated event information.

   @return
   None.
   */

typedef void (*qapi_DSS_Net_Ev_CB_t)
(
  qapi_DSS_Hndl_t         hndl,          /* Handle for which this event is associated */
  void                   *user_data,     /* Application-provided user data */
  qapi_DSS_Net_Evt_t      evt,           /* Event identifier */
  qapi_DSS_Evt_Payload_t *payload_ptr    /* Associated event information */
); 

/** @} */ /* end_addtogroup qapi_dss_typedefs */

#ifdef  QAPI_TXM_MODULE     // USER_MODE_DEFS

#define qapi_DSS_Init(a)                                 ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_INIT                         , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Release(a)                               ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_RELEASE                      , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Get_Data_Srvc_Hndl(a,b,c)                ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_GET_DATA_SRVC_HNDL           , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Rel_Data_Srvc_Hndl(a)                    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_REL_DATA_SRVC_HNDL           , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Set_Data_Call_Param(a,b,c)               ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_SET_DATA_CALL_PARAM          , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Start_Data_Call(a)                       ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_START_DATA_CALL              , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Stop_Data_Call(a)                        ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_STOP_DATA_CALL               , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Get_Pkt_Stats(a,b)                       ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_GET_PKT_STATS                , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Reset_Pkt_Stats(a)                       ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_RESET_PKT_STATS              , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Get_Call_End_Reason(a,b,c)               ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_GET_CALL_END_REASON          , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Get_Call_Tech(a,b)                       ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_GET_CALL_TECH                , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Get_Current_Data_Bearer_Tech(a,b)        ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_GET_CURRENT_DATA_BEARER_TECH , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Get_Device_Name(a,b,c)                   ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_GET_DEVICE_NAME              , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Get_Qmi_Port_Name(a,b,c)                 ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_GET_QMI_PORT_NAME            , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Get_IP_Addr_Count(a, b)                  ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_GET_IP_ADDR_COUNT            , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Get_IP_Addr(a,b,c)                       ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_GET_IP_ADDR                  , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Get_Link_Mtu(a,b)                        ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_GET_LINK_MTU                 , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Get_IP_Addr_Per_Family(a,b,c)            ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_GET_IP_ADDR_PER_FAMILY       , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Nipd_Send(a,b,c,d)                       ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_SEND_NIPD_DATA               , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Add_MO_Exception_IPdata_Filters(a,b,c)   ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_ADD_MO_EX_IP_FILTERS         , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_DSS_Remove_MO_Exception_IPdata_Filters(a,b)  ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_DSS_DEL_MO_EX_IP_FILTERS         , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))


#else

qapi_Status_t qapi_DSS_Handler(UINT id, UINT a1, UINT a2, UINT a3, UINT a4, UINT a5, UINT a6, UINT a7, UINT a8, UINT a9, UINT a10, UINT a11, UINT a12);


/*===========================================================================
  FUNCTION:  qapi_DSS_Init
===========================================================================*/
/** @ingroup qapi_DSS_Init

    Initializes the DSS netctrl library for the specified operating mode.
    Function must be invoked once per process, typically on process startup.

    @note1hang
    Only QAPI_DSS_MODE_GENERAL is to be used by applications.

    @param[in] mode Mode of operation in which to initialize the library.

    @return
    QAPI_OK - Initialization successful. 
    QAPI_ERROR - Initialization failed.

    @dependencies
    None.
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Init(int mode);

/*===========================================================================
  FUNCTION:  qapi_DSS_Release
===========================================================================*/
/** @ingroup qapi_DSS_Release
 
    Clean-up the DSS netctrl library. Function must be invoked once per 
    process, typically at the end to clean-up the resources.
    
    @note1hang
    Only QAPI_DSS_MODE_GENERAL is to be used by applications.

    @param[in] mode Mode of operation in which to de-initialize the library.

    @return    
    QAPI_OK -- Cleanup was successful.
    QAPI_ERROR -- Cleanup failed.

    @dependencies
    None.
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Release(int mode);

/*===========================================================================
  FUNCTION:  qapi_DSS_Get_Data_Srvc_Hndl
===========================================================================*/
/** @ingroup qapi_DSS_Get_Data_Srvc_Hndl

    Gets an opaque data service handle. All subsequent functions use this
    handle as an input parameter.

    @note1hang
    DSS netctrl library waits for initialization from the lower layers
    (QMI ports being opened, the RmNet interfaces being available, etc.) to
    support data services functionality. During initial bootup scenarios,
    these dependencies may not be available, which will cause an error to
    be returned by dss_get_data_srvc_hndl. In such cases, clients are
    asked to retry this function call repeatedly using a 500ms timeout
    interval. Once a non-NULL handle is returned, clients can exit out of
    the delayed retry loop.

    @param[in] user_cb_fn Client callback function used to post event indications.
    @param[in] user_data Pointer to the client context block (cookie). The
                         value may be NULL.
    @param[in] hndl Pointer to data service handle.
    
    @return    
    QAPI_OK -- Cleanup was successful.
    QAPI_ERROR -- Cleanup failed.


    @dependencies
    qapi_DSS_Init() must be called.
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Get_Data_Srvc_Hndl(qapi_DSS_Net_Ev_CB_t user_cb_fn, void *user_data, qapi_DSS_Hndl_t *hndl);

/*===========================================================================
  FUNCTION:  qapi_DSS_Rel_Data_Srvc_Hndl
===========================================================================*/
/** @ingroup qapi_DSS_Rel_Data_Srvc_Hndl

    Releases a data service handle. All resources associated with the handle
    in the library are released.

    @note1hang
    If the user starts an interface with this handle, the corresponding 
    interface is stopped before the DSS handle is released.

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().

    @return    
    QAPI_OK -- Cleanup was successful.
    QAPI_ERROR -- Cleanup failed.


    @dependencies
    qapi_DSS_Init() must be called.
    Valid handle needs to be obtained by dss_get_data_srvc_hndl().
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Rel_Data_Srvc_Hndl(qapi_DSS_Hndl_t hndl);

/*===========================================================================
  FUNCTION:  qapi_DSS_Set_Data_Call_Param
===========================================================================*/
/** @ingroup qapi_DSS_Set_Data_Call_Param

    Sets the data call parameter before trying to start a data call. Clients 
    may call this function multiple times with various types of parameters 
    that need to be set.

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[in] identifier Identifies the parameter information.
    @param[in] info Parameter value that is to be set.

    @return
    QAPI_OK - Data call parameter was set successfully. 
    QAPI_ERROR - Data call parameter was not set successfully.

    @dependencies
    qapi_DSS_Init() must be called.
    Valid handle needs to be obtained by dss_get_data_srvc_hndl(). 
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Set_Data_Call_Param(qapi_DSS_Hndl_t hndl, qapi_DSS_Call_Param_Identifier_t identifier, qapi_DSS_Call_Param_Value_t *info);

/*===========================================================================
  FUNCTION:  qapi_DSS_Start_Data_Call
===========================================================================*/
/** @ingroup qapi_DSS_Start_Data_Call

    Starts a data call.

    An immediate call return value indicates whether the request was sent
    successfully. The client receives asynchronous notfications via a callback
    registered with qapi_DSS_Get_Data_Srvc_Hndl() indicating the data call bring-up
    status.

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().

    @return
    QAPI_OK - Data call start request was sent successfully.
    QAPI_ERROR - Data call start request was unsuccessful.

    @dependencies
    qapi_DSS_Init() must be called.
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl(). 
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Start_Data_Call(qapi_DSS_Hndl_t hndl);


/*===========================================================================
  FUNCTION:  qapi_DSS_Stop_Data_Call
===========================================================================*/
/** @ingroup qapi_DSS_Stop_Data_Call

    Stops a data call.

    An immediate call return value indicates whether the request was sent
    successfully. The client receives asynchronous notification via a callback
    registered with qapi_DSS_Get_Data_Srvc_Hndl() indicating the data call tear-down
    status.

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().

    @return
    QAPI_OK - Data call stop request was sent successfully.
    QAPI_ERROR - Data call stop request was unsuccessful.

    @dependencies
    qapi_DSS_Init() must be called.
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl(). 
    Data call must have been brought up using qapi_DSS_Start_Data_Call().
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Stop_Data_Call(qapi_DSS_Hndl_t hndl);

/*===========================================================================
  FUNCTION:  qapi_DSS_Get_Pkt_Stats
===========================================================================*/
/** @ingroup qapi_DSS_Get_Pkt_Stats

    Queries the packet data transfer statistics from the current packet
    data session.

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[in] dss_data_stats Buffer to hold the queried statistics details.

    @return
    QAPI_OK - Packet data transfer statistics were queried successfully.
    QAPI_ERROR - Packet data transfer statistics query was unsuccessful.

    @dependencies
    qapi_DSS_Init() must be called.
    A valid handle must be obtained byqapi_DSS_Get_Data_Srvc_Hndl(). 
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Get_Pkt_Stats(qapi_DSS_Hndl_t hndl, qapi_DSS_Data_Pkt_Stats_t *dss_data_stats);

/*===========================================================================
  FUNCTION:  qapi_DSS_Reset_Pkt_Stats
===========================================================================*/
/** @ingroup qapi_DSS_Reset_Pkt_Stats

    Resets the packet data transfer statistics.

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().

    @return
    QAPI_OK - Packet data transfer statistics were reset successfully.
    QAPI_ERROR - Packet data transfer statistics reset was unsuccessful.

    @dependencies
    qapi_DSS_Init() must be called.
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl(). 
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Reset_Pkt_Stats(qapi_DSS_Hndl_t hndl);

/*===========================================================================
  FUNCTION:  qapi_DSS_Get_Call_End_Reason
===========================================================================*/
/** @ingroup qapi_DSS_Get_Call_End_Reason

    Queries for the reason for a data call being ended.

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[out] ce_reason Buffer to hold data call ending reason information.
    @param[in] ip_family IP family for which the call end reason was requested.

    @return
    QAPI_OK - Data call end reason was queried successfully.
    QAPI_ERROR - Data call end reason query was unsuccessful.

    @dependencies
    qapi_DSS_Init() must be called.
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl().
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Get_Call_End_Reason(qapi_DSS_Hndl_t hndl, qapi_DSS_CE_Reason_t *ce_reason, qapi_DSS_IP_Family_t ip_family);

/*===========================================================================
  FUNCTION:  qapi_DSS_Get_Call_Tech
===========================================================================*/
/** @ingroup qapi_DSS_Get_Call_Tech

    Gets the techcology on which the call was brought up. This function can
    be called any time after the client receives the QAPI_DSS_EVT_NET_IS_CONN event
    and before the client releases the dss handle. 

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[out] call_tech Buffer to hold the call technology.

    @return
    QAPI_OK - Data call bring-up technology was queried successfully.
    QAPI_ERROR - Data call bring-up technology query was unsuccessful.

    @dependencies
    qapi_DSS_Init() must be called.
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl().
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Get_Call_Tech(qapi_DSS_Hndl_t hndl, qapi_DSS_Call_Tech_Type_t  *call_tech);

/*===========================================================================
  FUNCTION:  qapi_DSS_Get_Current_Data_Bearer_Tech
===========================================================================*/
/** @ingroup qapi_DSS_Get_Current_Data_Bearer_Tech

    Queries the data bearer techcology on which the call was brought up. 
    This function can be called any time after QAPI_DSS_EVT_NET_IS_CONN event 
    is received by the client and before the client releases the dss handle. 

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[in] Pointer to retrieve data bearer technology.

    @return
    QAPI_OK - Data bearer technology was returned successfully. \n
    QAPI_ERROR - Data bearer technology was not returned successfully.

    @dependencies
    qapi_DSS_Init() must be called.
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl().
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Get_Current_Data_Bearer_Tech(qapi_DSS_Hndl_t hndl, qapi_DSS_Data_Bearer_Tech_t * bearer_tech);

/*===========================================================================
  FUNCTION:  qapi_DSS_Get_Device_Name
===========================================================================*/
/** @ingroup qapi_DSS_Get_Device_Name

    Queries the data interface name for the data call associated with the
    specified data service handle.

    @note1hang
    len must be at least QAPI_DSS_CALL_INFO_DEVICE_NAME_MAX_LEN + 1 long.

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[out] buf Buffer to hold the data interface name string.
    @param[in] len Length of the buffer allocated by client.

    @return
    QAPI_OK - Data interface name was returned successfully. \n
    QAPI_ERROR - Data interface name was not returned successfully.

    @dependencies
    qapi_DSS_Init() must be called.
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl().
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Get_Device_Name(qapi_DSS_Hndl_t hndl, char *buf, int len);

/*===========================================================================
  FUNCTION:  qapi_DSS_Get_Qmi_Port_Name
===========================================================================*/
/** @ingroup qapi_DSS_Get_Qmi_Port_Name

    Queries the QMI port name for the data call associated with the
    specified data service handle.

    @note1hang
    len must be at least DSI_CALL_INFO_DEVICE_NAME_MAX_LEN + 1 long.

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[out] buf Buffer to hold the QMI port name string.
    @param[in] len Length of the buffer allocated by client.

    @return
    QAPI_OK - Port name was returned successfully. \n
    QAPI_ERROR - Port name was not returned successfully.

    @dependencies
    qapi_DSS_Init() must be called.
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl().
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Get_Qmi_Port_Name(qapi_DSS_Hndl_t hndl, char *buf, int len);

/*===========================================================================
  FUNCTION:  qapi_DSS_Get_IP_Addr_Count
===========================================================================*/
/** @ingroup qapi_DSS_Get_IP_Addr_Count

    Queries the number of IP addresses (IPv4 and global IPv6) associated with
    the DSs interface.

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[in] Pointer to retrieve number of IP addresses associated with
               the DSS interface.

    @return
    QAPI_OK - IP address count query was successful. \n
    QAPI_ERROR - IP address count query was unsuccessful.

    @dependencies
    qapi_DSS_Init() must be called.
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl().
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Get_IP_Addr_Count(qapi_DSS_Hndl_t hndl, unsigned int *ip_addr_cnt);

/*===========================================================================
  FUNCTION:  qapi_DSS_Get_IP_Addr
===========================================================================*/
/** @ingroup qapi_DSS_Get_IP_Addr

    Queries the IP address information structure (network order).

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[out] info_ptr Buffer containing the IP address information.
    @param[in] len Number of IP address buffers

    @return
    QAPI_OK - IP address query was successful. \n
    QAPI_ERROR - IP address query was unsuccessful.

    @dependencies
    qapi_DSS_Init() must be called.
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl(). \n
    The length parameter can be obtained by calling qapi_DSS_Get_IP_Addr_Count().
    It is assumed that the client has allocated memory for enough structures
    specified by the len field.
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Get_IP_Addr(qapi_DSS_Hndl_t hndl, qapi_DSS_Addr_Info_t  *info_ptr, int len);

/*===========================================================================
  FUNCTION:  qapi_DSS_Get_IP_Addr_Per_Family
===========================================================================*/
/** @ingroup qapi_DSS_Get_IP_Addr_Per_Family

    Queries the IP address information structure (network order).

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[out] info_ptr Buffer containing the IP address information.
    @param[in] addr_family IPv4 / IPv6 

    @return
    QAPI_OK - IP address query was successful. \n
    QAPI_ERROR - IP address query was unsuccessful.

    @dependencies
    qapi_DSS_Init() must be called.
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl().\n
    The length parameter can be obtained by calling qapi_DSS_Get_IP_Addr_Count().
    It is assumed that the client has allocated memory for enough structures
    specified by the len field.
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Get_IP_Addr_Per_Family(qapi_DSS_Hndl_t hndl, qapi_DSS_Addr_Info_t  *info_ptr, unsigned int addr_family);


/*===========================================================================
  FUNCTION:  qapi_DSS_Get_Link_Mtu
===========================================================================*/
/** @ingroup qapi_DSS_Get_Link_Mtu

    Queries the MTU information associated with the link.

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[out] mtu Buffer containing the MTU information.

    @return
    QAPI_OK - MTU query was successful. \n
    QAPI_ERROR - MTU query was unsuccessful.

    @dependencies
    qapi_DSS_Init() must be called. \n
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl().
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Get_Link_Mtu(qapi_DSS_Hndl_t hndl, unsigned int *mtu);

/*===========================================================================
  FUNCTION:  qapi_DSS_Add_MO_Exception_IPdata_Filters
===========================================================================*/
/** @ingroup qapi_DSS_Add_MO_Exception_IPdata_Filters

    Adds filters for MO Exception IP data call. 

    @param[in]  hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[in] filter_req Filter rules information to be added 
    @param[out] filter_rsp Filter rules handles and error information  

    @return
    QAPI_OK - Adding filter rules was successful. \n
    QAPI_ERROR - Adding filter rules was unsuccessful.

    @dependencies
    qapi_DSS_Init() must be called. \n
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl().
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Add_MO_Exception_IPdata_Filters
(
  qapi_DSS_Hndl_t hndl, 
  qapi_DSS_Add_MO_Exception_Filters_Req_t *filter_req, 
  qapi_DSS_Add_MO_Exception_Filters_Rsp_t *filter_rsp
);

/*===========================================================================
  FUNCTION:  qapi_DSS_Remove_MO_Exception_IPdata_Filters
===========================================================================*/
/** @ingroup qapi_DSS_Remove_MO_Exception_IPdata_Filters

    Remove filters for MO Exception IP data call. 

    @param[in]  hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[in] filter_req Filter rules information to be removed.   

    @return
    QAPI_OK - Removing filter rules was successful. \n
    QAPI_ERROR - Removing filter rules was unsuccessful.

    @dependencies
    qapi_DSS_Init() must be called. \n
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl().
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Remove_MO_Exception_IPdata_Filters
(
  qapi_DSS_Hndl_t hndl, 
  qapi_DSS_Remove_MO_Exception_Filters_t *filter_req
);

/*===========================================================================
  FUNCTION:  qapi_DSS_Nipd_Send
===========================================================================*/
/** @ingroup qapi_DSS_Nipd_Send

    Sends non-ip UL data. 

    @param[in] hndl Handle received from qapi_DSS_Get_Data_Srvc_Hndl().
    @param[in] data Non-ip data payload buffer the needs to be sent.
    @param[in] data_len Length of the data payload to be sent.    
	@param[in] ex_data MO Exception non-ip or not (QAPI_DSS_MO_EXCEPTION_NONIP_DATA or QAPI_DSS_MO_EXCEPTION_NONE)
  
    @return
    QAPI_OK - Send Data  was successful. \n
    QAPI_ERROR - Send Data was unsuccessful.

    @dependencies
    qapi_DSS_Init() must be called. \n
    A valid handle must be obtained by qapi_DSS_Get_Data_Srvc_Hndl().
*/
/*=========================================================================*/

qapi_Status_t qapi_DSS_Nipd_Send(qapi_DSS_Hndl_t hndl, uint8_t *data, uint32_t data_len, uint8_t ex_data);

#endif

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif /* QAPI_DSS_H */

