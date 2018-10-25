#ifndef __QAPI_FTL_H
#define __QAPI_FTL_H

/**
 * @file qapi_ftl.h
 *
 * @brief QAPI FTL Functional Overview
 *
 * @addtogroup qapi_ftl
 * @{ 
 *
 * @details The FTL layer is a wrapper on top of the FLASH FTL layer. the FLASH
 *          FTL layer provides APIs for raw NAND read/write/erase access
 *          and is responsible for bad block management and logical to
 *          physical block conversation.
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
 * 2017-05-03   leo    (Tech Comm) Edited/added Doxygen comments and markup.
 * 2017-03-10   svl    Create.
 * 
 * ==========================================================================*/

#include <qapi_ftl_types.h>

/*=============================================================================
 * Data structure definitions
 ============================================================================*/

/** @addtogroup qapi_ftl
@{ */

/* Currently supported size of the FTL device name.
   This value should not be changed.
*/
#define QAPI_FTL_DEVICE_NAME_SIZE                (32)

/** Structure for storing information about a partition. */
typedef struct qapi_FTL_info
{
  uint8_t  device_name[QAPI_FTL_DEVICE_NAME_SIZE]; /**< Device name string. */
  uint32_t maker_id;                   /**< Manufacturer ID. */
  uint32_t device_id;                  /**< Device ID. */
  uint32_t lpa_count;                  /**< Number of LPAs in the device. */
  uint32_t lpa_size_in_kbytes;         /**< LPA size in kB. */
  uint32_t erase_block_count;          /**< Number of eraseable units in the partition. */
  uint32_t erase_block_size_in_kbytes; /**< Erase unit size in kB. */
}qapi_FTL_info_t;

/** Handle returned to the client. One
    handle is returned per partition. */
typedef void *qapi_FTL_client_t;

/* Driver ID defines */

/* ID to open a partition. */
#define TXM_QAPI_FTL_OPEN           TXM_QAPI_FTL_BASE + 0
/* ID to close a partition. */
#define TXM_QAPI_FTL_CLOSE          TXM_QAPI_FTL_BASE + 1
/* ID to get information about a partition. */
#define TXM_QAPI_FTL_GET_INFO       TXM_QAPI_FTL_BASE + 2
/* ID to read data in multiples of LPA in a partition. */
#define TXM_QAPI_FTL_READ_LPA       TXM_QAPI_FTL_BASE + 3
/* ID to write data in multiples of LPA in a partition. */
#define TXM_QAPI_FTL_WRITE_LPA      TXM_QAPI_FTL_BASE + 4
/* ID to erase blocks in a partition. */
#define TXM_QAPI_FTL_ERASE_BLOCK    TXM_QAPI_FTL_BASE + 5

/*=============================================================================
 * APIs
 ============================================================================*/

#ifdef  QAPI_TXM_MODULE

/* Refer "#elif defined QAPI_TXM_SOURCE_CODE" sections for comments */
#define qapi_FTL_Open(handle,part_name)     (qapi_Status_t)                   \
                                            _txm_module_system_call4          \
                                            ( TXM_QAPI_FTL_OPEN,              \
                                              (ULONG) handle,                 \
                                              (ULONG) part_name,              \
                                              0,0                             \
                                            )

/* Refer "#elif defined QAPI_TXM_SOURCE_CODE" sections for comments */
#define  qapi_FTL_Close(handle)             (qapi_Status_t)                   \
                                            _txm_module_system_call4          \
                                            ( TXM_QAPI_FTL_CLOSE,             \
                                              (ULONG) handle,                 \
                                              0,0,0                           \
                                            )

/* Refer "#elif defined QAPI_TXM_SOURCE_CODE" sections for comments */
#define  qapi_FTL_Get_info(handle,info)     (qapi_Status_t)                   \
                                            _txm_module_system_call4          \
                                            ( TXM_QAPI_FTL_GET_INFO,          \
                                              (ULONG)handle,                  \
                                              (ULONG)info,                    \
                                              0,0   \
                                            )

