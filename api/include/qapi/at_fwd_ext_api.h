#pragma once
#include <stdint.h>

/*
This header was not part of qapi but was referenced by it.
Everything in here is based on guessing. We tried our best,
but it might not be accurate.
*/

typedef void(*at_fwd_cb_type)(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
