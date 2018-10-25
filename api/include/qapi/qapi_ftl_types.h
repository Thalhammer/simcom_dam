#ifndef __QAPI_FTL_TYPES_H
#define __QAPI_FTL_TYPES_H

/*
 * @file qapi_ftl_types.h
 *
 * @brief Datatypes for QAPI FTL layer.
 *
 * @addtogroup qapi_ftl
 * @{ 
 *
 * @details This file defines the error types specific to ftl
 * @}
 */
/*
 *
 * Copyright (c) 2017 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
*/
/*=============================================================================
 * 
 *                         EDIT HISTORY FOR MODULE
 * 
 *   This section contains comments describing changes made to the module.
 *   Notice that changes are listed in reverse chronological order.
 * 
 * when         who   what, where, why
 * ----------   ---   ---------------------------------------------------------
 * 2017-05-03   svl    Updated Doxygen comments and markup.
 * 2017-03-10   svl    Create.
 * 
 * ==========================================================================*/

#include <qapi_status.h>

/*=============================================================================
                              ERROR MACROS
 ============================================================================*/

 /** @addtogroup qapi_ftl
@{ */

/** Utility macro to define QAPI_FTL specific error types */
#define __QAPI_FTL_ERROR(x)  \
                          ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BSP_FTL,  x)))

/** returned if FTL APIs are called without calling FTL init first */
#define QAPI_FTL_NOT_INIT           __QAPI_FTL_ERROR(0)        

/** returned if NAND is out of good blocks */
#define QAPI_FTL_OUT_OF_GOOD_BLOCKS __QAPI_FTL_ERROR(1)

/** returned if registering QAPI handler fails */
#define QAPI_FTL_ERR_UNKNOWN        __QAPI_FTL_ERROR(2)

/** returned if QAPI handler is called with an invalid ID */
#define QAPI_FTL_ERR_INVLD_ID       __QAPI_FTL_ERROR(3)

/** @} */ /* end_addtogroup qapi_ftl */

#endif /* QAPI_FTL_TYPES_H */
