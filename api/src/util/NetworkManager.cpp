#include "util/NetworkManager.h"
#include "util/trace.h"
#include <cstring>

extern "C" {
#include "qapi/qapi.h"
#include "qapi/qapi_socket.h"
#include "qapi/qapi_dss.h"
#include "qapi/qapi_dnsc.h"
#include "qapi/qapi_ns_utils.h"
#include "qapi/qapi_timer.h"
}

#define TRACE_TAG "NetworkManager"

bool NetworkManager::begin() noexcept {
    return true;
}

bool NetworkManager::end() noexcept {
    return true;
}

bool NetworkManager::add_constate_cb(void(*fn)(constate, void*), void* arg) noexcept {
    return m_constate_cbs.add_callback(fn, arg);
}

bool NetworkManager::remove_constate_cb(void(*fn)(constate, void*), void* arg) noexcept {
    return m_constate_cbs.remove_callback(fn, arg);
}

bool NetworkManager::connect(const char* APN, const char* user, const char* pw) noexcept {
    if(APN != nullptr && strlen(APN) > sizeof(m_apn) - 1) return false;
    if(user != nullptr && strlen(user) > sizeof(m_username) - 1) return false;
    if(pw != nullptr && strlen(pw) > sizeof(m_password) - 1) return false;
    memset(m_apn, 0, sizeof(m_apn));
    memset(m_username, 0, sizeof(m_username));
    memset(m_password, 0, sizeof(m_password));
    if(APN) strcpy(m_apn, APN);
    if(user) strcpy(m_username, user);
    if(pw) strcpy(m_password, pw);
    if(!reconnect()) {
        m_constate = constate::disconnected;
        return false;
    }
    return true;
}

bool NetworkManager::reconnect() noexcept {
	qapi_DSS_Call_Param_Value_t param_info;

	if(m_debug_enabled) TRACE("reconnecting network\r\n");

	m_constate = constate::connecting;

	auto result = qapi_DSS_Get_Data_Srvc_Hndl(&NetworkManager::_dss_cb, this,  &m_dss_handle);
 
	if (result != QAPI_OK || m_dss_handle == NULL ) {
        if(m_debug_enabled) TRACE("failed to get data hndl: %d\r\n", result);
        return false;
    }
	
	param_info.buf_val = NULL;
	param_info.num_val = QAPI_DSS_RADIO_TECH_UNKNOWN;
	result = qapi_DSS_Set_Data_Call_Param(m_dss_handle, QAPI_DSS_CALL_INFO_TECH_PREF_E, &param_info);
	if(result != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to set tech param: %d\r\n", result);
        return false;
    }
	param_info.buf_val = NULL;
	param_info.num_val = QAPI_DSS_IP_VERSION_4;
	result = qapi_DSS_Set_Data_Call_Param(m_dss_handle, QAPI_DSS_CALL_INFO_IP_VERSION_E, &param_info);
	if(result != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to set ipversion param: %d\r\n", result);
        return false;
    }
	param_info.buf_val = NULL;
	param_info.num_val = 1;
	result = qapi_DSS_Set_Data_Call_Param(m_dss_handle, QAPI_DSS_CALL_INFO_UMTS_PROFILE_IDX_E, &param_info);
	if(result != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to set profile param: %d\r\n", result);
        return false;
    }
	if(m_apn[0] != '\0')
	{
		param_info.buf_val = (char*)m_apn;
		param_info.num_val = strlen(m_apn);
		result = qapi_DSS_Set_Data_Call_Param(m_dss_handle, QAPI_DSS_CALL_INFO_APN_NAME_E, &param_info);
		if(result != QAPI_OK) {
            if(m_debug_enabled) TRACE("failed to set apn param: %d\r\n", result);
            return false;
        }
	}
	if(m_username[0] != '\0')
	{
		param_info.buf_val = (char*)m_username;
		param_info.num_val = strlen(m_username);
		result = qapi_DSS_Set_Data_Call_Param(m_dss_handle, QAPI_DSS_CALL_INFO_USERNAME_E, &param_info);
		if(result != QAPI_OK) {
            if(m_debug_enabled) TRACE("failed to set user param: %d\r\n", result);
            return false;
        }
	}
	if(m_password[0] != '\0')
	{
		param_info.buf_val = (char*)m_password;
		param_info.num_val = strlen(m_password);
		result = qapi_DSS_Set_Data_Call_Param(m_dss_handle, QAPI_DSS_CALL_INFO_PASSWORD_E, &param_info);
		if(result != QAPI_OK) {
            if(m_debug_enabled) TRACE("failed to set pass param: %d\r\n", result);
            return false;
        }
	}
	result = qapi_DSS_Start_Data_Call(m_dss_handle);
	if(result != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to start data call: %d\r\n", result);
        return false;
    }

	return true;
}

