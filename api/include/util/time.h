#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "qapi/qapi_timer.h"

typedef __UINT32_TYPE__ time_t;

typedef struct time_julian_type {
    uint32_t days;
    uint32_t day_secs;
} time_julian_type;
typedef qapi_time_julian_type time_gregorian_type;
typedef time_t time_unix_type;

time_julian_type time_convert_unix_to_julian(time_t ts);
time_julian_type time_convert_gregorian_to_julian(time_gregorian_type time);
time_t time_convert_julian_to_unix(time_julian_type time);
time_t time_convert_gregorian_to_unix(time_gregorian_type time);
time_gregorian_type time_convert_julian_to_gregorian(time_julian_type time);
time_gregorian_type time_convert_unix_to_gregorian(time_t ts);

int time_parse_cclk_string(const char* str, time_gregorian_type* time);

#ifdef __cplusplus
}
#endif