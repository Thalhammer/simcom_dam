/* Copyright (c) 2011-2015.  Qualcomm Atheros, Inc.
All rights reserved.

Qualcomm Atheros Confidential and Proprietary.

*/

/**
 * @file qapi_types.h
 *
 * @brief QAPI base type definitions
 *
 * @details This file provides the base type definitions used by the QAPI.
 *          This includes the basic integer types (based on stdint.h and
 *          stddef.h) and a basic boolean type.
 */

#ifndef __QAPI_TYPES_H__ // [
#define __QAPI_TYPES_H__

#include <stdint.h>
#include <stddef.h>

typedef uint32_t qbool_t;

#ifndef false
   #define false     (0)
#endif

#ifndef true
   #define true      (1)
#endif

#define A_TRUE          ((A_BOOL)1) //(QOSAL_TRUE)
#define A_FALSE         ((A_BOOL)0) //(QOSAL_FALSE)


#endif // ] #ifndef __QAPI_TYPES_H__

