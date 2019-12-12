#pragma once
#include <cstdint>
#include <txpp/event_flags_group.h>

class GNSS_Client {
    struct location {
        uint64_t timestamp;                 /**< UTC timestamp for a location fix; milliseconds since Jan. 1, 1970. */
        double latitude;                    /**< Latitude in degrees. */
        double longitude;                   /**< Longitude in degrees. */
        double altitude;                    /**< Altitude in meters above the WGS 84 reference ellipsoid. */
        float speed;                        /**< Speed in meters per second. */
        float accuracy;                     /**< Accuracy in meters. */
    };
    typedef void(*on_location_cb_t)(const struct location* loc, void* udata);
private:
    bool m_is_initialized;
    bool m_debug_enabled;

    uint32_t m_client;
    uint32_t m_session;
    int m_capabilities;
    location m_last_location;
    int m_last_error;

    txpp::event_flags_group m_flags;

    void* m_userdata;
    on_location_cb_t m_on_location;

    // Make some room for callback wrappers
    // TODO: If GNSS_Client::begin() code is changed make sure this matches
    alignas(uint32_t) uint8_t m_callback_wrapper_code[112];

    static void Capabilities_Callback(GNSS_Client* instance, uint32_t caps) noexcept;
    static void Tracking_Callback(GNSS_Client* instance, void* location) noexcept;
    static void Response_Callback(GNSS_Client* instance, uint32_t err, uint32_t id) noexcept;
    static void Collective_Response_Callback(GNSS_Client* instance, size_t count, uint32_t* err, uint32_t* ids) noexcept;
public:
    constexpr GNSS_Client() noexcept
        : m_is_initialized(false), m_debug_enabled(false),
            m_client(0), m_session(0), m_capabilities(0),
            m_last_location({}), m_last_error(0), m_flags(),
            m_userdata(nullptr), m_on_location(nullptr),
            m_callback_wrapper_code{}
    {}
    ~GNSS_Client()
    {
        if(m_is_initialized) end();
    }

    GNSS_Client(const GNSS_Client&) = delete;
    GNSS_Client& operator=(const GNSS_Client&) = delete;
    GNSS_Client(GNSS_Client&&) = delete;
    GNSS_Client& operator=(GNSS_Client&&) = delete;

    void set_debug_enabled(bool debug) noexcept { m_debug_enabled = debug; }

    void set_on_location(on_location_cb_t cb, void* udata = nullptr) {
        m_on_location = nullptr;
        m_userdata = udata;
        m_on_location = cb;
    }

    bool begin() noexcept;
    bool end() noexcept;

    bool await_fix() noexcept;
};