/* Refer "#elif defined QAPI_TXM_SOURCE_CODE" sections for comments */
#define  qapi_FTL_Read_lpa(handle,lpa,lpa_count,buffer)                       \
                                            (qapi_Status_t)                   \
                                            _txm_module_system_call4          \
                                            ( TXM_QAPI_FTL_READ_LPA,          \
                                              (ULONG) handle,                 \
                                              (ULONG) lpa,                    \
                                              (ULONG) lpa_count,              \
                                              (ULONG) buffer                 \
                                            )

/* Refer "#elif defined QAPI_TXM_SOURCE_CODE" sections for comments */
#define  qapi_FTL_Write_lpa(handle,lpa,lpa_count,buffer)                      \
                                            (qapi_Status_t)                   \
                                            _txm_module_system_call4          \
                                            ( TXM_QAPI_FTL_WRITE_LPA,         \
                                              (ULONG) handle,                 \
                                              (ULONG) lpa,                    \
                                              (ULONG) lpa_count,              \
                                              (ULONG) buffer                 \
                                            )

/* Refer "#elif defined QAPI_TXM_SOURCE_CODE" sections for comments */
#define  qapi_FTL_Erase_block(handle,erase_block,erase_block_count)           \
                                            (qapi_Status_t)                   \
                                            _txm_module_system_call4          \
                                            ( TXM_QAPI_FTL_ERASE_BLOCK,       \
                                              (ULONG) handle,                 \
                                              (ULONG) erase_block,            \
                                              (ULONG) erase_block_count,      \
                                              0                               \
                                            )

#elif defined QAPI_TXM_SOURCE_CODE

/**
 * @brief Opens an FTL.
 *
 * @details This is the first API a client must call before any other call to
 * this module is made.
 *
 * This API opens the requested partition and returns a handle to that partition.
 * This handle is a void pointer and does not expose any data in and of itself.
 * The handle is to be used with FTL APIs to perform other tasks, e.g., use
 * this handle with qapi_FTL_Get_info() to get FTL information in the format of
 * #qapi_FTL_info_t. As with read and write data functions, this handle must be
 * passed with the correct offset and size.
 *
 * @note1hang One handle is returned per partition.
 *
 * @param[in] part_name  Name of the partition the client wants to use.
 * @param[out] handle    Handle that is passed to the client for further use.
 *                       The client must pass the address of the pointer in
 *                       which this handle is to be stored. If the return
 *                       status is FLASH_FTL_OK, handle will contain the
 *                       handle to the partition, which is used for any read
 *                       or write operation on partition part_name.
 *
 * @return
 * - FLASH_FTL_INVALID_PARAM      -- handle or part_name is NULL, or part_name is invalid.
 * - FLASH_FTL_FAIL               -- An internal failure occured.
 * - FLASH_FTL_OUT_OF_GOOD_BLOCKS -- The partition is not usable.
 * - FLASH_FTL_OK                 -- Success.
 */
qapi_Status_t
  qapi_FTL_Open(  qapi_FTL_client_t *handle,
                  const uint8_t     *part_name);

/**
 * Closes a partition once the client is done with it.
 *
 * @param[in] handle  Handle of the partition to be closed.
 *
 * @return
 * - FLASH_FTL_INVALID_PARAM -- handle or part_name is NULL, or part_name is invalid.
 * - FLASH_FTL_FAIL          -- An internal failure occured.
 * - FLASH_FTL_OK            -- Success.
 */
qapi_Status_t
  qapi_FTL_Close(qapi_FTL_client_t *handle);


/**
 * Gets partition and client-specific information in a format specified
 * by #qapi_FTL_info_t, which can be used to get partition information,
 * such as size.
 *
 * @note1hang The total usable partition size in kB = lpa_size_in_kbytes*lpa_count.
 *
 * @param[in] handle  Handle returned from qapi_FTL_Open().
 * @param[out] info   Pointer to where the information is stored.
 *
 * @return
 * - FLASH_FTL_INVALID_PARAM -- handle or info is NULL.
 * - FLASH_FTL_OK            -- Success.
 */
qapi_Status_t
  qapi_FTL_Get_info(  qapi_FTL_client_t handle,
                      qapi_FTL_info_t   *info);

