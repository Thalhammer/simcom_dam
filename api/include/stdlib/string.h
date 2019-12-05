#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
extern size_t strlen(const char* str);
extern void* memset(void* ptr, int value, size_t num);
extern void* memcpy(void* destination, const void* source, size_t num);
extern int memcmp(const void* destination, const void* source, size_t num);

extern int strcmp(const char* str1, const char* str2);
extern char * strchr ( const char *, int );

#ifdef __cplusplus
}
#endif