#include "util/BME280.h"
#include "util/I2C_Master.h"
#include "util/trace.h"

#define TRACE_TAG "BME280"

#define    BME280_DIG_T1_REG   0x88
#define    BME280_DIG_T2_REG   0x8A
#define    BME280_DIG_T3_REG   0x8C
#define    BME280_DIG_P1_REG   0x8E
#define    BME280_DIG_P2_REG   0x90
#define    BME280_DIG_P3_REG   0x92
#define    BME280_DIG_P4_REG   0x94
#define    BME280_DIG_P5_REG   0x96
#define    BME280_DIG_P6_REG   0x98
#define    BME280_DIG_P7_REG   0x9A
#define    BME280_DIG_P8_REG   0x9C
#define    BME280_DIG_P9_REG   0x9E
    
    
#define    BME280_DIG_H1_REG   0xA1
#define    BME280_DIG_H2_REG   0xE1
#define    BME280_DIG_H3_REG   0xE3
#define    BME280_DIG_H4_REG   0xE4
#define    BME280_DIG_H5_REG   0xE5
#define    BME280_DIG_H6_REG   0xE7
    
    
#define    BME280_REGISTER_CHIPID       0xD0
#define    BME280_REGISTER_VERSION      0xD1
#define    BME280_REGISTER_SOFTRESET    0xE0
#define    BME280_REGISTER_CAL26        0xE1
#define    BME280_REGISTER_CONTROLHUMID     0xF2
#define    BME280_REGISTER_CONTROL          0xF4
#define    BME280_REGISTER_CONFIG           0xF5
#define    BME280_REGISTER_PRESSUREDATA     0xF7
#define    BME280_REGISTER_TEMPDATA         0xFA
#define    BME280_REGISTER_HUMIDDATA        0xFD

bool BME280::read8(uint8_t reg, uint8_t* out) noexcept {
    if(!m_i2c->write(m_addr, &reg, 1)) return false;
    return m_i2c->read(m_addr, out, 1);
}

bool BME280::read16(uint8_t reg, uint16_t* out) noexcept {
    if(!m_i2c->write(m_addr, &reg, 1)) return false;
    auto ptr = reinterpret_cast<uint8_t*>(out);
    if(!m_i2c->read(m_addr, ptr, 2)) return false;
    auto t = ptr[1];
    ptr[1] = ptr[0];
    ptr[0] = t;
    return true;
}

bool BME280::read16_LE(uint8_t reg, uint16_t* out) noexcept{
    if(!m_i2c->write(m_addr, &reg, 1)) return false;
    auto ptr = reinterpret_cast<uint8_t*>(out);
    if(!m_i2c->read(m_addr, ptr, 2)) return false;
    return true;
}

bool BME280::read24(uint8_t reg, uint32_t* out) noexcept {
    if(!m_i2c->write(m_addr, &reg, 1)) return false;
    uint8_t buf[3];
    if(!m_i2c->read(m_addr, buf, 3)) return false;
    *out = buf[0];
    *out = (*out << 8) | buf[1];
    *out = (*out << 8) | buf[2];
    return true;
}

bool BME280::write8(uint8_t reg, uint8_t val) noexcept {
    uint8_t data[2];
    data[0] = reg;
    data[1] = val;
    return m_i2c->write(m_addr, data, 2);
}

