#include "qapi_timer.h"

qapi_Status_t qapi_time_get(qapi_time_unit_type time_get_unit, qapi_time_get_t* time) {
	return (qapi_Status_t)_txm_module_system_call12(TXM_QAPI_TIME_GET, (ULONG)time_get_unit, (ULONG)time, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

qapi_Status_t qapi_Timer_Set(qapi_TIMER_handle_t timer_handle, qapi_TIMER_set_attr_t* timer_attr) {
	return (qapi_Status_t)_txm_module_system_call12(TXM_QAPI_TIMER_SET, (ULONG)timer_handle, (ULONG)timer_attr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

qapi_Status_t qapi_Timer_Get_Timer_Info(qapi_TIMER_handle_t timer_handle, qapi_TIMER_get_info_attr_t* timer_info, uint64_t* data) {
	return (qapi_Status_t)_txm_module_system_call12(TXM_QAPI_TIMER_GET_INFO, (ULONG)timer_handle, (ULONG)timer_info, (ULONG)data, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

qapi_Status_t qapi_Timer_Sleep(uint64_t timeout, qapi_TIMER_unit_type unit, qbool_t non_deferrable) {
	return (qapi_Status_t)_txm_module_system_call12(TXM_QAPI_TIMER_SLEEP, (ULONG)unit, (ULONG)timeout, (ULONG)non_deferrable, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

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