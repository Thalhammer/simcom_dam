#pragma once
#include <stddef.h>
#include "qapi_status.h"
#include <stdarg.h>

struct uart_context_s;
typedef struct uart_context_s* uart_context_t;

typedef enum
{
	UART_5_BITS_PER_CHAR_E = 0,
	UART_6_BITS_PER_CHAR_E = 1,
	UART_7_BITS_PER_CHAR_E = 2,
	UART_8_BITS_PER_CHAR_E = 3,
} UART_Bits_Per_Char_e;

typedef enum
{
	UART_0_5_STOP_BITS_E = 0,
	UART_1_0_STOP_BITS_E = 1,
	UART_1_5_STOP_BITS_E = 2,
	UART_2_0_STOP_BITS_E = 3,
} UART_Num_Stop_Bits_e;

typedef enum
{
	UART_NO_PARITY_E = 0,
	UART_ODD_PARITY_E = 1,
	UART_EVEN_PARITY_E = 2,
	UART_SPACE_PARITY_E = 3,
} UART_Parity_Mode_e;

typedef enum
{
	UART_PORT_DEFAULT = 2,
	UART_PORT_DEBUG = 0
} UART_Port_e;

typedef struct uart_init_config_s {
	uint32_t baud_Rate;
	UART_Parity_Mode_e parity_Mode;
	UART_Num_Stop_Bits_e num_Stop_Bits;
	UART_Bits_Per_Char_e bits_Per_Char;
	qbool_t enable_Loopback;
	qbool_t enable_Flow_Ctrl;
	void(*rxCb)(uint32_t num_bytes, void *cb_data);
	UART_Port_e port;
	uint8_t* buf;
	uint32_t buf_len;
} uart_init_config_t;

extern qapi_Status_t uart_required_buf(int* bufsize, int sendbuf);
extern qapi_Status_t uart_default_cfg(uart_init_config_t* cfg);
extern qapi_Status_t uart_debug_cfg(uart_init_config_t* cfg);

extern qapi_Status_t uart_init(uart_context_t* ctx, const uart_init_config_t* cfg);
extern qapi_Status_t uart_write_str(uart_context_t ctx,const char* str);
extern qapi_Status_t uart_write(uart_context_t ctx,const char* str, size_t len);
extern qapi_Status_t uart_vprintf(uart_context_t ctx, const char* fmt, va_list args);
extern qapi_Status_t uart_printf(uart_context_t ctx, const char* fmt, ...);

extern qapi_Status_t uart_power_off(uart_context_t ctx);
extern qapi_Status_t uart_power_on(uart_context_t ctx);
