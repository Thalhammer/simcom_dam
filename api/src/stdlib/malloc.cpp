#include "malloc_internal.h"
#include "txpp/api.h"
#include "txpp/byte_pool.h"

extern "C" {
static txpp::byte_pool _heap_pool;

void* malloc(size_t size) {
	return _heap_pool.malloc(size);
}

void* calloc(size_t num, size_t size) {
	return _heap_pool.calloc(num, size);
}

void free(void* ptr) {
	_heap_pool.free(ptr);
}

int malloc_init(void* baseptr, size_t len) {
	return _heap_pool.initialize(baseptr, len, "heap_pool") ? 0 : -1;
}

int malloc_stats(malloc_stats_t* stats) {
	::txpp::byte_pool::pool_info info;
	if(!_heap_pool.get_info(info)) return -1;
	stats->bytes_free = info.available_bytes;
	stats->bytes_total = info.total_bytes;
	stats->num_current_allocations = info.fragments;
	return 0;
}

struct TX_BYTE_POOL_STRUCT* malloc_get_heap_pool_raw() {
	return _heap_pool.raw_pool();
}

}

txpp::byte_pool& malloc_get_heap_pool() {
	return _heap_pool;
}

extern "C" [[noreturn]] void abort_with_message(const char*);

extern "C" void* __emutls_get_address() {
	abort_with_message("tls not supported");
}
