#pragma once

#include "stddef.h"
#include "stdarg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  TODO: everything else :(
 */

extern int sprintf(char* str, const char* format, ...);
extern int snprintf(char* str, size_t len, const char* fmt, ...);
extern int vsprintf(char* s, const char* fmt, va_list arg);
extern int vsnprintf(char* s, size_t len, const char* fmt, va_list arg);

// Extentions
extern int vcbprintf(const char* fmt, va_list arg, void(*cb)(char, void*), void* cbarg);

#ifdef __cplusplus
}
#endif