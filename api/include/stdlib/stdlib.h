#pragma once

typedef struct {
	int quot;
	int rem;
} div_t;

extern char* itoa(int value, char* str, int base);
extern int abs(int value);
extern long int labs(long int value);

extern div_t div(int numer, int denom);