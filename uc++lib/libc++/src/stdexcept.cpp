#include "stdexcept"
#include "typeinfo"
#include "new"

namespace std {
    logic_error::logic_error(const string &arg)
        : m_msg(arg)
    {}

    #if __cplusplus >= 201103L
    logic_error::logic_error(const char * str)
        : m_msg(str)
    {}
    #endif
        
    logic_error::logic_error(const logic_error &other) noexcept
        : m_msg(other.m_msg)
    {}

    logic_error& logic_error::operator=(const logic_error & other) noexcept {
        m_msg = other.m_msg;
        return *this;
    }

    logic_error::~logic_error() noexcept {

    }
    
    const char* logic_error::what() const noexcept {
        return m_msg.c_str();
    }

    domain_error::domain_error(const string &arg)
        : logic_error(arg)
    {}

    #if __cplusplus >= 201103L
    domain_error::domain_error(const char *str)
        : logic_error(str)
    {}
    #endif

    domain_error::~domain_error() noexcept {
    }

    invalid_argument::invalid_argument(const string &arg)
        : logic_error(arg)
    {}

    #if __cplusplus >= 201103L
    invalid_argument::invalid_argument(const char *str)
        : logic_error(str)
    {}
    #endif

    invalid_argument::~invalid_argument() noexcept {
    }

    length_error::length_error(const string &arg)
        : logic_error(arg)
    {}

    #if __cplusplus >= 201103L
    length_error::length_error(const char *str)
        : logic_error(str)
    {}
    #endif

    length_error::~length_error() noexcept {
    }

    out_of_range::out_of_range(const string &arg)
        : logic_error(arg)
    {}

    #if __cplusplus >= 201103L
    out_of_range::out_of_range(const char *str)
        : logic_error(str)
    {}
    #endif

    out_of_range::~out_of_range() noexcept {
    }

    runtime_error::runtime_error(const string &arg)
        : m_msg(arg)
    {}

    #if __cplusplus >= 201103L
    runtime_error::runtime_error(const char * str)
        : m_msg(str)
    {}
    #endif

    runtime_error::runtime_error(const runtime_error & o) noexcept
        : m_msg(o.m_msg)
    {}

    runtime_error& runtime_error::operator=(const runtime_error & o) noexcept {
        m_msg = o.m_msg;
        return *this;
    }

    runtime_error::~runtime_error() noexcept {
    }

    const char *runtime_error::what() const noexcept {
        return m_msg.c_str();
    }

    range_error::range_error(const string &arg)
        : runtime_error(arg)
    {}

    #if __cplusplus >= 201103L
    range_error::range_error(const char *str)
        : runtime_error(str)
    {}
    #endif

    range_error::~range_error() noexcept {
    }

    overflow_error::overflow_error(const string &arg)
        : runtime_error(arg)
    {}

    #if __cplusplus >= 201103L
    overflow_error::overflow_error(const char * str)
        : runtime_error(str)
    {}
    #endif

    overflow_error::~overflow_error() noexcept {
    }

    underflow_error::underflow_error(const string &arg)
        : runtime_error(arg)
    {}

    #if __cplusplus >= 201103L
    underflow_error::underflow_error(const char * str)
        : runtime_error(str)
    {}
    #endif

    underflow_error::~underflow_error() noexcept {
    }

    bad_alloc::~bad_alloc() noexcept { }

    const char* bad_alloc::what() const noexcept {
        return "std::bad_alloc";
    }

    bad_array_new_length::~bad_array_new_length() noexcept { }

    const char* bad_array_new_length::what() const noexcept {
        return "std::bad_array_new_length";
    }

    bad_cast::~bad_cast() noexcept { }

    const char* bad_cast::what() const noexcept {
        return "std::bad_cast";
    }

    bad_typeid::~bad_typeid() noexcept { }

    const char* bad_typeid::what() const noexcept {
        return "std::bad_typeid";
    }
}