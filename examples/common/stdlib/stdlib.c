#include "stdlib.h"

char* itoa(int value, char* str, int base) {
	unsigned int uval = abs(value);
	unsigned int val = uval;
	int len = 0;
	if(value < 0 && base == 10) {
		str[0] = '-';
		len = 1;
	}
	do { val /= base; len++; } while(val != 0);
	val = uval;
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

unsigned int abs(int value) {
	const int mask = value >> (sizeof(int) * 8 - 1); 
	return ((value + mask) ^ mask); 
}

unsigned long int labs(long int value) {
	const long int mask = value >> (sizeof(long int) * 8 - 1); 
	return ((value + mask) ^ mask);
}

div_t div(int numer, int denom) {
	div_t res;
	res.rem = numer % denom;
	res.quot = numer/denom;
	return res;
}