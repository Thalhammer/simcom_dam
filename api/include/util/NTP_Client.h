#pragma once
#include <cstdint>
#include <txpp/event_flags_group.h>
#include <util/CallbackList.h>
#include "util/time.h"

class NTP_Client {
    txpp::event_flags_group m_flags;
    time_unix_type m_timeoffset;
    bool m_is_initialized;
    bool m_debug_enabled;

    CallbackList<16, void, int32_t> m_on_connect;
public:
    constexpr NTP_Client() noexcept
        : m_flags(), m_timeoffset(0), m_is_initialized(false), m_debug_enabled(false)
    {}
    ~NTP_Client() {
        if(m_is_initialized) end();
    }

    NTP_Client(const NTP_Client&) = delete;
    NTP_Client& operator=(const NTP_Client&) = delete;
    NTP_Client(NTP_Client&&) = delete;
    NTP_Client& operator=(NTP_Client&&) = delete;

    void set_debug_enabled(bool debug) noexcept { m_debug_enabled = debug; }

    bool begin() noexcept;
    bool end() noexcept;

    bool sync(const char* remote = nullptr) noexcept;

    time_unix_type get_offset() const noexcept;
    time_unix_type get_time() const noexcept;
};