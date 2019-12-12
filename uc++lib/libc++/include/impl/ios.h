#pragma once
#include <cstddef>

// TODO: Only numeric types yet, alot of work still needed
namespace std {
	// Need rework
	typedef size_t streamoff;
	typedef size_t streampos;
	typedef size_t u16streampos;
	typedef size_t u32streampos;
	typedef size_t wstreampos;

	typedef size_t wint_t;
}