/** @file qapi_mqtt.h
*/
/* Copyright (c) 2015-2017 Qualcomm Technologies, Inc.
All rights reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.

*/

#ifndef _QAPI_NET_MQTT_H
#define _QAPI_NET_MQTT_H
#define MQTT_CLIENT_SECURITY
#define CLI_MQTT_PORT 1883
#define CLI_MQTT_SECURE_PORT 8883

#include "qapi/qapi_status.h"

#ifdef MQTT_CLIENT_SECURITY
#include "qapi/qapi_ssl.h"
#endif

// MQTT ID defines
#define  TXM_QAPI_MQTT_NEW                TXM_QAPI_MQTT_BASE + 1
#define  TXM_QAPI_MQTT_DESTROY            TXM_QAPI_MQTT_BASE + 2
#define  TXM_QAPI_MQTT_CONNECT            TXM_QAPI_MQTT_BASE + 3
#define  TXM_QAPI_MQTT_DISCONNECT         TXM_QAPI_MQTT_BASE + 4
#define  TXM_QAPI_MQTT_PUBLISH            TXM_QAPI_MQTT_BASE + 5
#define  TXM_QAPI_MQTT_SUBSCRIBE          TXM_QAPI_MQTT_BASE + 6
#define  TXM_QAPI_MQTT_UNSUSCRIBE         TXM_QAPI_MQTT_BASE + 7
#define  TXM_QAPI_MQTT_SET_CONNECT_CB     TXM_QAPI_MQTT_BASE + 8
#define  TXM_QAPI_MQTT_SET_SUBSCRIBE_CB   TXM_QAPI_MQTT_BASE + 9
#define  TXM_QAPI_MQTT_SET_MESSAGE_CB     TXM_QAPI_MQTT_BASE + 10
#define  TXM_QAPI_MQTT_SET_PUBLISH_CB     TXM_QAPI_MQTT_BASE + 11
#define  TXM_QAPI_MQTT_PUBLISH_ID         TXM_QAPI_MQTT_BASE + 12
#define  TXM_QAPI_MQTT_SET_ALLOW_UNSUB_PUB TXM_QAPI_MQTT_BASE + 13


    
/***********************************************************
 * Constant definitions
 **********************************************************/
/** @addtogroup qapi_net_mqtt_datatypes
@{ */

/** @name Net MQTT Length Defines
@{ */

#define QAPI_NET_MQTT_MAX_CLIENT_ID_LEN 128 /*MQTT Stack uses same value*/
#define QAPI_NET_MQTT_MAX_TOPIC_LEN 128    /*MAX Topic Len*/

/** @} */ /* end_namegroup */

/* reason codes for subscription callback */
enum /** @cond */QAPI_NET_MQTT_SUBSCRIBE_CBK_MSG /** @endcond */{
  QAPI_NET_MQTT_SUBSCRIBE_DENIED_E,  /**< subscription denied by broker */
  QAPI_NET_MQTT_SUBSCRIBE_GRANTED_E, /**< subscription granted by broker */
  QAPI_NET_MQTT_SUBSCRIBE_MSG_E     /**< message received from broker */
};

typedef enum QAPI_NET_MQTT_SUBSCRIBE_CBK_MSG qapi_Net_MQTT_Subscribe_Cbk_Msg_t;

enum /** @cond */  QAPI_NET_MQTT_CONNECT_CBK_MSG /** @endcond */{
  QAPI_NET_MQTT_CONNECT_SUCCEEDED_E,  /**< MQTT connect succeeded */
  QAPI_NET_MQTT_TCP_CONNECT_FAILED_E, /**< TCP connect failed */
  QAPI_NET_MQTT_SSL_CONNECT_FAILED_E, /**< SSL connect failed */
  QAPI_NET_MQTT_CONNECT_FAILED_E,     /**< QAPI_MQTT connect failed */
};

typedef enum QAPI_NET_MQTT_CONNECT_CBK_MSG qapi_Net_MQTT_Connect_Cbk_Msg_t;