bool BME280::read_calibration_data() noexcept {
    if(!read16_LE(BME280_DIG_T1_REG, &m_calibration.dig_T1)) return false;
    if(!read16_LE(BME280_DIG_T2_REG, reinterpret_cast<uint16_t*>(&m_calibration.dig_T2))) return false;
    if(!read16_LE(BME280_DIG_T3_REG, reinterpret_cast<uint16_t*>(&m_calibration.dig_T3))) return false;
    if(!read16_LE(BME280_DIG_P1_REG, &m_calibration.dig_P1)) return false;
    if(!read16_LE(BME280_DIG_P2_REG, reinterpret_cast<uint16_t*>(&m_calibration.dig_P2))) return false;
    if(!read16_LE(BME280_DIG_P3_REG, reinterpret_cast<uint16_t*>(&m_calibration.dig_P3))) return false;
    if(!read16_LE(BME280_DIG_P4_REG, reinterpret_cast<uint16_t*>(&m_calibration.dig_P4))) return false;
    if(!read16_LE(BME280_DIG_P5_REG, reinterpret_cast<uint16_t*>(&m_calibration.dig_P5))) return false;
    if(!read16_LE(BME280_DIG_P6_REG, reinterpret_cast<uint16_t*>(&m_calibration.dig_P6))) return false;
    if(!read16_LE(BME280_DIG_P7_REG, reinterpret_cast<uint16_t*>(&m_calibration.dig_P7))) return false;
    if(!read16_LE(BME280_DIG_P8_REG, reinterpret_cast<uint16_t*>(&m_calibration.dig_P8))) return false;
    if(!read16_LE(BME280_DIG_P9_REG, reinterpret_cast<uint16_t*>(&m_calibration.dig_P9))) return false;
    if(!read8(BME280_DIG_H1_REG, &m_calibration.dig_H1)) return false;
    if(!read16_LE(BME280_DIG_H2_REG, reinterpret_cast<uint16_t*>(&m_calibration.dig_H2))) return false;
    if(!read8(BME280_DIG_H3_REG, &m_calibration.dig_H3)) return false;
    uint8_t temp, temp2;
    if(!read8(BME280_DIG_H4_REG, &temp)) return false;
    if(!read8(BME280_DIG_H4_REG + 1, &temp2)) return false;
    m_calibration.dig_H4 = (temp << 4) | (temp2 & 0xF);
    if(!read8(BME280_DIG_H5_REG, &temp)) return false;
    if(!read8(BME280_DIG_H5_REG + 1, &temp2)) return false;
    m_calibration.dig_H5 = (temp2 << 4) | (temp >> 4);
    if(!read8(BME280_DIG_H6_REG, reinterpret_cast<uint8_t*>(&m_calibration.dig_H6))) return false;
    if(m_debug_enabled) {
        TRACE("dig_T1 = %u\r\n", m_calibration.dig_T1);
        TRACE("dig_T2 = %d\r\n", m_calibration.dig_T2);
        TRACE("dig_T3 = %d\r\n", m_calibration.dig_T3);
        TRACE("dig_P1 = %u\r\n", m_calibration.dig_P1);
        TRACE("dig_P2 = %d\r\n", m_calibration.dig_P2);
        TRACE("dig_P3 = %d\r\n", m_calibration.dig_P3);
        TRACE("dig_P4 = %d\r\n", m_calibration.dig_P4);
        TRACE("dig_P5 = %d\r\n", m_calibration.dig_P5);
        TRACE("dig_P6 = %d\r\n", m_calibration.dig_P6);
        TRACE("dig_P7 = %d\r\n", m_calibration.dig_P7);
        TRACE("dig_P8 = %d\r\n", m_calibration.dig_P8);
        TRACE("dig_P9 = %d\r\n", m_calibration.dig_P9);
        TRACE("dig_H1 = %u\r\n", m_calibration.dig_H1);
        TRACE("dig_H2 = %d\r\n", m_calibration.dig_H2);
        TRACE("dig_H3 = %u\r\n", m_calibration.dig_H3);
        TRACE("dig_H4 = %d\r\n", m_calibration.dig_H4);
        TRACE("dig_H5 = %d\r\n", m_calibration.dig_H5);
        TRACE("dig_H6 = %d\r\n", m_calibration.dig_H6);
    }
    return true;
}

float BME280::calculate_temperature(uint8_t a, uint8_t b, uint8_t c, int32_t* t_fine) noexcept {
    int32_t adc_T = a;
    adc_T = (adc_T << 8) | b;
    adc_T = (adc_T << 8) | c;
    adc_T >>= 4;
    if(m_debug_enabled) TRACE("adc_T = %d\r\n", adc_T);
    int32_t var1 = ((((adc_T>>3) - ((int32_t)m_calibration.dig_T1 << 1))) * ((int32_t)m_calibration.dig_T2)) >> 11;
    int32_t var2 = (((((adc_T>>4) - ((int32_t)m_calibration.dig_T1)) * ((adc_T>>4) - ((int32_t)m_calibration.dig_T1))) >> 12) * ((int32_t)m_calibration.dig_T3)) >> 14;
    
    *t_fine = var1 + var2;
    if(m_debug_enabled) TRACE("t_fine = %d\r\n", *t_fine);
    return static_cast<float>((*t_fine * 5 + 128) >> 8) / 100;
}

