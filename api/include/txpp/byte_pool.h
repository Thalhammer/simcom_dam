#pragma once

#ifndef __cplusplus
#error "This is a c++ library"
#endif

#include "api.h"

namespace txpp {
    class byte_pool {
        TX_BYTE_POOL* m_pool;
        size_t m_length;
    public:
        struct pool_info {
            char* name;
            ULONG available_bytes;
            ULONG fragments;
            ULONG suspended_count;
            ULONG total_bytes;
        };

        constexpr byte_pool() noexcept
            : m_pool(nullptr), m_length(0)
        {}

        byte_pool(void* ptr, size_t len, const char* name = "pool") noexcept
            : m_pool(nullptr), m_length(len)
        {
            initialize(ptr, len, name);
        }

        byte_pool(const byte_pool& other) = delete;
        byte_pool& operator=(const byte_pool& other) = delete;

        byte_pool(byte_pool&& other) noexcept
            : m_pool(other.m_pool), m_length(other.m_length)
        {
            other.m_pool = nullptr;
            other.m_length = 0;
        }
        byte_pool& operator=(byte_pool&& other) noexcept {
            if(m_pool) {
                tx_byte_pool_delete(m_pool);
                txm_module_object_deallocate(m_pool);
            }
            m_pool = other.m_pool;
            m_length = other.m_length;
            other.m_pool = nullptr;
            other.m_length = 0;
            return *this;
        }

        ~byte_pool() noexcept {
            if(m_pool) {
                tx_byte_pool_delete(m_pool);
                txm_module_object_deallocate(m_pool);
                m_pool = nullptr;
                m_length = 0;
            }
        }

        bool initialize(void* ptr, size_t len, const char* name = "pool") noexcept
        {
            if(ptr == NULL || len == 0) return false;
            if(m_pool != nullptr) return false;
            if(txm_module_object_allocate(&m_pool) != TX_SUCCESS) return false;
            if(tx_byte_pool_create(m_pool, name, ptr, len) != TX_SUCCESS) {
                txm_module_object_deallocate(m_pool);
                m_pool = nullptr;
                return false;
            }
            m_length = len;
            return true;
        }

        bool is_initialized() const noexcept { return m_pool != nullptr; }

        bool free(void* ptr) noexcept {
            if(ptr == nullptr) return true;
            return tx_byte_release(ptr) == TX_SUCCESS;
        }

        void* malloc(size_t len, unsigned long timeout = TX_NO_WAIT) noexcept {
            if(!is_initialized()) return nullptr;
            void* ptr = nullptr;
            if(tx_byte_allocate(m_pool, &ptr, len, timeout) != TX_SUCCESS || ptr == NULL) {
                return nullptr;
            }
            return ptr;
        }

        void* calloc(size_t num, size_t size, unsigned long timeout = TX_NO_WAIT) noexcept {
            void* ptr = this->malloc(num * size, timeout);
            if(ptr == nullptr) return nullptr;
            memset(ptr, 0, num*size);
            return ptr;
        }

        bool get_info(pool_info& info) const noexcept {
            if(!is_initialized()) return false;
            if(tx_byte_pool_info_get(m_pool, &info.name, &info.available_bytes, &info.fragments, nullptr, &info.suspended_count, nullptr) != TX_SUCCESS) return false;
            info.total_bytes = m_length;
            return true;
        }
    };

    template<size_t NumBytes>
    class static_byte_pool : private byte_pool {
        char m_data[NumBytes];
    public:
        static_byte_pool(const char* name = "pool")
            : byte_pool(m_data, NumBytes, name)
        {}

        static_byte_pool(const static_byte_pool& other) = delete;
        static_byte_pool& operator=(const static_byte_pool& other) = delete;
        static_byte_pool(static_byte_pool&& other) noexcept = delete;
        static_byte_pool& operator=(static_byte_pool&& other) noexcept = delete;

        bool is_initialized() const noexcept { return byte_pool::is_initialized(); }
        bool free(void* ptr) noexcept { return byte_pool::free(ptr); }
        void* malloc(size_t len, unsigned long timeout = TX_NO_WAIT) noexcept { return byte_pool::malloc(len, timeout); }
        void* calloc(size_t num, size_t size, unsigned long timeout = TX_NO_WAIT) noexcept { return byte_pool::calloc(num, size, timeout); }
        bool get_info(pool_info& info) const noexcept { return byte_pool::get_info(info); }
    };
}