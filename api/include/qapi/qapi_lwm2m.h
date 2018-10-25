/**
  @file
  qapi_lwm2m.h

  @brief
  LWM2M interface file to interact with the LWM2M client module. 
*/

/*===========================================================================

  Copyright (c) 2008-2017 Qualcomm Technologies, Inc. All Rights Reserved

  Qualcomm Technologies Proprietary

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

/*===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: 

when       who     what, where, why
--------   ---     ----------------------------------------------------------
13/09/17   leo     (Tech Comm) Edited/added Doxygen comments and markup.
27/08/17  vpulimi  Added support for extensible LWM2M objects.
===========================================================================*/

#ifndef LWM2M_QAPI_H
#define LWM2M_QAPI_H

#include "stdbool.h"
#include "qapi_status.h"
#include "qapi_data_txm_base.h"

/** @addtogroup qapi_lwm2m_datatypes
@{ */

/**
* @brief  Maximum allowed LWM2M message ID size.
*/
#define QAPI_MAX_LWM2M_MSG_ID_LENGTH  10

/**
* @brief  Retrieve the LWM2M server short ID from the message ID information. 
*/
#define QAPI_LWM2M_SERVER_ID_INFO(msg_buf, msg_len, server_id) \
{                                                              \
  server_id = 0x00;                                            \
  if (msg_len)                                                 \
    server_id = *((uint16_t *)(msg_buf + (msg_len - 2)));      \
}

/** @name LWM2M Client Request IDs
@{ */
#define  TXM_QAPI_LWM2M_REGISTER_APP               TXM_QAPI_NET_LWM2M_BASE + 1
#define  TXM_QAPI_LWM2M_REGISTER_APP_EXTENDED      TXM_QAPI_NET_LWM2M_BASE + 2
#define  TXM_QAPI_LWM2M_DEREGISTER_APP             TXM_QAPI_NET_LWM2M_BASE + 3
#define  TXM_QAPI_LWM2M_OBSERVE                    TXM_QAPI_NET_LWM2M_BASE + 4
#define  TXM_QAPI_LWM2M_CANCEL_OBSERVE             TXM_QAPI_NET_LWM2M_BASE + 5
#define  TXM_QAPI_LWM2M_CREATE_OBJECT_INSTANCE     TXM_QAPI_NET_LWM2M_BASE + 6
#define  TXM_QAPI_LWM2M_DELETE_OBJECT_INSTANCE     TXM_QAPI_NET_LWM2M_BASE + 7
#define  TXM_QAPI_LWM2M_GET                        TXM_QAPI_NET_LWM2M_BASE + 8
#define  TXM_QAPI_LWM2M_SET                        TXM_QAPI_NET_LWM2M_BASE + 9
#define  TXM_QAPI_LW2M_SEND_MESSAGE                TXM_QAPI_NET_LWM2M_BASE + 10
#define  TXM_QAPI_LWM2M_ENCODE_APP_PAYLOAD         TXM_QAPI_NET_LWM2M_BASE + 11
#define  TXM_QAPI_LWM2M_DECODE_APP_PAYLOAD         TXM_QAPI_NET_LWM2M_BASE + 12
#define  TXM_QAPI_LWM2M_WAKEUP                     TXM_QAPI_NET_LWM2M_BASE + 13
#define  TXM_QAPI_LWM2M_CONFIG_CLIENT              TXM_QAPI_NET_LWM2M_BASE + 14
#define  TXM_QAPI_LWM2M_DEFAULT_ATTR_INFO          TXM_QAPI_NET_LWM2M_BASE + 15

/** @} */ /* end_namegroup */

/**
* @brief  Handler provide by LWM2M client to the application.
*/
typedef void * qapi_Net_LWM2M_App_Handler_t;

/**
 * @brief Enum used to identify a particular object with an object ID.
*/
typedef enum qapi_Net_LWM2M_Object_ID_e 
{
  QAPI_NET_LWM2M_DEVICE_OBJECT_ID_E          =  3,  /**< Device object ID. */
  QAPI_NET_LWM2M_FIRMWARE_UPDATE_OBJECT_ID_E =  5,  /**< Firmware update object ID. */
  QAPI_NET_LWM2M_LOCATION_OBJECT_ID_E        =  6,  /**< Location object ID. */
  QAPI_NET_LWM2M_SOFTWARE_MGNT_OBJECT_ID_E   =  9,  /**< Software management object ID. */
  QAPI_NET_LWM2M_DEVICE_CAP_OBJECT_ID_E      = 15,  /**< Device capability object ID. */
} qapi_Net_LWM2M_Object_ID_t;

/**
 * @brief Enum used to identify a particular resource of a device capability object.
*/  
typedef enum qapi_Net_LWM2M_Devicecap_Resource_Id_e 
{
  QAPI_NET_LWM2M_DEVICE_RES_M_PROPERTY_E         = 0,  /**< Property resource. */
  QAPI_NET_LWM2M_DEVICE_RES_M_GROUP_E            = 1,  /**< Group resource. */
  QAPI_NET_LWM2M_DEVICE_RES_O_DESCRIPTION_E      = 2,  /**< Description resource. */
  QAPI_NET_LWM2M_DEVICE_RES_O_ATTACHED_E         = 3,  /**< Attached resource. */
  QAPI_NET_LWM2M_DEVICE_RES_M_ENABLED_E          = 4,  /**< Enabled resource. */
  QAPI_NET_LWM2M_DEVICE_RES_M_OP_ENABLE_E        = 5,  /**< Operation enable. */
  QAPI_NET_LWM2M_DEVICE_RES_M_OP_DISBALE_E       = 6,  /**< Operation disable. */
  QAPI_NET_LWM2M_DEVICE_RES_O_NOTIFY_EN_E        = 7   /**< Notify EN ??. */
} qapi_Net_LWM2M_Devicecap_Resource_Id_t;

