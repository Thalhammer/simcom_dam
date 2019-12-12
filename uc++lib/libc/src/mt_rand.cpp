#include "mt_rand.h"

#define UPPER_MASK		0x80000000
#define LOWER_MASK		0x7fffffff
#define TEMPERING_MASK_B	0x9d2c5680
#define TEMPERING_MASK_C	0xefc60000

namespace libc_impl {
    void mt_rand::seed(unsigned long seed) noexcept {
        /* set initial seeds to mt[STATE_VECTOR_LENGTH] using the generator
         * from Line 25 of Table 1 in: Donald Knuth, "The Art of Computer
         * Programming," Vol. 2 (2nd Ed.) pp.102.
         */
        m_mt[0] = seed & 0xffffffff;
        for(m_index = 1; m_index < STATE_VECTOR_LENGTH; m_index++) {
            m_mt[m_index] = (6069 * m_mt[m_index - 1]) & 0xffffffff;
        }
    }

    unsigned long mt_rand::operator()() noexcept {
        unsigned long y;
        static constexpr unsigned long mag[2] = {0x0, 0x9908b0df}; /* mag[x] = x * 0x9908b0df for x = 0,1 */
        if(m_index >= STATE_VECTOR_LENGTH || m_index < 0) {
            /* generate STATE_VECTOR_LENGTH words at a time */
            int kk;
            if(m_index >= STATE_VECTOR_LENGTH + 1 || m_index < 0) {
                seed(4357);
            }
            for(kk=0; kk<STATE_VECTOR_LENGTH-STATE_VECTOR_M; kk++) {
                y = (m_mt[kk] & UPPER_MASK) | (m_mt[kk+1] & LOWER_MASK);
                m_mt[kk] = m_mt[kk+STATE_VECTOR_M] ^ (y >> 1) ^ mag[y & 0x1];
            }
            for(; kk<STATE_VECTOR_LENGTH-1; kk++) {
                y = (m_mt[kk] & UPPER_MASK) | (m_mt[kk+1] & LOWER_MASK);
                m_mt[kk] = m_mt[kk+(STATE_VECTOR_M-STATE_VECTOR_LENGTH)] ^ (y >> 1) ^ mag[y & 0x1];
            }
            y = (m_mt[STATE_VECTOR_LENGTH-1] & UPPER_MASK) | (m_mt[0] & LOWER_MASK);
            m_mt[STATE_VECTOR_LENGTH-1] = m_mt[STATE_VECTOR_M-1] ^ (y >> 1) ^ mag[y & 0x1];
            m_index = 0;
        }
        y = m_mt[m_index++];
        y ^= (y >> 11);
        y ^= (y << 7) & TEMPERING_MASK_B;
        y ^= (y << 15) & TEMPERING_MASK_C;
        y ^= (y >> 18);
        return y;
    }
}