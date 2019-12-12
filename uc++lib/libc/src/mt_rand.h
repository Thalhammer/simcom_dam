#pragma once
#include <stddef.h>

namespace libc_impl {
    class mt_rand {
        constexpr static int STATE_VECTOR_LENGTH = 624;
        constexpr static int STATE_VECTOR_M = 397;

        unsigned long m_mt[STATE_VECTOR_LENGTH];
        int m_index;
    public:
        void seed(unsigned long seed) noexcept;
        unsigned long operator()() noexcept;
    };
}