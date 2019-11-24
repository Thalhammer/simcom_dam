#pragma once

#ifndef __cplusplus
#error "This is a c++ library"
#endif

#include "api.h"

namespace txpp {
    template<size_t MaxCallbacks, typename UserDataType, typename... Args>
    class callback_list {
        struct entry {
            void(*function)(Args..., UserDataType*);
            UserDataType* userdata;
        };
        entry m_entries[MaxCallbacks];
    public:
        constexpr callback_list() noexcept
            : m_entries{}
        {}

        callback_list(const callback_list& other) {
            memcpy(&m_entries, other.m_entries, sizeof(m_entries));
        }
        callback_list& operator=(const callback_list& other) {
            memcpy(&m_entries, other.m_entries, sizeof(m_entries));
            return *this;
        }

        bool add_callback(void(*fn)(Args..., UserDataType*), UserDataType* ud = nullptr) noexcept {
            if(fn == nullptr) return false;
            for(auto& e : m_entries) {
                if(e.function == nullptr) {
                    e.function = fn;
                    e.userdata = ud;
                    return true;
                }
            }
            return false;
        }

        bool remove_callback(void(*fn)(Args..., UserDataType*), UserDataType* ud = nullptr) noexcept {
            if(fn == nullptr) return false;
            for(auto& e : m_entries) {
                if(e.function == fn && e.userdata == ud) {
                    e.function = nullptr;
                    e.userdata = nullptr;
                    return true;
                }
            }
            return false;
        }

        void call(Args... args) const noexcept {
            for(auto& e : m_entries) {
                if(e.function != nullptr)
                    e.function(args..., e.userdata);
            }
        }
    };
}