/**
 * qapi_fs_types.h
 * @brief Datatypes for QAPI FS.
 * @details This file defines the datatypes for QAPI wrapper layer.
 */

/*==========================================================================
 * Copyright (C) 2017 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 =========================================================================*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2017-06-30   as    Modified doxygen comment updates.
2017-04-27   leo   (Tech Comm) Edited/added Doxygen comments and markup.
2017-04-27   as    Updated doxygen comments.
2017-04-13   as    Defining statvfs structure in QAPI same as in EFS.
2017-02-22   as    Create.

===========================================================================*/


#ifndef QAPI_FS_TYPE_H
#define QAPI_FS_TYPE_H

#include "qapi_txm_base.h"
#include "qapi_status.h"

/*==============================================================================
                              MACROS
==============================================================================*/

/* QAPI Filesystem Macros */

#define QAPI_FS_NAME_MAX 768   /* Maximum length of a file name. */
  
#define QAPI_FS_MAX_DESCRIPTORS 128  /* Maximum number of files that can be kept
                                          opened simultaneously.*/
/* Error Macros defined for QAPI errors */
 
#define ___QAPI_ERROR(x)  ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BSP_FS,  x)))

#define QAPI_ERR_EPERM            ___QAPI_ERROR(1)
                                        /* Operation is not permitted. */

#define QAPI_ERR_EBADF            ___QAPI_ERROR(2)
                                        /* Bad file descriptor. */

#define QAPI_ERR_EACCES           ___QAPI_ERROR(3)
                                        /* Permission denied. */

#define QAPI_ERR_EXDEV            ___QAPI_ERROR(4)
                                        /* Attempt to cross the device. */

#define QAPI_ERR_ENODEV           ___QAPI_ERROR(5)
                                        /* No such device. */

#define QAPI_ERR_ENOTDIR          ___QAPI_ERROR(6)
                                        /* Not a directory. */

#define QAPI_ERR_EISDIR           ___QAPI_ERROR(7)
                                        /* Is a directory. */ 

#define QAPI_ERR_EMFILE           ___QAPI_ERROR(8)
                                        /* Too many open files. */

#define QAPI_ERR_ETXTBSY          ___QAPI_ERROR(9)
                                        /* File or directory is already open. */

#define QAPI_ERR_ENOSPC           ___QAPI_ERROR(10)
                                        /* No space is left on the device. */

#define QAPI_ERR_ESPIPE           ___QAPI_ERROR(11)
                                        /* Seek is not permitted. */

#define QAPI_ERR_ENAMETOOLONG     ___QAPI_ERROR(12)
                                        /* File name is too long. */

#define QAPI_ERR_ENOTEMPTY        ___QAPI_ERROR(13)
                                        /* Directory is not empty. */

#define QAPI_ERR_ELOOP            ___QAPI_ERROR(14)
                                        /* Too many symbolic links were encountered. */

#define QAPI_ERR_EILSEQ           ___QAPI_ERROR(15)
                                        /* Illegal byte sequence. */

#define QAPI_ERR_ESTALE           ___QAPI_ERROR(16)
                                        /* Stale remote file handle. */

#define QAPI_ERR_EDQUOT           ___QAPI_ERROR(17)
                                        /* Attempt to write beyond the quota, */

#define QAPI_ERR_EEOF             ___QAPI_ERROR(18)
                                        /* End of file. */

#define QAPI_ERR_INVLD_ID         ___QAPI_ERROR(19)
                                        /* Invalid ID was passed by the kernel framework. */

#define QAPI_ERR_UNKNOWN          ___QAPI_ERROR(20)
                                        /* Unknown error */


/*======================================================================
                          TYPEDEFS
 ======================================================================*/

/* Datatypes taken from C standard  data types. */
#ifndef _INT32_DEFINED
typedef signed long int    int32;
#endif
#ifndef _UINT16_DEFINED
typedef unsigned short     uint16;
#endif
#ifndef _UINT32_DEFINED
typedef unsigned long int  uint32;
#endif
#ifndef _UINT8_DEFINED
typedef unsigned char      uint8;
#endif

/* Datatypes defined for QAPIs*/
typedef int32              qapi_FS_Status_t;
typedef uint16             qapi_FS_Mode_t;
typedef void*              qapi_FS_Iter_Handle_t;
typedef long long          qapi_FS_Offset_t;

/** @addtogroup qapi_fs_types
@{ */

/*=============================================================================
                                   ENUMS
=============================================================================*/

/* Flag bits to open a file. */
enum{
    QAPI_FS_O_RDONLY_E  = 1,
    QAPI_FS_O_WRONLY_E  = 2,
    QAPI_FS_O_RDWR_E    = 4,
    QAPI_FS_O_CREAT_E   = 8,
    QAPI_FS_O_EXCL_E    = 16,
    QAPI_FS_O_TRUNC_E   = 32,
    QAPI_FS_O_APPEND_E  = 64,
};

/* Mode bits to open a file. */
enum{
/* User permissions. */
    QAPI_FS_S_IRUSR_E = 1,
    QAPI_FS_S_IWUSR_E = 2,
    QAPI_FS_S_IXUSR_E = 4,
/* Group permissions. */
    QAPI_FS_S_IRGRP_E = 8,
    QAPI_FS_S_IWGRP_E = 16,
    QAPI_FS_S_IXGRP_E = 32,
/* Other permissions. */
    QAPI_FS_S_IROTH_E = 64,
    QAPI_FS_S_IWOTH_E = 128,
    QAPI_FS_S_IXOTH_E = 256,
/* High bits. */
    QAPI_FS_S_ISUID_E = 512,
    QAPI_FS_S_ISGID_E = 1024,
    QAPI_FS_S_ISVTX_E = 2048,
};

