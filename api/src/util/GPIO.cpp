#include "util/GPIO.h"
#include "util/trace.h"
extern "C" {
#include "qapi_tlmm.h"
}

#define TRACE_TAG "GPIO"

bool GPIO::begin() noexcept {
    if(m_is_initialized) return reconfigure(true, 0);

    qapi_TLMM_Config_t tlmm_config;
    memset(&tlmm_config, 0, sizeof(tlmm_config));
    tlmm_config.pin = m_pin;
	auto status = qapi_TLMM_Get_Gpio_ID(&tlmm_config, &m_tlmm_id);
    if(status != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to get gpio id %d\r\n", status);
        return false;
    }
    m_is_initialized = true;
    return reconfigure(false, 0, pull::none);
}

bool GPIO::end() noexcept {
    qapi_TLMM_Config_t tlmm_config;
    memset(&tlmm_config, 0, sizeof(tlmm_config));
    tlmm_config.pin = m_pin;
    auto status = qapi_TLMM_Release_Gpio_ID(&tlmm_config, m_tlmm_id);
    if(status != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to release gpio id %d\r\n", status);
        return false;
    }
    m_is_initialized = false;
    m_tlmm_id = 0;
    return true;
}

bool GPIO::reconfigure(bool output, uint32_t function, pull p) noexcept {
    if(!m_is_initialized) return false;
    qapi_TLMM_Config_t config;
    config.dir = output ? QAPI_GPIO_OUTPUT_E : QAPI_GPIO_INPUT_E;
    config.func = function;
    config.drive = QAPI_GPIO_2MA_E;
    config.pin = m_pin;
    config.pull = (qapi_GPIO_Pull_t)p;
    auto status = qapi_TLMM_Config_Gpio(m_tlmm_id, &config);
	if(status != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to reconfigure gpio %d\r\n", status);
        return false;
    }
    return true;
}

bool GPIO::drive(bool high) noexcept {
    if(!m_is_initialized) {
        if(!begin()) return false;
        // Default is input, no pull
        if(!reconfigure(true)) return false;
    }
    auto status = qapi_TLMM_Drive_Gpio(m_tlmm_id, m_pin, high ? QAPI_GPIO_HIGH_VALUE_E : QAPI_GPIO_LOW_VALUE_E);
    if(status != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to drive gpio %d\r\n", status);
        return false;
    }
    return true;
}

bool GPIO::read(bool* is_high) noexcept {
    if(!m_is_initialized) {
        if(!begin()) return false;
    }
    qapi_GPIO_Value_t val;
    auto status = qapi_TLMM_Read_Gpio(m_tlmm_id, m_pin, &val);
	if(status != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to drive gpio %d\r\n", status);
        return false;
    }
    *is_high = val == QAPI_GPIO_HIGH_VALUE_E;
    return true;
}

GPIO gpio2(10);
GPIO gpio3(11);
GPIO gpio4(26);
GPIO netlight(50);