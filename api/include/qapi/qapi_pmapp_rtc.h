
#ifndef __QAPI_PMAPP_RTC_H__
#define __QAPI_PMAPP_RTC_H__

/*===========================================================================
              QAPI P M   R T C   A P P   H E A D E R   F I L E

===========================================================================*/
/**
 * @file qapi_pmapp_rtc.h
 *
 * @addtogroup qapi_pmapp_rtc
 * @{ 
 *
 * @brief 
 *
 * @details This module provides the definations to configure the real-time clock
   (RTC) alarm pheripheral in the power management IC (PMIC).  
 * 
 * @}
 *  
 */

/*===========================================================================
  Copyright (c) 2016 QUALCOMM Technologies, Inc.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 
============================================================================*/


/*=============================================================================
                            EDIT HISTORY FOR File

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header:

when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/29/17   kcs     Updated Enums for driver ID's.
03/14/17   kcs     created
=============================================================================*/

/* =========================================================================
                         INCLUDE FILES
========================================================================= */
#ifdef __cplusplus
extern "C" {
#endif


#include "qapi_types.h"
#include "qapi_status.h"
#include "qapi_txm_base.h"

#define TXM_QAPI_PM_RTC_BASE   TXM_QAPI_PMIC_BASE

/* =========================================================================
                       USER_Mode_DEFS
========================================================================= */

// Driver ID defines
#define  TXM_QAPI_PMIC_RTC_INIT           	     TXM_QAPI_PM_RTC_BASE + 1
#define  TXM_QAPI_PMIC_SET_RTC_DISPLAY_MODE      TXM_QAPI_PM_RTC_BASE + 2
#define  TXM_QAPI_PMIC_RTC_READ_CMD              TXM_QAPI_PM_RTC_BASE + 3
#define  TXM_QAPI_PMIC_RTC_ALARM_RW_CMD          TXM_QAPI_PM_RTC_BASE + 4

/* =========================================================================
                         TYPE DEFINITIONS
========================================================================= */

/** @addtogroup qapi_pmapp_rtc
@{ */

/** Real-time clock command type.
*/
typedef enum
{
   QAPI_PM_RTC_SET_CMD_E,  /**< Set command. */
   QAPI_PM_RTC_GET_CMD_E,  /**< Get command. */
   QAPI_PM_RTC_INVALID_CMD_E
}qapi_PM_Rtc_Cmd_Type_t;

/** Real-time clock display mode type.
*/
typedef enum
{
   QAPI_PM_RTC_12HR_MODE_E,  /**< 12 hour display mode. */
   QAPI_PM_RTC_24HR_MODE_E,  /**< 24 hour display mode. */
   QAPI_PM_RTC_INVALID_MODE_E
}qapi_PM_Rtc_Display_Type_t;

/** PMIC's version of the Julian time structure.
*/
typedef struct qapi_PM_Rtc_Julian_Type_s
{
   uint64_t year;            /**< Year [1980 to 2100]. */
   uint64_t month;           /**< Month of the year [1 to 12]. */
   uint64_t day;             /**< Day of the month [1 to 31]. */
   uint64_t hour;            /**< Hour of the day [0 to 23]. */
   uint64_t minute;          /**< Minute of the hour [0 to 59]. */
   uint64_t second;          /**< Second of the minute [0 to 59]. */
   uint64_t day_of_week;     /**< Day of the week [0 to 6]; Monday through Sunday. */
} qapi_PM_Rtc_Julian_Type_t;

/** RTC alarms. */
typedef enum
{
   QAPI_PM_RTC_ALARM_1_E       = 0x01,  /**< Alarm 1. */
   QAPI_PM_RTC_ALL_ALARMS_E    = 0x01,  /**< Refers collectively to all supported alarms. */
   QAPI_PM_RTC_ALARM_INVALID_E
} qapi_PM_Rtc_Alarm_Type_t;

/** @} */ /* end_addtogroup qapi_pmapp_rtc */

#ifdef  QAPI_TXM_MODULE

// API Definitions 
#define qapi_PM_Rtc_Init()\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_PMIC_RTC_INIT,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0,\
    (ULONG) 0,(ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, \
    (ULONG) 0))