bool NetworkManager::dump_status() noexcept {
	qapi_DSS_Data_Pkt_Stats_t stats;
	memset(&stats, 0, sizeof(stats));
	auto res = qapi_DSS_Get_Pkt_Stats(m_dss_handle, &stats);
	if(res != QAPI_OK) {
		if(m_debug_enabled) TRACE("could not get packet statistics\r\n");
        return false;
	} else {
		if(m_debug_enabled) TRACE("rx=%d(%d bytes), tx=%d(%d bytes), droppedrx=%d, droppedtx=%d\r\n",
			(int)stats.pkts_rx, (int)stats.bytes_rx, (int)stats.pkts_tx, (int)stats.bytes_tx, (int)stats.pkts_dropped_rx, (int)stats.pkts_dropped_tx);
        return true;
    }
}

bool NetworkManager::set_autoreconnect(bool enabled) noexcept {
    if(m_reconnect_timer == NULL && enabled) {
		qapi_TIMER_define_attr_t timer_def_attr;
		memset(&timer_def_attr, 0, sizeof(timer_def_attr));
		timer_def_attr.cb_type = QAPI_TIMER_FUNC1_CB_TYPE;
		timer_def_attr.sigs_func_ptr = (void*)_reconnect_cb;
        timer_def_attr.sigs_mask_data = (uint32_t)this;
		int res = qapi_Timer_Def( &m_reconnect_timer, &timer_def_attr);
		if(res != 0) {
			if(m_debug_enabled) TRACE("failed to define reconnect timer: %d\r\n", res);
			return false;
		}

		qapi_TIMER_set_attr_t timer_set_attr;
		memset(&timer_set_attr, 0, sizeof(timer_set_attr));
		timer_set_attr.reload = 1000;
		timer_set_attr.time = 1000; 
		timer_set_attr.unit = QAPI_TIMER_UNIT_MSEC;
		res = qapi_Timer_Set(m_reconnect_timer, &timer_set_attr);
		if(res != 0){
			if(m_debug_enabled) TRACE("failed to set reconnect timer: %d\r\n", res);
			res = qapi_Timer_Undef(m_reconnect_timer);
            m_reconnect_timer = nullptr;
			if(res != 0) {
				if(m_debug_enabled) TRACE("failed to undef reconnect timer: %d\r\n", res);
			}
            return false;
		}
	} else if(m_reconnect_timer != NULL && !enabled) {
		int res = qapi_Timer_Stop(m_reconnect_timer);
		if(res != 0) {
			if(m_debug_enabled) TRACE("failed to stop reconnect timer: %d\r\n", res);
			return false;
		}
		res = qapi_Timer_Undef(m_reconnect_timer);
		if(res != 0) {
			if(m_debug_enabled) TRACE("failed to undef reconnect timer: %d\r\n", res);
			return false;
		}
		m_reconnect_timer = nullptr;
	}
    return true;
}

