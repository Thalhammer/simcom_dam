#include "stdlib.h"
#include "mt_rand.h"

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

long long int llabs(long long int value) {
	if(value < 0) return value*-1;
	else return value;
}

div_t div(int numer, int denom) {
	div_t res;
	res.rem = numer % denom;
	res.quot = numer/denom;
	return res;
}

ldiv_t ldiv(long int numer, long int denom) {
	ldiv_t res;
	res.rem = numer % denom;
	res.quot = numer/denom;
	return res;
}

lldiv_t lldiv(long long int numer, long long int denom) {
	lldiv_t res;
	res.rem = numer % denom;
	res.quot = numer/denom;
	return res;
}

static libc_impl::mt_rand g_rand;

void srand(unsigned int seed) {
	g_rand.seed(seed);
}

int rand(void) {
	return g_rand() % RAND_MAX;
}

extern void* memset(void* ptr, int value, size_t num);

void* calloc(size_t num, size_t size) {
	auto ptr = malloc(num * size);
	if(ptr == nullptr) return nullptr;
	memset(ptr, 0, num * size);
	return ptr;
}

}