#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_socket.h"
#include "qapi/qapi_dss.h"
#include "qapi/qapi_dnsc.h"
#include "qapi/qapi_ns_utils.h"
#include "qapi/qapi_timer.h"
#include "util/uart.h"
#include "util/boot_cfg.h"

#include "tx_api.h"

static uart_context_t uart;
static uint8_t uart_buf[256];
static qapi_DSS_Hndl_t dss_handle;

#include "../../config.h"

#define CHECK(x) {\
	result = x;\
	if(result != QAPI_OK) \
		uart_printf(uart, #x " failed: %d\r\n", result); \
}

static qapi_Status_t net_connect(void);
static int reconnect;

static int strlen_wrapper(const char* str) {
	if(str != NULL) return strlen(str);
	return 0;
}

static void net_cb(
	qapi_DSS_Hndl_t hndl, /* Handle for which this event is associated */
	void *user_data, /* Application-provided user data */
	qapi_DSS_Net_Evt_t evt, /* Event identifier */
	qapi_DSS_Evt_Payload_t *payload_ptr /* Associated event information */
)
{
	(void)hndl;
	(void)user_data;
	(void)payload_ptr;
	// Network is now available
	if(evt == QAPI_DSS_EVT_NET_IS_CONN_E)
	{
		uart_printf(uart, "network became active\r\n");
		
		// Check if DNS is already started
		if(0 == qapi_Net_DNSc_Is_Started())
		{
			uart_printf(uart, "starting dns client\r\n");
			qapi_Net_DNSc_Command(QAPI_NET_DNS_START_E);
		}

		unsigned int len = 0;
		int done = 0;
		// There might be more than one IP but I never had a mobile network that assigns more than one.
		if (qapi_DSS_Get_IP_Addr_Count(dss_handle, &len) == QAPI_OK)
		{
			uart_printf(uart, "number of ip addresses: %d\r\n", len);
			qapi_DSS_Addr_Info_t info;
			char dp_v4[16];
			char ds_v4[16];
			char ip_v4[16];
			char gateway_v4[16];
			memset(&info, 0, sizeof(qapi_DSS_Addr_Info_t));
			// Get upto 1 IP addresses, you should normaly alloc based on len to get all.
			if (qapi_DSS_Get_IP_Addr(dss_handle,&info,1) == QAPI_OK)
			{
				// Convert ip to strings
				if((NULL != inet_ntop(AF_INET,&info.iface_addr_s.addr.v4,ip_v4,sizeof(ip_v4)))
					&&(NULL != inet_ntop(AF_INET,&info.gtwy_addr_s.addr.v4,gateway_v4,sizeof(gateway_v4)))
					&&(NULL != inet_ntop(AF_INET,&info.dnsp_addr_s.addr.v4,dp_v4,sizeof(dp_v4)))
					&&(NULL != inet_ntop(AF_INET,&info.dnss_addr_s.addr.v4,ds_v4,sizeof(ds_v4))))
				{
					// And output it
					uart_printf(uart, "ip address:  %s\r\n", ip_v4);
					uart_printf(uart, "gateway:     %s\r\n", gateway_v4);
					uart_printf(uart, "dns servers: %s %s\r\n", dp_v4, ds_v4);
					// Use the first dns server for client
					if((0 == qapi_Net_DNSc_Add_Server(dp_v4, QAPI_NET_DNS_ANY_SERVER_ID) )
						&& (0 == qapi_Net_DNSc_Add_Server(ds_v4, QAPI_NET_DNS_ANY_SERVER_ID))) {
						done = 1;
					}
				} else {
					uart_printf(uart, " failed to parse addresses\r\n");
				}
				
			}
		}
		
		// We did not get a server by searching through our ips, so use google's
		if(!done)
		{
			qapi_Net_DNSc_Add_Server("8.8.4.4", QAPI_NET_DNS_ANY_SERVER_ID);
			qapi_Net_DNSc_Add_Server("8.8.8.8", QAPI_NET_DNS_ANY_SERVER_ID);
		}
	}
	else // We are now disconnected
	{
		uart_printf(uart, "network became inactive (%d)\r\n", evt);
		// Release handle
		if(dss_handle != NULL)
			qapi_DSS_Rel_Data_Srvc_Hndl(dss_handle);
		dss_handle = NULL;
		// and set flag to cause a reconnect
		reconnect = 1;
	}
}

