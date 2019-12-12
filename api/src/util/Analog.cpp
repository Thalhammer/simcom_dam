#include "util/Analog.h"
#include "util/trace.h"
extern "C" {
#include "qapi/qapi_adc.h"
}

#define TRACE_TAG "Analog"

bool Analog::begin() noexcept {
    if(m_handle == nullptr) return true;
    qapi_Status_t status = qapi_ADC_Open(&m_handle, 0);
    if(status != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to open adc %d\r\n", status);
        return false;
    }
    qapi_Adc_Input_Properties_Type_t props;
    status = qapi_ADC_Get_Input_Properties(m_handle,
                    m_channel_name,
                    strlen(m_channel_name),
                    &props);
    if(status != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to get adc properties %d\r\n", status);
        status = qapi_ADC_Close(m_handle, false);
        m_handle = nullptr;
        if(status == QAPI_OK) {
            if(m_debug_enabled) TRACE("failed to close adc %d\r\n", status);
            return false;
        }
        return false;
    }
    m_device_index = props.nDeviceIdx;
    m_channel_index = props.nChannelIdx;
    return true;
}

bool Analog::end() noexcept {
    if(m_handle == nullptr) return false;
    auto status = qapi_ADC_Close(m_handle, false);
    if(status == QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to close adc %d\r\n", status);
        return false;
    }
    m_handle = NULL;
    return true;
}

bool Analog::read(int32_t* value) noexcept {
    if(m_handle == nullptr) {
        if(!begin()) return false;
    }
    qapi_Adc_Input_Properties_Type_t props;
    props.nDeviceIdx = m_device_index;
    props.nChannelIdx = m_channel_index;
    qapi_ADC_Read_Result_t result;
    auto res = qapi_ADC_Read_Channel(m_handle, &props, &result);
    if(res != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to read adc %d\r\n", res);
        return false;
    }
    *value = result.nPhysical;
    return true;
}

Analog ADC_VBATT(ADC_INPUT_VBATT);
Analog ADC_VPH_PWR(ADC_INPUT_VPH_PWR);
Analog ADC_PMIC_THERM(ADC_INPUT_PMIC_THERM);
Analog ADC_BATT_ID(ADC_INPUT_BATT_ID);
Analog ADC_XO_THERM(ADC_INPUT_XO_THERM);
Analog ADC_XO_THERM_GPS(ADC_INPUT_XO_THERM_GPS);
Analog ADC_PA_THERM(ADC_INPUT_PA_THERM);
Analog ADC_PA_THERM1(ADC_INPUT_PA_THERM1);
Analog ADC_EXTERNAL(ADC_INPUT_MPP6);