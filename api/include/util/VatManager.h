#pragma once
#include "txpp/event_flags_group.h"
#include "util/time.h"
#include "stdint.h"


class VatManager {
public:
    /**
     * \brief Structure used to store information about urc handlers
     */
    struct urc_handler_entry {
        /// URC Identifier (e.g. CCLK)
        const char* urc;
        /// Handler callback
        int(*cb)(const char*, const char*, void*);
        /// Userdata argument passed as last argument to handler
        void* arg;
    };
    /**
     * \brief Structure used to pass information to execute_ex.
     */
    struct execute_args {
        /// Command to execute (should include \r\n to end the line)
        const char* msg;
        /// Buffer to store result
        char* result_buf;
        /// Result buffer length in bytes
        size_t result_buf_len;
        /// Handler function that gets passed the result
        int(*result_handler)(const char*, void*);
        /// Handler function user argument
        void* result_handler_arg;
        /// Array of temporary urc handlers only active until the call is finished
        urc_handler_entry* urc_handlers;
        /// Number of entries in urc_handlers
        size_t urc_handlers_size;
    };
private:
    struct exec_ctx;
    txpp::event_flags_group m_flags;
    struct exec_ctx* m_exec_context;
    urc_handler_entry m_urc_handlers[64];
    const urc_handler_entry* m_temp_urc;
    int m_temp_urc_remaining_lines;
    bool m_init_done;
    bool m_debug_enabled;
    char m_line_buf[2049];
    unsigned int m_line_idx;

    void handle_response(const char* resp) noexcept;
    void handle_urc(const char* urc, const char* value) noexcept;
    void handle_line(char* line) noexcept;
    void handle_dtr() noexcept;
public:
    constexpr VatManager() noexcept
        : m_flags(), m_exec_context(nullptr), m_urc_handlers{},
            m_temp_urc(nullptr), m_temp_urc_remaining_lines(0),
            m_init_done(false), m_debug_enabled(false),
            m_line_buf{}, m_line_idx(0)
    {}

    VatManager(const VatManager&) = delete;
    VatManager& operator=(const VatManager&) = delete;
    VatManager(VatManager&&) = delete;
    VatManager& operator=(VatManager&&) = delete;

    void set_debug_enabled(bool debug) noexcept { m_debug_enabled = debug; }

    /// Initialize VatManager
    bool begin() noexcept;
    /// Clean up VatManager
    bool end() noexcept;

    bool is_initialized() const noexcept { return m_init_done; }

    /**
     * \brief Send output to vat engine
     * \param msg String to send
     * \return false if an error occurred or begin was not called
     */
    bool write(const char* msg) noexcept;
    /**
     * \brief Simple execute
     * \param msg String to send
     */
    int execute(const char* msg) noexcept;
    /**
     * \brief Advanced execute
     * \param args Information about the call, check struct execute_args
     */
    int execute_ex(const execute_args* args) noexcept;
    /**
     * \brief Register multiple global urc handlers
     * \param entries Array of urc handlers with arguments
     * \param nentries Number of entries in the array
     * \return true if all handlers where registered correctly
     */
    bool register_urcs(const urc_handler_entry* entries, size_t nentries) noexcept;
    /**
     * \brief Register a single global urc handler
     * \param urc ID of the urc to handle (or null for a catch all handler)
     * \param cb Handler callback
     * \param arg Userargument passed to the callback
     * \return true if the handler was registered correctly
     */
    bool register_urc(const char* urc, int(*cb)(const char*, const char*, void*), void* arg) noexcept;



    /** Helper Methods **/
    /**
     * \brief Set Phone Functionality
     * \param fun Function level (0=min, 1=full, 4=rf/tx of, 5=factory, 6=reset, 7=offline)
     */
    int set_cfun(int fun) noexcept;
    /**
     * \brief Get Phone Functionality
     * \param fun Function level Output pointer (0=min, 1=full, 4=rf/tx of, 5=factory, 6=reset, 7=offline)
     */
    int get_cfun(int* fun) noexcept;
    /**
     * \brief Set CCLK Clock
     * \param timestamp Unix timestamp
     */
    int set_cclk(time_t timestamp) noexcept;
    /**
     * \brief Get CCLK Clock
     * \param timestamp Pointer to output timestamp
     */
    int get_cclk(time_t* timestamp) noexcept;
    /**
     * \brief Set Power saving enabled
     * \param enabled true to enabled PSM support
     */
    int set_cpsms(bool enabled) noexcept;
    /**
     * \brief Get Power saving enabled
     * \param enabled Status pointer
     */
    int get_cpsms(bool* enabled) noexcept;
    /**
     * \brief Get Signal Quality Report
     * \param rssi CSQ Rssi output (0-31,99)
     */
    int get_csq(int* rssi) noexcept;
};

extern VatManager VAT;