/** @brief Enum to identify valid firmware update resource IDs.
*/ 
typedef enum qapi_Net_LWM2M_Fota_Resource_Id_e 
{
  QAPI_NET_LWM2M_FOTA_RES_M_PACKAGE_E                 =  0,  /**< Package resource. */
  QAPI_NET_LWM2M_FOTA_RES_M_PACKAGE_URI_E             =  1,  /**< Package URI resource. */
  QAPI_NET_LWM2M_FOTA_RES_M_UPDATE_E                  =  2,  /**< Update resource. */
  QAPI_NET_LWM2M_FOTA_RES_M_STATE_E                   =  3,  /**< State resource. */
  QAPI_NET_LWM2M_FOTA_RES_M_UPDATE_RESULT_E           =  5,  /**< Update result resource. */
  QAPI_NET_LWM2M_FOTA_RES_O_PACKAGE_NAME_E            =  6,  /**< Package name resource. */
  QAPI_NET_LWM2M_FOTA_RES_O_PACKAGE_VERSION_E         =  7,  /**< Package version resource. */
  QAPI_NET_LWM2M_FOTA_RES_O_UPDATE_PROTOCOL_SUPPORT_E =  8,  /**< Update protocol support resource. */
  QAPI_NET_LWM2M_FOTA_RES_M_UPDATE_DELIVERY_METHOD_E  =  9,  /**< Update delivery method resource. */
} qapi_Net_LWM2M_Fota_Resource_Id_t;

/** @brief Enum to identify valid firmware update results.
*/
typedef enum  qapi_Net_LWM2M_Fota_Result_t_e 
{
  QAPI_NET_LWM2M_FOTA_RESULT_INITIAL_E                  = 0,  /**< Initial result. */
  QAPI_NET_LWM2M_FOTA_RESULT_UPDATE_SUCCESS_E           = 1,  /**< Update success. */
  QAPI_NET_LWM2M_FOTA_RESULT_NOT_ENOUGH_STORAGE_E       = 2,  /**< Not enough storage. */
  QAPI_NET_LWM2M_FOTA_RESULT_OUT_OF_MEMORY_E            = 3,  /**< Out of memory. */
  QAPI_NET_LWM2M_FOTA_RESULT_CONNECTION_LOST_E          = 4,  /**< Connection was lost. */
  QAPI_NET_LWM2M_FOTA_RESULT_CRC_CHECK_FAIL_E           = 5,  /**< CRC check failed. */
  QAPI_NET_LWM2M_FOTA_RESULT_UNSUPPORTED_PACKAGE_TYPE_E = 6,  /**< Unsupported package type. */
  QAPI_NET_LWM2M_FOTA_RESULT_INVAILD_URI_E              = 7,  /**< Invalid URI. */
  QAPI_NET_LWM2M_FOTA_RESULT_UPDATE_FAILED_E            = 8,  /**< Update failed. */
  QAPI_NET_LWM2M_FOTA_RESULT_UNSUPPORTED_PROTOCOL_E     = 9,  /**< Unsupported protocol. */
} qapi_Net_LWM2M_Fota_Result_t;

/** @brief Enum to identify supported protocols.
*/
typedef enum qapi_Net_LWM2M_Fota_Supported_Protocols_e 
{
  QAPI_NET_LWM2M_FOTA_PROTOCOL_COAP  = 0,    /**< COAP Protocol. */
  QAPI_NET_LWM2M_FOTA_PROTOCOL_COAPS = 1,    /**< COAPS Protocol. */
  QAPI_NET_LWM2M_FOTA_PROTOCOL_HTTP  = 2,    /**< HTTP Protocol. */
  QAPI_NET_LWM2M_FOTA_PROTOCOL_HTTPS = 3,    /**< HTTPS Protocol. */
} qapi_Net_LWM2M_Fota_Supported_Protocols_t;

/** @brief Enum to identify the update delivery method.
*/
typedef enum qapi_Net_LWM2M_Fota_Update_Delivery_Method_e 
{
  QAPI_NET_LWM2M_FOTA_UPDATE_PULL_E = 0,  /**< Supports only the package method. */
  QAPI_NET_LWM2M_FOTA_UPDATE_PUSH_E = 1,  /**< Supports only the package URI method. */
  QAPI_NET_LWM2M_FOTA_UPDATE_BOTH_E = 2,  /**< Supports both the package and package URI methods. */
} qapi_Net_LWM2M_Fota_Update_Delivery_Method_t;

/** @brief Enum to identify the location resource ID.
*/
typedef enum qapi_Net_LWM2M_Location_Resource_Id_e
{
  QAPI_NET_LWM2M_LOCATION_RES_O_RADIUS_E = 3,  /**< Location resource is the radius. */
} qapi_Net_LWM2M_Location_Resource_Id_t;

/**
 * @brief Enum to identify a particular resource of a software management object.
*/ 
typedef enum qapi_Net_LWM2M_SW_Mgnt_Resource_Id_e 
{
  QAPI_NET_LWM2M_SW_MGNT_RES_O_PACKAGE_NAME_E      = 0,  /**< Resource ID for Package Name. */
  QAPI_NET_LWM2M_SW_MGNT_RES_O_PACKAGE_VERSION_E   = 1,  /**< Resource ID for Package Version. */
  QAPI_NET_LWM2M_SW_MGNT_RES_O_PACKAGE_E           = 2,  /**< Resource ID for Package. */
  QAPI_NET_LWM2M_SW_MGNT_RES_O_PACKAGE_URI_E       = 3,  /**< Resource ID for Package URI. */
  QAPI_NET_LWM2M_SW_MGNT_RES_M_INSTALL_E           = 4,  /**< Resource ID for Install. */
  QAPI_NET_LWM2M_SW_MGNT_RES_M_UNINSTALL_E         = 6,  /**< Resource ID for Uninstall. */
  QAPI_NET_LWM2M_SW_MGNT_RES_M_UPDATE_STATE_E      = 7,  /**< Resource ID for Update State. */
  QAPI_NET_LWM2M_SW_MGNT_RES_M_UPDATE_RESULT_E     = 9,  /**< Resource ID for Update Result. */   
  QAPI_NET_LWM2M_SW_MGNT_RES_M_ACTIVATE_E          = 10, /**< Resource ID for Activate. */
  QAPI_NET_LWM2M_SW_MGNT_RES_M_DEACTIVATE_E        = 11, /**< Resource ID for Deactivate. */
  QAPI_NET_LWM2M_SW_MGNT_RES_M_ACTIVATION_STATE_E  = 12, /**< Resource ID for Activation State. */
} qapi_Net_LWM2M_SW_Mgnt_Resource_Id_t;

