#pragma once

#ifdef __cplusplus
extern "C" {
#endif
extern int* __get_errno_location();
#ifdef __cplusplus
}
#endif

#define errno (*(__get_errno_location()))

// NOTE: This is not defined but we follow the linux numbering to portability
#define EDOM            33      /* Math argument out of domain of func */
#define ERANGE          34      /* Math result not representable */
#define EILSEQ          84      /* Illegal byte sequence */