/**
 * Reads data in multiples of LPA(s)or pages.
 *
 * @param[in] handle  Handle returned from qapi_FTL_Open().
 * @param[in] lpa     Logical page address (or page number) from which the data
 *                    is to be read. The LPA is with respect to the start of
 *                    the partition.
 * @param[in] lpa_count  Number of LPAs or pages to read.
 * @param[out] buffer    Pointer to where the read data is stored.
 *
 * @return
 * - FLASH_FTL_INVALID_PARAM      -- handle or part_name is NULL.
 * - FLASH_FTL_FAIL               -- An internal failure occured.
 * - FLASH_FTL_OUT_OF_GOOD_BLOCKS -- The partition is not usable.
 * - FLASH_FTL_OK                 -- Success.
 */
qapi_Status_t
  qapi_FTL_Read_lpa(qapi_FTL_client_t handle,
                    uint32_t lpa,
                    uint32_t lpa_count,
                    uint8_t  *buffer);

/**
 * Writes data in multiples of LPA(s) or pages sequentially.
 *
 * The number of LPAs in a block = (erase_block_size_in_kbytes/lpa_size_in_kbytes).
 * Data can only be written in an erased block, so before writing 
 * in an LPA, the block to which it correspond should be erased by calling
 * qapi_FTL_Erase_block(). For example, if a block has four LPAs, the block is
 * not erased, and the user wants to write in LPA 0, the user must erase the
 * entire block first and then write. Because the entire block is erased, the
 * user does not need to erase before writing in lpa1-lpa3.
 *
 * @note1hang Only sequential writes are allowed.
 * If the user wants to write in lpa0 after writing in lpa1, the user must
 * erase the entire block. In this case, the data in the entire block is lost.
 * If user wants to write into a previously written LPA, the user must make a
 * back up of the entire block, erase it, and copy in the backed up data. This
 * is the user's responsibility. For example, if the user wants to write in lpa0
 * after writing in lpa3, the user must follow this sequence:
 * -# Back up the entire block (if required)
 * -# Erase the entire block using qapi_FTL_Erase_block()
 * -# Write into lpa0
 * -# Copy lpa1 to lpa3 if a backup was taken before
 *
 * FTL does not take ownership of a data loss in cases where a
 * sequential write is not followed.
 *
 * Ideally, the user should erase the whole partition first and
 * then start writing data sequentially.
 *
 * @param[in] handle  Handle returned from qapi_FTL_Open().
 * @param[in] lpa     Logical page address (or page number) where the data is
 *                    to be written. The LPA is with respect to the start of
 *                    the partition
 * @param[in] lpa_count  Number of LPAs or pages to write.
 * @param[in] buffer   Pointer to the buffer to which the data is to be written.
 *
 * @return
 * - FLASH_FTL_INVALID_PARAM      -- handle or part_name is NULL.
 * - FLASH_FTL_FAIL               -- An internal failure occured.
 * - FLASH_FTL_OUT_OF_GOOD_BLOCKS -- The partition is not usable.
 * - FLASH_FTL_OK                 -- Success.
 */
qapi_Status_t
  qapi_FTL_Write_lpa( qapi_FTL_client_t handle,
                      uint32_t lpa,
                      uint32_t lpa_count,
                      uint8_t  *buffer);

/**
 * Erases a block.
 *
 * The block size is defined by erase_block_size_in_kbytes. The
 * number of LPAs in a block = (erase_block_size_in_kbytes/lpa_size_in_kbytes).
 * Data can only be written in an erased block, so before writing 
 * in an LPA, the block to which it corresponds to must be erased with this API.
 *
 * @param[in] handle  Handle returned from qapi_FTL_Open().
 * @param[in] erase_block  Start erase block.
 * @param[in] erase_block_count  Number of blocks to be erased from Flash
 *                               starting at erase_block.
 *
 * @return
 * - FLASH_FTL_INVALID_PARAM      -- handle is NULL.
 * - FLASH_FTL_FAIL               -- An internal failure occured.
 * - FLASH_FTL_OUT_OF_GOOD_BLOCKS -- The partition is not usable.
 * - FLASH_FTL_OK                 -- Success.
 */
qapi_Status_t
  qapi_FTL_Erase_block( qapi_FTL_client_t handle,
                        uint32_t erase_block,
                        uint32_t erase_block_count);

#else   /* }{ */

  #error "No QAPI flags defined"

#endif  /* } */

/** @} */ /* end_addtogroup qapi_ftl */

#endif /* __QAPI_FTL_H */
