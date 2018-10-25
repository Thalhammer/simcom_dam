#ifndef QAPI_FS_H
#define QAPI_FS_H
/**
 * @file qapi_fs.h
 * @brief QAPI FS Functional Overview
 * @details This file provides QAPI wrapper over filesystem APIs.
*/
/*
 * Copyright (C) 2017 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

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
2017-04-13   as    Fixed Klockwork error in qapi_FS_Iter_Next.
2017-02-22   as    Create.

===========================================================================*/

#include "qapi_fs_types.h"
                                                                                                                           
/*============================================================================
                USER_Mode_DEFS
============================================================================*/

                 /* Driver ID defines */

#define  TXM_QAPI_FS_OPEN_WITH_MODE           TXM_QAPI_FS_BASE  
#define  TXM_QAPI_FS_OPEN                     TXM_QAPI_FS_BASE + 1
#define  TXM_QAPI_FS_READ                     TXM_QAPI_FS_BASE + 2
#define  TXM_QAPI_FS_WRITE                    TXM_QAPI_FS_BASE + 3
#define  TXM_QAPI_FS_CLOSE                    TXM_QAPI_FS_BASE + 4
#define  TXM_QAPI_FS_TRUNCATE                 TXM_QAPI_FS_BASE + 5
#define  TXM_QAPI_FS_RENAME                   TXM_QAPI_FS_BASE + 6
#define  TXM_QAPI_FS_SEEK                     TXM_QAPI_FS_BASE + 7
#define  TXM_QAPI_FS_MK_DIR                   TXM_QAPI_FS_BASE + 8
#define  TXM_QAPI_FS_RM_DIR                   TXM_QAPI_FS_BASE + 9
#define  TXM_QAPI_FS_UNLINK                   TXM_QAPI_FS_BASE + 10
#define  TXM_QAPI_FS_STAT                     TXM_QAPI_FS_BASE + 11
#define  TXM_QAPI_FS_STAT_WITH_HANDLE         TXM_QAPI_FS_BASE + 12
#define  TXM_QAPI_FS_STATVFS                  TXM_QAPI_FS_BASE + 13
#define  TXM_QAPI_FS_ITER_OPEN                TXM_QAPI_FS_BASE + 14
#define  TXM_QAPI_FS_ITER_NEXT                TXM_QAPI_FS_BASE + 15
#define  TXM_QAPI_FS_ITER_CLOSE               TXM_QAPI_FS_BASE + 16
#define  TXM_QAPI_FS_LAST_ERROR               TXM_QAPI_FS_BASE + 17

#ifdef  QAPI_TXM_MODULE
               
                /* API Definitions */

#define qapi_FS_Open_With_Mode(Path, Oflag, Mode, Fdptr)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_OPEN_WITH_MODE,\
    (ULONG) Path,(ULONG) Oflag, (ULONG) Mode, (ULONG) Fdptr,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define qapi_FS_Open(Path, Oflag, Fdptr)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_OPEN,\
    (ULONG) Path, (ULONG) Oflag, (ULONG) Fdptr, (ULONG) 0,(ULONG) 0, (ULONG) 0,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
                                                                                                                                                                                                                                                                                                                 
#define qapi_FS_Read(Fd, Buf, Count, Bytes_Read_Ptr)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_READ,\
    (ULONG) Fd,(ULONG) Buf, (ULONG) Count, (ULONG) Bytes_Read_Ptr,\
    (ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0))
                                                                                                                                                                                                                                                                                                                      
#define qapi_FS_Write(Fd, Buf, Count, Bytes_Written_Ptr)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_WRITE,\
    (ULONG) Fd, (ULONG) Buf, (ULONG) Count, (ULONG) Bytes_Written_Ptr,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0))
                                                                                                                                                                                                                                                                                                                      
#define qapi_FS_Close(Fd)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_CLOSE ,\
    (ULONG) Fd,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
                                                                                                                                                                                                                                                                                                                 
#define qapi_FS_Rename(Old_Path, New_Path)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_RENAME,\
    (ULONG) Old_Path, (ULONG) New_Path, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0))
                                                                                                                                                                                                                                                                                                                 
