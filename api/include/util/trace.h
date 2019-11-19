#pragma once
#include "util/debug.h"

#define TRACE(...) debug_printf("[" TRACE_TAG "] " __VA_ARGS__)
