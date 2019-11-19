#include <stdlib.h>
#include <stdbool.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_tlmm.h"
#include "qapi/qapi_timer.h"
#include "qapi/qapi_socket.h"
#include "qapi/qapi_ns_utils.h"
#include "qapi/qapi_dnsc.h"
#include "qapi/qapi_mqtt.h"
#include "util/debug.h"
#include "util/trace.h"
#include "util/netmgr.h"
#include "util/htons.h"
#include "util/boot_cfg.h"
#include "stdio.h"
#include "txm_module.h"

#include "config.h"

#define TRACE_TAG "main"

static qapi_Net_MQTT_Hndl_t mqtt_client;

static void mqtt_msgcb(qapi_Net_MQTT_Hndl_t mqtt, int32_t reason, const uint8_t* topic, int32_t topic_length,
						const uint8_t* msg, int32_t msg_length, int32_t qos, const void* sid) {
	(void)reason;
	(void)topic;
	(void)topic_length;
	(void)qos;
	(void)sid;
	char reply[128];
	memset(reply, 0, 128);
	memcpy(reply, "Reply ", 6);
	msg_length = msg_length > 121 ? 121 : msg_length;
	memcpy(&reply[6], msg, msg_length);

	TRACE("sending reply: %s\r\n", reply);

	int res = qapi_Net_MQTT_Publish(mqtt, "test/reply", reply, msg_length + 6, 1, false);
	if(res != QAPI_OK) TRACE("failed to publish reply: %d\r\n", res);
}

static void mqtt_concb(qapi_Net_MQTT_Hndl_t mqtt, int32_t reason) {
	(void)reason;
	TRACE("connected to mqtt, reason=%d\r\n", reason);
	int res = qapi_Net_MQTT_Subscribe(mqtt, "test/echo", 1);
	if(res != QAPI_OK) TRACE("failed to subscribe to topic\r\n");
}

static void constate_changed(netmgr_constate_t s, void* a) {
	(void)a;
	if(s == NETMGR_connected) {
		TRACE("connected to the internet\r\n");
		qapi_Net_MQTT_Config_t config;
		const char* addr;
		char buf[16];
		memset(&config, 0x00, sizeof(config));
		config.remote.sa_family = AF_INET;
		int res = qapi_Net_DNSc_Reshost(MQTT_HOST, &config.remote);
		if(res != 0) TRACE("DNS Request failed: %d\r\n", res);
		else {
			addr = inet_ntop(config.remote.sa_family, &config.remote.sa_data, buf, 50);
			if(addr != NULL) {
				TRACE("connecting to: %s\r\n", addr);

				config.local.sa_family = AF_INET;
				config.remote.sa_port = htons(1883);
				config.nonblocking_connect = true;
				memcpy(config.client_id, MQTT_CLIENTID, sizeof(MQTT_CLIENTID) - 1);
				config.client_id_len = 5;
				config.keepalive_duration = 300;
				config.clean_session = 1;
				config.username = MQTT_USER;
				config.username_len = strlen((const char*)config.username);
				config.password = MQTT_PASS;
				config.password_len = strlen((const char*)config.password);

				res = qapi_Net_MQTT_Connect(mqtt_client, &config);
				if(res == QAPI_OK) TRACE("connected mqtt client\r\n");
				else TRACE("failed to connect mqtt client\r\n");
			} else {
				TRACE("failed to resolve host\r\n");
			}
		}
	} else TRACE("failed to connect to network\r\n");
}

int dam_app_start(void)
{
	TRACE("starting network\r\n");
	if(netmgr_init() != 0) {
		TRACE("failed to init network manager\r\n");
		return TX_SUCCESS;
	}
	netmgr_set_autoreconnect(true);
	netmgr_add_constate_cb(constate_changed, NULL);
	TRACE("connecting to network\r\n");
	if(netmgr_connect(APN, USER, PASS) != 0) {
		TRACE("failed to start connecting to network\r\n");
		return TX_SUCCESS;
	}

	TRACE("initiating mqtt\r\n");
	int res = qapi_Net_MQTT_New(&mqtt_client);
	if(res != QAPI_OK) TRACE("failed to create mqtt client\r\n");

	res = qapi_Net_MQTT_Set_Connect_Callback(mqtt_client, mqtt_concb);
	if(res != QAPI_OK) TRACE("failed to set mqtt callback\r\n");

	res = qapi_Net_MQTT_Set_Message_Callback(mqtt_client, mqtt_msgcb);
	if(res != QAPI_OK) TRACE("failed to set mqtt callback\r\n");

	TRACE("init done\r\n");

	// Global destructors run on return,
	// so we must make sure main does not return until
	// all background processes and threads are done.
	while(true) { tx_thread_sleep(10000); }
}