enum/** @cond */ QAPI_NET_MQTT_CONN_STATE  /** @endcond */{
  QAPI_NET_MQTT_ST_DORMANT_E, /**< Connection is Idle*/
  QAPI_NET_MQTT_ST_TCP_CONNECTING_E, /**< TCP Connecting*/
  QAPI_NET_MQTT_ST_TCP_CONNECTED_E, /**< TCP Connected*/
  QAPI_NET_MQTT_ST_SSL_CONNECTING_E,/**< SSL Connecting*/
  QAPI_NET_MQTT_ST_SSL_CONNECTED_E,/**< SSL Connected*/
  QAPI_NET_MQTT_ST_MQTT_CONNECTING_E,/**< MQTT Connecting*/
  QAPI_NET_MQTT_ST_MQTT_CONNECTED_E,/**< MQTT Connected*/
  QAPI_NET_MQTT_ST_MQTT_TERMINATING_E,/**< MQTT connection terminating*/
  QAPI_NET_MQTT_ST_SSL_TERMINATING_E,/**< SSL connection terminating*/
  QAPI_NET_MQTT_ST_TCP_TERMINATING_E,/**< TCP connection terminating*/
  QAPI_NET_MQTT_ST_DYING_E, /**< MQTT connection dying*/
  QAPI_NET_MQTT_ST_DEAD_E, /**< MQTT connection dead*/
};

enum QAPI_NET_MQTT_MSG_TYPES{
  QAPI_NET_MQTT_CONNECT = 1,
  QAPI_NET_MQTT_CONNACK,
  QAPI_NET_MQTT_PUBLISH,
  QAPI_NET_MQTT_PUBACK,
  QAPI_NET_MQTT_PUBREC,
  QAPI_NET_MQTT_PUBREL,
  QAPI_NET_MQTT_PUBCOMP,
  QAPI_NET_MQTT_SUBSCRIBE,
  QAPI_NET_MQTT_SUBACK,
  QAPI_NET_MQTT_UNSUBSCRIBE,
  QAPI_NET_MQTT_UNSUBACK,
  QAPI_NET_MQTT_PINGREQ,
  QAPI_NET_MQTT_PINGRESP,
  QAPI_NET_MQTT_DISCONNECT,
  QAPI_NET_MQTT_MQTT_NO_RESPONSE_MSG_REQD,
  QAPI_NET_MQTT_INVALID_RESP,
};


typedef enum QAPI_NET_MQTT_CONN_STATE qapi_Net_MQTT_Conn_State_t;
/********************************************************
 * MQTT Structures
 ********************************************************/

/*MQTT Configuration*/
struct /** @cond */ qapi_Net_MQTT_config_s /** @endcond */{
  struct sockaddr local /**< MQTT Cliet IP Address and Port Number*/;
  struct sockaddr remote/**< MQTT Server IP Address and Port Number */;
  bool nonblocking_connect; /**<Blocking or non blocking MQTT Connection*/
  uint8_t client_id[QAPI_NET_MQTT_MAX_CLIENT_ID_LEN];/**< MQTT Client ID*/
  int32_t client_id_len;/**< MQTT Client ID length*/
  uint32_t keepalive_duration;/**< Conection Keepalive duration in seconds*/
  uint8_t clean_session;/**< clean session flag 0 - no clean session, 1 - clean session*/
  uint8_t* will_topic; /**< Will topic name*/
  int32_t will_topic_len; /**< Will topic length*/
  uint8_t* will_message; /**< Will message*/
  int32_t will_message_len; /**< Will message length*/
  uint8_t will_retained; /**< Will retain flag*/
  uint8_t will_qos; /**< Will QOS*/
  uint8_t* username; /**< Client username*/
  int32_t username_len; /**< Client user length*/ 
  uint8_t* password; /**< Client Password*/
  int32_t password_len; /**< Client Password length*/
#ifdef MQTT_CLIENT_SECURITY
  qapi_Net_SSL_Config_t ssl_cfg; /**< SSL Configuration*/
  qapi_Net_SSL_CAList_t ca_list; /**< SSL CA Cert details*/
  qapi_Net_SSL_Cert_t cert; /**< SSL Cert details*/
#endif
} ;
typedef struct qapi_Net_MQTT_config_s qapi_Net_MQTT_Config_t;

/** @} */ /* end_addtogroup qapi_net_mqtt_datatypes */

