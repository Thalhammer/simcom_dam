#include "util/PSM.h"
#include "util/trace.h"
#include "util/AsmBuilder.h"
#include "util/NetworkManager.h"
#include "util/VatManager.h"
extern "C" {
#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_psm.h"
#include "qapi/qapi_pmapp_rtc.h"
}

#define TRACE_TAG "PSM"

extern "C" int __cxa_atexit(void (*func) (void *), void * arg, void * dso_handle);
extern "C" void *__dso_handle;

static constexpr const char* status_map[] = {
	"NONE",
	"REJECT",            /**< PSM enter request is rejected */
	"READY",             /**< Ready to enter into PSM mode. */
	"NOT_READY",         /**< Not ready to enter PSM. */
	"COMPLETE",          /**< Entered into PSM mode, system might shutdown any time. */
	"DISCONNECTED",      /**< PSM Server is down. */
	"MODEM_LOADED",      /**< Modem is loaded as part of boot up. */
	"MODEM_NOT_LOADED",  /**< Modem is not loaded as part of boot up.*/
	"NW_OOS",            /** < Network is OOS. */
	"NW_LIMITED_SERVICE",/**< Network is Limited Service. */
	"HEALTH_CHECK",      /**< Application health check.*/
	"FEATURE_ENABLED",   /**< Feature is dynamically enabled.*/
	"FEATURE_DISABLED"
};

static constexpr const char* reason_map[] = {
	"NONE",                /**< Reject reason None.*/
	"NOT_ENABLED",         /**< PSM feature is not enabled. */
	"MODEM_NOT_READY",     /**< Modem is not ready to enter into PSM mode.*/
	"DURATION_TOO_SHORT",  /**< PSM duration is too short to enter into PSM mode.*/
};

void PSM_Manager::PSM_Callback(PSM_Manager* instance, void* info) noexcept {
    auto msg = reinterpret_cast<psm_status_msg_type*>(info);
	if(instance->m_debug_enabled) TRACE("psm_cb client=%d reason=%s(%d) status=%s(%d)\r\n", msg->client_id, reason_map[msg->reason], msg->reason, status_map[msg->status], msg->status);
	if(msg->status == PSM_STATUS_HEALTH_CHECK)
		qapi_PSM_Client_Hc_Ack(msg->client_id);
	if(msg->status == PSM_STATUS_REJECT && msg->reason == PSM_REJECT_REASON_NOT_ENABLED) {
		if(instance->m_debug_enabled) TRACE("PSM is not enabled, please enable it using AT or VisualAT in the APP\r\n");
		if(instance->m_debug_enabled) TRACE("Execute \"AT+CSCLK=0\" and \"AT+CPSMS=1\" to enable power safe mode.\r\n");
	}
	if(msg->status == PSM_STATUS_READY) {
		if(instance->m_debug_enabled) TRACE("ready state signaled, entering PSM any moment\r\n");
	}
    instance->m_callbacks.call(static_cast<status>(msg->status), static_cast<reason>(msg->reason));
}

bool PSM_Manager::begin() noexcept {
    if(m_clientid != -1) return true;
    int res = qapi_PM_Rtc_Init();
	if(res != QAPI_OK) {
		if(m_debug_enabled) TRACE("failed to init rtc: %d\r\n", res);
		return false;
	}
    if(m_debug_enabled) TRACE("rtc initialized\r\n");

    AsmBuilder builder(m_callback_wrapper_code, sizeof(m_callback_wrapper_code));
    auto cb = reinterpret_cast<void(*)(psm_status_msg_type*)>(m_callback_wrapper_code);
	builder.mov(AsmBuilder::r1, AsmBuilder::r0);          // mov r1, r0
	builder.mov(AsmBuilder::r0, (uint32_t)this);          // mov r0, this
	builder.branch(&PSM_Manager::PSM_Callback);           // b Callback

	res = qapi_PSM_Client_Register(&m_clientid, cb);
	if(res != QAPI_OK) {
		if(m_debug_enabled) TRACE("failed to register client: %d\r\n", res);
		return false;
	}
    if(m_debug_enabled) TRACE("registered client %d with psmserver\r\n", m_clientid);

	if(!m_at_exit_called) {
		__cxa_atexit([](void* arg){
			PSM_Manager* that = reinterpret_cast<PSM_Manager*>(arg);
			if(that->m_clientid != 0)
				that->end();
		}, this, __dso_handle);
		m_at_exit_called = true;
	}
    return true;
}

bool PSM_Manager::end() noexcept {
    if(m_clientid == -1) return false;
    auto res = qapi_PSM_Client_Unregister(m_clientid);
    if(res != QAPI_OK) {
		if(m_debug_enabled) TRACE("failed to unregister client: %d\r\n", res);
		return false;
    }
    m_clientid = 0;
    return true;
}

bool PSM_Manager::enable_feature() const noexcept {
	return VAT.set_cpsms(true) == 1;
}

bool PSM_Manager::disable_feature() const noexcept {
	return VAT.set_cpsms(false) == 1;
}

bool PSM_Manager::enter_psm(uint32_t time_in_secs, uint32_t secs_to_wait) noexcept {
    if(m_clientid == -1) return false;

	Network.end();

    psm_info_type info;
	memset(&info, 0, sizeof(info));
	// You might specify PSM_WAKEUP_MEASUREMENT_ONLY if you don't want to do network access on next wakeup.
	// If you do so, the modem might not get loaded which should save startuptime and power.
	info.psm_wakeup_type = PSM_WAKEUP_MEASUREMENT_ONLY;
	info.psm_time_info.time_format_flag = PSM_TIME_IN_SECS; // Time is specified in seconds
	// Time to sleep for in seconds (Minimum 550 seconds, 9:10 minutes)
	// however this time might not be accurate
	info.psm_time_info.psm_duration_in_secs = time_in_secs;
	info.active_time_in_secs = secs_to_wait; // Time in secs to wait until entering PSM mode
	while(true) {
		auto res = qapi_PSM_Client_Enter_Psm(m_clientid, &info);
		if(res != QAPI_OK) {
			if(m_debug_enabled) TRACE("failed to enter psm: %d\r\n", res);
			return false;
		}
		if(m_debug_enabled) TRACE("entering psm mode\r\n");
		tx_thread_sleep(100);
	}
}

bool PSM_Manager::load_modem() noexcept {
    if(m_clientid == -1) return false;
	auto res = qapi_PSM_Client_Load_Modem(m_clientid);
	if(res != QAPI_OK) {
		if(m_debug_enabled) TRACE("failed to load modem: %d\r\n", res);
		return false;
	}
    return true;
}

PSM_Manager PSM;