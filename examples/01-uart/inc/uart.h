#pragma once
#include <stddef.h>

extern void app_uart_init(void);
extern void app_uart_write_str(const char* str);
extern void app_uart_write(const char* str, size_t len);
