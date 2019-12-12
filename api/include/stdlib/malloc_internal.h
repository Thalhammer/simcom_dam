#pragma once
#include "stddef.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif
// Non standard interface
typedef struct {
	size_t bytes_total;
	size_t bytes_free;
	size_t num_current_allocations;
} malloc_stats_t;
struct TX_BYTE_POOL_STRUCT;
extern int malloc_init(void* baseptr, size_t len);
extern int malloc_stats(malloc_stats_t* stats);
extern struct TX_BYTE_POOL_STRUCT* malloc_get_heap_pool_raw();
#ifdef __cplusplus
}
namespace txpp { class byte_pool; }
extern txpp::byte_pool& malloc_get_heap_pool();
#endif