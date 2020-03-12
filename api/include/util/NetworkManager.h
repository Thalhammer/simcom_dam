#pragma once
#include "util/CallbackList.h"

class NetworkManager {
public:
    enum class constate {
        initiated,
        connecting,
        connected,
        disconnected
    };
private:
    void* m_dss_handle;
    void* m_reconnect_timer;
    constate m_constate;
    CallbackList<64, void, constate> m_constate_cbs;
    bool m_debug_enabled;
    bool m_reconnect_enabled;
    char m_username[128];
    char m_password[128];
    char m_apn[151];

    static void _dss_cb(void* hndl, void *user_data, int evt, void *payload_ptr);
    static void _reconnect_cb(void* ptr);
public:
    constexpr NetworkManager() noexcept
        : m_dss_handle(nullptr), m_reconnect_timer(nullptr), m_constate(constate::initiated),
            m_constate_cbs{}, m_debug_enabled(false),
            m_reconnect_enabled(false), m_username{}, m_password{}, m_apn{}
    {}

    NetworkManager(const NetworkManager&) = delete;
    NetworkManager& operator=(const NetworkManager&) = delete;
    NetworkManager(NetworkManager&&) = delete;
    NetworkManager& operator=(NetworkManager&&) = delete;

    void set_debug_enabled(bool debug) noexcept { m_debug_enabled = debug; }

    bool begin() noexcept;
    bool end() noexcept;

    bool add_constate_cb(void(*fn)(constate, void*), void* arg) noexcept;
    bool remove_constate_cb(void(*fn)(constate, void*), void* arg) noexcept;

    bool connect(const char* apn, const char* user, const char* pw) noexcept;
    bool reconnect() noexcept;
    bool dump_status() noexcept;
    constate get_state() noexcept { return m_constate; }
    bool set_autoreconnect(bool enabled) noexcept;
};

extern NetworkManager Network;