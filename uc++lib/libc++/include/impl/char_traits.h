#pragma once
#include "ios.h"
#include <cstring>
#include <cstdint>

namespace std {
	template<class charT> struct char_traits;
	template<> struct char_traits<char>;
	template<> struct char_traits<char16_t>;
	template<> struct char_traits<char32_t>;
	template<> struct char_traits<wchar_t>;

	template<> struct char_traits<char> {
		using char_type = char;
		using int_type = int;
		using off_type = streamoff;
		using pos_type = streampos;
		//using state_type = mbstate_t;
		static constexpr void assign(char_type& c1, const char_type& c2) noexcept { c1 = c2; }
		static constexpr bool eq(char_type c1, char_type c2) noexcept { return c1 == c2; }
		static constexpr bool lt(char_type c1, char_type c2) noexcept { return c1 < c2; }
		static constexpr int compare(const char_type* s1, const char_type* s2, size_t n) {
			for(size_t i=0; i<n; i++) {
				int r= to_int_type(s1[i]) - to_int_type(s2[i]);
				if(r != 0) return r;
			}
			return 0;
		}
		static constexpr size_t length(const char_type* s) {
			size_t len = 0;
			while(s[len] != 0x00) len++;
			return len;
		}
		static constexpr const char_type* find(const char_type* s, size_t n, const char_type& a) {
			for(auto end = s + n; s != end; s++) {
				if(*s == a) return s;
			}
			return NULL;
		}
		static char_type* move(char_type* dest, const char_type* src, size_t n) {
			if(dest < src) {
				for(size_t i=0; i < n; i++) {
					dest[i] = src[i];
				}
			} else {
				for(size_t i=n; i != 0; i--) {
					dest[i-1] = src[i-1];
				}
			}
			return dest;
		}
		static char_type* copy(char_type* dest, const char_type* src, size_t n) {
			return move(dest, src, n);
		}
		static char_type* assign(char_type* s, size_t n, char_type a) { for(size_t i=0; i<n; i++) s[i] = a; return s; }
		static constexpr int_type not_eof(int_type c) noexcept { if(eq_int_type(c, eof())) return 0x00; else return c; }
		static constexpr char_type to_char_type(int_type c) noexcept { return (char_type)c; }
		static constexpr int_type to_int_type(char_type c) noexcept { return c; }
		static constexpr bool eq_int_type(int_type c1, int_type c2) noexcept { return c1 == c2; }
		static constexpr int_type eof() noexcept { return -1; }
	};
	
	template<> struct char_traits<char16_t> {
		using char_type = char16_t;
		using int_type = uint_least16_t;
		using off_type = streamoff;
		using pos_type = u16streampos;
		//using state_type = mbstate_t;
		static constexpr void assign(char_type& c1, const char_type& c2) noexcept { c1 = c2; }
		static constexpr bool eq(char_type c1, char_type c2) noexcept { return c1 == c2; }
		static constexpr bool lt(char_type c1, char_type c2) noexcept { return c1 < c2; }
		static constexpr int compare(const char_type* s1, const char_type* s2, size_t n) {
			for(size_t i=0; i<n; i++) {
				int r= to_int_type(s1[i]) - to_int_type(s2[i]);
				if(r != 0) return r;
			}
		}
		static constexpr size_t length(const char_type* s) {
			size_t len = 0;
			while(s[len] != 0x00) len++;
			return len;
		}
		static constexpr const char_type* find(const char_type* s, size_t n, const char_type& a) {
			for(auto end = s + n; s != end; s++) {
				if(*s == a) return s;
			}
			return NULL;
		}
		static char_type* move(char_type* dest, const char_type* src, size_t n) {
			if(dest < src) {
				for(size_t i=0; i < n; i++) {
					dest[i] = src[i];
				}
			} else {
				for(size_t i=n; i != 0; i--) {
					dest[i-1] = src[i-1];
				}
			}
			return dest;
		}
		static char_type* copy(char_type* dest, const char_type* src, size_t n) {
			return move(dest, src, n);
		}
		static char_type* assign(char_type* s, size_t n, char_type a) { for(size_t i=0; i<n; i++) s[i] = a; return s; }
		static constexpr int_type not_eof(int_type c) noexcept { if(eq_int_type(c, eof())) return 0x00; else return c; }
		static constexpr char_type to_char_type(int_type c) noexcept { return (char_type)c; }
		static constexpr int_type to_int_type(char_type c) noexcept { return c; }
		static constexpr bool eq_int_type(int_type c1, int_type c2) noexcept { return c1 == c2; }
		static constexpr int_type eof() noexcept { return -1; }
	};
	
