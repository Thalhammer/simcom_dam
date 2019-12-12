#pragma once
#include <cstdint>

class I2C_Master {
    void* m_handle;
    uint32_t m_speed;
    uint8_t m_port;
    bool m_debug_enabled;
    bool m_at_exit_called;
public:
    constexpr I2C_Master(uint8_t port, uint32_t speed = 400000) noexcept
        : m_handle(nullptr), m_speed(speed), m_port(port), m_debug_enabled(false), m_at_exit_called(false)
    {}

    I2C_Master(const I2C_Master&) = delete;
    I2C_Master& operator=(const I2C_Master&) = delete;
    I2C_Master(I2C_Master&&) = delete;
    I2C_Master& operator=(I2C_Master&&) = delete;

    void set_debug_enabled(bool debug) noexcept { m_debug_enabled = debug; }
    
    void set_clock_speed(uint32_t speed) noexcept { m_speed = speed; }

    bool begin() noexcept;
    bool end() noexcept;

    bool read(uint8_t slave, uint8_t* data, uint32_t len) noexcept;
    bool write(uint8_t slave, const uint8_t* data, uint32_t len) noexcept;

    bool power_on() noexcept;
    bool power_off() noexcept;
};

extern I2C_Master Wire;