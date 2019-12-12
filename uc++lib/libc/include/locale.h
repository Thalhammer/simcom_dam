#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define LC_ALL       0
#define LC_COLLATE   1
#define LC_CTYPE     2
#define LC_MESSAGES  3
#define LC_MONETARY  4
#define LC_NUMERIC   5
#define LC_TIME      6

typedef struct lconv {
    const char* decimal_point;
    const char* thousands_sep;
    const char* grouping;
    const char* int_curr_symbol;
    const char* currency_symbol;
    const char* mon_decimal_point;
    const char* mon_thousands_sep;
    const char* mon_grouping;
    const char* positive_sign;
    const char* negative_sign;
    char frac_digits;
    char p_cs_precedes;
    char n_cs_precedes;
    char p_sep_by_space;
    char n_sep_by_space;
    char p_sign_posn;
    char n_sign_posn;
    char int_frac_digits;
    char int_p_cs_precedes;
    char int_n_cs_precedes;
    char int_p_sep_by_space;
    char int_n_sep_by_space;
    char int_p_sign_posn;
    char int_n_sign_posn;
} lconv;

// NOTE: We only support "C" as of now, so the below is a stub
// NOTE: Return value should be "char*" but "const char*" makes the implementation easier
extern const char* setlocale(int category, const char* locale);
// NOTE: Return value should be "struct lconv*" but "const struct lconv*" makes the implementation easier
extern const struct lconv* localeconv(void);

#ifdef __cplusplus
}
#endif