#pragma once

#ifndef __cplusplus
#ifndef bool
#define bool        _Bool
#endif
#ifndef true
#define true        1
#endif
#ifndef false
#define false        0
#endif
#else
#ifndef _Bool
#define _Bool        bool
#endif
#endif

#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined 1
#endif