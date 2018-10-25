/**
Copyright (c) 2015-2017 Qualcomm Technologies, Inc.
All rights reserved.

Confidential and Proprietary - Qualcomm Technologies, Inc.

*/

/** @file qapi_net_status.h
 *
 * @details This section contains QAPI error codes that can be returned as a
 * result of an error in one of the Networking Services.
 *
 */


#ifndef _QAPI_NET_STATUS_H_
#define _QAPI_NET_STATUS_H_

#include "qapi/qapi_status.h"

/** @addtogroup qapi_status
@{ */


/** @name SSL Module Error Codes
 * @{
 */

#define QAPI_ERR_SSL_CERT __QAPI_ERROR(QAPI_MOD_NETWORKING, 1) /**< Error in own certificate. */

#define QAPI_ERR_SSL_CONN __QAPI_ERROR(QAPI_MOD_NETWORKING, 2) /**< Error with SSL connection. */

#define QAPI_ERR_SSL_HS_NOT_DONE __QAPI_ERROR(QAPI_MOD_NETWORKING, 3) /** Handshake must be completed before the operation can be attempted */

#define QAPI_ERR_SSL_ALERT_RECV __QAPI_ERROR(QAPI_MOD_NETWORKING, 4) /**< Received SSL warning alert message. */

#define QAPI_ERR_SSL_ALERT_FATAL __QAPI_ERROR(QAPI_MOD_NETWORKING, 5) /**< Received SSL fatal alert message. */

#define QAPI_SSL_HS_IN_PROGRESS __QAPI_ERROR(QAPI_MOD_NETWORKING, 6) /**< Handshake in progress. */

#define QAPI_SSL_OK_HS __QAPI_ERROR(QAPI_MOD_NETWORKING, 7) /**< Handshake successful. */

#define QAPI_ERR_SSL_CERT_CN __QAPI_ERROR(QAPI_MOD_NETWORKING, 8) /**< The SSL certificate of the peer is trusted, CN matches the host name, time is expired. */

#define QAPI_ERR_SSL_CERT_TIME __QAPI_ERROR(QAPI_MOD_NETWORKING, 9) /**< The SSL certificate of the peer is trusted, CN does not match the host name, time is valid. */

#define QAPI_ERR_SSL_CERT_NONE __QAPI_ERROR(QAPI_MOD_NETWORKING, 10) /**< The SSL certificate of the peer is not trusted. */

#define QAPI_ERR_SSL_NETBUF __QAPI_ERROR(QAPI_MOD_NETWORKING, 11) /**< Connection drops when out of network buffers; usually a
  resource configuration error. */

#define QAPI_ERR_SSL_SOCK __QAPI_ERROR(QAPI_MOD_NETWORKING, 12) /**< Socket error; use qapi_errno.h to check for the reason code. */
/** @} */

/*
 * @name Generic Error Codes
 * @{
 */

/** IP address is invalid. */
#define QAPI_NET_ERR_INVALID_IPADDR         ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_NETWORKING,  21))) 

/** Failed to get the scope ID. */
#define QAPI_NET_ERR_CANNOT_GET_SCOPEID     ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_NETWORKING,  22))) 

/** Socket command timed out. */
#define QAPI_NET_ERR_SOCKET_CMD_TIME_OUT    ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_NETWORKING,  23))) 

/** Max server add (v4/v6) reached in server's list. */
#define QAPI_NET_ERR_MAX_SERVER_REACHED     ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_NETWORKING,  24)))

/*
 * MQTT Error codes
 */
   
/** MQTT error number start*/
#define QAPI_NET_MQTT_ERR_NUM_START      25

/** MQTT Memory allocation failed*/
#define QAPI_NET_MQTT_ERR_ALLOC_FAILURE ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START)

/** MQTT Bad parameter while invocing API*/
#define QAPI_NET_MQTT_ERR_BAD_PARAM     ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 1))

/** MQTT Connection is in bad state*/
#define QAPI_NET_MQTT_ERR_BAD_STATE     ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 2))

