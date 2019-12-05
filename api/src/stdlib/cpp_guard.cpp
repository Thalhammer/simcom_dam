#include <cstdint>
#include <cassert>
#include "threadx_api/txm_module.h"

static TX_MUTEX* cpp_guard_mutex = nullptr;

extern "C" int __cxa_guard_init_system(void) {
	if(txm_module_object_allocate((void**)&cpp_guard_mutex, sizeof(TX_MUTEX)) != TX_SUCCESS)
		return -1;
	if(tx_mutex_create(cpp_guard_mutex, "cpp_guard_mtx", TX_INHERIT) != TX_SUCCESS) {
		txm_module_object_deallocate(cpp_guard_mutex);
		cpp_guard_mutex = nullptr;
		return -2;
	}
	return 0;
}

using guard_type = uint32_t;

static bool get_initializer_has_run(const guard_type* g) {
	return reinterpret_cast<const uint8_t*>(g)[0] != 0;
}

static void set_initializer_has_run(guard_type* g) {
	reinterpret_cast<uint8_t*>(g)[0] = 1;
}

static bool get_in_use(const guard_type* g) {
	return reinterpret_cast<const uint8_t*>(g)[1] != 0;
}

static void set_in_use(guard_type* g, bool inuse) {
	reinterpret_cast<uint8_t*>(g)[0] = inuse ? 1 : 0;
}

extern "C" int __cxa_guard_acquire(guard_type* g)
{
	if(get_initializer_has_run(g)) return 0;

	assert(tx_mutex_get(cpp_guard_mutex, TX_WAIT_FOREVER) == TX_SUCCESS);

	if(get_initializer_has_run(g)) {
		assert(tx_mutex_put(cpp_guard_mutex) == TX_SUCCESS);
		return 0;
	}

	assert(get_in_use(g) == false);
	set_in_use(g, true);

	return 1;
}

extern "C" void __cxa_guard_release(guard_type* g)
{
	set_initializer_has_run(g);
	assert(tx_mutex_put(cpp_guard_mutex) == TX_SUCCESS);
}

extern "C" void __cxa_guard_abort(guard_type* g)
{
	set_in_use(g, false);
	assert(tx_mutex_put(cpp_guard_mutex) == TX_SUCCESS);
}