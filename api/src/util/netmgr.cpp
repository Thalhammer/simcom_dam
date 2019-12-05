#include "util/netmgr.h"
#include "util/trace.h"

extern "C" {
#include "qapi/qapi.h"
#include "qapi/qapi_socket.h"
#include "qapi/qapi_dss.h"
#include "qapi/qapi_dnsc.h"
#include "qapi/qapi_ns_utils.h"
#include "qapi/qapi_timer.h"
}

#include "txpp/byte_pool.h"
#include "txpp/callback_list.h"

#define TRACE_TAG "netmgr"

typedef struct {
	netmgr_constate_cb_t callback;
	void* argument;
} callback_t;

#define MAX_CONSTATE_CBS 64

static struct {
	netmgr_constate_t constate;
	qapi_DSS_Hndl_t dss_handle;
	char* apn;
	char* user;
	char* pass;
	qapi_TIMER_handle_t reconnect_timer;
	txpp::callback_list<MAX_CONSTATE_CBS, void, netmgr_constate_t> constate_cbs;
	txpp::static_byte_pool<2048> pool;
} _netmgr_state;

static void _netmgr_dss_cb(
	qapi_DSS_Hndl_t hndl, /* Handle for which this event is associated */
	void *user_data, /* Application-provided user data */
	qapi_DSS_Net_Evt_t evt, /* Event identifier */
	qapi_DSS_Evt_Payload_t *payload_ptr /* Associated event information */
)
{
	(void)hndl;
	(void)user_data;
	(void)payload_ptr;
	int done = 0;

	if(evt == QAPI_DSS_EVT_NET_IS_CONN_E) {
		// Early out if we were already connected
		if (_netmgr_state.constate == NETMGR_connected)
			return;
		_netmgr_state.constate = NETMGR_connected;

		TRACE("network became active\r\n");

		// Check if DNS is already started
		if(0 == qapi_Net_DNSc_Is_Started())
		{
			TRACE("starting dns client\r\n");
			qapi_Net_DNSc_Command(QAPI_NET_DNS_START_E);
		}

		unsigned int len = 0;
		if (qapi_DSS_Get_IP_Addr_Count(_netmgr_state.dss_handle, &len) == QAPI_OK)
		{
			TRACE("number of ip addresses: %d\r\n", len);

			qapi_DSS_Addr_Info_t* info_ptr = (qapi_DSS_Addr_Info_t*)_netmgr_state.pool.calloc(len, sizeof(qapi_DSS_Addr_t));

			if (info_ptr != NULL && qapi_DSS_Get_IP_Addr(_netmgr_state.dss_handle,info_ptr,len) == QAPI_OK)
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
						TRACE("[%d]ip address:  %s\r\n", i, ip_v4);
						TRACE("[%d]gateway:     %s\r\n", i, gateway_v4);
						TRACE("[%d]dns servers: %s %s\r\n", i, dns_primary_v4, dns_secondary_v4);
						// Use the first dns server for client
						if(i == 0) {
							if((0 == qapi_Net_DNSc_Add_Server(dns_primary_v4, QAPI_NET_DNS_ANY_SERVER_ID) )
								&& (0 == qapi_Net_DNSc_Add_Server(dns_secondary_v4, QAPI_NET_DNS_ANY_SERVER_ID))) {
								done = 1;
							}
						}
					} else {
						TRACE("[%d] failed to parse addresses\r\n",i );
					}
				}
				_netmgr_state.pool.free(info_ptr);
			} else {
				TRACE("failed to allocate memory for ip addresses\r\n");
			}
		}
		
		if(!done)
		{
			qapi_Net_DNSc_Add_Server("8.8.8.8", QAPI_NET_DNS_ANY_SERVER_ID);
			qapi_Net_DNSc_Add_Server("8.8.4.4", QAPI_NET_DNS_ANY_SERVER_ID);
		}

		_netmgr_state.constate_cbs.call(_netmgr_state.constate);
	} else if(evt == QAPI_DSS_EVT_NET_NO_NET_E) {
		if (_netmgr_state.constate == NETMGR_disconnected)
			return;
		_netmgr_state.constate = NETMGR_disconnected;
		
		TRACE("network became inactive\r\n");
		if(_netmgr_state.dss_handle != NULL)
			qapi_DSS_Rel_Data_Srvc_Hndl(_netmgr_state.dss_handle);
		_netmgr_state.dss_handle = NULL;

		_netmgr_state.constate_cbs.call(_netmgr_state.constate);
	} else if(evt == QAPI_DSS_EVT_NET_RECONFIGURED_E) {
		TRACE("network call reconfigured\r\n");
	} else if(evt == QAPI_DSS_EVT_NET_NEWADDR_E) {
		TRACE("network got new ip\r\n");
	} else if(evt == QAPI_DSS_EVT_NET_DELADDR_E) {
		TRACE("network lost ip\r\n");
	} else if(evt == QAPI_DSS_EVT_NIPD_DL_DATA_E) {
		TRACE("QAPI_DSS_EVT_NIPD_DL_DATA_E\r\n");
	} else {
		TRACE("unknown network event %d\r\n", evt);
	}
}

