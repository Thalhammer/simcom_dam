#ifndef __QAPI_TIMER_H__
#define __QAPI_TIMER_H__

/**=================================================================================
 *
 *                       TIMER SERVICES
 *
 *==================================================================================
 *
 * @file qapi_timer.h
 *
 * @addtogroup qapi_timer
 * @{
 *
 * @brief Timer Services 
 *
 * @details This interface implements Advanced Time Services (ATS) timer services. 
            This timer service is different than RTOS timer service. 
            This timer service will be available in SOM mode.
 * 
 * 
 * @note    These routines are FULLY re-entrant.  In order to prevent memory leaks,
            whenever timer usage is done, timer should be undefined using 
            qapi_Timer_Undef API. Timer callbacks should do minimal processing. 
            Time callbacks implementation should not contain any mutex or RPC.
 *          
 *
 * @code {.c}
 *
 *    /\*
 *    * Code snippet below demonstrates usage of timer interface. In the example
 *    * below a client defines a timer, sets a timer, stops the timer and undefines
        a timer.
 *    * For Brevity, the sequence assumes that all calls succeed. 
 *    *\/
 * 
 *    qapi_TIMER_handle_t timer_handle;	  
 *    
      qapi_TIMER_def_attr_t timer_def_attr; 
      timer_def_attr.cb_type = TIMER_FUNC1_CB_TYPE; //notification type
      timer_def_attr.sigs_func_ptr = &timer_test_cb; //callback to call when timer expires
      timer_def_attr.sigs_mask_data = 0x1; //this data will be returned in the callback
      timer_def_attr.deferrable = false; //set to true for non-deferrable timer
 *    
      //define the timer. Note: This call allocates memory and hence qapi_Timer_Undef()
      //should be called whenever the timer usage is done.
      qapi_Timer_def( &timer_handle, &timer_def_attr);

      qapi_TIMER_set_attr_t timer_set_attr; 
      timer_set_attr.reload = FALSE; //Do not restart timer after it expires
      timer_set_attr.time = time_duration; 
      timer_set_attr.unit = T_MSEC; 
 *    
      //set or start the timer
      qapi_Timer_set( timer_handle, &timer_set_attr);

      //stop a running timer
      qapi_Timer_stop( timer_handle);

      //Undef the timer. Releases memory allocated in qapi_Timer_Def()
      qapi_Timer_undef( timer_handle);
 
 *
 * @endcode
 *
 *  @}
*/

/*==================================================================================
       Copyright (c) 2016 QUALCOMM Technologies Incorporated.
                       All Rights Reserved.
                QUALCOMM Proprietary and Confidential.
==================================================================================*/

/* $Header: //components/rel/core.tx/1.0.c3/api/services/qapi_timer.h#2 $ */

/*==========================================================================
when       who     what, where, why
--------   ---    ---------------------------------------------------------- 
05/01/16   gp     Created
===========================================================================*/


/*==================================================================================

                               TYPE DEFINITIONS

==================================================================================*/
#include "qapi_status.h"
#include "qapi_timer_id.h"

/** @addtogroup qapi_timer
@{ */
/**
* Timer Notification Type.
*
* This enumeration lists the notifications available on timer 
* expiry. 
*/
typedef enum {
  QAPI_TIMER_NO_NOTIFY_TYPE,          /**< No notification. */  
  QAPI_TIMER_NATIVE_OS_SIGNAL_TYPE,   /**< Signal an object. */    
  QAPI_TIMER_FUNC1_CB_TYPE,           /**< Call back a function. */    
  QAPI_TIMER_INVALID_NOTIFY_TYPE    
} qapi_TIMER_notify_t;

/** @addtogroup qapi_timer
@{ */
/**
* Timer Unit Type.
*
* This enumeration lists the units in which timer duration can 
* be specified. 
*/
typedef enum {
  QAPI_TIMER_UNIT_TICK,     /**< Return time in Ticks. */
  QAPI_TIMER_UNIT_USEC,     /**< Return time in Microseconds. */
  QAPI_TIMER_UNIT_MSEC,     /**< Return time in Milliseconds. */
  QAPI_TIMER_UNIT_SEC,      /**< Return time in Seconds. */
  QAPI_TIMER_UNIT_MIN,      /**< Return time in Minutes. */
  QAPI_TIMER_UNIT_HOUR,     /**< Return time in Hours. */
  QAPI_TIMER_UNIT_MAX
}qapi_TIMER_unit_type;

/** @addtogroup qapi_timer
@{ */
/**
* Timer Info Type.
*
* This enumeration lists the type of information that can be 
* obtained for a timer. 
*/
typedef enum{
  QAPI_TIMER_TIMER_INFO_ABS_EXPIRY = 0, /**< Return the timetick of timer expiry in native ticks. */
  QAPI_TIMER_TIMER_INFO_TIMER_DURATION, /**< Return the total duration of the timer in asked unit. */
  QAPI_TIMER_TIMER_INFO_TIMER_REMAINING, /**< Returns the remaining duration of the timer in asked unit. */
  QAPI_TIMER_TIMER_INFO_MAX, 
}qapi_TIMER_info_type;


