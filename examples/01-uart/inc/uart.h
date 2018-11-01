#pragma once
#include <stddef.h>

extern void uart_init(void);
extern void uart_write_str(const char* str);
extern void uart_write(const char* str, size_t len);
