#ifndef FX_API_H
#define FX_API_H
/**
  @file fx_api.h
  @brief  Prototypes of functions used (by TXM module manager) for file operations

EXTERNAL FUNCTIONS
   qurt_efs_read

INITIALIZATION AND SEQUENCING REQUIREMENTS
   None.

Copyright (c) 2013-2015  by Qualcomm Technologies, Inc.  All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.


=============================================================================*/
#include "fs_public.h"

extern int32 qurt_efs_read(int32 fd, void *buf, uint32 size, uint32 *bytesRead);

#define FX_FILE  int						/*File data type*/
#define FX_SUCCESS  ((unsigned int) 0x00)

/* Actual function mappings */
#define fx_file_read 	qurt_efs_read
#define fx_file_close 	efs_close

#endif /*FX_API_H*/