/** @addtogroup qapi_timer
@{ */
/**
* Timer Define Attribute Type.
*
* This type is used to specify parameters when defining a timer. 
* @verbatim 
* sigs_func_ptr will depend on the value of qapi_TIMER_notify_t.
* qapi_TIMER_notify_t == QAPI_TIMER_NO_NOTIFY_TYPE, 
* sigs_func_ptr = Don't care 
*  
* qapi_TIMER_notify_t == QAPI_TIMER_NATIVE_OS_SIGNAL_TYPE, 
* sigs_func_ptr = qurt signal object 
*  
* qapi_TIMER_notify_t == QAPI_TIMER_FUNC1_CB_TYPE, 
* sigs_func_ptr == specify a callback of type qapi_TIMER_cb_t
* @endverbatim
*/
typedef struct
{
  qbool_t                   deferrable; /**< FALSE = deferrable. */  
  qapi_TIMER_notify_t       cb_type;    /**< Type of notification desired. */  
  void*                     sigs_func_ptr; /**< Specify the signal object or callback function.  */  
  uint32_t                  sigs_mask_data; /**< specify signal mask or callback data. */  
}qapi_TIMER_define_attr_t;

/** @addtogroup qapi_timer
@{ */
/**
* Timer Set Attribute Type.
*
* This type is used to specify parameters when starting a timer.
*/
typedef struct
{
  uint64_t              time;   /**< Timer duration. */  
  uint64_t              reload; /**< Reload duration. */
  qapi_TIMER_unit_type  unit;   /**< Specify units for timer duration. */  
}qapi_TIMER_set_attr_t;

/** @addtogroup qapi_timer
@{ */
/**
* Timer Info Attribute Type.
*
* This is used to get information for a given timer.
*/
typedef struct
{
  qapi_TIMER_info_type   timer_info;   /**< Timer Info Type. */
  qapi_TIMER_unit_type   unit;   /**< Specify units to use for return. */
}qapi_TIMER_get_info_attr_t;


/** @addtogroup qapi_timer
@{ */
/**
* Timer handle.
*
* Handle provided by the timer module to the client. Clients 
* must pass this handle as a token with subsequent timer calls. 
* Note that the clients should cache the handle. Once lost, it 
* cannot be queried back from the module. 
*/

typedef void* qapi_TIMER_handle_t;


/** @addtogroup qapi_timer
@{ */
/**
* Timer callback type.
*
* Timer callbacks should adhere to this signature.
*/
typedef void (*qapi_TIMER_cb_t)(uint32_t data);


/** @addtogroup qapi_timer
@{ */
/**
* Time type.
*
* Native timestamp type.
*/
typedef unsigned long qapi_qword[ 2 ];
typedef qapi_qword qapi_time_type;



/** @addtogroup qapi_timer
@{ */
/**
* Time Julian Type.
*
* Time julian type definition.
*/
typedef struct
{
  uint16_t year; /**< Year [1980 through 2100]. */
  uint16_t month; /**< Month of year [1 through 12]. */
  uint16_t day; /**< Day of month [1 through 31]. */
  uint16_t hour; /**< Hour of day [0 through 23]. */
  uint16_t minute; /**< Minute of hour [0 through 59]. */
  uint16_t second; /**< Second of minute [0 through 59]. */
  uint16_t day_of_week; /**< Day of the week [0 through 6] or [Monday through 
                           Sunday]. */
}
qapi_time_julian_type;


/** @addtogroup qapi_timer
@{ */
/**
* Time unit type.
*
* Enumeration of the types of time that can be
* obtained from time get QAPI.
*/
typedef enum
{
  QAPI_TIME_STAMP = 0x10, /**< Return the time in timestamp format. */
  QAPI_TIME_MSECS, /**< Return the time in millisecond format. */
  QAPI_TIME_SECS, /**< Return the time in second format. */
  QAPI_TIME_JULIAN, /**< Return the time in julian calendar format. */
}qapi_time_unit_type;


/** @addtogroup qapi_timer
@{ */
/**
* Time Get attribute type.
*
* Used to specify parameters when getting time. 
* @verbatim 
* Pointers will depend on the value of qapi_time_unit_type.
* qapi_time_unit_type == QAPI_TIME_STAMP, 
* time_ts = Of type qapi_time_type
*  
* qapi_time_unit_type == QAPI_TIME_MSECS, 
* time_msecs = Of type unint64_t
*
* qapi_time_unit_type == QAPI_TIME_SECS, 
* time_secs = Of type unint64_t
*
* qapi_time_unit_type == QAPI_TIME_JULIAN, 
* time_julian = Of type qapi_time_julian_type
* @endverbatim
*/
typedef union
{
  qapi_time_type time_ts; /**< Specify the qapi_time_type variable pointer. */
  uint64_t time_msecs; /**< Variable for getting time in msec. */
  uint64_t time_secs; /**< Variable for getting time in sec. */
  qapi_time_julian_type time_julian; /**< Variable for getting time in Julian. */
}qapi_time_get_t;