/**
 *@brief Enum to identify a particular error value of a software management object.
*/ 
typedef enum qapi_Net_LWM2M_SW_Mgnt_Error_Value_e 
{
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_INITIAL_E            = 0 , /**< Update result is Initial. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_DOWNLOADING_E        = 1 , /**< Update result is Downloading. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_INSTALL_SUCCESS_E    = 2 , /**< Update result is Install Success. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_NO_ENOUGH_STORAGE_E  = 50, /**< Update result is Not Enough Storage. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_OUT_OF_MEMORY_E      = 51, /**< Update result is Device is Out of Memory. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_CONNECTION_LOST_E    = 52, /**< Update result is Connection Lost. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_PKG_CHECK_FAILURE_E  = 53, /**< Update result is Package Check Failure. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_PKG_UNSUPPORTED_E    = 54, /**< Update result is Package Unsupported. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_INVALID_URI_E        = 56, /**< Update result is Invalid URI. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_UPDATE_ERROR_E       = 57, /**< Update result is Update Error. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_INSTALL_ERROR_E      = 58, /**< Update result is Install Error. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_UNINSTALL_ERROR_E    = 59, /**< Update result is Uninstall Error. */
} qapi_Net_LWM2M_SW_Mgnt_Error_Value_t;

/**
 * @brief  Enum to identify the particular state of a software management object.
*/
typedef enum qapi_Net_LWM2M_SW_Mgnt_State_e
{
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_STATE_INITIAL_E           = 0, /**< Update state is Initial. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_STATE_DOWNLOAD_STARTED_E  = 1, /**< Update state is Download Started. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_STATE_DOWNLOADED_E        = 2, /**< Update state is Downloaded. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_STATE_DELIVERED_E         = 3, /**< Update state is Delivered. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_STATE_INSTALLED_E         = 4, /**< Update state is Installed. */
} qapi_Net_LWM2M_SW_Mgnt_State_t;

/**
 * @brief  Enum to identify the particular state of a firmware object.
*/
typedef enum qapi_Net_Firmware_State_e 
{
  QAPI_NET_LWM2M_FIRWARE_STATE_IDLE_E = 0,     /**< Firmware state is Idle. */
  QAPI_NET_LWM2M_FIRWARE_STATE_DOWNLOADING_E,  /**< Firmware state is Downloading. */
  QAPI_NET_LWM2M_FIRWARE_STATE_DOWNLOADED_E,   /**< Firmware state is Downloaded. */
  QAPI_NET_LWM2M_FIRWARE_STATE_UPDATING_E,     /**< Firmware state is Updating. */
} qapi_Net_Firmware_State_t;

/**
* @brief  Enum to identify the type of ID set in the LWM2M object information.
*/
typedef enum qapi_Net_LWM2M_ID_e
{
  QAPI_NET_LWM2M_OBJECT_ID_E             = 0x01,  /**< Object ID. */
  QAPI_NET_LWM2M_INSTANCE_ID_E           = 0x02,  /**< Instance ID. */
  QAPI_NET_LWM2M_RESOURCE_ID_E           = 0x04,  /**< Resource ID. */
  QAPI_NET_LWM2M_RESOURCE_INSTANCE_ID_E  = 0x08,  /**< Resource instance ID. */
} qapi_Net_LWM2M_ID_t;

/**
* @brief  Enum to identify the type of resource value.
*/
typedef enum qapi_Net_LWM2M_Value_Type_e
{
  QAPI_NET_LWM2M_TYPE_UNDEFINED         = 0,  /**< Resource value type is Undefined. */
  QAPI_NET_LWM2M_TYPE_OBJECT            = 1,  /**< Resource value type is Object. */
  QAPI_NET_LWM2M_TYPE_OBJECT_INSTANCE   = 2,  /**< Resource value type is Object Instance. */
  QAPI_NET_LWM2M_TYPE_MULTIPLE_RESOURCE = 3,  /**< Resource value type is Multiple Resource. */
  QAPI_NET_LWM2M_TYPE_STRING_E          = 4,  /**< Resource value type is String. */
  QAPI_NET_LWM2M_TYPE_OPAQUE_E          = 5,  /**< Resource value type is Opaque. */
  QAPI_NET_LWM2M_TYPE_INTEGER_E         = 6,  /**< Resource value type is Integer. */
  QAPI_NET_LWM2M_TYPE_FLOAT_E           = 7,  /**< Resource value type is Float. */
  QAPI_NET_LWM2M_TYPE_BOOLEAN_E         = 8,  /**< Resource value type is Boolean. */
  QAPI_NET_LWM2M_TYPE_OBJECT_LINK       = 9,  /**< Resource value type is Object Link. */
} qapi_Net_LWM2M_Value_Type_t;

/**
* @brief  LWM2M write attribute types.
*/
typedef enum qapi_Net_LWM2M_Write_Attr_e
{
  QAPI_NET_LWM2M_MIN_PERIOD_E   = 1,   /**< Minimum period. */
  QAPI_NET_LWM2M_MAX_PERIOD_E   = 2,   /**< Maximum period. */
  QAPI_NET_LWM2M_GREATER_THAN_E = 4,   /**< Greater than. */
  QAPI_NET_LWM2M_LESS_THAN_E    = 8,   /**< Less than. */
  QAPI_NET_LWM2M_STEP_E         = 16,  /**< Step. */
  QAPI_NET_LWM2M_DIM_E          = 32,  /**< Dimension. */
} qapi_Net_LWM2M_Write_Attr_t;