#define qapi_PM_Set_Rtc_Display_Mode(mode)\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_PMIC_SET_RTC_DISPLAY_MODE,\
    (ULONG) mode, (ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#define qapi_PM_Rtc_Read_Cmd(qapi_current_time_ptr)\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_PMIC_RTC_READ_CMD,\
    (ULONG) qapi_current_time_ptr, (ULONG) 0, (ULONG) 0, (ULONG) 0,(ULONG) 0, (ULONG) 0,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#define qapi_PM_Rtc_Alarm_RW_Cmd(cmd,what_alarm,qapi_alarm_time_ptr)\
    ((qapi_Status_t) (_txm_module_system_call12)(TXM_QAPI_PMIC_RTC_ALARM_RW_CMD,\
    (ULONG) cmd, (ULONG) what_alarm, (ULONG) qapi_alarm_time_ptr, (ULONG) 0,(ULONG) 0, (ULONG) 0,\
    (ULONG) 0,(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
	
#elif defined QAPI_TXM_SOURCE_CODE
	

/*===========================================================================
                   KERNEL_Mode_DEFS
===========================================================================*/

/** @addtogroup qapi_pmapp_rtc
@{ */

/*===========================================================================
FUNCTION   qapi_PM_Rtc_Init                                 
===========================================================================*/
/**

  Initializes the RTC after a power reset.

@return
   Possible values (see @xhyperref{hdr:QAPIStatust,qapi\_Status\_t}):
   - QAPI_OK                  -- Operation succeeded.
   - QAPI_ERR_NOT_SUPPORTED   -- Feature is not supported.
   - QAPI_ERROR               -- Any other errors.
*/
qapi_Status_t
qapi_PM_Rtc_Init(void);
/*~ FUNCTION qapi_PM_Rtc_Init */

/*===========================================================================
FUNCTION   qapi_PM_Set_Rtc_Display_Mode                       
===========================================================================*/
/**

   Configures the real time clock display mode (24 or 12 hour mode).
   The RTC defaults to 24 hr mode on phone power up and
   remains so until it is set to 12 hr mode explicitly using
   qapi_PM_Set_Rtc_Display_Mode().

@param[in] mode  New RTC time display mode to be used. \n
                 Valid values (see #qapi_PM_Rtc_Display_Type_t):
                 - QAPI_PM_RTC_12HR_MODE_E
                 - QAPI_PM_RTC_24HR_MODE_E @tablebulletend

@return
   Possible values (see @xhyperref{hdr:QAPIStatust,qapi\_Status\_t}):
   - QAPI_OK                   -- Operation succeeded.
   - QAPI_ERR_INVALID_PARAM    -- Invalid parameter.
   - QAPI_ERR_NOT_SUPPORTED    -- Feature is not spported.
   - QAPI_ERROR                -- Any other errors.
*/
qapi_Status_t
qapi_PM_Set_Rtc_Display_Mode(qapi_PM_Rtc_Display_Type_t mode);
/*~ FUNCTION qpai_PM_Set_Rtc_Display_Mode */


/*===========================================================================
FUNCTION   qapi_PM_Rtc_Read_Cmd    // confirm about RW                               
===========================================================================*/

/**
   Reads/writes the time and date from/to the PMIC RTC.
   The time/date format must be in 24 or 12 Hr mode depending on
   in which mode the RTC was initialized. See the description of
   qpai_PM_Set_Rtc_Display_Mode() for details.

   24 hr and 12 hr mode displays are:

   24 HR -- 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 \n
   12 HR -- 12 01 02 03 04 05 06 07 08 09 10 11 32 21 22 23 24 25 26 27 28 29 30 31


@param[in] qapi_current_time_ptr  Depending on the command, this function will use the
        #qapi_PM_Rtc_Julian_Type_t pointer to update or return the current time in the RTC.
         @note day_of_week is not required for setting the current time, but it
               returns the correct information when retrieving time from the RTC.

@return
   Possible values (see @xhyperref{hdr:QAPIStatust,qapi\_Status\_t}):
   - QAPI_OK                 -- Operation succeeded.
   - QAPI_ERR_INVALID_PARAM  -- Invalid parameter.
   - QAPI_ERROR              -- Any other errors.
     
*/
qapi_Status_t
qapi_PM_Rtc_Read_Cmd(qapi_PM_Rtc_Julian_Type_t   *qapi_current_time_ptr);
/*~ FUNCTION qapi_PM_Rtc_Read_Cmd */
/*~ PARAM INOUT qapi_current_time_ptr POINTER */


/*===========================================================================
FUNCTION   qapi_PM_Rtc_Alarm_RW_Cmd                             
==========================================================================*/

/**
   Reads/writes the time and date from/to the PMIC RTC.
   The time/date format must be in 24 or 12 Hr mode depending on
   in which mode the RTC was initialized. See the description of
   qpai_PM_Set_Rtc_Display_Mode() for details.

   24 hr and 12 hr mode displays are:

   24 HR -- 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 \n
   12 HR -- 12 01 02 03 04 05 06 07 08 09 10 11 32 21 22 23 24 25 26 27 28 29 30 31


@param[in] cmd  Indicates whether to set or get the current time in the RTC. \n
        Valid values (see qapi_PM_Rtc_Cmd_Type_t):
        - QAPI_PM_RTC_SET_CMD_E
        - QAPI_PM_RTC_GET_CMD_E @tablebulletend
@param[in] what_alarm  Alarm type. See #qapi_PM_Rtc_Alarm_Type_t.
@param[in] qapi_alarm_time_ptr  Depending on the command, this function will use the structure
           #qapi_PM_Rtc_Julian_Type_t pointer to update or return the alaram time in the RTC.
           @note day_of_week is not required for setting the current time, but it
               returns the correct information when retrieving time from the RTC.

@return
   Possible values (see @xhyperref{hdr:QAPIStatust,qapi\_Status\_t}):
   - QAPI_OK                 -- Operation succeeded.
   - QAPI_ERR_INVALID_PARAM  -- Invalid parameter.
   - QAPI_ERROR              -- Any other errors.
*/
qapi_Status_t qapi_PM_Rtc_Alarm_RW_Cmd(
   qapi_PM_Rtc_Cmd_Type_t       cmd,
   qapi_PM_Rtc_Alarm_Type_t     what_alarm,
   qapi_PM_Rtc_Julian_Type_t   *qapi_alarm_time_ptr);
/*~ FUNCTION qapi_PM_Rtc_Alarm_RW_Cmd */
/*~ PARAM INOUT qapi_alarm_time_ptr POINTER */

#else   // DEF_END

#error "No QAPI flags defined"

#endif
#ifdef __cplusplus
} /* closing brace for extern "C" */

#endif

/** @} */ /* end_addtogroup qapi_pmapp_rtc */

#endif /* __QAPI_PMAPP_RTC_H__  */
