#include <stdint.h>
#include "txm_module.h"

#include "qapi/qapi_timer.h"
#include "util/debug.h"
#include "util/trace.h"
#include "util/boot_cfg.h"

#define TRACE_TAG "init"

extern int dam_app_start(void);

extern void (*__preinit_array_start []) (void);
extern void (*__preinit_array_end []) (void);
extern void (*__init_array_start []) (void);
extern void (*__init_array_end []) (void);
extern void (*__fini_array_start []) (void);
extern void (*__fini_array_end []) (void);

static int call_preinit() {
	TRACE("calling preinit array\r\n");
	size_t count = __preinit_array_end - __preinit_array_start;
	for(size_t i = 0; i < count; i++) {
		TRACE("calling %x\r\n", __preinit_array_start[i]);
		__preinit_array_start[i]();
	}
	return TX_SUCCESS;
}

static int call_init() {
	TRACE("calling init array\r\n");
	size_t count = __init_array_end - __init_array_start;
	for(size_t i = 0; i < count; i++) {
		TRACE("calling %x\r\n", __init_array_start[i]);
		__init_array_start[i]();
	}
	return TX_SUCCESS;
}

static int call_fini() {
	TRACE("calling fini array\r\n");
	size_t count = __fini_array_end - __fini_array_start;
	for(size_t i = 0; i < count; i++) {
		TRACE("calling %x\r\n", __fini_array_start[i]);
		__fini_array_start[i]();
	}
	return TX_SUCCESS;
}

extern void __cxa_finalize(void*);

int _libc_app_init(void) {
	if(boot_cfg() != TX_SUCCESS) return TX_SUCCESS;
	if(debug_init() != TX_SUCCESS) return TX_SUCCESS;
	TRACE("waiting some time\r\n");
	qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true);
	TRACE("init\r\n");

	int res = call_preinit();
	if(res != TX_SUCCESS) return res;
	res = call_init();
	if(res != TX_SUCCESS) return res;

	int app_result = dam_app_start();

	__cxa_finalize(NULL);

	res = call_fini();
	if(res != TX_SUCCESS) return res;

	TRACE("exiting to os with code %d\r\n", app_result);

	return app_result;
}
