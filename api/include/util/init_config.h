#pragma once

/*
Control init behaviour:
By default _libc_app_init will
- Check if gpio3 is pulled low and cancel boot if so
- Init the debug uart to 115200 baud
- Wait 10 seconds to give time to reflash on error

You can define a couple of symbols which, if present, will configure these features.
In order to configure them, place the following makros somewhere in the global scope of your program once.
Placeing the twice will result in a linker error.
*/

#ifdef __cplusplus
/* Disable auto init of the debug uart */
#define INIT_DISABLE_DEBUG_UART() extern "C" {  int _init_debug_uart = 0; }
/* Disable 10 second delay */
#define INIT_DISABLE_SAFETY_DELAY() extern "C" {  int _init_safety_delay = 0; }
#else
/* Disable auto init of the debug uart */
#define INIT_DISABLE_DEBUG_UART() int _init_debug_uart = 0;
/* Disable 10 second delay */
#define INIT_DISABLE_SAFETY_DELAY() int _init_safety_delay = 0;
#endif