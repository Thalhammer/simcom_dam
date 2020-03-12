#pragma once
#include <cstdint>
#include <txpp/event_flags_group.h>
#include <util/CallbackList.h>

class MQTT_Client {
public:
    struct last_will {
        const char* topic;
        const uint8_t* message;
        int32_t message_len;
        bool retained;
        uint8_t qos;
    };
    struct connect_info {
        const char* host;
        uint16_t port;
        const char* client_id;
        uint32_t keepalive_duration;
        bool clean_session;
        const char* username;
        const char* password;
        const struct last_will* lw;
    };
private:
    void* m_handle;
    txpp::event_flags_group m_flags;
    bool m_is_initialized;
    bool m_debug_enabled;
    const struct connect_info* m_info;

    CallbackList<16, void, int32_t> m_on_connect;
    CallbackList<16, void, int, int, uint16_t> m_on_publish;


    // Make some room for callback wrappers
    // TODO: If MQTT_Client::begin() code is changed make sure this matches
    alignas(uint32_t) uint8_t m_callback_wrapper_code[48];

    static void ConnectCB(MQTT_Client* instance, int32_t reason);
    static void SubscribeCB(MQTT_Client* instance, int32_t reason, const uint8_t* topic, int32_t topic_length, int32_t qos, const void* sid);
    static void MessageCB(MQTT_Client* mqtt, int32_t reason, const uint8_t* topic, int32_t topic_length, const uint8_t* msg, int32_t msg_length, int32_t qos, const void* sid);
    static void PublishCB(MQTT_Client* mqtt, int msgtype, int qos, uint16_t msg_id);
public:
    constexpr MQTT_Client() noexcept
        : m_handle(nullptr), m_flags(), m_is_initialized(false), m_debug_enabled(false), m_info(nullptr), m_callback_wrapper_code{}
    {}
    ~MQTT_Client() {
        if(m_is_initialized) end();
    }

    MQTT_Client(const MQTT_Client&) = delete;
    MQTT_Client& operator=(const MQTT_Client&) = delete;
    MQTT_Client(MQTT_Client&&) = delete;
    MQTT_Client& operator=(MQTT_Client&&) = delete;

    void set_debug_enabled(bool debug) noexcept { m_debug_enabled = debug; }

    bool begin() noexcept;
    bool end() noexcept;

    bool await_connected(uint32_t timeout) noexcept;
    bool is_connected() noexcept;

    bool subscribe(const char* topic, int qos) noexcept;
    bool unsubscribe(const char* topic) noexcept;
    bool publish(const char* topic, const uint8_t* msg, int32_t msg_len, int32_t qos, bool retain) noexcept;
    bool publish(const char* topic, const uint8_t* msg, int32_t qos, bool retain) noexcept;
    bool publish(const char* topic, const char* msg, int32_t msg_len, int32_t qos, bool retain) noexcept {
        return publish(topic, reinterpret_cast<const uint8_t*>(msg), msg_len, qos, retain);
    }
    bool publish(const char* topic, const char* msg, int32_t qos, bool retain) noexcept {
        return publish(topic, reinterpret_cast<const uint8_t*>(msg), qos, retain);
    }

    bool add_connect_cb(void(*fn)(int32_t, void*), void* arg) noexcept {
        return m_on_connect.add_callback(fn, arg);
    }
    bool remove_connect_cb(void(*fn)(int32_t, void*), void* arg) noexcept {
        return m_on_connect.remove_callback(fn, arg);
    }

    bool add_publish_cb(void(*fn)(int, int, uint16_t, void*), void* arg) noexcept {
        return m_on_publish.add_callback(fn, arg);
    }
    bool remove_publish_cb(void(*fn)(int, int, uint16_t, void*), void* arg) noexcept {
        return m_on_publish.remove_callback(fn, arg);
    }

    // Should not be freed as long as this client exists
    bool set_connect_info(const struct connect_info* info) noexcept;

    bool enable_autoreconnect(bool enable) noexcept;

    bool connect() noexcept;
    bool disconnect() noexcept;
};