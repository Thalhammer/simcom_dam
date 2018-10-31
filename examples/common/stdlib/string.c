#include <string.h>
#include <stdint.h>

size_t strlen(const char* str) {
	const char* end = str;
	while(*end++ != '\0');
	return end - str;
}

void* memset(void* ptr, int value, size_t num) {
	value = value & 0xff;
	uint32_t mask = value << 24 | value << 16 | value << 8 | value;
	const size_t mult4 = num/4;
	for(size_t i=0; i<mult4; i++) {
		((uint32_t*)ptr)[i] = mask;
	}
	switch(num%4) {
		case 3:
			((uint8_t*)ptr)[num - 3] = mask;
		case 2:
			((uint8_t*)ptr)[num - 2] = mask;
		case 1:
			((uint8_t*)ptr)[num - 1] = mask;
		case 0:
			break;
	}
	return ptr;
}

void* memcpy(void* destination, const void* source, size_t num) {
	const size_t mult4 = num/4;
	for(size_t i=0; i<mult4; i++) {
		((uint32_t*)destination)[i] = ((uint32_t*)source)[i];
	}
	switch(num%4) {
		case 3:
			((uint8_t*)destination)[num - 3] = ((uint8_t*)source)[num - 3];
		case 2:
			((uint8_t*)destination)[num - 2] = ((uint8_t*)source)[num - 2];
		case 1:
			((uint8_t*)destination)[num - 1] = ((uint8_t*)source)[num - 1];
		case 0:
			break;
	}
	return destination;
}
