typedef __SIZE_TYPE__ size_t;

#ifndef __cplusplus
#define NULL ((void *)0)
#else   /* C++ */
#define NULL 0
#endif  /* C++ */

#define offsetof(TYPE, MEMBER) __builtin_offsetof (TYPE, MEMBER)

#if defined(__cplusplus) && __cplusplus >= 201103L
  typedef decltype(nullptr) nullptr_t;
#endif