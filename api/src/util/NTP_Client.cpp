#include "util/NTP_Client.h"
#include "util/trace.h"
#include "assert.h"
#include "util/htons.h"
#include "util/time.h"
extern "C" {
#include "qapi/qapi_socket.h"
#include "qapi/qapi_ns_utils.h"
#include "qapi/qapi_dnsc.h"
}

#define TRACE_TAG "NTP_Client"

bool NTP_Client::begin() noexcept {
    return true;
}

bool NTP_Client::end() noexcept {
    return true;
}

const uint8_t ntp_send[] = {
0xe3, 0x00, 0x06, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x4e, 0x31, 0x34,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

bool NTP_Client::sync(const char* remotestr) noexcept {
    if(remotestr == nullptr) remotestr = "pool.ntp.org";
    int res;

    sockaddr_in remote;
	remote.sin_family = AF_INET;
    res = qapi_Net_DNSc_Reshost(remotestr, &remote);
	if(res != 0) {
        if(m_debug_enabled) TRACE("DNS Request failed: %d\r\n", res);
        return false;
	}
	char buf[16];
	const char* addr = inet_ntop(remote.sin_family, &remote.sin_addr, buf, sizeof(buf));
    if(addr == NULL) {
        if(m_debug_enabled) TRACE("inet_ntop failed\r\n");
        return false;
    }
	
    if(m_debug_enabled) TRACE("connecting to: %s %s\r\n", remotestr, addr);

    remote.sin_family = AF_INET;
    remote.sin_port = htons(123);

    int socket = qapi_socket(AF_INET, SOCK_DGRAM, 0);
    if(socket < 0) return false;

    if(m_debug_enabled) TRACE("socket=%d\r\n", socket);

    uint8_t result[128];
    for(size_t i=0; i<10; i++) {
        res = qapi_sendto(socket, ntp_send, sizeof(ntp_send), 0, &remote, sizeof(sockaddr_in));
        if(m_debug_enabled) TRACE("sento= %d %d\r\n", res, qapi_errno(socket));
        if(res != 48) {
            qapi_socketclose(socket);
            return false;
        }

        fd_set set;
        qapi_fd_zero(&set);
        qapi_fd_set(socket, &set);
        res = qapi_select(&set, NULL, NULL, 250);
        if(m_debug_enabled) TRACE("res=%d\r\n", res);
        if(res == 1) {
            res = qapi_recvfrom(socket, result, sizeof(result), MSG_DONTWAIT, NULL, NULL);
            if(m_debug_enabled) TRACE("recvfrom= %d\r\n", res);
            if(res != 48) {
                continue;
            }
            qapi_socketclose(socket);

            if(m_debug_enabled) TRACE("%x %x %x %x\r\n", result[40], result[41], result[42], result[43]);
            uint32_t time = result[40];
            time = time << 8 | result[41];
            time = time << 8 | result[42];
            time = time << 8 | result[43];
            time -= 2208988800; // NTP Date epoch is 1.1.1900, while unix epoch is 1.1.1970 => remove 70 years
            qapi_time_get_t ctime;
            if(qapi_time_get(QAPI_TIME_MSECS, &ctime) != QAPI_OK) {
                if(m_debug_enabled) TRACE("failed to get rtc time\r\n");
            }
            m_timeoffset = time - (ctime.time_msecs/1000);
            return true;
        }
    }
    if(m_debug_enabled) TRACE("Failed to get ntp response in time\r\n");
    qapi_socketclose(socket);
    return false;
}

time_unix_type NTP_Client::get_offset() const noexcept {
    return m_timeoffset;
}

time_unix_type NTP_Client::get_time() const noexcept {
    qapi_time_get_t ctime;
    if(qapi_time_get(QAPI_TIME_MSECS, &ctime) != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to get rtc time\r\n");
        return 0;
    }
    return m_timeoffset + (ctime.time_msecs / 1000);
}