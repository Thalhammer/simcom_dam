#include "txm_module.h"

extern TXM_MODULE_THREAD_ENTRY_INFO* _txm_module_entry_info;

void _txm_module_callback_request_thread_entry(ULONG id) {
	// parameter seems to be unused in original code ?
	// r0 is overwritten right after entry
	// but it is in the prototype, so we include it here
	(void)id;

	TXM_MODULE_CALLBACK_NOTIFY notify;
	int ret;
	TX_QUEUE* req_queue = _txm_module_entry_info->txm_module_thread_entry_info_callback_request_queue;
	TX_QUEUE* resp_queue = _txm_module_entry_info->txm_module_thread_entry_info_callback_response_queue;

	do {
		// Receive notify
		ret = tx_queue_receive(req_queue, &notify, TX_NO_WAIT);
		if(ret != TX_SUCCESS) break;
		switch(notify.txm_module_callback_notify_type) {
			case 0:
			case 1:
			case 2:
			case 3:
				((void(*)(ULONG))notify.txm_module_callback_notify_application_function)(notify.txm_module_callback_notify_param_1);
				break;
			case 4:
				((void(*)(ULONG,ULONG))notify.txm_module_callback_notify_application_function)
					(notify.txm_module_callback_notify_param_1, notify.txm_module_callback_notify_param_2);
				break;
			default:
				break;
		}
		// Send back unmodified notify. Maybe for acknowledge ?
		ret = tx_queue_send(resp_queue, &notify, TX_NO_WAIT);
	} while(ret == TX_SUCCESS);
}
