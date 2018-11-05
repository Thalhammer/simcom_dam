#pragma once

struct uart_context_s;
typedef struct uart_context_s* uart_context_t;

extern int debug_init(void);
extern uart_context_t debug_get_handle(void);
extern void debug_printf(const char* fmt, ...);
