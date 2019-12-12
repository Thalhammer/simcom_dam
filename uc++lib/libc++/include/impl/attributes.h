#pragma once
#ifdef __has_cpp_attribute
	#if __has_cpp_attribute(nodiscard) // TODO
		#define NODISCARD [[nodiscard]]
	#endif
#endif
#ifndef NODISCARD
#ifdef __cplusplus
	#define NODISCARD [[gnu::warn_unused_result]]
#else
	#define NODISCARD
#endif
#endif