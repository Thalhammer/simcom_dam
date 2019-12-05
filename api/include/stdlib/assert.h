#pragma once

#ifdef __cplusplus
extern "C" void abort_with_message(const char*);
#else
extern void abort_with_message(const char*);
#endif

#define xstr(s) str(s)
#define str(s) #s

#define assert(x) \
    if(!(x)) abort_with_message("Assertion \"" #x "\" failed! file: \"" __FILE__ "\" line:" xstr(__LINE__));
