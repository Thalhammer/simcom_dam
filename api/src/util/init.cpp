extern "C" {
#include <stdint.h>
#include "txm_module.h"

#include "qapi/qapi_timer.h"
#include "util/trace.h"
#include "util/boot_cfg.h"

#include "assert.h"

#define TRACE_TAG "init"

extern int dam_app_start(void);

extern void (*__preinit_array_start []) (void);
extern void (*__preinit_array_end []) (void);
extern void (*__init_array_start []) (void);
extern void (*__init_array_end []) (void);
extern void (*__fini_array_start []) (void);
extern void (*__fini_array_end []) (void);

int __attribute__((weak)) _init_debug_uart = 1;
int __attribute__((weak)) _init_safety_delay = 1;

static int call_preinit() {
	TRACE("calling preinit array\r\n");
	size_t count = __preinit_array_end - __preinit_array_start;
	for(size_t i = 0; i < count; i++) {
		TRACE("calling %x\r\n", __preinit_array_start[i]);
#if __cpp_exceptions >= 199711
		try {
#endif
		__preinit_array_start[i]();
#if __cpp_exceptions >= 199711
		} catch(...) {
			TRACE("exception handling preinit function %x\r\n", __preinit_array_start[i]);
			return -1;
		}
#endif
	}
	return TX_SUCCESS;
}

static int call_init() {
	TRACE("calling init array\r\n");
	size_t count = __init_array_end - __init_array_start;
	for(size_t i = 0; i < count; i++) {
		TRACE("calling %x\r\n", __init_array_start[i]);
#if __cpp_exceptions >= 199711
		try {
#endif
		__init_array_start[i]();
#if __cpp_exceptions >= 199711
		} catch(...) {
			TRACE("exception handling init function %x\r\n", __init_array_start[i]);
			return -1;
		}
#endif
	}
	return TX_SUCCESS;
}

static int call_fini() {
	TRACE("calling fini array\r\n");
	size_t count = __fini_array_end - __fini_array_start;
	for(size_t i = 0; i < count; i++) {
		TRACE("calling %x\r\n", __fini_array_start[i]);
#if __cpp_exceptions >= 199711
		try {
#endif
		__fini_array_start[i]();
#if __cpp_exceptions >= 199711
		} catch(...) {
			TRACE("exception handling fini function %x\r\n", __fini_array_start[i]);
			return -1;
		}
#endif
	}
	return TX_SUCCESS;
}

extern void __cxa_finalize(void*);
extern int __cxa_guard_init_system(void);

int _libc_app_init(void) {
	if(boot_cfg() != TX_SUCCESS) return TX_SUCCESS;
	if(_init_debug_uart) {
		if(debug_init() != TX_SUCCESS) return TX_SUCCESS;
	}
	if(_init_safety_delay) {
		TRACE("waiting some time\r\n");
		qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true);
		TRACE("init\r\n");
	}

	int res = __cxa_guard_init_system();
	if(res != TX_SUCCESS) {
		TRACE("failed to init cpp guard mutex: %d\r\n", res);
		return TX_SUCCESS;
	}

	res = call_preinit();
	if(res != TX_SUCCESS) return res;
	res = call_init();
	if(res != TX_SUCCESS) return res;

	int app_result;
#if __cpp_exceptions >= 199711
	try {
#endif
	app_result = dam_app_start();
#if __cpp_exceptions >= 199711
	} catch(...) {
		TRACE("exception in main\r\n");
		return TX_SUCCESS;
	}
#endif

	__cxa_finalize(NULL);

	res = call_fini();
	if(res != TX_SUCCESS) return res;

	TRACE("exiting to os with code %d\r\n", app_result);

	return app_result;
}

}