/** @addtogroup qapi_net_mqtt_typedefs
@{ */
/*MQTT handle*/
typedef void* qapi_Net_MQTT_Hndl_t;

/*Connect callback typedef*/
typedef void (*qapi_Net_MQTT_Connect_CB_t)(qapi_Net_MQTT_Hndl_t mqtt, int32_t reason);

/*Subscribe callback typedef*/
typedef void (*qapi_Net_MQTT_Subscribe_CB_t)(qapi_Net_MQTT_Hndl_t mqtt,
    int32_t reason,
    const uint8_t* topic,
    int32_t topic_length,
    int32_t qos,
    const void* sid);

/* Message callback typedef*/
typedef void (*qapi_Net_MQTT_Message_CB_t)(qapi_Net_MQTT_Hndl_t mqtt,
    int32_t reason,
    const uint8_t* topic,
    int32_t topic_length,
    const uint8_t* msg,
    int32_t msg_length,
    int32_t qos,
    const void* sid);

typedef void (*qapi_Net_MQTT_Publish_CB_t)(qapi_Net_MQTT_Hndl_t mqtt,
    enum QAPI_NET_MQTT_MSG_TYPES msgtype,
    int qos,
    uint16_t msg_id);

#ifdef  QAPI_TXM_MODULE     // USER_MODE_DEFS

#define qapi_Net_MQTT_New(a)                        ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_MQTT_NEW               , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_MQTT_Destroy(a)                    ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_MQTT_DESTROY            , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_MQTT_Connect(a,b)                  ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_MQTT_CONNECT            , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_MQTT_Disconnect(a)                 ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_MQTT_DISCONNECT         , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_MQTT_Publish(a,b,c,d,e,f)          ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_MQTT_PUBLISH            , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) e, (ULONG) f, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_MQTT_Publish_Get_Msg_Id(a,b,c,d,e,f,g)     ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_MQTT_PUBLISH_ID         , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) e, (ULONG) f, (ULONG) g, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_MQTT_Subscribe(a,b,c)              ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_MQTT_SUBSCRIBE          , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_MQTT_Unsubscribe(a,b)              ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_MQTT_UNSUSCRIBE         , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_MQTT_Set_Connect_Callback(a,b)     ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_MQTT_SET_CONNECT_CB     , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_MQTT_Set_Subscribe_Callback(a,b)   ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_MQTT_SET_SUBSCRIBE_CB   , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_MQTT_Set_Message_Callback(a,b)     ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_MQTT_SET_MESSAGE_CB     , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_MQTT_Set_Publish_Callback(a,b)     ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_MQTT_SET_PUBLISH_CB     , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_MQTT_Allow_Unsub_Publish(a,b)      ((qapi_Status_t)  (_txm_module_system_call12)(TXM_QAPI_MQTT_SET_ALLOW_UNSUB_PUB     , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#else

UINT qapi_Net_MQTT_Handler(UINT id, UINT a1, UINT a2, UINT a3, UINT a4, UINT a5, UINT a6, UINT a7, UINT a8, UINT a9, UINT a10, UINT a11, UINT a12);


/**
 * @brief Create a new MQTT context
 * @param[out] hndl Newly created MQTT context
 * @return QAPI_OK on Success, QAPI_ERROR on Failure
 */
qapi_Status_t qapi_Net_MQTT_New(qapi_Net_MQTT_Hndl_t *hndl);

/**
 * @brief Destroy MQTT Context
 * @param[in] mqtt MQTT Context to be destroyed
 * @return QAPI_OK on Success or QAPI_ERROR on Failure
 */
qapi_Status_t qapi_Net_MQTT_Destroy(qapi_Net_MQTT_Hndl_t hndl);

/**
 * @brief Connect to MQTT Broker
 * @param[in] hndl MQTT Handle
 * @param[in] config MQTT Client Configuration
 * @return QAPI_OK on Success or < 0 on Failure
 */
qapi_Status_t qapi_Net_MQTT_Connect(qapi_Net_MQTT_Hndl_t hndl, const qapi_Net_MQTT_Config_t* config);

/**
 * @brief Disconnect from MQTT Broker
 * @param[in]  hdnl MQTT Handle
 * @return QAPI_OK on Success or < 0 on Failure
 */
