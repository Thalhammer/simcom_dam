#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	ANALOG_VBATT,           /* battery voltage in mV */
	ANALOG_VPH_PWR,         /* some voltage close to battery voltage in mV */
	ANALOG_PMIC_THERM,      /* pmic temperature in C ?*/
	ANALOG_BATT_ID,         /* ? */
	ANALOG_XO_THERM,        /* ? */
	ANALOG_XO_THERM_GPS,    /* ? */
	ANALOG_PA_THERM,        /* power amplifier? temperature in C*/
	ANALOG_PA_THERM1,       /* power amplifier? temperature in C*/
	ANALOG_EXTERNAL,        /* external ADC in mV */
} analog_channel_t;

extern int analog_init(void);
extern int analog_read_channel(analog_channel_t channel, int* value);
extern const char* analog_get_channel_name(analog_channel_t channel);
extern int analog_deinit(void);

#ifdef __cplusplus
}
#endif