/* Offset bits to seek a file. */
enum{
    QAPI_FS_SEEK_SET_E = 1,
    QAPI_FS_SEEK_CUR_E = 2,
    QAPI_FS_SEEK_END_E = 4,
};

/** File name rules. */
enum qapi_FS_Filename_Rule_e{
    QAPI_FS_FILENAME_RULE_8BIT_RELAXED = 1,  /**< 8-bit relaxed rule. */
    QAPI_FS_FILENAME_RULE_FAT          = 2,	 /**< FAT rule. */
    QAPI_FS_FILENAME_RULE_FDI          = 3	 /**< FDI rule. */
};

/** File name encoding schemes. */
enum qapi_FS_Filename_Encoding_e{
    QAPI_FS_FILENAME_ENCODING_8BIT = 1,  /**< 8-bit encoding. */
    QAPI_FS_FILENAME_ENCODING_UTF8 = 2 	 /**< UTF8 encoding. */
};

 /*============================================================================
                                  STRUCTURES
============================================================================*/

/** Statistics type, used in the qapi_FS_Stat() API. */
 struct qapi_FS_Stat_Type_s {
  uint16          st_dev;       /**< Unique device ID among the mounted file
                                     systems. */
  uint32          st_ino;       /**< INode number associated with the file. */
  uint16          st_Mode;      /**< Mode associated with the file. */
  uint8           st_nlink;     /**< Number of active links that are
                                     referencing this file. The	space occupied
                                     by the file is released after its
                                     references are reduced to 0. */
  uint32          st_size;      /**< File size in bytes. */
  unsigned long   st_blksize;   /**< Block size; smallest allocation unit of
                                     the file system. The unit in which
                                     the block Count is represented. */
  unsigned long   st_blocks;    /**< Number of blocks allocated for this file
                                     in st_blksize units. */
  uint32          st_atime;     /**< Last access time. This is not updated, so 
                                     it might have an incorrect value. */
  uint32          st_mtime;     /**< Last modification time. Currently, this 
                                     indicates the time when the file was
                                     created. */
  uint32          st_ctime;     /**< Last status change time. Currently, this
                                     indicates the time when the file was
                                     created. */
  uint32          st_rdev;      /**< Major and minor device number for special
                                     device files. */
  uint16          st_uid;       /**< Owner or user ID of the file. */
  uint16          st_gid;       /**< Group ID of the file. The stored file data
                                     blocks are charged to the quota of this
                                     group ID. */
};

/** File system information, used in the qapi_FS_Statvfs() API. */
 struct qapi_FS_Statvfs_Type_s {
  unsigned long                        f_bsize;
  /**< Fundamental file system block size. Minimum allocations in
       the file system happen at this size. */
  uint32                               f_blocks;
  /**< Maximum possible number of blocks available in the entire
       file system. */
  uint32                               f_bfree;
  /**< Total number of free blocks. */
  uint32                               f_bavail;
  /**< Number of free blocks currently available. */
  uint32                               f_files;
  /**< Total number of file serial numbers. */
  uint32                               f_ffree;
  /**< Total number of free file serial numbers. */
  uint32                               f_favail;
  /**< Number of file serial numbers available. */
  unsigned long                        f_fsid;
  /**< File system ID; this varies depending on the implementation
       of the file system. */
  unsigned long                        f_flag;
  /**< Bitmask of f_flag values. */
  unsigned long                        f_namemax;
  /**< Maximum length of the name part of the string for a file,
       directory, or symlink. */
  unsigned long                        f_maxwrite;
  /**< Maximum number of bytes that can be written in a single
       write call. */
  uint32                               f_balloc;
  /**< Blocks allocated in the general pool. */
  uint32                               f_hardalloc;
  /**< Hard allocation count. Resource intensive, so this is not
       usually computed. */
  unsigned long                        f_pathmax;
  /**< Maximum path length, excluding the trailing NULL. The unit here
       is in terms of character symbols. The number of bytes needed 
       to represent a character will vary depending on the 
       file name encoding scheme. For example, in a UTF8 encoding scheme,
       representing a single character could take anywhere between 
       1 to 4 bytes. */
  unsigned long                        f_is_case_sensitive;
  /**< Set to 1 if Path is case sensitive. */
  unsigned long                        f_is_case_preserving;
  /**< Set to 1 if Path is case preserved. */
  unsigned long                        f_max_file_size;
  /**< Maximum file size in the units determined by the member
       f_max_file_size_unit. */
  unsigned long                        f_max_file_size_unit;
  /**< Unit type for f_max_file_size. */
  unsigned long                        f_max_open_files;
  /**< This member tells how many files can be kept opened for one 
       particular file system. However, there is a global limit on how 
	   many files can be kept opened simultaneously across all 
	   file systems, which is configured by QAPI_FS_MAX_DESCRIPTORS. */
  enum qapi_FS_Filename_Rule_e         f_name_rule;
  /**< File naming rule. */
  enum qapi_FS_Filename_Encoding_e     f_name_encoding;
  /**< Encoding scheme. */
};

/** See the qapi_FS_Iter_Next() API for information about this structure. */
struct qapi_FS_Iter_Entry_s {
  char file_Path[QAPI_FS_NAME_MAX+1];
  /**< Name of the directory component. */
  struct qapi_FS_Stat_Type_s SBuf;
  /**< See qapi_FS_Stat_Type_s for information on this structure. */
  uint32 qapi_FS_D_Stats_Present; 
  /**< Bitmask for the qapi_FS_Stat_Type_s structure that defines
       which fields are filled when the qapi_FS_Iter_Next() API is called. */
};

/** @} */ /* end_addtogroup qapi_fs_types */

#endif /** QAPI_FS_TYPE_H*/


