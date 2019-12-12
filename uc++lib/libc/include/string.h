#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
extern void* memchr(const void* ptr, int value, size_t num);
extern void* memset(void* ptr, int value, size_t num);
extern void* memcpy(void* destination, const void* source, size_t num);
extern void* memmove(void* destination, const void* source, size_t num);
extern int memcmp(const void* destination, const void* source, size_t num);

extern char* strcat(char *dest, const char *src);
extern size_t strlen(const char* str);
extern int strcmp(const char* str1, const char* str2);
extern int strcoll(const char* str1, const char* str2);
extern char* strchr(const char* str, int c);
extern char* strcpy(char *dest, const char *src);
extern size_t strcspn(const char *s1, const char *s2);
// Note: This is not exactly following the standard but returning a
// constant string makes it easier to implement and nobody with a sane
// mind would modify the returned string anyway.
extern const char* strerror(int errnum);
extern char* strncat(char *dest, const char *src, size_t n);
extern int strncmp(const char* s1, const char* s2, size_t n);
extern char* strncpy(char* dest, const char* src, size_t n);
extern char* strpbrk(const char *s1, const char *s2);
extern char* strrchr(const char *s, int c);
extern size_t strspn(const char *s1, const char *s2);
extern char* strstr(const char* s1, const char* s2);
extern char* strtok(char* str, const char* delim) __attribute__ ((deprecated("uses static state, use strtok_s instead")));
// Like strtok but without a static state (state is preserved using context variable)
extern char* strtok_s(char* str, const char* delimiters, char** context);
extern size_t strxfrm(char* dest, const char* src, size_t n);

#ifdef __cplusplus
}
#endif