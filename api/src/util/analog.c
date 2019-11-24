#include "util/analog.h"
#include "qapi/qapi_adc.h"

typedef struct {
    const char* channelName;
    qapi_Adc_Input_Properties_Type_t properties;
} analog_channel_info_t;

static struct {
    analog_channel_info_t channels[9];
    qapi_ADC_Handle_t handle;
} _analog_state = {{}, NULL};

int analog_init(void) {
    if(_analog_state.handle == NULL) {
        qapi_Status_t status = qapi_ADC_Open(&_analog_state.handle, 0);
        if(status != QAPI_OK) return status;
        memset(_analog_state.channels, 0, sizeof(_analog_state.channels));
        for(size_t i=0; i<(sizeof(_analog_state.channels)/sizeof(analog_channel_info_t)); i++) {
            _analog_state.channels[i].channelName = analog_get_channel_name(i);
            status = qapi_ADC_Get_Input_Properties(_analog_state.handle,
                            _analog_state.channels[i].channelName, strlen(_analog_state.channels[i].channelName),
                            &_analog_state.channels[i].properties);
            if(status != QAPI_OK) {
                qapi_ADC_Close(_analog_state.handle, false);
                return status;
            }
        }
    }
    return QAPI_OK;
}

int analog_read_channel(analog_channel_t channel, int* value) {
    if(channel > (sizeof(_analog_state.channels)/sizeof(analog_channel_info_t)) - 1) return QAPI_ERR_INVALID_PARAM;
    if(value == NULL) return QAPI_ERR_INVALID_PARAM;
    int res = analog_init();
    if(res != QAPI_OK) return res;
    
    qapi_ADC_Read_Result_t result;
    res = qapi_ADC_Read_Channel(_analog_state.handle, &_analog_state.channels[channel].properties, &result);
    if(res != QAPI_OK) return res;
    *value = result.nPhysical;
    return QAPI_OK;
}

const char* analog_get_channel_name(analog_channel_t channel) {
    switch(channel) {
        case ANALOG_VBATT: return ADC_INPUT_VBATT;
        case ANALOG_VPH_PWR: return ADC_INPUT_VPH_PWR;
        case ANALOG_PMIC_THERM: return ADC_INPUT_PMIC_THERM;
        case ANALOG_BATT_ID: return ADC_INPUT_BATT_ID;
        case ANALOG_XO_THERM: return ADC_INPUT_XO_THERM;
        case ANALOG_XO_THERM_GPS: return ADC_INPUT_XO_THERM_GPS;
        case ANALOG_PA_THERM: return ADC_INPUT_PA_THERM;
        case ANALOG_PA_THERM1: return ADC_INPUT_PA_THERM1;
        case ANALOG_EXTERNAL: return ADC_INPUT_MPP6;
        default: return NULL;
    }
}

int analog_deinit(void) {
    if(_analog_state.handle != NULL) {
        qapi_ADC_Close(_analog_state.handle, false);
        _analog_state.handle = NULL;
    }
    return QAPI_OK;
}

#ifdef __cplusplus
}
#endif