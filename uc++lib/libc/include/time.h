#pragma once
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef __UINT64_TYPE__ clock_t;
typedef __UINT64_TYPE__ time_t;
typedef struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
} tm;

extern double difftime(time_t end, time_t beginning);

// TODO: CLOCKS_PER_SEC, functions

#ifdef __cplusplus
}
#endif