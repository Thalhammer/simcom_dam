/* Copyright (c) 2011-2015.  Qualcomm Atheros, Inc.
All rights reserved.

Qualcomm Atheros Confidential and Proprietary.

*/

/**
 * @file qapi_status.h
 *
 * @brief QAPI status defintions
 *
 * @details This file defines the QAPI status type and common status
 *          values. It also defins the module IDs that can be used by
 *          modules to add additional status codes.
 */

#ifndef __QAPI_STATUS_H__ // [
#define __QAPI_STATUS_H__

#include "qapi_types.h"

/** @addtogroup qapi_status
@{ */

typedef int32_t qapi_Status_t;

/*
 * The following definitions are used to format error codes based on their
 * module. Error codes that use these macros will be a negative value of
 * the format -((10000 * <Module ID>) + <Status Code>).
 */
#define __QAPI_ERR_MOD_OFFSET                (10000)
#define __QAPI_ERR_ENCAP_MOD_ID(__mod_id__)  ((__mod_id__) * __QAPI_ERR_MOD_OFFSET)
#define __QAPI_ERROR(__mod_id__, __err__)    (0 - (__QAPI_ERR_ENCAP_MOD_ID(__mod_id__) + (__err__)))

/*
 * The following definitions represent the IDs for the various modules of
 * the QAPI.
 *
 * Note if the OEM wishes to added their own module IDs, it is recommended
 * to start at 100 to avoid possible conflicts with updates to the QAPI
 * that adds in additional modules.
 */
#define QAPI_MOD_BASE                        (0)
#define QAPI_MOD_802_15_4                    (1)
#define QAPI_MOD_NETWORKING                  (2)
#define QAPI_MOD_WIFI                        (3)
#define QAPI_MOD_BT                          (4)
#define QAPI_MOD_BSP                         (5)
#define QAPI_MOD_BSP_I2C_MASTER              (6)
#define QAPI_MOD_BSP_SPI_MASTER              (7)
#define QAPI_MOD_BSP_TLMM                    (8)
#define QAPI_MOD_BSP_GPIOINT                 (9)
#define QAPI_MOD_BSP_PWM                     (10)
#define QAPI_MOD_BSP_ERR                     (11)
#define QAPI_MOD_BSP_DIAG                    (12)
#define QAPI_MOD_BSP_OM_SMEM                 (13)
#define QAPI_MOD_CRYPTO                      (14)
#define QAPI_MOD_BSP_FS                      (15)
#define QAPI_MOD_BSP_USB                     (16)
#define QAPI_MOD_BSP_FTL                     (17)
#define QAPI_MOD_RIL                         (18)
#define QAPI_MOD_BSP_ADC                     (19)
#define QAPI_MOD_BSP_TSENS                   (20)
/*
 * The following definitions represent the status codes common to all of
 * the QAPI modules.
 */
#define QAPI_OK                              ((qapi_Status_t)(0))                               /**< Success                    */
#define QAPI_ERROR                           ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BASE,  1))) /**< General error             */
#define QAPI_ERR_INVALID_PARAM               ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BASE,  2))) /**< Invalid parameter         */
#define QAPI_ERR_NO_MEMORY                   ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BASE,  3))) /**< Memory allocation error   */
#define QAPI_ERR_NO_RESOURCE                 ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BASE,  4))) /**< Resource allocation error */
#define QAPI_ERR_BUSY                        ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BASE,  6))) /**< Opertion busy             */
#define QAPI_ERR_NO_ENTRY                    ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BASE,  7))) /**< Entry not found           */
#define QAPI_ERR_NOT_SUPPORTED               ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BASE,  8))) /**< Feature not supported     */
#define QAPI_ERR_TIMEOUT                     ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BASE,  9))) /**< Operation timed out       */
#define QAPI_ERR_BOUNDS                      ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BASE, 10))) /**< Out of bounds             */
#define QAPI_ERR_BAD_PAYLOAD                 ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BASE, 11))) /**< Bad Payload               */
#define QAPI_ERR_EXISTS                      ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BASE, 12))) /**< Entry already exists      */
#define QAPI_ERR_NOT_INITIALIZED             ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BASE, 13))) /**< Unintialized              */
#define QAPI_ERR_INVALID_STATE               ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BASE, 13))) /**< Invalid state             */



/** @} */
#endif // ] #ifndef __QAPI_STATUS_H__