float BME280::calculate_pressure(uint8_t a, uint8_t b, uint8_t c, int32_t t_fine) noexcept {
    int32_t adc_P = a;
    adc_P = (adc_P << 8) | b;
    adc_P = (adc_P << 8) | c;
    adc_P >>= 4;
    if(m_debug_enabled) TRACE("adc_P = %d\r\n", adc_P);
    int64_t var1 = ((int64_t)t_fine) - 128000;
    int64_t var2 = var1 * var1 * (int64_t)m_calibration.dig_P6;
    var2 = var2 + ((var1*(int64_t)m_calibration.dig_P5)<<17);
    var2 = var2 + (((int64_t)m_calibration.dig_P4)<<35);
    var1 = ((var1 * var1 * (int64_t)m_calibration.dig_P3)>>8) + ((var1 * (int64_t)m_calibration.dig_P2)<<12);
    var1 = (((((int64_t)1)<<47)+var1))*((int64_t)m_calibration.dig_P1)>>33;

    if (var1 == 0) return 0;

    int64_t p = 1048576-adc_P;
    p = (((p<<31)-var2)*3125)/var1;
    var1 = (((int64_t)m_calibration.dig_P9) * (p>>13) * (p>>13)) >> 25;
    var2 = (((int64_t)m_calibration.dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)m_calibration.dig_P7)<<4);

    return static_cast<float>(p) / 256;
}

float BME280::calculate_humidity(uint8_t a, uint8_t b, int32_t t_fine) noexcept {
    int32_t adc_H = a;
    adc_H = (adc_H << 8) | b;
    if(m_debug_enabled) TRACE("adc_H = %d\r\n", adc_H);
    int32_t v_x1_u32r;
    v_x1_u32r = (t_fine - ((int32_t)76800));
    v_x1_u32r = (((((adc_H << 14) - (((int32_t)m_calibration.dig_H4) << 20) - (((int32_t)m_calibration.dig_H5) * v_x1_u32r))
    + ((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)m_calibration.dig_H6)) >> 10) * (((v_x1_u32r * 
    ((int32_t)m_calibration.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
    ((int32_t)m_calibration.dig_H2) + 8192) >> 14));
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)m_calibration.dig_H1)) >> 4));
    v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
    return static_cast<float>(v_x1_u32r>>12) / 1024;
}

bool BME280::reset_device() noexcept {
    constexpr uint8_t reset_val = 0xb6;
    return write8(BME280_REGISTER_SOFTRESET, reset_val);
}

bool BME280::begin(uint8_t slave, I2C_Master* i2c) noexcept {
    if(m_i2c == nullptr || i2c != nullptr) m_i2c = i2c;
    if(slave != 0xff) m_addr = slave;
    m_i2c->begin();
    
    uint8_t chip_id;
    if(!read8(BME280_REGISTER_CHIPID, &chip_id) || (int)chip_id != (int)0x60) {
        if(m_debug_enabled) TRACE("chip id does not match expected\r\n");
        return false;
    }

    //if(!reset_device()) return false;
    
    if(!read_calibration_data()) return false;
    
    // Set Humidity oversampling to 1
    if(!write8(BME280_REGISTER_CONTROLHUMID, 0x01)) return false; // Set before CONTROL (DS 5.4.3)
    if(!write8(BME280_REGISTER_CONTROL, 0x3F)) return false;
    
    m_is_initialized = true;
    return true;
}

bool BME280::read_sensors() noexcept {
    if(!m_is_initialized) return false;
    constexpr uint8_t reg = 0xf7;
    if(!m_i2c->write(m_addr, &reg, 1)) return false;
    uint8_t buf[8];
    if(!m_i2c->read(m_addr, buf, 8)) return false;

    int32_t t_fine;
    m_temperature = calculate_temperature(buf[3], buf[4], buf[5], &t_fine);
    m_pressure = calculate_pressure(buf[0], buf[1], buf[2], t_fine);
    m_humidity = calculate_humidity(buf[6], buf[7], t_fine);

    return true;
}

bool BME280::read_status(uint8_t* status) noexcept {
    if(!m_is_initialized) return false;
    if(!read8(0xf3, status)) return false;
    if(m_debug_enabled) TRACE("status=%x\r\n", *status);
    return true;
}