	template<> struct char_traits<char32_t> {
		using char_type = char32_t;
		using int_type = uint_least32_t;
		using off_type = streamoff;
		using pos_type = u32streampos;
		//using state_type = mbstate_t;
		static constexpr void assign(char_type& c1, const char_type& c2) noexcept { c1 = c2; }
		static constexpr bool eq(char_type c1, char_type c2) noexcept { return c1 == c2; }
		static constexpr bool lt(char_type c1, char_type c2) noexcept { return c1 < c2; }
		static constexpr int compare(const char_type* s1, const char_type* s2, size_t n) {
			for(size_t i=0; i<n; i++) {
				int r= to_int_type(s1[i]) - to_int_type(s2[i]);
				if(r != 0) return r;
			}
		}
		static constexpr size_t length(const char_type* s) {
			size_t len = 0;
			while(s[len] != 0x00) len++;
			return len;
		}
		static constexpr const char_type* find(const char_type* s, size_t n, const char_type& a) {
			for(auto end = s + n; s != end; s++) {
				if(*s == a) return s;
			}
			return NULL;
		}
		static char_type* move(char_type* dest, const char_type* src, size_t n) {
			if(dest < src) {
				for(size_t i=0; i < n; i++) {
					dest[i] = src[i];
				}
			} else {
				for(size_t i=n; i != 0; i--) {
					dest[i-1] = src[i-1];
				}
			}
			return dest;
		}
		static char_type* copy(char_type* dest, const char_type* src, size_t n) {
			return move(dest, src, n);
		}
		static char_type* assign(char_type* s, size_t n, char_type a) { for(size_t i=0; i<n; i++) s[i] = a; return s; }
		static constexpr int_type not_eof(int_type c) noexcept { if(eq_int_type(c, eof())) return 0x00; else return c; }
		static constexpr char_type to_char_type(int_type c) noexcept { return (char_type)c; }
		static constexpr int_type to_int_type(char_type c) noexcept { return c; }
		static constexpr bool eq_int_type(int_type c1, int_type c2) noexcept { return c1 == c2; }
		static constexpr int_type eof() noexcept { return -1; }
	};
	
	template<> struct char_traits<wchar_t> {
		using char_type = wchar_t;
		using int_type = wint_t;
		using off_type = streamoff;
		using pos_type = wstreampos;
		//using state_type = mbstate_t;
		static constexpr void assign(char_type& c1, const char_type& c2) noexcept { c1 = c2; }
		static constexpr bool eq(char_type c1, char_type c2) noexcept { return c1 == c2; }
		static constexpr bool lt(char_type c1, char_type c2) noexcept { return c1 < c2; }
		static constexpr int compare(const char_type* s1, const char_type* s2, size_t n) {
			for(size_t i=0; i<n; i++) {
				int r= to_int_type(s1[i]) - to_int_type(s2[i]);
				if(r != 0) return r;
			}
		}
		static constexpr size_t length(const char_type* s) {
			size_t len = 0;
			while(s[len] != 0x00) len++;
			return len;
		}
		static constexpr const char_type* find(const char_type* s, size_t n, const char_type& a) {
			for(auto end = s + n; s != end; s++) {
				if(*s == a) return s;
			}
			return NULL;
		}
		static char_type* move(char_type* dest, const char_type* src, size_t n) {
			if(dest < src) {
				for(size_t i=0; i < n; i++) {
					dest[i] = src[i];
				}
			} else {
				for(size_t i=n; i != 0; i--) {
					dest[i-1] = src[i-1];
				}
			}
			return dest;
		}
		static char_type* copy(char_type* dest, const char_type* src, size_t n) {
			return move(dest, src, n);
		}
		static char_type* assign(char_type* s, size_t n, char_type a) { for(size_t i=0; i<n; i++) s[i] = a; return s; }
		static constexpr int_type not_eof(int_type c) noexcept { if(eq_int_type(c, eof())) return 0x00; else return c; }
		static constexpr char_type to_char_type(int_type c) noexcept { return (char_type)c; }
		static constexpr int_type to_int_type(char_type c) noexcept { return c; }
		static constexpr bool eq_int_type(int_type c1, int_type c2) noexcept { return c1 == c2; }
		static constexpr int_type eof() noexcept { return -1; }
	};
}