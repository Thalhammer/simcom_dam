#pragma once
#include <cstdint>

class Analog {
    void* m_handle = nullptr;
	const char* m_channel_name = nullptr;
	uint32_t m_device_index = 0;
	uint32_t m_channel_index = 0;
    bool m_debug_enabled = false;
public:
    constexpr Analog(const char* name)
        : m_handle(nullptr), m_channel_name(name), m_device_index(0), m_channel_index(0), m_debug_enabled(false)
    {}
    Analog(const Analog&) = delete;
    Analog& operator=(const Analog&) = delete;
    Analog(Analog&&) = delete;
    Analog& operator=(Analog&&) = delete;

    void set_debug_enabled(bool debug) noexcept { m_debug_enabled = debug; }
    
    bool begin() noexcept;
    bool end() noexcept;

	bool read(int32_t* value) noexcept;

    const char* get_name() const noexcept { return m_channel_name; }
};

extern Analog ADC_VBATT;           /* battery voltage in mV */
extern Analog ADC_VPH_PWR;         /* some voltage close to battery voltage in mV */
extern Analog ADC_PMIC_THERM;      /* pmic temperature in C ?*/
extern Analog ADC_BATT_ID;         /* ? */
extern Analog ADC_XO_THERM;        /* ? */
extern Analog ADC_XO_THERM_GPS;    /* ? */
extern Analog ADC_PA_THERM;        /* power amplifier? temperature in C*/
extern Analog ADC_PA_THERM1;       /* power amplifier? temperature in C*/
extern Analog ADC_EXTERNAL;        /* external ADC in mV */