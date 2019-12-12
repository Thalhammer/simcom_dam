#pragma once

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	int quot;
	int rem;
} div_t;
typedef struct {
	long quot;
	long rem;
} ldiv_t;
typedef struct {
	long long quot;
	long long rem;
} lldiv_t;

extern char* itoa(int value, char* str, int base);
extern char* itoa_unsigned(unsigned int value, char* str, int base);
extern int abs(int value);
extern div_t div(int numer, int denom);
extern long int labs(long int value);
extern ldiv_t ldiv(long int numer, long int denom);
extern long long int llabs(long long int value);
extern lldiv_t lldiv(long long int numer, long long int denom);

#define RAND_MAX __INT32_MAX__
extern void srand(unsigned int seed);
extern int rand(void);

extern void* calloc(size_t num, size_t size);
/**
 * malloc, free and realloc are not implemented in libc but instead
 * in the respective os library
 */
extern void* malloc(size_t size);
extern void free(void* ptr);
extern void* realloc(void* ptr, size_t size);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

/**
 *  TODO: atof, atoi, atol, atoll, strtod, strtof, strtol, strtold, strtoll, strtoul, strtoull
 *  TODO: abort, atexit, at_quick_exit, exit, getenv, quick_exit, system, _Exit
 *  TODO: bsearch, qsort
 *  TODO: mblen, mbtowc, wctomb, mbstowcs, wcstombs
 */


#ifdef __cplusplus
}
#endif