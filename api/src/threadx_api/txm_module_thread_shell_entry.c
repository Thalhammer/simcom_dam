#include "txm_module.h"

ULONG (*_txm_module_kernel_call_dispatcher)(ULONG type, ULONG param_1, ULONG param_2, ULONG param3);
TXM_MODULE_INSTANCE *_txm_module_entry_info;
TXM_MODULE_THREAD_ENTRY_INFO *_txm_module_instance_ptr;

VOID  _txm_module_thread_shell_entry(TX_THREAD *thread_ptr, TXM_MODULE_THREAD_ENTRY_INFO *thread_info) {
	if(thread_info->txm_module_thread_entry_info_start_thread) {
		_txm_module_entry_info = thread_info->txm_module_thread_entry_info_module;
		_txm_module_instance_ptr = thread_info;
		_txm_module_kernel_call_dispatcher = thread_info->txm_module_thread_entry_info_kernel_call_dispatcher;
		// This is an endless loop if the dispatcher is null, maybe this is a bug in the original.
		// There might have been something inside the loop that got removed by the compiler or so,
		// But this represents the behaviour of the original, so we leave it here.
		// Relevant asm:
		//      0x0800005c      ldr  ip, [r4, 0x2c] ; load kernel call dispatcher
		// .--> 0x08000064      cmp  ip, 0 ; endless loop if it is zero ? This might be intentional or a bug, I don't know
		// `==< 0x08000068      beq  0x8000064
		while(_txm_module_kernel_call_dispatcher == NULL);
		tx_thread_resume(thread_info->txm_module_thread_entry_info_callback_request_thread);
	}
	thread_info->txm_module_thread_entry_info_entry(thread_info->txm_module_thread_entry_info_parameter);
	txm_module_thread_system_suspend(thread_ptr);
}
