#pragma once
#include <stdint.h>

class I2C_Master;
class BME280 {
    struct Calibration_Data
    {
        uint16_t dig_T1;
        int16_t  dig_T2;
        int16_t  dig_T3;
        
        uint16_t dig_P1;
        int16_t  dig_P2;
        int16_t  dig_P3;
        int16_t  dig_P4;
        int16_t  dig_P5;
        int16_t  dig_P6;
        int16_t  dig_P7;
        int16_t  dig_P8;
        int16_t  dig_P9;
        
        uint8_t  dig_H1;
        int16_t  dig_H2;
        uint8_t  dig_H3;
        int16_t  dig_H4;
        int16_t  dig_H5;
        int8_t   dig_H6;
    };

    I2C_Master* m_i2c;
    uint8_t m_addr;
    bool m_debug_enabled;
    bool m_is_initialized;
    struct Calibration_Data m_calibration;

    float m_temperature;
    float m_pressure;
    float m_humidity;

    bool read8(uint8_t reg, uint8_t* out) noexcept;
    bool read16(uint8_t reg, uint16_t* out) noexcept;
    bool read16_LE(uint8_t reg, uint16_t* out) noexcept;
    bool write8(uint8_t reg, uint8_t val) noexcept;
    bool read24(uint8_t reg, uint32_t* out) noexcept;
    bool read_calibration_data() noexcept;

    bool reset_device() noexcept;

    float calculate_temperature(uint8_t a, uint8_t b, uint8_t c, int32_t* t_fine) noexcept;
    float calculate_pressure(uint8_t a, uint8_t b, uint8_t c, int32_t t_fine) noexcept;
    float calculate_humidity(uint8_t a, uint8_t b, int32_t t_fine) noexcept;
public:
    constexpr BME280(uint8_t slave = 0x76, I2C_Master* i2c = nullptr) noexcept
        : m_i2c(i2c), m_addr(slave), m_debug_enabled(false), m_is_initialized(false), m_calibration({}), m_temperature(0.0), m_pressure(0.0), m_humidity(0.0)
    {}

    BME280(const BME280&) = delete;
    BME280& operator=(const BME280&) = delete;
    BME280(BME280&&) = delete;
    BME280& operator=(BME280&&) = delete;

    void set_debug_enabled(bool debug) noexcept { m_debug_enabled = debug; }

    bool begin(uint8_t slave = 0x76, I2C_Master* i2c = nullptr) noexcept;
    bool begin(I2C_Master* i2c) noexcept { return begin(0x76, i2c); }

    bool is_initialized() const noexcept { return m_is_initialized; }

    bool read_sensors() noexcept;

    float get_temperature() const noexcept { return m_temperature; }
    float get_pressure() const noexcept { return m_pressure; }
    float get_humidity() const noexcept { return m_humidity; }

    bool read_status(uint8_t* status) noexcept;
};