static void _netmgr_reconnect_cb() {
	if(_netmgr_state.constate == NETMGR_disconnected) {
		netmgr_reconnect();
	}
}

extern "C" int netmgr_init(void) {
	TRACE("netmgr is initialising\r\n");
	_netmgr_state.constate = NETMGR_initiated;
	_netmgr_state.dss_handle = NULL;
	_netmgr_state.apn = NULL;
	_netmgr_state.user = NULL;
	_netmgr_state.pass = NULL;
	_netmgr_state.reconnect_timer = NULL;
	return QAPI_OK;
}

extern "C" int netmgr_add_constate_cb(netmgr_constate_cb_t cb, void* arg) {
	return _netmgr_state.constate_cbs.add_callback(cb, arg) ? 1 : 0;
}

extern "C" int netmgr_remove_constate_cb(netmgr_constate_cb_t cb, void* arg) {
	return _netmgr_state.constate_cbs.remove_callback(cb, arg) ? 1 : 0;
}

extern "C" int netmgr_connect(const char* APN, const char* user, const char* pw) {
	char* buf_apn = NULL;
	char* buf_user = NULL;
	char* buf_pw = NULL;

	int len_apn = APN != NULL ? strlen(APN) : 0;
	int len_user = user != NULL ? strlen(user) : 0;
	int len_pw = pw != NULL ? strlen(pw) : 0;

	// Duplicate arguments
	if(len_apn != 0) {
		buf_apn = (char*)_netmgr_state.pool.malloc(len_apn + 1);
		if(buf_apn == NULL) {
			TRACE("failed to alloc memory for apn\r\n");
			return QAPI_ERR_NO_MEMORY;
		}
		memcpy(buf_apn, APN, len_apn + 1);
	}
	if(len_user != 0) {
		buf_user = (char*)_netmgr_state.pool.malloc(len_user + 1);
		if(buf_user == NULL) {
			TRACE("failed to alloc memory for user\r\n");
			_netmgr_state.pool.free(buf_apn);
			return QAPI_ERR_NO_MEMORY;
		}
		memcpy(buf_user, user, len_user + 1);
	}
	if(len_pw != 0) {
		buf_pw = (char*)_netmgr_state.pool.malloc(len_pw + 1);
		if(buf_pw == NULL) {
			TRACE("failed to alloc memory for pw\r\n");
			_netmgr_state.pool.free(buf_apn);
			_netmgr_state.pool.free(buf_user);
			return QAPI_ERR_NO_MEMORY;
		}
		memcpy(buf_pw, pw, len_pw + 1);
	}
	// Release old params
	_netmgr_state.pool.free(_netmgr_state.apn);
	_netmgr_state.pool.free(_netmgr_state.user);
	_netmgr_state.pool.free(_netmgr_state.pass);
	_netmgr_state.apn = buf_apn;
	_netmgr_state.user = buf_user;
	_netmgr_state.pass = buf_pw;
	int res = netmgr_reconnect();
	if(res != QAPI_OK && _netmgr_state.reconnect_timer != NULL) {
		_netmgr_state.constate = NETMGR_disconnected;
		return TX_SUCCESS;
	}
	return res;
}