void NetworkManager::_dss_cb(
	void* hndl, /* Handle for which this event is associated */
	void *user_data, /* Application-provided user data */
	int evt, /* Event identifier */
	void *payload_ptr /* Associated event information */
)
{
    auto that = reinterpret_cast<NetworkManager*>(user_data);
	(void)hndl;
	(void)payload_ptr;
	int done = 0;

	if(evt == QAPI_DSS_EVT_NET_IS_CONN_E) {
		// Early out if we were already connected
		if (that->m_constate == constate::connected)
			return;
		that->m_constate = constate::connected;

		if(that->m_debug_enabled) TRACE("network became active\r\n");

		// Check if DNS is already started
		if(0 == qapi_Net_DNSc_Is_Started())
		{
			if(that->m_debug_enabled) TRACE("starting dns client\r\n");
			qapi_Net_DNSc_Command(QAPI_NET_DNS_START_E);
		}

		unsigned int len = 0;
		if (qapi_DSS_Get_IP_Addr_Count(that->m_dss_handle, &len) == QAPI_OK)
		{
			if(that->m_debug_enabled) TRACE("number of ip addresses: %d\r\n", len);

			qapi_DSS_Addr_Info_t info_ptr[len];

			if (qapi_DSS_Get_IP_Addr(that->m_dss_handle,info_ptr,len) == QAPI_OK)
			{
				for(uint32_t i=0; i < len; i++) {
					char dns_primary_v4[16];
					char dns_secondary_v4[16];
					char ip_v4[16];
					char gateway_v4[16];
					if((NULL != inet_ntop(AF_INET,&info_ptr[i].iface_addr_s.addr.v4,ip_v4,sizeof(ip_v4)))
						&&(NULL != inet_ntop(AF_INET,&info_ptr[i].gtwy_addr_s.addr.v4,gateway_v4,sizeof(gateway_v4)))
						&&(NULL != inet_ntop(AF_INET,&info_ptr[i].dnsp_addr_s.addr.v4,dns_primary_v4,sizeof(dns_primary_v4)))
						&&(NULL != inet_ntop(AF_INET,&info_ptr[i].dnss_addr_s.addr.v4,dns_secondary_v4,sizeof(dns_secondary_v4))))
					{
                        if(that->m_debug_enabled) {
                            TRACE("[%d]ip address:  %s\r\n", i, ip_v4);
                            TRACE("[%d]gateway:     %s\r\n", i, gateway_v4);
                            TRACE("[%d]dns servers: %s %s\r\n", i, dns_primary_v4, dns_secondary_v4);
                        }
						// Use the first dns server for client
						if(i == 0) {
							if((0 == qapi_Net_DNSc_Add_Server(dns_primary_v4, QAPI_NET_DNS_ANY_SERVER_ID) )
								&& (0 == qapi_Net_DNSc_Add_Server(dns_secondary_v4, QAPI_NET_DNS_ANY_SERVER_ID))) {
								done = 1;
							}
						}
					} else {
						if(that->m_debug_enabled) TRACE("[%d] failed to parse addresses\r\n",i );
					}
				}
			} else {
				if(that->m_debug_enabled) TRACE("failed to allocate memory for ip addresses\r\n");
			}
		}
		
		if(!done)
		{
			qapi_Net_DNSc_Add_Server("8.8.8.8", QAPI_NET_DNS_ANY_SERVER_ID);
			qapi_Net_DNSc_Add_Server("8.8.4.4", QAPI_NET_DNS_ANY_SERVER_ID);
		}

		that->m_constate_cbs.call(that->m_constate);
	} else if(evt == QAPI_DSS_EVT_NET_NO_NET_E) {
		if (that->m_constate == constate::disconnected)
			return;
		that->m_constate = constate::disconnected;
		
		if(that->m_debug_enabled) TRACE("network became inactive\r\n");
		if(that->m_dss_handle != NULL)
			qapi_DSS_Rel_Data_Srvc_Hndl(that->m_dss_handle);
		that->m_dss_handle = NULL;

		that->m_constate_cbs.call(that->m_constate);
	} else if(evt == QAPI_DSS_EVT_NET_RECONFIGURED_E) {
		if(that->m_debug_enabled) TRACE("network call reconfigured\r\n");
	} else if(evt == QAPI_DSS_EVT_NET_NEWADDR_E) {
		if(that->m_debug_enabled) TRACE("network got new ip\r\n");
	} else if(evt == QAPI_DSS_EVT_NET_DELADDR_E) {
		if(that->m_debug_enabled) TRACE("network lost ip\r\n");
	} else if(evt == QAPI_DSS_EVT_NIPD_DL_DATA_E) {
		if(that->m_debug_enabled) TRACE("QAPI_DSS_EVT_NIPD_DL_DATA_E\r\n");
	} else {
		if(that->m_debug_enabled) TRACE("unknown network event %d\r\n", evt);
	}
}

void NetworkManager::_reconnect_cb(void* ptr) {
    auto that = reinterpret_cast<NetworkManager*>(ptr);
	if(that->m_constate == constate::disconnected) {
		that->reconnect();
	}
}

NetworkManager Network;