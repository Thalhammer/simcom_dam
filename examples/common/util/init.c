#include <stdint.h>
#include "qapi_timer.h"

typedef void (*init_func_t)(void);

#ifdef __GNUC__
extern int __preinit_array_start;
extern int __preinit_array_end;
extern int __init_array_start;
extern int __init_array_end;
extern int __fini_array_start;
extern int __fini_array_end;
#else
extern int SHT$$INIT_ARRAY$$Base;
extern int SHT$$INIT_ARRAY$$Limit;
#endif

extern int Image$$ER_RO$$Base;
extern int Image$$ER_RO$$Limit;

extern int dam_app_start(void);

int _libc_app_init(void) {
#ifdef __GNUC__
	for (uint32_t* p = (uint32_t*)&__preinit_array_start; p < (uint32_t*)&__preinit_array_end; ++p) {
		uint32_t fn = *p;
		if(fn > (uint32_t)&Image$$ER_RO$$Base && fn < (uint32_t)&Image$$ER_RO$$Limit) ((init_func_t)fn)();
	}

	for (uint32_t* p = (uint32_t*)&__init_array_start; p < (uint32_t*)&__init_array_end; ++p) {
		uint32_t fn = *p;
#else
	for (init_func_t* p = (init_func_t*)&SHT$$INIT_ARRAY$$Base; p < (init_func_t*)&SHT$$INIT_ARRAY$$Limit; ++p) {
		uint32_t fn = ((uint32_t)p + (int)*p);
#endif
		if(fn > (uint32_t)&Image$$ER_RO$$Base && fn < (uint32_t)&Image$$ER_RO$$Limit) ((init_func_t)fn)();
	}

	int result = dam_app_start();

#ifdef __GNUC__
	for (uint32_t* p = (uint32_t*)&__fini_array_start; p < (uint32_t*)&__fini_array_end; ++p) {
		uint32_t fn = *p;
		if(fn > (uint32_t)&Image$$ER_RO$$Base && fn < (uint32_t)&Image$$ER_RO$$Limit) ((init_func_t)fn)();
	}
#endif

	return result;
}
