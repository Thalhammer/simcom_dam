#pragma once
#include <cstdint>
#include "CallbackList.h"

class PSM_Manager {
public:
    enum class status : int {
        NONE = 0,
        REJECT,            /**< PSM enter request is rejected */
        READY,             /**< Ready to enter into PSM mode. */
        NOT_READY,         /**< Not ready to enter PSM. */
        COMPLETE,          /**< Entered into PSM mode, system might shutdown any time. */
        DISCONNECTED,      /**< PSM Server is down. */
        MODEM_LOADED,      /**< Modem is loaded as part of boot up. */
        MODEM_NOT_LOADED,  /**< Modem is not loaded as part of boot up.*/
        NW_OOS,            /** < Network is OOS. */
        NW_LIMITED_SERVICE,/**< Network is Limited Service. */
        HEALTH_CHECK,      /**< Application health check.*/
        FEATURE_ENABLED,   /**< Feature is dynamically enabled.*/
        FEATURE_DISABLED
    };
    enum class reason : int{
        NONE = 0,            /**< Reject reason None.*/
        NOT_ENABLED,         /**< PSM feature is not enabled. */
        MODEM_NOT_READY,     /**< Modem is not ready to enter into PSM mode.*/
        DURATION_TOO_SHORT,  /**< PSM duration is too short to enter into PSM mode.*/
    };
private:
    int32_t m_clientid;
    bool m_debug_enabled;
    bool m_at_exit_called;
    CallbackList<32, void, status, reason> m_callbacks;

    // Make some room for callback wrappers
    // TODO: If PSM_Manager::begin() code is changed make sure this matches
    alignas(uint32_t) uint8_t m_callback_wrapper_code[112];
    static void PSM_Callback(PSM_Manager* instance, void* info) noexcept;
public:
    constexpr PSM_Manager() noexcept
        :m_clientid(-1), m_debug_enabled(false), m_at_exit_called(false), m_callbacks{}, m_callback_wrapper_code{}
    {}

    PSM_Manager(const PSM_Manager&) = delete;
    PSM_Manager& operator=(const PSM_Manager&) = delete;
    PSM_Manager(PSM_Manager&&) = delete;
    PSM_Manager& operator=(PSM_Manager&&) = delete;

    void set_debug_enabled(bool debug) noexcept { m_debug_enabled = debug; }

    bool add_callback(void(*cb)(status, reason, void*), void* arg) noexcept { return m_callbacks.add_callback(cb, arg); }
    bool remove_callback(void(*cb)(status, reason, void*), void* arg) noexcept { return m_callbacks.remove_callback(cb, arg); }

    bool begin() noexcept;
    bool end() noexcept;

    bool enable_feature() const noexcept;
    bool disable_feature() const noexcept;

    bool enter_psm(uint32_t sleeptime_in_secs, uint32_t secs_to_wait = 0) noexcept;
    bool load_modem() noexcept;
};

extern PSM_Manager PSM;