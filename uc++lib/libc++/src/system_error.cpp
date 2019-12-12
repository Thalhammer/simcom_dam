#include "system_error"

#define MSG_CASE(x) case errc::x: return #x;

namespace std {
    error_condition error_category::default_error_condition(int val) const noexcept {
        return error_condition (val, *this);
    }

    bool error_category::equivalent(int valcode, const error_condition& cond) const noexcept {
        return default_error_condition(valcode) == cond;
    }

    bool error_category::equivalent(const error_code& code, int valcond) const noexcept {
        return *this == code.category() && code.value() == valcond;
    }

    class system_error_category : public error_category {
    public:
        const char* name() const noexcept override {
            return "system";
        }

        std::string message(int val) const override {
            switch(static_cast<errc>(val)) {
                MSG_CASE(success)
                MSG_CASE(address_family_not_supported)
                MSG_CASE(address_in_use)
                MSG_CASE(address_not_available)
                MSG_CASE(already_connected)
                MSG_CASE(argument_list_too_long)
                MSG_CASE(argument_out_of_domain)
                MSG_CASE(bad_address)
                MSG_CASE(bad_file_descriptor)
                MSG_CASE(bad_message)
                MSG_CASE(broken_pipe)
                MSG_CASE(connection_aborted)
                MSG_CASE(connection_already_in_progress)
                MSG_CASE(connection_refused)
                MSG_CASE(connection_reset)
                MSG_CASE(cross_device_link)
                MSG_CASE(destination_address_required)
                MSG_CASE(device_or_resource_busy)
                MSG_CASE(directory_not_empty)
                MSG_CASE(executable_format_error)
                MSG_CASE(file_exists)
                MSG_CASE(file_too_large)
                MSG_CASE(filename_too_long)
                MSG_CASE(function_not_supported)
                MSG_CASE(host_unreachable)
                MSG_CASE(identifier_removed)
                MSG_CASE(illegal_byte_sequence)
                MSG_CASE(inappropriate_io_control_operation)
                MSG_CASE(interrupted)
                MSG_CASE(invalid_argument)
                MSG_CASE(invalid_seek)
                MSG_CASE(io_error)
                MSG_CASE(is_a_directory)
                MSG_CASE(message_size)
                MSG_CASE(network_down)
                MSG_CASE(network_reset)
                MSG_CASE(network_unreachable)
                MSG_CASE(no_buffer_space)
                MSG_CASE(no_child_process)
                MSG_CASE(no_link)
                MSG_CASE(no_lock_available)
                MSG_CASE(no_message)
                MSG_CASE(no_message_available)
                MSG_CASE(no_protocol_option)
                MSG_CASE(no_space_on_device)
                MSG_CASE(no_stream_resources)
                MSG_CASE(no_such_device)
                MSG_CASE(no_such_device_or_address)
                MSG_CASE(no_such_file_or_directory)
                MSG_CASE(no_such_process)
                MSG_CASE(not_a_directory)
                MSG_CASE(not_a_socket)
                MSG_CASE(not_a_stream)
                MSG_CASE(not_connected)
                MSG_CASE(not_enough_memory)
                MSG_CASE(not_supported)
                MSG_CASE(operation_canceled)
                MSG_CASE(operation_in_progress)
                MSG_CASE(operation_not_permitted)
                MSG_CASE(operation_not_supported)
                MSG_CASE(operation_would_block)
                MSG_CASE(owner_dead)
                MSG_CASE(permission_denied)
                MSG_CASE(protocol_error)
                MSG_CASE(protocol_not_supported)
                MSG_CASE(read_only_file_system)
                MSG_CASE(resource_deadlock_would_occur)
                MSG_CASE(resource_unavailable_try_again)
                MSG_CASE(result_out_of_range)
                MSG_CASE(state_not_recoverable)
                MSG_CASE(stream_timeout)
                MSG_CASE(text_file_busy)
                MSG_CASE(timed_out)
                MSG_CASE(too_many_files_open)
                MSG_CASE(too_many_files_open_in_system)
                MSG_CASE(too_many_links)
                MSG_CASE(too_many_symbolic_link_levels)
                MSG_CASE(value_too_large)
                MSG_CASE(wrong_protocol_type)
                default: return "unknown";
            }
        }
    };

    class generic_error_category : public error_category {
    public:
        const char* name() const noexcept override {
            return "generic";
        }

        std::string message(int val) const override {
            return system_category().message(val);
        }
    };

    const error_category& system_category() noexcept {
        static const system_error_category instance;
        return instance;
    }
    const error_category& generic_category() noexcept {
        static const generic_error_category instance;
        return instance;
    }
}