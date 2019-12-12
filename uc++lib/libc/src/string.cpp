#include <string.h>
#include <stdint.h>

extern "C" {

void* memchr(const void* ptr, int value, size_t num) {
	auto u8 = reinterpret_cast<const uint8_t*>(ptr);
	while(num-- && *u8 != value) u8++;
	if(*u8 != value) return nullptr;
	return const_cast<uint8_t*>(u8);
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
			__attribute__((fallthrough));
		case 2:
			((uint8_t*)ptr)[num - 2] = mask;
			__attribute__((fallthrough));
		case 1:
			((uint8_t*)ptr)[num - 1] = mask;
			__attribute__((fallthrough));
		case 0:
			break;
	}
	return ptr;
}

void* memcpy(void* destination, const void* source, size_t num) {
	if(reinterpret_cast<uintptr_t>(destination) % 4 == 0 && reinterpret_cast<uintptr_t>(source) % 4 == 0) {
		auto out = reinterpret_cast<uint32_t*>(destination);
		auto in = reinterpret_cast<const uint32_t*>(source);
		for(size_t i = 0; i<num/4; i++) {
			out[i] = in[i];
		}
		auto d8 = reinterpret_cast<uint8_t*>(destination);
		auto s8 = reinterpret_cast<const uint8_t*>(source);
		switch(num%4) {
			case 3:
				d8[num - 3] = s8[num - 3];
				__attribute__((fallthrough));
			case 2:
				d8[num - 2] = s8[num - 2];
				__attribute__((fallthrough));
			case 1:
				d8[num - 1] = s8[num - 1];
				__attribute__((fallthrough));
			case 0:
				break;
		}
	} else {
		auto out = reinterpret_cast<uint8_t*>(destination);
		auto in = reinterpret_cast<const uint8_t*>(source);
		for(size_t i = 0; i<num; i++) {
			out[i] = in[i];
		}
	}
    return destination;
}

void* memmove(void* destination, const void* source, size_t num) {
	if(reinterpret_cast<uintptr_t>(destination) < reinterpret_cast<uintptr_t>(source)) {
		return memcpy(destination, source, num);
	} else {
		auto out = reinterpret_cast<uint8_t*>(destination) + num - 1;
		auto in = reinterpret_cast<const uint8_t*>(source) + num - 1;
		for(size_t i = 0; i<num; i++) {
			*out = *in;
			out--;
			in--;
		}
	}
	return destination;
}

int memcmp(const void* destination, const void* source, size_t num) {
	const size_t mult4 = num/4;
	auto d32 = reinterpret_cast<const uint32_t*>(destination);
	auto s32 = reinterpret_cast<const uint32_t*>(source);
	for(size_t i=0; i<mult4; i++) {
		if(d32[i] != s32[i]) return d32[i] - s32[i];
	}
	auto d8 = reinterpret_cast<const uint8_t*>(destination);
	auto s8 = reinterpret_cast<const uint8_t*>(source);
	switch(num%4) {
		case 3:
			if(d8[num - 3] != s8[num - 3]) return (d8[num - 3] - s8[num - 3]);
			__attribute__((fallthrough));
		case 2:
			if(d8[num - 2] != s8[num - 2]) return (d8[num - 2] - s8[num - 2]);
			__attribute__((fallthrough));
		case 1:
			if(d8[num - 1] != s8[num - 1]) return (d8[num - 1] - s8[num - 1]);
			__attribute__((fallthrough));
		case 0:
			break;
	}
	return 0;
}

char* strcat(char *dest, const char *src)
{
    auto ret = dest;
    while (*dest) dest++;
    strcpy(dest, src);
    return ret;
}

size_t strlen(const char* str) {
	const char* end = str;
	while(*end++ != '\0');
	return (end - str) - 1;
}

int strcmp(const char* str1, const char* str2) {
	while(*str1 != '\0' && *str1 == *str2) { str1++; str2++; }
	return *str1 - *str2;
}

int strcoll( const char* str1, const char* str2) {
	// We only know about "C" locale
	return strcmp(str1, str2);
}

char* strchr(const char* str, int c) {
	while(*str != '\0' && *str != c) str++;
	if(*str != c) return NULL;
	return const_cast<char*>(str);
}

char* strcpy(char *dest, const char *src)
{
    auto ret = dest;
    while (*src) *dest++ = *src++;
    return ret;
}

size_t strcspn(const char *s1, const char *s2)
{
    size_t ret=0;
    while(*s1)
        if(strchr(s2,*s1)) return ret;
        else {
			s1++;
			ret++;
		}
    return ret;
}

const char *strerror(int errnum)
{
	// TODO: Implement
    return errnum ? "An error occurred" : "Success";
}

char* strncat(char *dest, const char *src, size_t n)
{
    auto ret = dest;
    while (*dest) dest++;
    while (n-- && *src) {
        *dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
    return ret;
}

int strncmp(const char* s1, const char* s2, size_t n)
{
    while(n-- && *s1 == *s2) {
		s1++;
		s2++;
	}
	return *reinterpret_cast<const unsigned char*>(s1) - *reinterpret_cast<const unsigned char*>(s2);
}

char* strncpy(char* dest, const char* src, size_t n)
{
    auto ret = dest;
    while(n-- && *src) {
		*dest = *src;
		dest++;
		src++;
	}
	while(n--) {
		*dest = '\0';
		dest++;
	}
    return ret;
}

char *strpbrk(const char* s1, const char* s2)
{
    for(; *s1; s1++) {
		for(auto i = s2; *i; i++) {
			if(*i == *s1) return const_cast<char*>(s1);
		}
	}
    return 0;
}

char *strrchr(const char *s, int c)
{
    char* ret=nullptr;
    do {
        if(*s == static_cast<char>(c)) ret = const_cast<char*>(s);
    } while(*s++);
    return ret;
}

size_t strspn(const char* s1, const char* s2)
{
    size_t ret=0;
    while(*s1 && strchr(s2,*s1++)) ret++;
    return ret;
}

char* strstr(const char* s1, const char* s2)
{
    size_t n = strlen(s2);
    for(; *s1; s1++) {
        if(!memcmp(s1, s2, n))
            return const_cast<char*>(s1);
	}
    return nullptr;
}

char* strtok(char* str, const char* delim)
{
    static char* context = nullptr;
	return strtok_s(str, delim, &context);
}

char* strtok_s(char* str, const char* delim, char** context)
{
    if(str) *context=str;
    else if(!(*context)) return nullptr;
    str = *context + strspn(*context, delim);
    *context = str + strcspn(str, delim);
    if(*context == str) {
		*context = nullptr;
		return *context;
	}
	if(*(*context)) {
		*(*context) = '\0';
		(*context)++;
	} else {
		*context = nullptr;
	}
    return str;
}

size_t strxfrm(char *dest, const char *src, size_t n)
{
    /* This implementation does not know about any locale but "C"... */
    size_t n2=strlen(src);
    if(n>n2)
        strcpy(dest,src);
    return n2;
}

}