qapi_Status_t qapi_Net_MQTT_Disconnect(qapi_Net_MQTT_Hndl_t hndl);

/**
 * @brief Publish message to a particular topic
 * @param[in] hdnl MQTT handle
 * @param[in] topic MQTT Topic
 * @param[in] msg MQTT Payload
 * @param[in] msg_len MQTT Payload length
 * @param[in] qos QOS to be used for message
 * @param[in] retain Retain flag
 * @return QAPI_OK on Success or <0 on Failure
 */
qapi_Status_t qapi_Net_MQTT_Publish(qapi_Net_MQTT_Hndl_t hndl, const uint8_t* topic, const uint8_t* msg, int32_t msg_len, int32_t qos, bool retain);

/**
 * @brief Publish message to a particular topic
 * @param[in] hdnl MQTT handle
 * @param[in] topic MQTT Topic
 * @param[in] msg MQTT Payload
 * @param[in] msg_len MQTT Payload length
 * @param[in] qos QOS to be used for message
 * @param[in] retain Retain flag
 * @param[out] Message id of the Mqtt publish msg
 * @return QAPI_OK on Success or <0 on Failure
 */
qapi_Status_t qapi_Net_MQTT_Publish_Get_Msg_Id(qapi_Net_MQTT_Hndl_t hndl, const uint8_t* topic, const uint8_t* msg, int32_t msg_len, int32_t qos, bool retain, uint16_t *msg_id);


/**
 * @brief Subscribe to a topic
 * @param[in] mqtt MQTT Handle
 * @param[in] topic Subscription topic
 * @param[in] qos QOS to be used
 * @return QAPI_OK on Success or < 0 on Failure
 */
qapi_Status_t qapi_Net_MQTT_Subscribe(qapi_Net_MQTT_Hndl_t hndl, const uint8_t* topic, int32_t qos);

/**
 * @brief Unsubscribe from a topic
 * @param mqtt MQTT Handle
 * @param topic Topic to unsubscribed
 * @return QAPI_OK on Success or < 0 on Failure
 */
qapi_Status_t qapi_Net_MQTT_Unsubscribe(qapi_Net_MQTT_Hndl_t hndl, const uint8_t* topic);

/**
 * @brief Set conncet callback, will be invoked when connect is successful
 * @param[in] mqtt MQTT handle
 * @param[in] callback Callback to be invoked
 * @return Success or Failure
 */

qapi_Status_t qapi_Net_MQTT_Set_Connect_Callback(qapi_Net_MQTT_Hndl_t hndl, qapi_Net_MQTT_Connect_CB_t callback);

/**
 * @brief Set subscribe callback, will be invoked when subscription is granted or denied
 * @param[in] mqtt MQTT handle
 * @param[in] callback Callback to be invoked
 * @return QAPI_OK on Success or < 0 on Failure
 */
qapi_Status_t qapi_Net_MQTT_Set_Subscribe_Callback(qapi_Net_MQTT_Hndl_t hndl, qapi_Net_MQTT_Subscribe_CB_t callback);

/**
 * @brief Set message callback, will be invoked when message is received for a subscribed topic
 * @param[in] mqtt MQTT handle
 * @param[in] callback Callback to be invoked
 * @return QAPI_OK on Success or < 0 on Failure
 */
qapi_Status_t qapi_Net_MQTT_Set_Message_Callback(qapi_Net_MQTT_Hndl_t hndl, qapi_Net_MQTT_Message_CB_t callback);


/**
 * @brief Set Publish callback, will be invoked when PUBACK(QOS1)/PUBREC,PUBCOMP(QOS2)
 * @param mqtt MQTT handle
 * @param callback Callback to be invoked
 * @return QAPI_OK on Success or < 0 on Failure
 */
qapi_Status_t qapi_Net_MQTT_Set_Publish_Callback(qapi_Net_MQTT_Hndl_t hndl, qapi_Net_MQTT_Publish_CB_t callback);
qapi_Status_t qapi_Net_MQTT_Allow_Unsub_Publish(qapi_Net_MQTT_Hndl_t hndl, bool  allow_unsub_pub);
#endif /*!TXM_MODULE*/

#endif /*_QAPI_NET_MQTT_H*/
