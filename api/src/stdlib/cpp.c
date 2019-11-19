#include "util/debug.h"
#include "util/trace.h"

#define TRACE_TAG "cxx_api"

#ifndef ATEXIT_NUM_FUNCS
#define ATEXIT_NUM_FUNCS 128
#endif

void *__dso_handle = &__dso_handle;

struct atexit_func_entry_t
{
	void (*destructor_func)(void *);
	void *obj_ptr;
	// Note: Normal implementations also have a dso pointer,
	// however we have no support for shared objects.
};
struct atexit_func_entry_t __atexit_funcs[ATEXIT_NUM_FUNCS];
unsigned int __atexit_funcs_count = 0;

void __cxa_pure_virtual()
{
}

void __cxa_finalize(void *f)
{
	(void)f;
	for (unsigned int i = 0; i < __atexit_funcs_count; i++)
	{
		if (__atexit_funcs[i].destructor_func)
			__atexit_funcs[i].destructor_func(__atexit_funcs[i].obj_ptr);
	}
	__atexit_funcs_count = 0;
}

int __cxa_atexit(void (*destructor)(void *), void *arg, void *__dso_handle)
{
	TRACE("cxa_atexit(%x, %x, %x)\r\n", destructor, arg, __dso_handle);

	if (__atexit_funcs_count >= ATEXIT_NUM_FUNCS)
		return -1;
	__atexit_funcs[__atexit_funcs_count].destructor_func = destructor;
	__atexit_funcs[__atexit_funcs_count].obj_ptr = arg;
	__atexit_funcs_count++;
	return 0;
}

int __aeabi_atexit(void *arg, void (*func)(void *), void *d)
{
	return __cxa_atexit(func, arg, d);
}

int __cxa_guard_acquire(char* g)
{
	if(__atomic_test_and_set(&g[1], __ATOMIC_ACQUIRE)) return 0;
	return !g[0];
}

void __cxa_guard_release(char* g)
{
	g[0] = 1;
	__atomic_clear(&g[1], __ATOMIC_RELEASE);
}

void __cxa_guard_abort(char* g)
{
	g[0] = 0;
	__atomic_clear(&g[1], __ATOMIC_RELEASE);
}