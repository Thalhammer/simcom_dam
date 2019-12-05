#pragma once

typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __SIZE_TYPE__ size_t;
#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;
#endif

#ifndef __cplusplus
#define NULL ((void *)0)
#else   /* C++ */
#define NULL 0
#endif  /* C++ */

#define offsetof(TYPE, MEMBER) __builtin_offsetof (TYPE, MEMBER)

#if defined(__cplusplus) && __cplusplus >= 201103L
  typedef decltype(nullptr) nullptr_t;
#endif

typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
} max_align_t;

#if defined(__cplusplus)
namespace std {
  using ptrdiff_t = ::ptrdiff_t;
  using size_t = ::size_t;
}
#endif