#define qapi_FS_Truncate(Path, Length)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_TRUNCATE,\
    (ULONG) Path,(ULONG) Length, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0))
                                                                                                                                                                                                                                                                                                                 
#define qapi_FS_Seek(Fd, Offset, Whence, Actual_Offset_Ptr)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_SEEK,\
    (ULONG) Fd,(ULONG) Offset,   (ULONG) Whence, (ULONG) Actual_Offset_Ptr,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0))
                                                                                                                                                                                                                                                                                                                 
#define qapi_FS_Rm_Dir(Path)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_RM_DIR,\
    (ULONG) Path,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0))
    
                                                                                                                                                                                                                                                                                                                 
#define qapi_FS_Mk_Dir(Path, Mode)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_MK_DIR,\
    (ULONG) Path,(ULONG) Mode , (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
                                                                                                                                                                                                                                                                                                                 
#define qapi_FS_Unlink(Path)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_UNLINK,\
    (ULONG) Path,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0,(ULONG) 0,(ULONG) 0))
                                                                                                                                                                                                                                                                                                                 
#define qapi_FS_Stat(Path, Sbuf)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_STAT,\
    (ULONG) Path,(ULONG) Sbuf , (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0))
                                                                                                                                                                                                                                                                                                                 
#define qapi_FS_Stat_With_Handle(fd_ptr, Sbuf)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)( \
    TXM_QAPI_FS_STAT_WITH_HANDLE, (ULONG) fd_ptr, (ULONG) Sbuf , (ULONG) 0,\
    (ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0, (ULONG) 0))
                                                                                                                                                                                                                                                                                                                
#define qapi_FS_Statvfs(Path, Sbuf)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_STATVFS,\
    (ULONG) Path,(ULONG) Sbuf , (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0))
                                                                                                                                                                                                                                                                                                                 
#define qapi_FS_Iter_Open(Path, Handle)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_ITER_OPEN,\
    (ULONG) Path,(ULONG) Handle , (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0))
                                                                                                                                                                                                                                                                                                                
#define qapi_FS_Iter_Next(Iter_Hdl, Entry)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_ITER_NEXT,\
    (ULONG) Iter_Hdl, (ULONG) Entry, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
    (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,(ULONG) 0))
                                                                                                                                                                                                                                                                                                               