/**MQTT Connection closed*/
#define QAPI_NET_MQTT_ERR_CONN_CLOSED   ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 3))

/**MQTT Packet decode failed*/
#define QAPI_NET_MQTT_ERR_MSG_DESERIALIZATION_FAILURE ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 4))

/**MQTT Packet encode failed*/
#define QAPI_NET_MQTT_ERR_MSG_SERIALIZATION_FAILURE   ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 5)) 

/**MQTT Negative CONNACK recevied*/
#define QAPI_NET_MQTT_ERR_NEGATIVE_CONNACK            ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 6))

/**MQTT no data*/
#define QAPI_NET_MQTT_ERR_NO_DATA                     ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 7))

/**MQTT no zero ref count while disconnecting*/
#define QAPI_NET_MQTT_ERR_NONZERO_REFCOUNT            ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 8))

/**MQTT Ping req msg creation failed*/
#define QAPI_NET_MQTT_ERR_PINGREQ_MSG_CREATION_FAILED ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 9))

/**MQTT Puback msg creation failed*/
#define QAPI_NET_MQTT_ERR_PUBACK_MSG_CREATION_FAILED  ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 10))
   
/**MQTT Pubcom msg creation failed*/
#define QAPI_NET_MQTT_ERR_PUBCOMP_MSG_CREATION_FAILED ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 11))

/**MQTT Publish msg creation failed*/
#define QAPI_NET_MQTT_ERR_PUBLISH_MSG_CREATION_FAILED ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 12))

/**MQTT Pubrec msg creation failed*/
#define QAPI_NET_MQTT_ERR_PUBREC_MSG_CREATION_FAILED  ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 13))

/**MQTT Pubrel msg creation failed*/
#define QAPI_NET_MQTT_ERR_PUBREL_MSG_CREATION_FAILED  ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 14))

/**MQTT RX incomplete*/
#define QAPI_NET_MQTT_ERR_RX_INCOMPLETE               ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 15))

/**MQTT Socket fatal error*/
#define QAPI_NET_MQTT_ERR_SOCKET_FATAL_ERROR          ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 16))

/**MQTT TCP Bind error*/
#define QAPI_NET_MQTT_ERR_TCP_BIND_FAILED             ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 17))

/**MQTT TCP connection error*/
#define QAPI_NET_MQTT_ERR_TCP_CONNECT_FAILED          ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 18))
   
/**MQTT SSL connection failed*/
#define QAPI_NET_MQTT_ERR_SSL_CONN_FAILURE                ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 19))

/**MQTT Subscribe msg creation failed*/
#define QAPI_NET_MQTT_ERR_SUBSCRIBE_MSG_CREATION_FAILED   ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 21))

/**MQTT Subscribe unknown topic*/
#define QAPI_NET_MQTT_ERR_SUBSCRIBE_UNKNOWN_TOPIC         ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 21))

/**MQTT Unsubscribe message creation failed*/
#define QAPI_NET_MQTT_ERR_UNSUBSCRIBE_MSG_CREATION_FAILED ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 22))

/**MQTT unexpected message receivied*/
#define QAPI_NET_MQTT_ERR_UNEXPECTED_MSG                  ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 23))

/**MQTT Subscription failed*/
#define QAPI_NET_MQTT_ERR_PARTIAL_SUBSCRIPTION_FAILURE    ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 24))

/**MQTT Restore failed*/
#define QAPI_NET_MQTT_ERR_RESTORE_FAILURE                 ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, QAPI_NET_MQTT_ERR_NUM_START + 25))

/**MQTT Maximum error number*/
#define QAPI_NET_MQTT_ERR_MAX_NUMS 26
/** @} */

/*
 * Data call management error codes
 */
   
/** Non IP data flow suspended */
#define QAPI_NET_NIPD_FLOW_SUSPENDED    ((qapi_Status_t)__QAPI_ERROR(QAPI_MOD_NETWORKING, 27))

#endif /* _QAPI_NET_STATUS_H_ */
