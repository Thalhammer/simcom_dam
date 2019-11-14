#include "util/time.h"

#define TIME_SECONDS_PER_DAY 86400
#define TIME_JGREG (15 + 31*(10+12*1582))

// Checked OK
time_julian_type time_convert_unix_to_julian(time_unix_type ts)
{
    time_julian_type res;
    res.days = ts / TIME_SECONDS_PER_DAY + 2440587;
    res.day_secs = (ts % TIME_SECONDS_PER_DAY) + (TIME_SECONDS_PER_DAY / 2);
    if(res.day_secs >= TIME_SECONDS_PER_DAY) {
        res.days++;
        res.day_secs -= TIME_SECONDS_PER_DAY;
    }
    return res;
}

// Checked OK
time_julian_type time_convert_gregorian_to_julian(time_gregorian_type time)
{
    time_julian_type res;
    int Y = time.year, M = time.month, D = time.day;
    res.days =  (1461 * (Y + 4800 + (M - 14)/12))/4 +(367 *(M - 2 - 12 * ((M - 14)/12)))/12 - (3 * ((Y + 4900 + (M - 14)/12)/100))/4 + D - 32075;
    res.day_secs = (TIME_SECONDS_PER_DAY/2 + (time.hour*60*60) + time.minute*60 + time.second) % TIME_SECONDS_PER_DAY;
    if(time.hour < 12) {
        res.days--;
    }
    return res;
}

// Checked OK
time_unix_type time_convert_julian_to_unix(time_julian_type time)
{
    int secs = time.day_secs;
    secs -= TIME_SECONDS_PER_DAY/2;
    time_unix_type res = (time.days - 2440587)*TIME_SECONDS_PER_DAY;
    res += secs;
    return res;
}

// Composit
time_unix_type time_convert_gregorian_to_unix(time_gregorian_type time)
{
    return time_convert_julian_to_unix(time_convert_gregorian_to_julian(time));
}

// Checked OK from 01.01.1970 - 28.02.2100
time_gregorian_type time_convert_julian_to_gregorian(time_julian_type time)
{
    time_gregorian_type res;
    {
        int secs = (time.day_secs + TIME_SECONDS_PER_DAY/2) % TIME_SECONDS_PER_DAY;
        if(secs >= TIME_SECONDS_PER_DAY) {
            secs -= TIME_SECONDS_PER_DAY;
        }
        res.second = secs % 60;
        res.minute = (secs / 60) % 60;
        res.hour = (secs / 3600) % 24;

    }

    double J = time.days + ((double)(time.day_secs + TIME_SECONDS_PER_DAY/2))/TIME_SECONDS_PER_DAY;

    const int y = 4716, j = 1401, m=2, n = 12, r=4, p=1461, v = 3, u = 5, s = 153, w = 2, B = 274277, C = -38;
    int f = J + j + (((int)(4*J + B) / 146097) * 3) / 4 + C;
    int e = r * f + v;
    int g = (e%p) / r;
    int h = u*g + w;
    res.day = ((h%s) / u) + 1;
    res.month = ((h/s + m)%n) + 1;
    res.year = (e/p) - y + (n + m - res.month) / n;

    return res;
}

// Composit
time_gregorian_type time_convert_unix_to_gregorian(time_unix_type ts)
{
    return time_convert_julian_to_gregorian(time_convert_unix_to_julian(ts));
}