/**
* @brief  LWM2M downlink message types.
*/
typedef enum qapi_Net_LWM2M_DL_Msg_e
{
  QAPI_NET_LWM2M_READ_REQ_E                  = 1,   /**< Read request. */
  QAPI_NET_LWM2M_WRITE_REPLACE_REQ_E         = 2,   /**< Write replace request. */
  QAPI_NET_LWM2M_WRITE_PARTIAL_UPDATE_REQ_E  = 3,   /**< Write partial update request. */
  QAPI_NET_LWM2M_WRITE_ATTR_REQ_E            = 4,   /**< Write attribute request. */
  QAPI_NET_LWM2M_DISCOVER_REQ_E              = 5,   /**< Discover request. */
  QAPI_NET_LWM2M_EXECUTE_REQ_E               = 6,   /**< Execute request. */
  QAPI_NET_LWM2M_DELETE_REQ_E                = 7,   /**< Delete request. */
  QAPI_NET_LWM2M_OBSERVE_REQ_E               = 8,   /**< Observe request. */
  QAPI_NET_LWM2M_CANCEL_OBSERVE_REQ_E        = 9,   /**< Cancel observe request. */
  QAPI_NET_LWM2M_ACK_MSG_E                   = 10,  /**< Acknowledge message. */
  QAPI_NET_LWM2M_INTERNAL_CLIENT_IND_E       = 11,  /**< Internal client indication. */
  QAPI_NET_LWM2M_CREATE_REQ_E                = 12,  /**< Create request. */
  QAPI_NET_LWM2M_DELETE_ALL_REQ_E            = 13,  /**< Delete all request. */
} qapi_Net_LWM2M_DL_Msg_t;

/**
* @brief  LWM2M uplink message types.
*/
typedef enum qapi_Net_LWM2M_UL_Msg_e
{
  QAPI_NET_LWM2M_RESPONSE_MSG_E              = 1,  /**< Response message. */
  QAPI_NET_LWM2M_NOTIFY_MSG_E                = 2,  /**< Notify message. */
  QAPI_NET_LWM2M_CREATE_RESPONSE_MSG_E       = 3,  /**< Create response message. */
} qapi_Net_LWM2M_UL_Msg_t;

/**
* @brief  LWM2M event information.
*/
typedef enum qapi_Net_LWM2M_Event_e
{
  QAPI_NET_LWM2M_STATE_INITIAL_E                 = 0,   /**< Initial state. */
  QAPI_NET_LWM2M_BOOTSTRAP_REQUIRED_E            = 1,   /**< Bootstrap required event. */
  QAPI_NET_LWM2M_BOOTSTRAP_COMPLETED_E           = 2,   /**< Bootstrap completed event. */
  QAPI_NET_LWM2M_BOOTSTRAP_FAILED_E              = 3,   /**< Bootstrap failed event. */
  QAPI_NET_LWM2M_REGISTERTION_COMPELTED_E        = 4,   /**< Registration completed event. */
  QAPI_NET_LWM2M_REGISTRATION_FAILED_E           = 5,   /**< Registration failed event. */
  QAPI_NET_LWM2M_DEVICE_REBOOT_E                 = 6,   /**< Device reboot event. */
  QAPI_NET_LWM2M_DEVICE_FACTORY_RESET_E          = 7,   /**< Device factory reset event. */
  QAPI_NET_LWM2M_DEVICE_REBOOTSTRAPPING_E        = 8,   /**< Device rebootstrapping event. */
  QAPI_NET_LWM2M_TX_MESSAGE_MAX_RETRY_FAILURE_E  = 9,   /**< Tx message maximum retry failure event. */
  QAPI_NET_LWM2M_RX_MESSAGE_INTERNAL_FAILURE_E   = 10,  /**< Rx message internal failure event. */
  QAPI_NET_LWM2M_SLEEP_E                         = 11,  /**< Sleep event. */
  QAPI_NET_LWM2M_WAKEUP_E                        = 12,  /**< Wake-up event. */
  QAPI_NET_LWM2M_CLIENT_RESET_E                  = 13,  /**< Reset event. */
} qapi_Net_LWM2M_Event_t;

/**
* @brief  LWM2M response status codes.
*/
typedef enum qapi_Net_LWM2M_Response_Code_e
{
  QAPI_NET_LWM2M_IGNORE_E                 = 0x00,  /**< Ignore. */
  QAPI_NET_LWM2M_201_CREATED_E            = 0x41,  /**< 201 - Created. */
  QAPI_NET_LWM2M_202_DELETED_E            = 0x42,  /**< 202 - Deleted. */
  QAPI_NET_LWM2M_204_CHANGED_E            = 0x44,  /**< 204 - Changed. */
  QAPI_NET_LWM2M_205_CONTENT_E            = 0x45,  /**< 205 - Content. */
  QAPI_NET_LWM2M_400_BAD_REQUEST_E        = 0x80,  /**< 400 - Bad request. */
  QAPI_NET_LWM2M_401_UNAUTHORIZED_E       = 0x81,  /**< 401 - Unauthorized. */
  QAPI_NET_LWM2M_402_BAD_OPTION_E         = 0x82,  /**< 402 - Bad option. */
  QAPI_NET_LWM2M_403_FORBIDDEN_E          = 0x83,  /**< 403 - Forbidden. */
  QAPI_NET_LWM2M_404_NOT_FOUND_E          = 0x84,  /**< 404 - Not found. */
  QAPI_NET_LWM2M_405_METHOD_NOT_ALLOWED_E = 0x85,  /**< 405 - Method is not allowed. */
  QAPI_NET_LWM2M_406_NOT_ACCEPTABLE_E     = 0x86,  /**< 406 - Not acceptable. */
  QAPI_NET_LWM2M_408_ENTITY_INCOMPLETE_E       = 0x88,  /**< 408 - Request Entity Incomplete. */
  QAPI_NET_LWM2M_413_ENTITY_TOO_LARGE_E        = 0x8D,  /**< 413 - Request entity too large. */
  QAPI_NET_LWM2M_415_UNSUPPORTED_DATA_FORMAT_E = 0x8F,  /**< 415 - Unsupported content format. */
  QAPI_NET_LWM2M_500_INTERNAL_SERVER_E    = 0xA0,  /**< 500 - Internal server. */
} qapi_Net_LWM2M_Response_Code_t;

