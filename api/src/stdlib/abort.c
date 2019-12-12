#include "util/trace.h"
#include "threadx_api/txm_module.h"
#include <stdint.h>

#define TRACE_TAG "abort"

void backtrace() {
	if(_txm_module_kernel_call_dispatcher == NULL) return;
 
	uint32_t* fp = 0;
	asm volatile("mov %0, fp":"=r"(fp));
	uint32_t lr = 0;
	asm volatile("mov %0, lr":"=r"(lr));

	TX_THREAD *cthread = tx_thread_identify();
	char* name = NULL;
	if(cthread == NULL || tx_thread_info_get(cthread, &name, NULL, NULL, NULL, NULL, NULL, NULL, NULL) != TX_SUCCESS)
		TRACE("failed to get thread name\r\n");
	else TRACE("backtrace of thread %x %s\r\n", cthread, name);
	
	TRACE("fp=%x lr=%x\r\n", fp, lr);
	if(fp == NULL || fp[0] != lr) {
		TRACE("fp does not match link register, compile with frame pointer enabled!\r\n");
		return;
	}

	int i=0;
	uint32_t pc = 0;
	asm volatile("mov %0, pc":"=r"(pc));
	TRACE("[%d] %x\r\n", i++, pc);
	while(fp != NULL && fp[0] > 0x42000000 && fp[0] < 0x42300000) {
		TRACE("[%d] %x\r\n", i++, fp[0]);
		fp = (uint32_t*)fp[1];
	}
	TRACE("done\r\n");
}

void abort(void) {
	if(_txm_module_kernel_call_dispatcher) TRACE("abort called\r\n");
	backtrace();
	while(_txm_module_kernel_call_dispatcher) {
		tx_thread_sleep(100);
	}
	for(;;) {}
}

void abort_with_message(const char* msg) {
	if(msg && _txm_module_kernel_call_dispatcher) TRACE("abort called: %s\r\n", msg);
	backtrace();
	while(_txm_module_kernel_call_dispatcher) {
		tx_thread_sleep(100);
	}
	for(;;) {}
}
