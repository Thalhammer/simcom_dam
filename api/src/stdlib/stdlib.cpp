#include "stdlib.h"
#include "txpp/api.h"
#include "txpp/byte_pool.h"

extern "C" {

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
}