#define qapi_FS_Iter_Close(Iter_Hdl)\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_ITER_CLOSE,\
    (ULONG) Iter_Hdl, (ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0,\
    (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
                                                                                                                                                                                                                                                                                                               
#define qapi_FS_Last_Error()\
    ((qapi_FS_Status_t) (_txm_module_system_call12)(TXM_QAPI_FS_LAST_ERROR,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0, \
    (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
                                                                                                                                                                                                                                                                                                               

#elif defined QAPI_TXM_SOURCE_CODE
    
/*============================================================================
                KERNEL_Mode_DEFS
============================================================================*/

/*============================================================================
                qapi_FS_Open_With_Mode
============================================================================*/

/** @addtogroup qapi_fs
@{ */

/**
 * @brief Opens a file as per the specified Oflag and mode.
 *
 * @param[in] Path  Path of the file that is to be opened.
 *
 * @param[in] Oflag     Argument that describes how this file is to
 *                      be opened. It contains one of the following values:
 *                      - QAPI_FS_O_RDONLY_E -- Open for read only.
 *                      - QAPI_FS_O_WRONLY_E -- Open for write only.
 *                      - QAPI_FS_O_RDWR_E -- Open for read and write.
 *                      In addition, the following flags can be bitwise ORed
 *                      with this value:
 *                      - QAPI_FS_O_APPEND_E -- All writes will self-seek to the 
 *                                              end of the file before writing.
 *                      - QAPI_FS_O_CREAT_E -- Create the file if it does not exist.
 *                      - QAPI_FS_O_TRUNC_E -- Truncate the file to zero bytes on
 *                                             successful open.
 *                      The following flags can be used to specify common 
 *                      ways of opening files:
 *                      - QAPI_FS_O_CREAT_E | QAPI_FS_O_TRUNC_E -- 
 *                                        Normal for writing a file. Creates it if 
 *                                        it does not exist. The resulting file is 
 *                                        zero bytes long.
 *                      - QAPI_FS_O_CREAT_E | QAPI_FS_O_EXCL_E -- Creates a file
 *                                         but fails if it already exists. @tablebulletend
 *
 * @param[in] Mode  If QAPI_FS_O_CREAT is a part of Oflag, a third argument
 *   (Mode) must be passed to qapi_FS_open() to define the file
 *   permissions given to the newly created file. If QAPI_FS_O_CREAT is
 *   not a  part of flag, set Mode=0. \n
 *   One or more of the following permission bits can be
 *   ORed as the Mode parameter:
 *   - QAPI_FS_S_IRUSR_E -- Read permission for a user
 *   - QAPI_FS_S_IWUSR_E -- Write permission for a user
 *   - QAPI_FS_S_IXUSR_E -- Execute permission for a user
 *   - QAPI_FS_S_IRGRP_E -- Read permission for a group
 *   - QAPI_FS_S_IWGRP_E -- Write permission for a group
 *   - QAPI_FS_S_IXGRP_E -- Execute permission for a group
 *   - QAPI_FS_S_IROTH_E -- Read permission for other
 *   - QAPI_FS_S_IWOTH_E -- Write permission for other
 *   - QAPI_FS_S_IXOTH_E -- Execute permission for other
 *   - QAPI_FS_S_ISUID_E -- Set UID on execution
 *   - QAPI_FS_S_ISGID_E -- Set GID on execution
 *   - QAPI_FS_S_ISVTX_E -- Sticky bit (hidden attribute in FAT) @tablebulletend
 *
 * @param[out] Fd_ptr   Address of the file descriptor variable.
 *                      On success, the file descriptor of an opened file is
 *                      written to it. On failure, the variable is set to -1.
 *
 * @return Returns QAPI_OK on success and -ve error code is returned on failure.
 * - QAPI_ERR_EEXIST -- Cannot create a file with the path name because another 
 *                      file with the same name exists and an exclusive open is 
 *                      requested or a special (exclusive) file with the same 
 *                      path name exists.
 * - QAPI_ERR_ENOENT -- No entry for the path name is found, the file cannot be
 *                      opened (and a new file is not created because the 
 *                      QAPI_FS_O_CREAT flag was not supplied).
 * - QAPI_ERR_EMFILE -- Maximum number of open descriptors is exceeded.
 * - QAPI_ERR_EISDIR -- Opening a file with a write flag (QAPI_FS_O_WRONLY or 
 *                      QAPI_FS_O_RDWR) was denied because a directory with the same
 *                      name exists.
 * - QAPI_ERR_ENOSPC -- No space is left on the device.
 * - QAPI_ERR_ENAMETOOLONG -- File/directory name exceeded the NAME_MAX limit or the
 *                            path name exceeded the Path_MAX limit, which is 1024 bytes.
 *                            The maximum length of a full path name, not including 
 *                            a trailing '\0' character.
 * - QAPI_ERR_ENOMEM -- No more dynamic memory is available.
 * - QAPI_ERR_ENODEV -- The device does not exist.
 * - QAPI_ERR_ENOTDIR -- The file could not be created under a path that is not
 *                       a directory. Another possibility is an open with the
 *                       QAPI_FS_O_CREAT flag tried to create a file in the 
 *                       ROM file system.
 * - QAPI_ERR_EINVAL -- Invalid parameter or path.
 */
qapi_FS_Status_t qapi_FS_Open_With_Mode(const char* Path, 
                                        int Oflag,
                                        qapi_FS_Mode_t Mode,
                                        int* Fd_ptr);

/*============================================================================
                qapi_FS_Open
============================================================================*/
/**
 *  @brief   Opens a file as per the specified Oflag.
 *
 *  @details The parameters, error codes, and return types are the same as in
 *           the API qapi_FS_Open_With_Mode(). This function does not require
 *           the mode as an input argument. It opens the file in Default mode,
 *           which gives read and write permissions to the user, but not
 *           execute permissions.
 *
 *  @param[in] Path   Path of the file that is to be opened.
 *  @param[in] Oflag  Argument that describes how this file should
 *                    be opened. See qapi_FS_Open_With_Mode().
 *  @param[out] Fd_ptr  Address of the file descriptor variable.
 *                      On success, the file descriptor of an opened file is
 *                      written to it. On failure, the variable is set to -1.
 *
 * @return
 * See qapi_FS_Open_With_Mode().
 */
qapi_FS_Status_t qapi_FS_Open(const char* Path, 
                              int Oflag,
                              int* Fd_ptr);
                              
/*============================================================================
                qapi_FS_Read
============================================================================*/
/**
 *  @brief Attempts to read Count bytes of data from the file associated with
 *         the specified file descriptor.
 *
 *  @details Zero is a valid result and generally indicates that the end of 
 *           the file has been reached. It is permitted for qapi_FS_Read to 
 *           return fewer bytes than were requested, even if the data is
 *           available in the file.
 *
 *  @param[in] Fd  File descriptor obtained via the qapi_FS_Open() function.
 *  @param[out] Buf  Buffer where the read bytes from the file will be 
 *                   stored.
 *  @param[in] Count  Number of bytes to read from the file.
 *  @param[out] Bytes_Read_Ptr  This is a return from the function with the 
 *                              number of bytes actually read.
 *
 *  @return Returns QAPI_OK on success, and -ve error code is returned on failure.
 */
qapi_FS_Status_t qapi_FS_Read(int Fd, 
                              uint8* Buf, 
                              uint32 Count,
                              uint32* Bytes_Read_Ptr);

/*============================================================================
                qapi_FS_Write
============================================================================*/
/**
 *  @brief Attempts to write 'Count' bytes of data to the file associated with
 *         the specified file descriptor.
 *
 *  @details The write ioperation may happen at the current file pointer or 
 *           at the end of the file if the file is opened with QAPI_FS_O_APPEND.
 *           It is permitted for qapi_FS_Write to write fewer bytes than were 
 *           requested, even if space is available. If the number of bytes written 
 *           is zero, it indicates that the file system is full (writing), which 
 *           will result in an QAPI_ERR_ENOSPC error.
 *
 *  @param[in] Fd  File descriptor obtained via the qapi_FS_Open() function.
 *
 *  @param[in] Buf  Buffer to which the file is to be written.
 *
 *  @param[in] Count  Number of bytes to write to the file.
 *
 *  @param[out] Bytes_Written_Ptr  This is a return from the function 
 *                                 with the number of bytes actually written.
 *
 *  @return Returns QAPI_OK on success and -ve error code is returned on failure.
 */
qapi_FS_Status_t qapi_FS_Write(int Fd, 
                               const uint8* Buf,
                               uint32 Count,
                               uint32* Bytes_Written_Ptr);
                             
/*============================================================================
                qapi_FS_Close
============================================================================*/
/**
 *  @brief  Closes the file descriptor.
 *
 *  @details The descriptor will no longer refer to any file and
 *            will be allocated to subsequent calls to qapi_FS_Open().
 *
 *  @param[in] Fd  File descriptor obtained via the qapi_FS_Open() function.
 *
 *  @return Returns QAPI_OK on success and -ve erro code is returned on failure.
 */
qapi_FS_Status_t qapi_FS_Close(int Fd);

/*============================================================================
                qapi_FS_Rename
============================================================================*/
/**
 *  @brief Renames a file or a directory.
 *
 *  @details Files and directories (under the same file system) can be renamed.
 *           The arguments Old_Path and New_Path do not have to be in the 
 *           same directory (but must be on the same file system device).
 *
 *  @param[in] Old_Path   Path name before the rename operation.
 *
 *  @param[in] New_Path   Path name after the rename operation.
 *
  * @note1hang
 *    qapi_FS_Rename is atomic and will either successfully rename the file or
 *    leave the file in its original location.
 *
 *  @return Returns QAPI_OK on success and -ve error code is returned on failure.
 *  - QAPI_ERR_EINVAL -- Invalid operation denied. The reasons can be a possible
 *                       permission access violation or the creation of cycle
 *                       symbolic links if the rename suceeded.
 *  - QAPI_ERR_EISIR -- The New_Path is a directory.
 *  - QAPI_ERR_EXDEV -- A rename operation accross different file systems is
 *                      not permitted.
 *  - QAPI_ERR_ENOTEMPTY -- The Old_Path directory is not empty.
 */
qapi_FS_Status_t qapi_FS_Rename(const char* Old_Path, const char* New_Path);

/*============================================================================
                qapi_FS_Truncate
============================================================================*/
/**
 * @brief Truncates a file to a specified length.
 *
 * @note1hang
 *    If the supplied length is greater than the current file size, it
 *    depends on the underlying file system to determine whether the file
 *    can grow in size.
 *
 * @param[in] Path    Path of the file whose length is to be truncated.
 * @param[in] Length  New size of the file. The length is in the range
 *           (-4 * 1024 * 1024 * 1024, + 4 * 1024 * 1024 * 1024 -1) bytes.
 *
 *  @return Returns QAPI_OK on success and -ve error code is returned on failure.
 *  - QAPI_ERR_EINVAL -- Truncation is not possible. Invalid operation or parameter.
 *  - QAPI_ERR_ENOENT -- A file with the specified path was not found.
 *  - QAPI_ERR_ENODEV -- The device does not exist.
 *  - QAPI_ERR_ENAMETOOLONG -- File-name or directory name exceeded the QAPI_FS_NAME_MAX  
 *                           limit, or the path name exceeded the Path_MAX limit.
 *                           The maximum length of a full path name, not including a 
 *                           trailing '\0' character: Path_MAX = 1024.
 *  - QAPI_ERR_EEOF -- Truncation is not allowed beyond End of File (EOF) on this  
 *                     file system.
 */
qapi_FS_Status_t qapi_FS_Truncate(const char* Path, qapi_FS_Offset_t Length);

/*============================================================================
                qapi_FS_Seek
============================================================================*/
/**
 *  @brief Changes the file offset for the opened file descriptor.
 *
 *  @details Changing the file offset does not modify the file. If you lseek 
 *           past the end of the file and then write, the gap will be filled  
 *           with zero bytes. This gap may not actually allocate space. Using  
 *           this API file can be seeked up to (4 GB -1) offset.
 *
 *  @param[in] Fd  File descriptor obtained via the qapi_FS_Open() API.
 *  @param[in] Offset  New offset of the file.
 *  @param[in] Whence  Indicates how the new offset is computed: \n
 *                      QAPI_FS_SEEK_SET_E -- Set to Offset. \n
 *                      QAPI_FS_SEEK_CUR_E -- Set to Offset + current position. \n
 *                      QAPI_FS_SEEK_END_E -- Set to Offset + file size.
 *  @param[out] Actual_Offset_Ptr  Upon success, the resulting offset as bytes from 
 *               the beginning of the file is filled in this parameter.
 *               On failure, the variable is set to -1. 
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 *  - QAPI_ERR_EINVAL -- Invalid operation.
 *  - QAPI_ERR_EBADF -- File descriptor was not found.
 *  - QAPI_ERR_ESPIPE -- Some file descriptors (like pipes and FIFOs) are not seekable.
 */
qapi_FS_Status_t qapi_FS_Seek(int Fd,
                              qapi_FS_Offset_t Offset,
                              int Whence,
                              qapi_FS_Offset_t* Actual_Offset_Ptr);

/*============================================================================
                qapi_FS_Mk_Dir
============================================================================*/
/**
 *  @brief Creates a new directory.
 *
 * @param[in] Path  Path for the directory.
 * @param[in] Mode  Permission bits of the new directory. See the 
 *                  qapi_FS_Open() API for information on Mode bits.
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 *  - QAPI_ERR_ENOENT -- No such Path was found.
 *  - QAPI_ERR_EINVAL -- Invalid operation or parameter.
 *  - QAPI_ERR_ENOSPC -- The operation could not be completed because the device is full.
 *  - QAPI_ERR_ENAMETOOLONG -- File name or directory name exceeded the NAME_MAX
 *                           limit, or the path name exceeded the Path_MAX limit.
 *                           The maximum length of a full path name, not including a 
 *                           trailing '\0' character: Path_MAX = 1024.
 */
qapi_FS_Status_t qapi_FS_Mk_Dir(const char* Path, 
                                qapi_FS_Mode_t Mode);

/*============================================================================
                qapi_FS_Rm_Dir
============================================================================*/
/**
 *  @brief Removes a directory. Only empty directories can be removed.
 *
 *  @param[in] Path  Path of the directory that is to be removed.
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 *  - QAPI_ERR_ENOTDIR -- The parameter Path is not a directory.
 *  - QAPI_ERR_ENOTEMPTY -- The directory is not empty.
 *  - QAPI_ERR_ETXTBSY -- The directory is in use or open.
 *  - QAPI_ERR_EINVAL -- Invalid parameter.
 */
qapi_FS_Status_t qapi_FS_Rm_Dir(const char* Path);

/*============================================================================
                qapi_FS_Unlink
============================================================================*/
/**
 *   @brief   Removes a link to a closed file.
 *
 *  @details  If the link Count goes to zero, this will also remove the
 *            file. The qapi_FS_Unlink() API can be used
 *            on all file system objects except for directories.
 *            Use qapi_FS_Rm_Dir() for directories.
 *
 *  @note1hang The file must be closed for unlinking or removing. If it is open,
 *             the error QAPI_ERR_ETXTBSY is returned, indicating that the file
 *             is not closed.
 *
 * @param[in] Path  File to which the link is to be removed.
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 *  - QAPI_ERR_ENOENT -- No such path was found.
 *  - QAPI_ERR_EPERM -- Permission is denied.
 *  - QAPI_ERR_ETXTBSY -- The file is in use or open.
 *  - QAPI_ERR_EINVAL -- Invalid parameter.
 *
 */
qapi_FS_Status_t qapi_FS_Unlink(const char* Path);

/*============================================================================
                qapi_FS_Stat
============================================================================*/
/**
 *  @brief  Returns the statistics of a file.
 *
 *  @param[in] Path  File descriptor of the file.
 *
 *  @param[out] SBuf  For information on what is returned in the structure, 
 *                    see struct #qapi_FS_Stat_Type_s.
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 *
 */
qapi_FS_Status_t qapi_FS_Stat(const char* Path, 
                              struct qapi_FS_Stat_Type_s* SBuf);

/*============================================================================
                qapi_FS_Stat_With_Handle
============================================================================*/
/**
 *  @brief Obtains information about the file with its open file handle.
 * 
 *  @param[in] Fd  Handle to a file otained using the qapi_FS_Open() API.
 *  @param[out] SBuf  Information is returned in the structure #qapi_FS_Stat_Type_s.
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 *
 */
qapi_FS_Status_t qapi_FS_Stat_With_Handle(int Fd, 
                                          struct qapi_FS_Stat_Type_s* SBuf);

/*============================================================================
                qapi_FS_Statvfs
============================================================================*/
/**
 *  @brief Obtains information about an entire file system.
 *
 *  @details
 *   Gets detailed information about the filesystem specified by the path.
 *   Root or any mounted path for which to get information can be specified.
 *   If the root path is specified, information about the root file system is
 *   returned. Otherwise, information about the mounted file system specified
 *   by the path or the file system in which the given path exists is returned.
 *   The content details are in struct #qapi_FS_Statvfs_Type_s.
 *
 * @param[in] Path  Valid path of a file or directory on the mounted file system.
 * @param[out] SBuf  Information is returned in the structure #qapi_FS_Statvfs_Type_s. 
 *
 * @return  Returns QAPI_OK on success, and -ve error code is returned on failure.
*/
qapi_FS_Status_t qapi_FS_Statvfs(const char* Path, 
                                 struct qapi_FS_Statvfs_Type_s* SBuf);

/*============================================================================
                qapi_FS_Iter_Open
==============================================================================*/
/**
 *  @brief Opens a directory and gets a handle to the directory.
 *  @details
 *    This function opens a directory for iteration and gets an opaque handle
 *    that can then be passed to qapi_FS_Iter_Next() to iterate through the
 *    entries of the opened directory. This same pointer must be passed
 *    to closedir to close the iterator.
 *
 * @param[in] Path  Valid path of the directory to iterate.
 * @param[out] handle  Handle provided by the module to the client. \n
 * @note Clients should cache the handle. Once lost, it cannot be queried back 
 *       from the module.
 *
 * @return Returns QAPI_OK on success and -ve error code is returned on failure.
 */
qapi_FS_Status_t qapi_FS_Iter_Open(const char* Path,
                                   qapi_FS_Iter_Handle_t* handle);

/*============================================================================
                qapi_FS_Iter_Next
==============================================================================*/
/**
 *  @brief Reads the next entry in the directory using the opened directory
 *  iterator.
 *
 *  @details If an entry is present, the structure parameter
 *           is filled with details about the entry. Otherwise, a NULL
 *           value is filled.
 *
 * @note1hang
 *    Any code that uses qapi_FS_Iter_Next() must be prepared for
 *    qapi_FS_D_Stats_Present() to be zero and call qapi_FS_Stat() for each entry.
 *
 *  @param[in] Iter_Hdl  Handle to directory obtained by the qapi_FS_Iter_Open() API.
 *  @param[out] Iter_Entry  Details about the next entry found is filled in \n
 *  struct qapi_FS_Dirent { \n
 *              char     file_Path[QAPI_FS_NAME_MAX+1] \n
 *              struct   qapi_FS_Stat_Type_s SBuf \n
 *              uint32 qapi_FS_D_Stats_Present; \n
 *              }
 *
 * - file_Path -- Name of the directory component
 * - SBuf      -- Information about the component; See
 *                  #qapi_FS_Stat_Type_s for information about this structure
 * - qapi_FS_D_Stats_Present -- This is a bitmask for the above structure that 
 *                              defines which fields are filled when this
 *                              this API is called. \n
 *    Bitmasks for qapi_FS_D_Stats_Present are defined as:
 * @verbatim 
    ::QAPI_FS_DIRENT_HAS_ST_DEV       = (1 << 1)
    ::QAPI_FS_DIRENT_HAS_ST_INO       = (1 << 2)
    ::QAPI_FS_DIRENT_HAS_ST_Mode      = (1 << 3)
    ::QAPI_FS_DIRENT_HAS_ST_NLINK     = (1 << 4)
    ::QAPI_FS_DIRENT_HAS_ST_SIZE      = (1 << 5)
    ::QAPI_FS_DIRENT_HAS_ST_BLKSIZE   = (1 << 6)
    ::QAPI_FS_DIRENT_HAS_ST_BLOCKS    = (1 << 7)
    ::QAPI_FS_DIRENT_HAS_ST_ATIME     = (1 << 8)
    ::QAPI_FS_DIRENT_HAS_ST_MTIME     = (1 << 9)
    ::QAPI_FS_DIRENT_HAS_ST_CTIME     = (1 << 10)
    ::QAPI_FS_DIRENT_HAS_ST_RDEV      = (1 << 11)
    ::QAPI_FS_DIRENT_HAS_ST_UID       = (1 << 12)
    ::QAPI_FS_DIRENT_HAS_ST_GID       = (1 << 13) @endverbatim
 *
 * @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 */
qapi_FS_Status_t qapi_FS_Iter_Next(qapi_FS_Iter_Handle_t Iter_Hdl,
                                   struct qapi_FS_Iter_Entry_s* Iter_Entry);

/*==============================================================================
                qapi_FS_Iter_Close
============================================================================*/
/**
 *  @brief Closes the directory iterator, releasing the iterator for reuse.
 *
 *  @param[in] Iter_Hdl  Handle to the directory obtained using the qapi_FS_Iter_Open() API.
 *
 *  @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 */
qapi_FS_Status_t qapi_FS_Iter_Close(qapi_FS_Iter_Handle_t Iter_Hdl);

/*==============================================================================
                qapi_FS_Last_Error
============================================================================*/
/**
 *  @brief Returns the last error that occured in current task's context.
 *
 *  If qapi_FS_Open() fails, an immediate call to qapi_FS_Last_Error 
 *  returns the error for the failure. Otherwise, if another API, e.g.,
 *  qapi_FS_Read(), is called after qapi_FS_Open failed within the same task, 
 *  the error will be overwritten with QAPI_OK or a QAPI error code, 
 *  depending whether qapi_FS_Read() was success or failed.
 *
 * @return  Returns QAPI_OK on success and -ve error code is returned on failure.
 */
qapi_FS_Status_t qapi_FS_Last_Error(void);

/** @} */ /* end_addtogroup qapi_fs */

#else   

  #error "No QAPI flags defined"

#endif


#endif /** QAPI_FS_H */