/**
* @brief  LWM2M message content type.
*/
typedef enum qapi_Net_LWM2M_Content_Type_t
{
  QAPI_NET_LWM2M_TEXT_PLAIN                    = 0,      /**< Plain text. */
  QAPI_NET_LWM2M_TEXT_XML                      = 1,      /**< XML text. */
  QAPI_NET_LWM2M_TEXT_CSV                      = 2,      /**< CSV text. */
  QAPI_NET_LWM2M_TEXT_HTML                     = 3,      /**< HTML text. */
  QAPI_NET_LWM2M_APPLICATION_LINK_FORMAT       = 40,     /**< Application link format. */
  QAPI_NET_LWM2M_APPLICATION_XML               = 41,     /**< Application XML. */
  QAPI_NET_LWM2M_APPLICATION_OCTET_STREAM      = 42,     /**< Application Octet stream. */
  QAPI_NET_LWM2M_APPLICATION_RDF_XML           = 43,     /**< Application RDF XML. */
  QAPI_NET_LWM2M_APPLICATION_SOAP_XML          = 44,     /**< Application SOAP XML. */
  QAPI_NET_LWM2M_APPLICATION_ATOM_XML          = 45,     /**< Application ATOM XML. */
  QAPI_NET_LWM2M_APPLICATION_XMPP_XML          = 46,     /**< Application XMPP XML. */
  QAPI_NET_LWM2M_APPLICATION_EXI               = 47,     /**< Application EXI. */
  QAPI_NET_LWM2M_APPLICATION_FASTINFOSET       = 48,     /**< Application FastInfoSet. */
  QAPI_NET_LWM2M_APPLICATION_SOAP_FASTINFOSET  = 49,     /**< Application SOAP FastInfoSet. */
  QAPI_NET_LWM2M_APPLICATION_JSON              = 50,     /**< Application JSON. */
  QAPI_NET_LWM2M_APPLICATION_X_OBIX_BINARY     = 51,     /**< Application X OBIX binary. */
  QAPI_NET_LWM2M_M2M_TLV                       = 11542,  /**< M2M TLV. */
  QAPI_NET_LWM2M_M2M_JSON                      = 11543   /**< M2M JSON. */
}qapi_Net_LWM2M_Content_Type_t;

/**
* @brief  LWM2M config parameter type. 
*/
typedef enum qapi_Net_LWM2M_Config_Type_t
{
  QAPI_NET_LWM2M_CONFIG_BOOTSTRAP_URL          = 0,
  QAPI_NET_LWM2M_CONFIG_APN_NAME               = 1,
  QAPI_NET_LWM2M_CONFIG_SECURITY_MODE          = 2,
}qapi_Net_LWM2M_Config_Type_t;

/**
* @brief  LWM2M security mode type. 
*/
typedef enum qapi_Net_LWM2M_Security_Mode_t
{
  QAPI_NET_LWM2M_SECURITY_MODE_PRE_SHARED_KEY  = 0,
  QAPI_NET_LWM2M_SECURITY_RAW_PUBLIC_KEY       = 1,
  QAPI_NET_LWM2M_SECURITY_CERTIFICATE          = 2,
  QAPI_NET_LWM2M_SECURITY_NONE                 = 3,
}qapi_Net_LWM2M_Security_Mode_t;

/**
* @brief  Structure to indicate the object/instance/resource ID for which the 
*         application is interested in monitoring or getting the value.
*/
typedef struct qapi_Net_LWM2M_Id_Info_s
{
  struct qapi_Net_LWM2M_Id_Info_s *next;  /**< Pointer to the next ID information. */
  uint8_t id_set;       /**< ID category defined in qapi_lwm2m_id. */
  uint16_t object_ID;   /**< Object ID. */
  uint8_t instance_ID;  /**< Object instance ID. */
  uint8_t resource_ID;  /**< Resource ID. */
} qapi_Net_LWM2M_Id_Info_t;

/**
* @brief  Structure to indicate the object/instance/resource for which the 
*         application is interested in monitoring or getting the value.
*/
typedef struct qapi_Net_LWM2M_Object_Info_s
{
  uint8_t no_object_info;             /**< Number of object information blocks. */
  qapi_Net_LWM2M_Id_Info_t *id_info;  /**< Pointer to the ID information. */
} qapi_Net_LWM2M_Object_Info_t;

/**
* @brief  Structure that indicates the resource information that is to be created.
*/
typedef struct qapi_Net_LWM2M_Resource_Info_s
{
  qapi_Net_LWM2M_Value_Type_t type;  /**< Type of resource. */
  uint8_t resource_ID;  /**< Resource ID. */
  /** Union of resource values. */
  union
  {
    bool asBoolean;     /**< Value in Boolean format. */
    int64_t asInteger;  /**< Value as an integer. */
    double asFloat;     /**< Value as a floating point. */
    struct
    {
      size_t length;    /**< String length. */
      uint8_t *buffer;  /**< Pointer to the string buffer. */
	  uint8_t  block1_more ; /* Block wise related info */
      uint32_t block1_num ;                                             
      uint16_t block1_size ;                          
      uint32_t block1_offset ;
    } asBuffer;         /**< Value as a string. */
  } value;
  struct qapi_Net_LWM2M_Resource_Info_s *next;  /**< Pointer to the next resource information. */
} qapi_Net_LWM2M_Resource_Info_t;

/**
* @brief  Structure to indicate the instance information that is to be created.
*/
typedef struct qapi_Net_LWM2M_Instance_Info_s
{
  struct qapi_Net_LWM2M_Instance_Info_s *next;  /**< Pointer to the next object instance. */
  uint8_t instance_ID;    /**< Instance ID. */
  uint8_t no_resources;   /**< Number of resources. */
  qapi_Net_LWM2M_Resource_Info_t * resource_info;  /**< Pointer to the resource information. */
} qapi_Net_LWM2M_Instance_Info_t;

/**
* @brief  Structure that is populated by the application and provided to an LWM2M client
*         when the application wants to create an instance of the 
*         LWM2M object to perform set and get operations. 
*/
typedef struct qapi_Net_LWM2M_Data_s
{
  struct qapi_Net_LWM2M_Data_s *next;  /**< Pointer to the next object data. */
  uint16_t object_ID;    /**< Object ID. */
  uint8_t no_instances;  /**< Number of instances. */
  qapi_Net_LWM2M_Instance_Info_t *instance_info;  /**< Pointer to the instance information. */
} qapi_Net_LWM2M_Data_t;

/**
* @brief  LWM2M object/URI-related information.
*/
typedef struct qapi_Net_LWM2M_Obj_Info_s
{
  qapi_Net_LWM2M_ID_t    obj_mask;         /**< Bitmap indicating valid object fields. */
  uint16_t               obj_id;           /**< Object ID. */
  uint16_t               obj_inst_id;      /**< Object instance ID. */
  uint16_t               res_id;           /**< Resource ID. */
  uint16_t               res_inst_id;      /**< Resource instance ID. */
} qapi_Net_LWM2M_Obj_Info_t;