/**
* @brief  
* Gets the time in the specified format. 
*
* @param[in] time_get_unit  Unit in which to get the time. 
* @param[in] time           Pointer to qapi_time_get_t variable. 

  @return
  QAPI_OK on success, an error code on failure.
*
* @dependencies
* none
*/
qapi_Status_t qapi_time_get(
   qapi_time_unit_type    time_get_unit,
   qapi_time_get_t* time
);


/**
  @brief  
* Allocates internal memory in the timer module. The internal 
* memory is then formatted with parameters provided in 
* timer_def_attr variable. The timer_handle is returned to the 
* client and this handle should be used for any subsequent timer 
* operations. 
  
* @param[in] timer_handle  Handle to the timer. 
* @param[in] timer_attr    Attributes for defining timer. 
  
  @return
  Returns QAPI_OK on success and an error code on failure
  
  @dependencies
* None. 
*  
* @sideeffects Calling this API will cause memory allocation. 
*              Therefore, whenever the timer usage is done and
*              not required, qapi_Timer_Undef shoule be called
*              to release the memory otherwise it will cause a
*              memory leak.
*/
qapi_Status_t qapi_Timer_Def(
   qapi_TIMER_handle_t*    timer_handle,
   qapi_TIMER_define_attr_t*  timer_attr  
);


/**
  @brief  
* Starts the timer with the duration specified in timer_attr. 
* If the timer is specified as a reload timer in timer_attr, 
* then the timer will restart after its expiry 
  
* @param[in] timer_handle  Handle to the timer. 
* @param[in] timer_attr    Attributes for setting timer. 
  
  @return
  Returns QAPI_OK on success and an error code on failure
  
  @dependencies
* qapi_Timer_Def API should be called for the timer before 
* calling qapi_Timer_Set function.
*/
qapi_Status_t qapi_Timer_Set(
   qapi_TIMER_handle_t    timer_handle,
   qapi_TIMER_set_attr_t* timer_attr  
);

/**
  @brief  
* Gets the specified information about the timer.
  
* @param[in] timer_handle  Handle to the timer. 
* @param[out] timer_info    Specify the type of information 
*       needed from the timer.
  
  @return
  Returns QAPI_OK on success and an error code is returned on failure
* 
*/
qapi_Status_t qapi_Timer_Get_Timer_Info(
   qapi_TIMER_handle_t         timer_handle,
   qapi_TIMER_get_info_attr_t* timer_info,
   uint64_t*                   data
);

/**
  @brief  
* Timed wait. Blocks a thread for specified time. 
  
* @param[in] timeout Specify the duration to block the thread 
* @param[in] unit    Specify the unit of duration 
* @param[in] non-deferrable  TRUE = processor (if in deep 
*       sleep or power collapse) will be awakened on timeout. \n
*       FALSE = processor will not awakened from deep sleep
*       or power collapse on timeout. \n Whenever the processor
*       wakes up due to some other reason after timeout, the
*       thread will be unblocked.
  
  @return
  Returns QAPI_OK on success and an error code on failure
* 
*/
qapi_Status_t qapi_Timer_Sleep(
  uint64_t             timeout,
  qapi_TIMER_unit_type unit,
  qbool_t              non_deferrable
);

/**
  @brief  
* Undefines the timer. This API needs to be called whenever 
* timer usage is done. Calling this API will release the 
* internal timer  memory that was allocated when the timer was 
* defined. 
  
* @param[in] handle Timer handle to undefine the timer.
  
  @return
  Returns QAPI_OK on success and an error code on failure
* 
*/
qapi_Status_t qapi_Timer_Undef(
    qapi_TIMER_handle_t    timer_handle
);

/**
  @brief  
* Stops the timer.
* @note This function does NOT deallocate the 
* memory that was allocated when timer was defined.  
  
* @param[in] handle Timer handle to stop the timer.
  
  @return
  Returns QAPI_OK on success and an error code on failure
* 
*/
qapi_Status_t qapi_Timer_Stop(
    qapi_TIMER_handle_t    timer_handle
);

/**
  @brief  
* Sets the timer with expiry specified in absolute ticks. 
  
* @param[in] handle Timer handle. 
* @param[in] abs_time Timetick when the timer expires. 
  
  @return
  Returns QAPI_OK on success and an error code on failure
* 
*/
qapi_Status_t qapi_Timer_set_absolute(
  qapi_TIMER_handle_t      timer,
  uint64_t                 abs_time
);

/*@}*/ /* group timer */

#endif /*__QAPI_TIMER_H__ */
