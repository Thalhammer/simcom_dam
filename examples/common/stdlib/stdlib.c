#include "stdlib.h"
#include "txm_module.h"

char* itoa(int value, char* str, int base) {
	if(value < 0 && base == 10) {
		str[0] = '-';
		itoa_unsigned(abs(value), &str[1], base);
	} else {
		itoa_unsigned(abs(value), str, base);
	}
	return str;
}

char* itoa_unsigned(unsigned int value, char* str, int base) {
	unsigned int val = value;
	int len = 0;
	do { val /= base; len++; } while(val != 0);
	val = value;
	for(int i=len; i > 0; i--) {
		int c = val % base;
		val /= base;
		if(c > 9) str[i-1] = 'A' + (c-10);
		else str[i-1] = '0' + c;
		if(val == 0) break;
	}
	str[len] = '\0';
	return str;
}

int abs(int value) {
	if(value < 0) return value*-1;
	else return value;
}

long int labs(long int value) {
	if(value < 0) return value*-1;
	else return value;
}

div_t div(int numer, int denom) {
	div_t res;
	res.rem = numer % denom;
	res.quot = numer/denom;
	return res;
}

/*
UINT        _tx_byte_pool_info_get(TX_BYTE_POOL *pool_ptr, CHAR **name, ULONG *available_bytes, 
                    ULONG *fragments, TX_THREAD **first_suspended, 
                    ULONG *suspended_count, TX_BYTE_POOL **next_pool);
*/

static TX_BYTE_POOL* _heap_pool;
static size_t _heap_pool_size = 0;

void* malloc(size_t size) {
	if(_heap_pool_size == 0) return NULL;
	void* ptr = NULL;
	if(tx_byte_allocate(&_heap_pool, &ptr, size, TX_NO_WAIT) != TX_SUCCESS || ptr == NULL) {
		return NULL;
	}
	return ptr;
}

void* calloc(size_t num, size_t size) {
	void* ptr = malloc(num * size);
	memset(ptr, 0, num*size);
	return ptr;
}

void free(void* ptr) {
	if(_heap_pool_size == 0) return;
	tx_byte_release(ptr);
}

int malloc_init(void* baseptr, size_t len) {
	if(baseptr == NULL || len == 0) return -2;
	if(_heap_pool_size != 0) return -1;
	if(txm_module_object_allocate((void**)&_heap_pool, sizeof(TX_BYTE_POOL)) != TX_SUCCESS) return -1;
	if(tx_byte_pool_create(&_heap_pool, "heap_pool", baseptr, len) != TX_SUCCESS) {
		txm_module_object_deallocate(_heap_pool);
		return -1;
	}
	_heap_pool_size = len;
	return 0;
}

int malloc_stats(malloc_stats_t* stats) {
	if(_heap_pool_size == 0) return -1;
	ULONG avail, fragments;
	if(tx_byte_pool_info_get(&_heap_pool, NULL, &avail, &fragments, NULL, NULL, NULL) != TX_SUCCESS) return -2;
	stats->bytes_free = avail;
	stats->num_current_allocations = fragments;
	stats->bytes_total = _heap_pool_size;
	return 0;
}