#include "util/I2C_Master.h"
#include "util/trace.h"
#include "qapi/qapi_i2c_master.h"

#define TRACE_TAG "I2C_Master"

static const char* const error_map[] = {
	"SUCCESS",
	"ERR_INVALID_PARAMETER",
	"ERR_UNSUPPORTED_CORE_INSTANCE",
	"ERR_API_INVALID_EXECUTION_LEVEL",
	"ERR_HANDLE_ALLOCATION",
	"ERR_HW_INFO_ALLOCATION",
	"ERR_BUS_NOT_IDLE",
	"ERR_TRANSFER_TIMEOUT",
	"ERR_INPUT_FIFO_OVER_RUN",
	"ERR_OUTPUT_FIFO_UNDER_RUN",
	"ERR_INPUT_FIFO_UNDER_RUN",
	"ERR_OUTPUT_FIFO_OVER_RUN",
	"ERR_INVALID_BUS_HIGH_TIME_VALUE",
	"ERR_QSTATE_INVALID",
	"ERR_START_STOP_UNEXPECTED",
	"ERR_DATA_NACK",
	"ERR_ADDR_NACK",
	"ERR_ARBITRATION_LOST",
	"ERR_INVALID_WRITE",
	"ERR_INVALID_TAG",
	"ERR_PLATFORM_INIT_FAIL",
	"ERR_PLATFORM_DEINIT_FAIL",
	"ERR_PLATFORM_REG_INT_FAIL",
	"ERR_PLATFORM_DE_REG_INT_FAIL",
	"ERR_PLATFORM_CLOCK_ENABLE_FAIL",
	"ERR_PLATFORM_GPIO_ENABLE_FAIL",
	"ERR_PLATFORM_CLOCK_DISABLE_FAIL",
	"ERR_PLATFORM_GPIO_DISABLE_FAIL",
	"TRANSFER_CANCELED",
	"TRANSFER_FORCE_TERMINATED",
	"TRANSFER_COMPLETED",
	"TRANSFER_INVALID",
	"ERROR_HANDLE_ALREADY_IN_QUEUE",
	"ERROR_OPEN_FAILURE",
	"ERROR_CLOSE_FAILURE",
	"ERROR_DALDETACH_FAILURE",

	"ERR_INVALID_DEV_HANDLE",
	"ERR_INVALID_CONFIG_POINTER",
	"ERR_INVALID_DESC_POINTER",
	"ERR_INVALID_CALLBACK_FN_POINTER",
	"ERR_INVALID_CALLBACK_ARG_POINTER",

	"ERROR_POWER_ON_FAILURE",
	"ERROR_POWER_OFF_FAILURE",
};

static const char* errnum_text(int errnum) {
	if(errnum == 0) return error_map[0];
	errnum = 0 - errnum;
	errnum -= __QAPI_ERR_ENCAP_MOD_ID(QAPI_MOD_BSP_I2C_MASTER);
	if(errnum > 0 && errnum < (int)(sizeof(error_map) / sizeof(error_map[0])))
		return error_map[errnum];
	else return "UNKNOWN";
}

static void client_callback(uint32_t status, void *ctxt)
{
	(void)status;
	(void)ctxt;
}

extern "C" int __cxa_atexit(void (*func) (void *), void * arg, void * dso_handle);
extern "C" void *__dso_handle;

bool I2C_Master::begin() noexcept
{
    if(m_handle) return true;
    auto res = qapi_I2CM_Open(m_port, &m_handle);
    if(m_debug_enabled)
        TRACE("[%d] qapi_I2CM_Open: %d (%s)\r\n", (int)m_port, res, errnum_text(res));
    if(res != QAPI_OK) return false;
    if(!power_on()) {
        end();
        return false;
    }
	if(!m_at_exit_called) {
		__cxa_atexit([](void* arg){
			I2C_Master* that = reinterpret_cast<I2C_Master*>(arg);
			if(that->m_handle != nullptr)
				that->end();
		}, this, __dso_handle);
		m_at_exit_called = true;
	}
    return true;
}

bool I2C_Master::end() noexcept
{
    if(m_handle == nullptr) return false;
    power_off();
    auto res = qapi_I2CM_Close(m_handle);
    if(m_debug_enabled)
        TRACE("[%d] qapi_I2CM_Close: %d (%s)\r\n", (int)m_port, res, errnum_text(res));
    if(res != QAPI_OK) return false;
    m_handle = nullptr;
    return true;
}

bool I2C_Master::read(uint8_t slave, uint8_t* data, uint32_t len) noexcept
{
    if(m_handle == nullptr) return false;
    qapi_I2CM_Config_t config;
    memset(&config, 0, sizeof(config));
	config.bus_Frequency_KHz = m_speed / 1000;
	config.slave_Address = slave;
	config.slave_Max_Clock_Stretch_Us = 100000;

	qapi_I2CM_Descriptor_t desc;
    memset(&desc, 0, sizeof(desc));
	desc.buffer      = data;
	desc.length      = len;
	desc.flags       = QAPI_I2C_FLAG_START | QAPI_I2C_FLAG_READ | QAPI_I2C_FLAG_STOP;

	auto res = qapi_I2CM_Transfer(m_handle, &config, &desc, 1, client_callback, 0x1, 100);
    if(m_debug_enabled)
        TRACE("[%d] qapi_I2CM_Transfer: %d (%s)\r\n", (int)m_port, res, errnum_text(res));
    return res == QAPI_OK;
}

bool I2C_Master::write(uint8_t slave, const uint8_t* data, uint32_t len) noexcept
{
    if(m_handle == nullptr) return false;
    qapi_I2CM_Config_t config;
    memset(&config, 0, sizeof(config));
	config.bus_Frequency_KHz = m_speed / 1000;
	config.slave_Address = slave;
	config.slave_Max_Clock_Stretch_Us = 100000;

	qapi_I2CM_Descriptor_t desc;
    memset(&desc, 0, sizeof(desc));
	desc.buffer      = const_cast<uint8_t*>(data);
	desc.length      = len;
	desc.flags       = QAPI_I2C_FLAG_START | QAPI_I2C_FLAG_WRITE | QAPI_I2C_FLAG_STOP;

	auto res = qapi_I2CM_Transfer(m_handle, &config, &desc, 1, client_callback, 0x1, 100);
    if(m_debug_enabled)
        TRACE("[%d] qapi_I2CM_Transfer: %d (%s)\r\n", (int)m_port, res, errnum_text(res));
    return res == QAPI_OK;
}

bool I2C_Master::power_on() noexcept
{
    if(m_handle == nullptr) return false;
    auto res = qapi_I2CM_Power_On(m_handle);
    if(m_debug_enabled)
        TRACE("[%d] qapi_I2CM_Power_On: %d (%s)\r\n", (int)m_port, res, errnum_text(res));
    return res == QAPI_OK;
}

bool I2C_Master::power_off() noexcept
{
    if(m_handle == nullptr) return false;
    auto res = qapi_I2CM_Power_Off(m_handle);
    if(m_debug_enabled)
        TRACE("[%d] qapi_I2CM_Power_Off: %d (%s)\r\n", (int)m_port, res, errnum_text(res));
    return res == QAPI_OK;
}

I2C_Master Wire{QAPI_I2CM_INSTANCE_003_E};