/**
* @brief  LWM2M write attribute information.
*/
typedef struct qapi_Net_LWM2M_Attributes_s
{
  qapi_Net_LWM2M_Obj_Info_t     obj_info;       /**< LWM2M object information associated with write attributes. */ 
  qapi_Net_LWM2M_Write_Attr_t   set_attr_mask;  /**< Bitmap indicating valid attribute fields to set. */
  qapi_Net_LWM2M_Write_Attr_t   clr_attr_mask;  /**< Bitmap indicating attribute fields to clear. */
  uint8_t                       dim;            /**< Dimension. */
  uint32_t                      minPeriod;      /**< Minimum period. */
  uint32_t                      maxPeriod;      /**< Maximum period. */
  double                        greaterThan;    /**< Greater than. */
  double                        lessThan;       /**< Less than. */
  uint8_t                       step_valid;     /**< Step validity. */
  double                        step;           /**< Step. */
  struct qapi_Net_LWM2M_Attributes_s *next;     /**< Pointer to the next attributes information. */
} qapi_Net_LWM2M_Attributes_t;

/**
* @brief  LWM2M resource information (in flat format) to encode/decode data payload.
*/
typedef struct qapi_Net_LWM2M_Flat_Data_s
{
  qapi_Net_LWM2M_Value_Type_t type;  /**< Value type. */
  uint16_t  id;  /**< Resource ID. */
  /** Union of value types. */
  union
  {
    bool     asBoolean;  /**< Value in Boolean format. */
    int64_t  asInteger;  /**< Value as an integer. */
    double   asFloat;    /**< Value as a floating point. */
    struct
    {
      size_t    length;        /**< String length. */
      uint8_t  *buffer;        /**< Pointer to the string buffer. */
      uint8_t   block1_more;   /**< More blocks to be received. */
      uint32_t  block1_num;    /**< Block number */                                             
      uint16_t  block1_size;   /**< Block size */                         
      uint32_t  block1_offset; /**< Block offset */ 
    } asBuffer;                /**< Value as a string. */
    struct
    {
      size_t   count;    /**< Count of the children. */
      struct qapi_Net_LWM2M_Flat_Data_s  *array;  /**< Flat data array. */
    } asChildren;        /**< Value as children. */
  } value;
} qapi_Net_LWM2M_Flat_Data_t;

/**
* @brief  LWM2M server request message data and internal LWM2M client state information.
*/
typedef struct qapi_Net_LWM2M_Server_Data_s
{
  qapi_Net_LWM2M_DL_Msg_t         msg_type;        /**< DL message type (requests, acknowledgements, or internal). */
  qapi_Net_LWM2M_Obj_Info_t       obj_info;        /**< Object information. */
  uint8_t                         msg_id_len;      /**< Message ID length.  */
  uint8_t                         msg_id[QAPI_MAX_LWM2M_MSG_ID_LENGTH];   
/**< Message ID. \n
   * The message ID is transparent to the application, but is passed to the application for every message
   * received from the server. The expectation is that the application stores the message ID associated
   * with the message and passes it to the LWM2M client when a response or notification must be sent to
   * the server. After the transaction pertaining to the message is complete, the message ID can be
   * discarded from the application. */
  uint16_t                        notification_id;
  /**< Notification ID.	\n
   * When a notification is sent using qapi_Net_LWM2M_Send_Message(), the notification ID associated
   * with the message is returned to the caller. It is the caller's responsibility to maintain the
   * notification ID for observation mapping. Later, when the network does a Cancel Observation for
   * a particular notification using RESET, it is indicated using the notification ID to the caller.
   * Using this notification ID, the caller can cancel the observation. If the cancel observation was not using
   * RESET, obj_info should have the information based on the observation that is to be cancelled. */  
  qapi_Net_LWM2M_Content_Type_t   content_type;    /**< Current encoded data payload content type. */
  uint32_t                        payload_len;     /**< Encoded data payload length. */
  uint8_t                        *payload;         /**< Encoded data payload. */
  qapi_Net_LWM2M_Attributes_t    *lwm2m_attr;      /**< Write attributes. */
  qapi_Net_LWM2M_Event_t          event;           /**< Internal events. */ 
} qapi_Net_LWM2M_Server_Data_t;

/**
* @brief  LWM2M application response message data and notification-related information. 
*/
typedef struct qapi_Net_LWM2M_App_Ex_Obj_Data_s
{
  qapi_Net_LWM2M_UL_Msg_t         msg_type;        /**< UL message type (response or notification). */
  qapi_Net_LWM2M_Obj_Info_t       obj_info;        /**< Object information. */
  qapi_Net_LWM2M_Response_Code_t  status_code;     /**< Application message status (applicable for responses only). */
  uint8_t                         conf_msg;        /**< Confirmable (ACK) or nonconfirmable application response/notifications. */  
  uint8_t                         msg_id_len;      /**< Message ID length. */ 

  uint8_t                         msg_id[QAPI_MAX_LWM2M_MSG_ID_LENGTH];
  /**< Message ID. \n
   * The message ID is transparent to the application, but is passed to the application for every message
   * received from the server. The expectation is that the application stores the message ID associated
   * with the message and passes it to the LWM2M client when a response or notification must be sent to
   * the server. After the transaction pertaining to the message is complete, the message ID can be
   * discarded from the application. */
  uint32_t                        observation_seq_num; /**< Observation sequence number. */
  uint16_t                        notification_id;
  /**< Notification ID. \n
   * When a notification is sent using qapi_Net_LWM2M_Send_Message(), the notification ID associated
   * with the message is returned to the caller. It is the caller's responsibility to maintain the
   * notification ID for observation mapping. Later, when the network does a Cancel Observation for
   * a particular notification using RESET, it is indicated using the notification ID to the caller.
   * Using this notification ID, the caller can cancel the observation. If the cancel observation was not using
   * RESET, obj_info should have the information based on the observation that is to be cancelled. */
  qapi_Net_LWM2M_Content_Type_t   content_type;    /**< Encoded data payload content type. */
  uint32_t                        payload_len;     /**< Encoded data payload length. */
  uint8_t                        *payload;         /**< Encoded data payload. */
} qapi_Net_LWM2M_App_Ex_Obj_Data_t;