static qapi_Status_t net_connect(void) {
	int result = 0;
	qapi_DSS_Call_Param_Value_t param_info;

	// get a handle to data service
	CHECK(qapi_DSS_Get_Data_Srvc_Hndl (net_cb, NULL,  &dss_handle));
 
	if (result == QAPI_OK && dss_handle != NULL )
	{   
		param_info.buf_val = NULL;
		param_info.num_val = QAPI_DSS_RADIO_TECH_UNKNOWN;
		CHECK(qapi_DSS_Set_Data_Call_Param(dss_handle, QAPI_DSS_CALL_INFO_TECH_PREF_E, &param_info));
 
		param_info.buf_val = NULL;
		param_info.num_val = QAPI_DSS_IP_VERSION_4;
		CHECK(qapi_DSS_Set_Data_Call_Param(dss_handle, QAPI_DSS_CALL_INFO_IP_VERSION_E, &param_info));
 
		param_info.buf_val = NULL;
		param_info.num_val = 1;
		CHECK(qapi_DSS_Set_Data_Call_Param(dss_handle, QAPI_DSS_CALL_INFO_UMTS_PROFILE_IDX_E, &param_info));

#ifdef APN
		param_info.buf_val = (char*)APN;
		param_info.num_val = strlen(APN);
		CHECK(qapi_DSS_Set_Data_Call_Param(dss_handle, QAPI_DSS_CALL_INFO_APN_NAME_E, &param_info));
#endif
#ifdef USER
		param_info.buf_val = (char*)USER;
		param_info.num_val = strlen_wrapper(USER);
		if(USER != NULL)
			CHECK(qapi_DSS_Set_Data_Call_Param(dss_handle, QAPI_DSS_CALL_INFO_USERNAME_E, &param_info));
#endif
#ifdef PASS
		param_info.buf_val = (char*)PASS;
		param_info.num_val = strlen_wrapper(PASS);
		if(PASS != NULL)
			CHECK(qapi_DSS_Set_Data_Call_Param(dss_handle, QAPI_DSS_CALL_INFO_PASSWORD_E, &param_info));
#endif
		CHECK(qapi_DSS_Start_Data_Call(dss_handle));
	}
	return result;
}

static void reconnect_cb(uint32_t udata) {
	(void)udata;
	// Called in a regular interval to trigger reconnecting
	if(reconnect == 1) {
		reconnect = 0;
		net_connect();
	}
}

int dam_app_start(void)
{
	if(boot_cfg() != 0) return TX_SUCCESS;
	uart_init_config_t uartcfg;
	uart_default_cfg(&uartcfg);
	uartcfg.buf = uart_buf;
	uartcfg.buf_len = 256;
	if(uart_init(&uart, &uartcfg) != QAPI_OK) return TX_SUCCESS;

	reconnect = 1;

	// Init a timer for reconnections. See example 03-timer for details.
	qapi_TIMER_handle_t timer_handle;
	qapi_TIMER_define_attr_t timer_def_attr;
	memset(&timer_def_attr, 0, sizeof(timer_def_attr));
	timer_def_attr.cb_type = QAPI_TIMER_FUNC1_CB_TYPE;
	timer_def_attr.sigs_func_ptr = &reconnect_cb;
	int res = qapi_Timer_Def( &timer_handle, &timer_def_attr);
	if(res != 0) {
		uart_printf(uart, "failed to def timer: %d\r\n", res);
		return TX_SUCCESS;
	}

	qapi_TIMER_set_attr_t timer_set_attr;
	memset(&timer_set_attr, 0, sizeof(timer_set_attr));
	timer_set_attr.reload = 1000;
	timer_set_attr.time = 1000; 
	timer_set_attr.unit = QAPI_TIMER_UNIT_MSEC;
	res = qapi_Timer_Set(timer_handle, &timer_set_attr);
	if(res != 0){
		uart_printf(uart, "failed to set timer: %d\r\n", res);
	}

	uart_printf(uart, "init done\r\n");

	return TX_SUCCESS;
}
