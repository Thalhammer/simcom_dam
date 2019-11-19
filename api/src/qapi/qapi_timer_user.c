#include "qapi_timer.h"

#ifndef SLEEP_WORKAROUND
#define SLEEP_WORKAROUND 1
#endif

qapi_Status_t qapi_time_get(qapi_time_unit_type time_get_unit, qapi_time_get_t* time) {
	return (qapi_Status_t)_txm_module_system_call12(TXM_QAPI_TIME_GET, (ULONG)time_get_unit, (ULONG)time, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

qapi_Status_t qapi_Timer_Set(qapi_TIMER_handle_t timer_handle, qapi_TIMER_set_attr_t* timer_attr) {
	return (qapi_Status_t)_txm_module_system_call12(TXM_QAPI_TIMER_SET, (ULONG)timer_handle, (ULONG)timer_attr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

qapi_Status_t qapi_Timer_Get_Timer_Info(qapi_TIMER_handle_t timer_handle, qapi_TIMER_get_info_attr_t* timer_info, uint64_t* data) {
	return (qapi_Status_t)_txm_module_system_call12(TXM_QAPI_TIMER_GET_INFO, (ULONG)timer_handle, (ULONG)timer_info, (ULONG)data, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

#if SLEEP_WORKAROUND
static void _timer_set_evt(void* evt) {
	tx_event_flags_set((TX_EVENT_FLAGS_GROUP*)evt, 0x1, TX_OR);
}

static qapi_Status_t _sleep_timer(uint64_t timeout, qapi_TIMER_unit_type unit) {
	TX_EVENT_FLAGS_GROUP evt_flags;
	qapi_TIMER_handle_t timer_handle;
	qapi_TIMER_define_attr_t timer_def_attr;
	timer_def_attr.cb_type = QAPI_TIMER_FUNC1_CB_TYPE;
	timer_def_attr.sigs_func_ptr = (void*)&_timer_set_evt;
	timer_def_attr.sigs_mask_data = (uint32_t)&evt_flags;
	timer_def_attr.deferrable = false;

	int res = qapi_Timer_Def(&timer_handle, &timer_def_attr);
	if(res != 0) return QAPI_ERR_NO_MEMORY;

	res = tx_event_flags_create(&evt_flags, "timer_wait");
	if(res != 0) {
		qapi_Timer_Undef(timer_handle);
		return QAPI_ERR_NO_MEMORY;
	}

	qapi_TIMER_set_attr_t timer_set_attr; 
	timer_set_attr.reload = 0;
	timer_set_attr.time = timeout;
	timer_set_attr.unit = unit; 

	res = qapi_Timer_Set(timer_handle, &timer_set_attr);
	if(res != 0) {
		qapi_Timer_Undef(timer_handle);
		tx_event_flags_delete(&evt_flags);
		return QAPI_ERR_NO_MEMORY;
	}

	ULONG flags;
	res = tx_event_flags_get(&evt_flags, 0x1, TX_AND_CLEAR, &flags, TX_WAIT_FOREVER);
	if(res != 0) {
		qapi_Timer_Stop(timer_handle);
		qapi_Timer_Undef(timer_handle);
		tx_event_flags_delete(&evt_flags);
		return QAPI_ERR_NO_MEMORY;
	}

	qapi_Timer_Stop(timer_handle);
	qapi_Timer_Undef(timer_handle);
	tx_event_flags_delete(&evt_flags);
	return QAPI_OK;
}

qapi_Status_t qapi_Timer_Sleep(uint64_t timeout, qapi_TIMER_unit_type unit, qbool_t non_deferrable) {
	switch(unit) {
	case QAPI_TIMER_UNIT_TICK:
		return (qapi_Status_t)_txm_module_system_call12(TXM_QAPI_TIMER_SLEEP, (ULONG)unit, (ULONG)timeout, (ULONG)non_deferrable, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	case QAPI_TIMER_UNIT_USEC:
		return QAPI_ERR_NOT_SUPPORTED;
	case QAPI_TIMER_UNIT_MSEC:
		if(timeout < 10) return QAPI_ERR_NOT_SUPPORTED;
		__attribute__((fallthrough));
	case QAPI_TIMER_UNIT_SEC:
		__attribute__((fallthrough));
	case QAPI_TIMER_UNIT_MIN:
		__attribute__((fallthrough));
	case QAPI_TIMER_UNIT_HOUR:
		return _sleep_timer(timeout, unit);
	default:
		return QAPI_ERR_INVALID_PARAM;
	}
}

#else
qapi_Status_t qapi_Timer_Sleep(uint64_t timeout, qapi_TIMER_unit_type unit, qbool_t non_deferrable) {
	return (qapi_Status_t)_txm_module_system_call12(TXM_QAPI_TIMER_SLEEP, (ULONG)unit, (ULONG)timeout, (ULONG)non_deferrable, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
#endif

qapi_Status_t qapi_Timer_Stop(qapi_TIMER_handle_t timer_handle) {
	return (qapi_Status_t)_txm_module_system_call12(TXM_QAPI_TIMER_STOP, (ULONG)timer_handle, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

qapi_Status_t qapi_Timer_set_absolute(qapi_TIMER_handle_t timer, uint64_t abs_time) {
	return (qapi_Status_t)_txm_module_system_call12(TXM_QAPI_TIMER_SET_ABS, (ULONG)timer, 0, abs_time, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

qapi_Status_t qapi_Timer_Undef(qapi_TIMER_handle_t timer_handle) {
	qapi_Status_t res = _txm_module_system_call12(TXM_QAPI_TIMER_UNDEF, (ULONG)timer_handle, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	if(res == QAPI_OK) {
		txm_module_object_deallocate(timer_handle);
	}
	return res;
}

qapi_Status_t qapi_Timer_Def(qapi_TIMER_handle_t* timer_handle, qapi_TIMER_define_attr_t* timer_attr) {
	if(timer_handle == NULL) return QAPI_ERR_INVALID_PARAM;
	int handle_size; // this value was cached in the original however this caused problems with gcc so we get it everytime.
	_txm_module_system_call12(TXM_QAPI_TIMER_GET_TIMER_TYPE_SIZE, (ULONG)&handle_size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	if(handle_size == 0) return QAPI_ERR_TIMEOUT;
	if(txm_module_object_allocate(timer_handle, handle_size) != 0 || *timer_handle == NULL) return QAPI_ERR_NO_MEMORY;
	qapi_Status_t res = _txm_module_system_call12(TXM_QAPI_TIMER_DEF, (ULONG)timer_handle, (ULONG)timer_attr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	if(res != QAPI_OK) {
		// Is this correct ?
		// Seems to be...
		txm_module_object_deallocate(timer_handle);
	}
	return res;
}