/**
* @brief  LWM2M config message data.
*/
typedef struct qapi_Net_LWM2M_Config_Data_s
{
  struct qapi_Net_LWM2M_Config_Data_s *next;        
  qapi_Net_LWM2M_Config_Type_t        config_type; 
  union
  {
    bool     asBoolean;
    int64_t  asInteger;
    double   asFloat;
    struct
    {
      size_t    length;
      uint8_t  *buffer;
    } asBuffer;	
  }value;
}qapi_Net_LWM2M_Config_Data_t;


/** @} */ /* end_addtogroup qapi_lwm2m_datatypes */


/* LWM2M client DAM QAPIs */
#ifdef  QAPI_TXM_MODULE    
#define qapi_Net_LWM2M_Register_App(a)                     ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_REGISTER_APP, (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_Register_App_Extended(a,b,c)        ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_REGISTER_APP_EXTENDED, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_DeRegister_App(a)                   ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_DEREGISTER_APP, (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_Observe(a,b,c)                      ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_OBSERVE, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_Cancel_Observe(a,b)                 ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_CANCEL_OBSERVE, (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_Create_Object_Instance(a,b)         ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_CREATE_OBJECT_INSTANCE, (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_Delete_Object_Instance(a,b)         ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_DELETE_OBJECT_INSTANCE, (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_Get(a,b,c)                          ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_GET, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_Set(a,b)                            ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_SET, (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_Send_Message(a,b)                   ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LW2M_SEND_MESSAGE, (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_Encode_App_Payload(a,b,c,d,e,f,g)   ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_ENCODE_APP_PAYLOAD, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) e, (ULONG) f, (ULONG) g, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_Decode_App_Payload(a,b,c,d,e,f)     ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_DECODE_APP_PAYLOAD, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) e, (ULONG) f, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_Wakeup(a,b,c)                       ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_WAKEUP, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_ConfigClient(a,b)                   ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_CONFIG_CLIENT, (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_LWM2M_Default_Attribute_Info(a,b,c,d)     ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_LWM2M_DEFAULT_ATTR_INFO, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#else
qapi_Status_t qapi_LWM2Mc_Handler(UINT id, UINT a1, UINT a2, UINT a3, UINT a4, UINT a5, UINT a6, UINT a7, UINT a8, UINT a9, UINT a10, UINT a11, UINT a12);

/** @addtogroup qapi_lwm2m_apis
@{ */

/**
* @brief  Callback registered from the application, which is used by the LWM2M 
*         client to indicate the resource value change to the application.
*
* @param[in] handle  Handle received from qapi_Net_LWM2M_Register_App() or qapi_Net_LWM2M_Register_App_Extended().
* @param[in] lwm2m_data  Pointer to the LWM2M data.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK(0) is returned. Other value on error.
*/
typedef qapi_Status_t (*qapi_Net_LWM2M_App_CB_t)
(
  qapi_Net_LWM2M_App_Handler_t handle, 
  qapi_Net_LWM2M_Data_t *lwm2m_data
);

/**
* @brief  Callback registered from the application, which is used by the LWM2M client to indicate 
*         any extended object-specific messages from the server to the appropriate application. Each server 
*         message request is associated with a message ID and passed to the caller as part of the LWM2M server. 
*         The application must maintain the message ID to message mapping and use the message ID for 
*         any futher transactions that involve responses or notification events pertaining to the message.
*
* @param[in] handle  Handle received from qapi_Net_LWM2M_Register_App() or qapi_Net_LWM2M_Register_App_Extended().
* @param[in] lwm2m_srv_data  Pointer to the LWM2M server data.
* @param[in] user_data  Pointer to the user data.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK(0) is returned. Other value on error.
*/
typedef qapi_Status_t (*qapi_Net_LWM2M_App_Extended_CB_t)
(
  qapi_Net_LWM2M_App_Handler_t handle, 
  qapi_Net_LWM2M_Server_Data_t *lwm2m_srv_data,
  void *user_data
);

