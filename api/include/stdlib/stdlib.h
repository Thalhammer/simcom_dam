#pragma once
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
	int quot;
	int rem;
} div_t;

extern char* itoa(int value, char* str, int base);
extern char* itoa_unsigned(unsigned int value, char* str, int base);
extern int abs(int value);
extern long int labs(long int value);

extern div_t div(int numer, int denom);

extern void* malloc(size_t size);
extern void* calloc(size_t num, size_t size);
extern void free(void* ptr);

extern void abort();

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