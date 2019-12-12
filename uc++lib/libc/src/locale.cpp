#include "locale.h"
#include "string.h"
#include "limits.h"

extern "C" {

static struct lconv g_local_C = {
    .decimal_point = ".",
    .thousands_sep = "",
    .grouping = "",
    .int_curr_symbol = "",
    .currency_symbol = "",
    .mon_decimal_point = "",
    .mon_thousands_sep = "",
    .mon_grouping = "",
    .positive_sign = "",
    .negative_sign = "",
    .frac_digits = CHAR_MAX,
    .p_cs_precedes = CHAR_MAX,
    .n_cs_precedes = CHAR_MAX,
    .p_sep_by_space = CHAR_MAX,
    .n_sep_by_space = CHAR_MAX,
    .p_sign_posn = CHAR_MAX,
    .n_sign_posn = CHAR_MAX,
    .int_frac_digits = CHAR_MAX,
    .int_p_cs_precedes = CHAR_MAX,
    .int_n_cs_precedes = CHAR_MAX,
    .int_p_sep_by_space = CHAR_MAX,
    .int_n_sep_by_space = CHAR_MAX,
    .int_p_sign_posn = CHAR_MAX,
    .int_n_sign_posn = CHAR_MAX
};

const char* setlocale(int category, const char* locale) {
    if(category < 0 || category > 6) return nullptr;
    if(locale == nullptr || strcmp(locale, "C") == 0 || strcmp(locale, "") == 0) return "C";
    return nullptr;
}

const struct lconv* localeconv(void) {
    return &g_local_C;
}

}