/**
* @brief  Registers an application with an LWM2M client. The application gets a handle  
*         on successful registration with the LWM2M client.
*
* @param[in,out] handle  Handle that is provided to the application on successful registration.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Register_App 
(
  qapi_Net_LWM2M_App_Handler_t *handle
);

/**
* @brief  Registers an application with an LWM2M client along with a callback handle. The application
*         gets a handle on successful registration with the LWM2M client and must use this handle for
*         subsequent calls to the LWM2M client in the APIs.
*
* @param[in,out] handle  Handle that is provided to the application on successful registration.
* @param[in] user_data  Transparent user data payload (to be returned in the user callback).
* @param[in] user_cb_fn  User client callback handle to forward data to the application.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Register_App_Extended
(
  qapi_Net_LWM2M_App_Handler_t *handle, 
  void *user_data, 
  qapi_Net_LWM2M_App_Extended_CB_t user_cb_fn
);

/**
* @brief  Deregisters an application. Any object instances associated with the handle are 
*         automatically cleaned up as a result of deregistration.
*
* @param[in] handle  Handle that was provided to the application on successful registration.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_DeRegister_App
(
  qapi_Net_LWM2M_App_Handler_t handle
);

/**
* @brief  Used by the application to indicate to the LWM2M client the object/instance/resource that 
*         the application is interested in observing. Only allowed for standard objects.
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] observe_cb_fn  Application callback to be invoked on a value change.
* @param[in] observe_info  Object/instance/resource information that the application is interested
*                          in monitoring on on the LWM2M client.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Observe 
(
  qapi_Net_LWM2M_App_Handler_t handle,  
  qapi_Net_LWM2M_App_CB_t observe_cb_fn, 
  qapi_Net_LWM2M_Object_Info_t *observe_info
);

/**
* @brief  Used by the application to cancel the observation.
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] observe_info  Object/instance/resource information for which the application
*                          is to cancel the observation.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Cancel_Observe 
(
  qapi_Net_LWM2M_App_Handler_t handle,  
  qapi_Net_LWM2M_Object_Info_t *observe_info
);

/**
* @brief  Creates standard/custom LWM2M object instances from the application. Only one object 
*         instance is allowed at a time. Applications are allowed to create instances of 
*         standard objects at any time and can pass the information associated with the instance. 
*         However, custom/extensible object instances can only be created by the application within 
*         the bootstrap window during the bootstrap phase. If the application missed the 
*         bootstrap window internally, rebootstrapping can be set to force the device to perform 
*         rebootstrapping on the next reboot, and the application is then allowed to create the 
*         new object instance. It is not required by the application to pass the information of the
*         custom object instance. 
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] lwm2m_data  LWM2M object instance and its resource information.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Create_Object_Instance 
(
  qapi_Net_LWM2M_App_Handler_t handle,   
  qapi_Net_LWM2M_Data_t *lwm2m_data
);

/**
* @brief  Deletes an LWM2M object instance from the application. Only one object instance deletion 
*         is allowed at a time.
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] instance_info  LWM2M object instance and its resource information.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Delete_Object_Instance 
(
  qapi_Net_LWM2M_App_Handler_t handle,  
  qapi_Net_LWM2M_Object_Info_t *instance_info
);

/**
* @brief  Gets the value of the LWM2M object/instance/resource from the application. Only one query of 
*         an object instance is allowed at a time.
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] lwm2m_info_req  Object/instance/resource information requested from the application.
* @param[out] lwm2m_data  Value of the LWM2M object/instance/resource information.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Get
(
  qapi_Net_LWM2M_App_Handler_t handle, 
  qapi_Net_LWM2M_Object_Info_t *lwm2m_info_req, 
  qapi_Net_LWM2M_Data_t **lwm2m_data
);

/**
* @brief  Sets the value of LWM2M resources. Only one object instance setting is allowed at a time.
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] lwm2m_data  Value of the LWM2M resource to be set.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Set 
(
  qapi_Net_LWM2M_App_Handler_t handle, 
  qapi_Net_LWM2M_Data_t *lwm2m_data
);

/**
* @brief  Sends application data, which can be responses or notification events, to the server. For 
*         notifications, a notification ID is returned by the LWM2M client, and it is the application's
*         responsiblity to store this notification ID. If there is an observation cancellation, the LWM2M
*         client will send this notification ID through the registered callback. Applications can 
*         encode the data payload either using the provided qapi_Net_LWM2M_Encode_App_Payload() QAPI or
*         using their own encode functions.  
*
* @param[in] handle  Handle received after successful application registration.
* @param[in,out] lwm2m_app_data  Value of the LWM2M extended/custom object information to be sent.
*                                The application is responsible for releasing any allocated resources.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Send_Message 
(
  qapi_Net_LWM2M_App_Handler_t handle,
  qapi_Net_LWM2M_App_Ex_Obj_Data_t *lwm2m_app_data
);

/**
* @brief  Utility function to encode application response/notification data before sending them to 
*         the server. If applications have their own encoding functions, they are free to use those 
*         functions to encode the data payload.  
*
* @param[in] obj_info  Object/URI information.
* @param[in] in_dec_data  Input data that is to be encoded.
* @param[in] in_dec_data_size  Input data size (in buffers).
* @param[in] write_attr  Write attribute information.
* @param[in] enc_content_type  Encoding format of the data.
* @param[out] out_enc_data  Output data buffer in encoded format. Resources are allocated internally.
*                           The application is responsible for releasing any allocated resources.  
* @param[out] out_enc_data_len  Output encoded data buffer length.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Encode_App_Payload 
(
  qapi_Net_LWM2M_Obj_Info_t *obj_info,
  qapi_Net_LWM2M_Flat_Data_t *in_dec_data,
  size_t in_dec_data_size,
  qapi_Net_LWM2M_Attributes_t *write_attr,  
  qapi_Net_LWM2M_Content_Type_t enc_content_type,
  uint8_t **out_enc_data,
  uint32_t *out_enc_data_len
);

/**
* @brief  Utility function to decode the server request data received through the registered application 
*         callback. If applications have their own decoding functions, they are free to use those functions 
*         to decode the data payload.
*
* @param[in] obj_info  Object/URI information.
* @param[in] in_enc_data  Input data that is to be decoded.
* @param[in] in_enc_data_len  Input data length.
* @param[in] dec_content_type  Decoding format of the input data.
* @param[out] out_dec_data  Output data buffer in decoded format. Resources are allocated internally.
*                           The application is responsible for releasing any allocated resources.  
* @param[out] out_dec_data_size  Output decoded data size (in buffers).
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Decode_App_Payload 
(
  qapi_Net_LWM2M_Obj_Info_t *obj_info,
  uint8_t *in_enc_data,
  uint32_t in_enc_data_len,
  qapi_Net_LWM2M_Content_Type_t dec_content_type,
  qapi_Net_LWM2M_Flat_Data_t **out_dec_data,
  size_t *out_dec_data_size
);

/**
* @brief  Wakes up the LWM2M client module to send notifications to the server. Wake-up and Sleep states of 
*         the LWM2M client are indicated to the application using the registered callback. The application is 
*         responsible for tracking the states of the LWM2M client.     
*               
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] msg_id  Message ID information associated with the request.
* @param[in] msg_id_len  Message ID information length.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Wakeup 
(
  qapi_Net_LWM2M_App_Handler_t handle,
  uint8_t *msg_id,
  uint8_t  msg_id_len
);

/**
* @brief  Initialization configuration parameters to LWM2M client module.
*
*
* @param[in] handle       Handler received after successful registration of the application. 
* @param[in] config_data  Config parameter associated with the request. 
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK(0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_ConfigClient
(
  qapi_Net_LWM2M_App_Handler_t handle,
  qapi_Net_LWM2M_Config_Data_t* config_data
);

/**
* @brief   Gets the value of the default Pmin and Pmax information for a specific server.
*               
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] server_id  Server ID information (use QAPI_LWM2M_SERVER_ID_INFO macro). 
* @param[out] p_min  Default "p_min" server attribute value. 
* @param[out] p_max  Default "p_max" server attribute value. 

*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK(0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Default_Attribute_Info 
(
  qapi_Net_LWM2M_App_Handler_t handle,
  uint32_t server_id,
  uint32_t *p_min,
  uint32_t *p_max
);


/** @} */ /* end_addtogroup qapi_lwm2m_apis */

#endif
#endif

