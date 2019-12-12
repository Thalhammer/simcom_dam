#pragma once

#ifndef __cplusplus
#error "This is a c++ library"
#endif

#include "api.h"

namespace txpp {
    class event_flags_group {
        TX_EVENT_FLAGS_GROUP* m_group;
    public:
        constexpr event_flags_group() noexcept
            : m_group(nullptr)
        {}

        event_flags_group(const event_flags_group& other) = delete;
        event_flags_group& operator=(const event_flags_group& other) = delete;

        event_flags_group(event_flags_group&& other) noexcept
            : m_group(other.m_group)
        {
            other.m_group = nullptr;
        }
        event_flags_group& operator=(event_flags_group&& other) noexcept {
            if(m_group) {
                tx_event_flags_delete(m_group);
                txm_module_object_deallocate(m_group);
            }
            m_group = other.m_group;
            other.m_group = nullptr;
            return *this;
        }

        ~event_flags_group() noexcept {
            if(m_group) {
                tx_event_flags_delete(m_group);
                txm_module_object_deallocate(m_group);
            }
        }

        bool initialize(const char* name = nullptr) noexcept {
            if(m_group) return false;
            if(txm_module_object_allocate(&m_group, sizeof(TX_EVENT_FLAGS_GROUP)) != TX_SUCCESS || m_group == nullptr) {
                return false;
            }
            if(tx_event_flags_create(m_group, (name ? name : "unnamed")) != TX_SUCCESS) {
                txm_module_object_deallocate(m_group);
                return false;
            }
            return true;
        }

        bool is_initialized() const noexcept { return m_group != nullptr; }

        TX_EVENT_FLAGS_GROUP* raw_group() noexcept { return m_group; }

        bool get(ULONG requested_flags, ULONG m, ULONG *actual_flags_ptr, ULONG wait_option = TX_WAIT_FOREVER) noexcept {
            if(m_group == nullptr) return false;
            if(tx_event_flags_get(m_group, requested_flags, m, actual_flags_ptr, wait_option) != TX_SUCCESS) return false;
            return true;
        }

        bool set(ULONG flags_to_set, ULONG m = TX_OR) noexcept {
            if(m_group == nullptr) return false;
            if(tx_event_flags_set(m_group, flags_to_set, m) != TX_SUCCESS) return false;
            return true;
        }
    };
}