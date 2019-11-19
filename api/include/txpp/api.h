#pragma once

#ifndef __cplusplus
#error "This is a c++ library"
#endif

#include "threadx_api/txm_module.h"

//#undef txm_module_object_allocate

template<typename T>
inline UINT txm_module_object_allocate(T** o) {
    return ((UINT)(_txm_module_kernel_call_dispatcher)(TXM_MODULE_OBJECT_ALLOCATE_CALL, (ULONG) o, (ULONG) sizeof(T), (ULONG) 0));
}