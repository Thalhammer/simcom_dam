#pragma once
#include "stdarg.h"
#include "stddef.h"

extern int vcbprintf(char* buf, size_t n, int(*cb)(char*,size_t, void*), void* param, const char* format, va_list args);
extern int vsnprintf(char* s, size_t n, const char* format, va_list args);
extern int snprintf(char* s, size_t n, const char* format, ... );