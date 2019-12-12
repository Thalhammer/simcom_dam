#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>

class AsmBuilder {
    uint8_t* m_buffer;
    size_t m_buffer_size;
    size_t m_offset;

    bool add_instruction(uint32_t instr) noexcept {
        if(m_buffer_size - m_offset < 4) return false;
        memcpy(&m_buffer[m_offset], &instr, 4);
        m_offset += 4;
        return true;
    }
public:
    struct reg { uint8_t id; private: constexpr reg(uint8_t v) : id(v) {} friend class AsmBuilder; };

    static reg r0;
    static reg r1;
    static reg r2;
    static reg r3;
    static reg r4;
    static reg r5;
    static reg r6;
    static reg r7;
    static reg r8;
    static reg r9;
    static reg r10;
    static reg r11;
    static reg r12;
    static reg r13;
    static reg r14;
    static reg r15;
    static reg fp;
    static reg ip;
    static reg sp;
    static reg lr;
    static reg pc;

    constexpr AsmBuilder(uint8_t* ptr, size_t size)
        : m_buffer(ptr), m_buffer_size(size), m_offset(0)
    {}

    AsmBuilder(const AsmBuilder&) = delete;
    AsmBuilder(AsmBuilder&&) = delete;
    AsmBuilder& operator=(const AsmBuilder&) = delete;
    AsmBuilder& operator=(AsmBuilder&&) = delete;

    size_t get_length() const noexcept { return m_offset; }

    bool sub_reg_i(reg dest_reg, reg src_reg, uint8_t val) noexcept {
        dest_reg.id &= 0xf;
        src_reg.id &= 0xf;
        uint32_t instr = 0xe2400000;
        instr |= (src_reg.id) << 16;
        instr |= (dest_reg.id) << 12;
        instr |= val;
        return add_instruction(instr);
    }

    bool add_reg_i(reg dest_reg, reg src_reg, uint8_t val) noexcept {
        dest_reg.id &= 0xf;
        src_reg.id &= 0xf;
        uint32_t instr = 0xe2800000;
        instr |= (src_reg.id) << 16;
        instr |= (dest_reg.id) << 12;
        instr |= val;
        return add_instruction(instr);
    }

    bool bdt(reg basereg, uint16_t bitmap, bool l_bit, bool p_bit, bool u_bit , bool s_bit, bool w_bit) noexcept {
        basereg.id &= 0xf;
        uint32_t instr = 0xe8000000;
        instr |= p_bit ? 0x01000000 : 0x00000000;
        instr |= u_bit ? 0x00800000 : 0x00000000;
        instr |= s_bit ? 0x00400000 : 0x00000000;
        instr |= w_bit ? 0x00200000 : 0x00000000;
        instr |= l_bit ? 0x00100000 : 0x00000000;
        instr |= basereg.id << 16;
        instr |= bitmap;
        return add_instruction(instr);
    }

    bool dp(bool i_bit, uint8_t opcode, bool s_bit, reg rdest, reg rop1, uint8_t op2_shift, uint8_t op2) noexcept {
        opcode &= 0xf;
        rdest.id &= 0xf;
        rop1.id &= 0xf;
        uint32_t instr = 0xe0000000;
        instr |= i_bit ? 0x02000000 : 0x00000000;
        instr |= ((uint32_t)opcode) << 21;
        instr |= s_bit ? 0x00100000 : 0x00000000;
        instr |= ((uint32_t)rop1.id) << 16;
        instr |= ((uint32_t)rdest.id) << 12;
        if(i_bit) {
            instr |= ((uint32_t)(op2_shift & 0x0f)) << 8;
            instr |= op2;
        } else {
            instr |= ((uint32_t)op2_shift) << 4;
            instr |= op2 & 0x0f;
        }
        return add_instruction(instr);
    }

    bool stm(reg basereg, uint16_t bitmap, bool p_bit = false, bool u_bit = true, bool s_bit = false, bool w_bit = false) noexcept {
        return bdt(basereg, bitmap, false, p_bit, u_bit, s_bit, w_bit);
    }

    bool ldm(reg basereg, uint16_t bitmap, bool p_bit = false, bool u_bit = true, bool s_bit = false, bool w_bit = false) noexcept {
        return bdt(basereg, bitmap, true, p_bit, u_bit, s_bit, w_bit);
    }

    bool stmia(reg basereg, uint16_t bitmap, bool s_bit = false, bool w_bit = false) noexcept {
        return stm(basereg, bitmap, false, true, s_bit, w_bit);
    }

    bool stmib(reg basereg, uint16_t bitmap, bool s_bit = false, bool w_bit = false) noexcept {
        return stm(basereg, bitmap, true, true, s_bit, w_bit);
    }

    bool stmda(reg basereg, uint16_t bitmap, bool s_bit = false, bool w_bit = false) noexcept {
        return stm(basereg, bitmap, false, false, s_bit, w_bit);
    }

    bool stmdb(reg basereg, uint16_t bitmap, bool s_bit = false, bool w_bit = false) noexcept {
        return stm(basereg, bitmap, true, false, s_bit, w_bit);
    }

    bool ldmia(reg basereg, uint16_t bitmap, bool s_bit = false, bool w_bit = false) noexcept {
        return ldm(basereg, bitmap, false, true, s_bit, w_bit);
    }

    bool ldmib(reg basereg, uint16_t bitmap, bool s_bit = false, bool w_bit = false) noexcept {
        return ldm(basereg, bitmap, true, true, s_bit, w_bit);
    }

    bool ldmda(reg basereg, uint16_t bitmap, bool s_bit = false, bool w_bit = false) noexcept {
        return ldm(basereg, bitmap, false, false, s_bit, w_bit);
    }

    bool ldmdb(reg basereg, uint16_t bitmap, bool s_bit = false, bool w_bit = false) noexcept {
        return ldm(basereg, bitmap, true, false, s_bit, w_bit);
    }

    bool push(reg reg) noexcept {
        return stmdb(13, (1 << reg.id), false, true);
    }

    bool pop(reg reg) noexcept {
        return ldmia(13, (1 << reg.id), false, true);
    }

    bool movw(reg reg, uint16_t value) noexcept {
        return dp(true, 0b1000, false, reg, value >> 12, value >> 8, value);
    }

    bool movt(reg reg, uint16_t value) noexcept {
        return dp(true, 0b1010, false, reg, value >> 12, value >> 8, value);
    }

    bool mov(reg reg, uint32_t value) noexcept {
        if(!movw(reg, value & 0xffff)) return false;
        return movt(reg, (value >> 16) & 0xffff);
    }

    bool mov(reg dest, reg src) noexcept {
        return dp(false, 0b1101, 0, dest, 0, 0, src.id);
    }

    bool branch_exchange(reg reg) noexcept {
        uint32_t instr = 0xe12fff10;
        instr |= reg.id & 0xf;
        return add_instruction(instr);
    }

    bool branch(void* target, bool link = false) noexcept {
        int32_t jmp_offset = ((uintptr_t)target) - ((uintptr_t)&m_buffer[m_offset]);
        uint32_t instr = 0xea000000;
        instr |= link ? 0x01000000 : 0x00000000;
        instr |= (((jmp_offset - 8) >> 2) & 0x00ffffff);
        return add_instruction(instr);
    }

    template<typename T>
    bool branch(T* target, bool link = false) noexcept {
        return branch(reinterpret_cast<void*>(target), link);
    }

    template<typename T>
    bool branch_link(T* target) noexcept {
        return branch(reinterpret_cast<void*>(target), true);
    }
};