extern "C" int netmgr_reconnect(void) {
	int result = 0;
	qapi_DSS_Call_Param_Value_t param_info;

	TRACE("reconnecting network\r\n");

	_netmgr_state.constate = NETMGR_connecting;

	result = qapi_DSS_Get_Data_Srvc_Hndl(_netmgr_dss_cb, NULL,  &_netmgr_state.dss_handle);
 
	if (result != QAPI_OK || _netmgr_state.dss_handle == NULL ) { TRACE("failed to get data hndl: %d\r\n", result); return result; }
	
	param_info.buf_val = NULL;
	param_info.num_val = QAPI_DSS_RADIO_TECH_UNKNOWN;
	result = qapi_DSS_Set_Data_Call_Param(_netmgr_state.dss_handle, QAPI_DSS_CALL_INFO_TECH_PREF_E, &param_info);
	if(result != QAPI_OK) { TRACE("failed to set tech param: %d\r\n", result); return result; }
	param_info.buf_val = NULL;
	param_info.num_val = QAPI_DSS_IP_VERSION_4;
	result = qapi_DSS_Set_Data_Call_Param(_netmgr_state.dss_handle, QAPI_DSS_CALL_INFO_IP_VERSION_E, &param_info);
	if(result != QAPI_OK) { TRACE("failed to set ipversion param: %d\r\n", result); return result; }
	param_info.buf_val = NULL;
	param_info.num_val = 1;
	result = qapi_DSS_Set_Data_Call_Param(_netmgr_state.dss_handle, QAPI_DSS_CALL_INFO_UMTS_PROFILE_IDX_E, &param_info);
	if(result != QAPI_OK) { TRACE("failed to set profile param: %d\r\n", result); return result; }
	if(_netmgr_state.apn != NULL)
	{
		param_info.buf_val = (char*)_netmgr_state.apn;
		param_info.num_val = strlen(_netmgr_state.apn);
		result = qapi_DSS_Set_Data_Call_Param(_netmgr_state.dss_handle, QAPI_DSS_CALL_INFO_APN_NAME_E, &param_info);
		if(result != QAPI_OK) { TRACE("failed to set apn param: %d\r\n", result); return result; }
	}
	if(_netmgr_state.user != NULL)
	{
		param_info.buf_val = (char*)_netmgr_state.user;
		param_info.num_val = strlen(_netmgr_state.user);
		result = qapi_DSS_Set_Data_Call_Param(_netmgr_state.dss_handle, QAPI_DSS_CALL_INFO_USERNAME_E, &param_info);
		if(result != QAPI_OK) { TRACE("failed to set user param: %d\r\n", result); return result; }
	}
	if(_netmgr_state.pass != NULL)
	{
		param_info.buf_val = (char*)_netmgr_state.pass;
		param_info.num_val = strlen(_netmgr_state.pass);
		result = qapi_DSS_Set_Data_Call_Param(_netmgr_state.dss_handle, QAPI_DSS_CALL_INFO_PASSWORD_E, &param_info);
		if(result != QAPI_OK) { TRACE("failed to set pass param: %d\r\n", result); return result; }
	}
	result = qapi_DSS_Start_Data_Call (_netmgr_state.dss_handle);
	if(result != QAPI_OK) { TRACE("failed to start data call: %d\r\n", result); return result; }

	return result;
}

extern "C" void netmgr_dump_status(void) {
	int res;
	qapi_DSS_Data_Pkt_Stats_t stats;
	memset(&stats, 0, sizeof(stats));
	res = qapi_DSS_Get_Pkt_Stats(_netmgr_state.dss_handle, &stats);
	if(res != QAPI_OK) {
		TRACE("could not get packet statistics\r\n");
	} else {
		TRACE("rx=%d(%d bytes), tx=%d(%d bytes), droppedrx=%d, droppedtx=%d\r\n",
			(int)stats.pkts_rx, (int)stats.bytes_rx, (int)stats.pkts_tx, (int)stats.bytes_tx, (int)stats.pkts_dropped_rx, (int)stats.pkts_dropped_tx);
	}
}

extern "C" netmgr_constate_t netmgr_get_state(void) {
	return _netmgr_state.constate;
}

extern "C" void netmgr_set_autoreconnect(int s) {
	if(_netmgr_state.reconnect_timer == NULL && s == 1) {
		qapi_TIMER_define_attr_t timer_def_attr;
		memset(&timer_def_attr, 0, sizeof(timer_def_attr));
		timer_def_attr.cb_type = QAPI_TIMER_FUNC1_CB_TYPE;
		timer_def_attr.sigs_func_ptr = (void*)_netmgr_reconnect_cb;
		int res = qapi_Timer_Def( &_netmgr_state.reconnect_timer, &timer_def_attr);
		if(res != 0) {
			TRACE("failed to define reconnect timer: %d\r\n", res);
			return;
		}

		qapi_TIMER_set_attr_t timer_set_attr;
		memset(&timer_set_attr, 0, sizeof(timer_set_attr));
		timer_set_attr.reload = 1000;
		timer_set_attr.time = 1000; 
		timer_set_attr.unit = QAPI_TIMER_UNIT_MSEC;
		res = qapi_Timer_Set(_netmgr_state.reconnect_timer, &timer_set_attr);
		if(res != 0){
			TRACE("failed to set reconnect timer: %d\r\n", res);
			res = qapi_Timer_Undef(_netmgr_state.reconnect_timer);
			if(res != 0) {
				TRACE("failed to undef reconnect timer: %d\r\n", res);
				return;
			}
		}
	} else if(_netmgr_state.reconnect_timer != NULL && s == 0) {
		int res = qapi_Timer_Stop(_netmgr_state.reconnect_timer);
		if(res != 0) {
			TRACE("failed to stop reconnect timer: %d\r\n", res);
			return;
		}
		res = qapi_Timer_Undef(_netmgr_state.reconnect_timer);
		if(res != 0) {
			TRACE("failed to undef reconnect timer: %d\r\n", res);
			return;
		}
		_netmgr_state.reconnect_timer = NULL;
	}
}
