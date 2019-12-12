#pragma once
#include <cstdint>

class GPIO {
    uint16_t m_tlmm_id = 0;
    int m_pin = 0;
    bool m_is_initialized = false;
    bool m_debug_enabled = false;
public:
    enum class pull {
        none = 0x00,
        down = 0x01,
        keep = 0x02,
        up = 0x03
    };
    constexpr GPIO(int pin)
        : m_tlmm_id(0), m_pin(pin), m_is_initialized(false), m_debug_enabled(false)
    {}
    /*~GPIO() {
        if(m_is_initialized) end();
    }*/
    GPIO(const GPIO&) = delete;
    GPIO& operator=(const GPIO&) = delete;
    GPIO(GPIO&&) = delete;
    GPIO& operator=(GPIO&&) = delete;

    void set_debug_enabled(bool debug) noexcept { m_debug_enabled = debug; }
    
    bool begin() noexcept;
    bool end() noexcept;

    bool reconfigure(bool is_out, uint32_t function = 0, pull p = pull::keep) noexcept;

    bool drive(bool high) noexcept;
    bool read(bool* is_high) noexcept;
};

extern GPIO gpio2;
extern GPIO gpio3;
extern GPIO gpio4;
extern GPIO netlight;