#include "util/MQTT_Client.h"
#include "util/trace.h"
#include "assert.h"
#include "util/AsmBuilder.h"
#include "util/htons.h"
#include "util/NetworkManager.h"
extern "C" {
#include "qapi/qapi_socket.h"
#include "qapi/qapi_ns_utils.h"
#include "qapi/qapi_dnsc.h"
#include "qapi/qapi_mqtt.h"
}

#define TRACE_TAG "MQTT_Client"

#define EVT_FLAG_INIT_DONE    (1<<0)
#define EVT_FLAG_IS_CONNECTED (1<<1)
#define EVT_FLAG_PUBLISH_LOCK (1<<2)
#define EVT_FLAG_PUBLISH_DONE (1<<3)

void MQTT_Client::ConnectCB(MQTT_Client* instance, int32_t reason) {
    if(instance->m_debug_enabled) TRACE("ConnectCB(%p, %d)\r\n", instance, reason);

    if(reason == 0) {
        instance->m_flags.set(EVT_FLAG_IS_CONNECTED, TX_OR);
    } else {
        ULONG act;
        instance->m_flags.get(EVT_FLAG_IS_CONNECTED, TX_OR_CLEAR, &act);
    }
    instance->m_on_connect.call(reason);
}

void MQTT_Client::SubscribeCB(MQTT_Client* instance, int32_t reason, const uint8_t* topic,
    int32_t topic_length, int32_t qos, const void* sid) {
    (void)topic_length;

    if(instance->m_debug_enabled) TRACE("SubscribeCB(%p, %d, %s, %d, %p)\r\n", instance, reason, topic, qos, sid);
}

void MQTT_Client::MessageCB(MQTT_Client* instance, int32_t reason, const uint8_t* topic, int32_t topic_length,
    const uint8_t* msg, int32_t msg_length, int32_t qos, const void* sid) {
    (void)topic_length;
    (void)msg_length;

    if(instance->m_debug_enabled) TRACE("MessageCB(%p, %d, %s, %s, %d, %p)\r\n", instance, reason, topic, msg, qos, sid);
}

void MQTT_Client::PublishCB(MQTT_Client* instance, int msgtype, int qos, uint16_t msg_id) {
    if(instance->m_debug_enabled) TRACE("PublishCB(%p, %d, %d, %d)\r\n", instance, msgtype, qos, (int)msg_id);
    instance->m_flags.set(EVT_FLAG_PUBLISH_DONE, TX_OR);
    instance->m_on_publish.call(msgtype, qos, msg_id);
}

bool MQTT_Client::begin() noexcept {
    if(m_is_initialized) return true;

    if(!m_flags.is_initialized() && !m_flags.initialize("MQTT_Client_flags")) {
        if(m_debug_enabled) TRACE("failed to create event flags\r\n");
        return false;
    }

    AsmBuilder builder(m_callback_wrapper_code, sizeof(m_callback_wrapper_code));
    auto concb = (qapi_Net_MQTT_Connect_CB_t)m_callback_wrapper_code;
	builder.mov(AsmBuilder::r0, (uint32_t)this);        // mov r0, this
	builder.branch(&MQTT_Client::ConnectCB);            // b Callback
    auto subcb = (qapi_Net_MQTT_Subscribe_CB_t)&m_callback_wrapper_code[builder.get_length()];
	builder.mov(AsmBuilder::r0, (uint32_t)this);        // mov r0, this
	builder.branch(&MQTT_Client::SubscribeCB);          // b Callback
    auto msgcb = (qapi_Net_MQTT_Message_CB_t)&m_callback_wrapper_code[builder.get_length()];
	builder.mov(AsmBuilder::r0, (uint32_t)this);        // mov r0, this
	builder.branch(&MQTT_Client::MessageCB);            // b Callback
    auto pubcb = (qapi_Net_MQTT_Publish_CB_t)&m_callback_wrapper_code[builder.get_length()];
	builder.mov(AsmBuilder::r0, (uint32_t)this);        // mov r0, this
	builder.branch(&MQTT_Client::PublishCB);            // b Callback

    assert(builder.get_length() <= sizeof(m_callback_wrapper_code));
    if(m_debug_enabled) TRACE("builder total = %u\r\n", builder.get_length());

    if(m_debug_enabled) TRACE("instance=%x\r\n", this);

	int res = qapi_Net_MQTT_New(&m_handle);
	if(res != QAPI_OK) TRACE("failed to create mqtt client\r\n");

	res = qapi_Net_MQTT_Set_Connect_Callback(m_handle, concb);
	if(res != QAPI_OK) TRACE("failed to set mqtt callback\r\n");

	res = qapi_Net_MQTT_Set_Message_Callback(m_handle, msgcb);
	if(res != QAPI_OK) TRACE("failed to set mqtt callback\r\n");

	res = qapi_Net_MQTT_Set_Publish_Callback(m_handle, pubcb);
	if(res != QAPI_OK) TRACE("failed to set mqtt callback\r\n");

	res = qapi_Net_MQTT_Set_Subscribe_Callback(m_handle, subcb);
	if(res != QAPI_OK) TRACE("failed to set mqtt callback\r\n");

    m_flags.clear(EVT_FLAG_PUBLISH_DONE);
    m_flags.set(EVT_FLAG_PUBLISH_LOCK);

    m_is_initialized = true;
    return true;
}

bool MQTT_Client::end() noexcept {
    if(!m_is_initialized) return true;

    qapi_Net_MQTT_Destroy(m_handle);
    m_handle = nullptr;

    m_is_initialized = false;
    return true;
}

bool MQTT_Client::await_connected(uint32_t timeout) noexcept {
    if(m_is_initialized!= true) return false;
    return m_flags.get_all(EVT_FLAG_IS_CONNECTED, false, timeout ? timeout : TX_WAIT_FOREVER);
}

bool MQTT_Client::is_connected() noexcept {
    if(m_is_initialized!= true) return false;
    return m_flags.get_all(EVT_FLAG_IS_CONNECTED, false, TX_NO_WAIT);
}

bool MQTT_Client::subscribe(const char* topic, int qos) noexcept {
    if(m_is_initialized!= true) return false;

    if(qapi_Net_MQTT_Subscribe(m_handle, topic, qos) != QAPI_OK) return false;
    return true;
}

bool MQTT_Client::unsubscribe(const char* topic) noexcept {
    if(m_is_initialized!= true) return false;

    if(qapi_Net_MQTT_Unsubscribe(m_handle, topic) != QAPI_OK) return false;
    return true;
}

bool MQTT_Client::publish(const char* topic, const uint8_t* msg, int32_t msg_len, int32_t qos, bool retain) noexcept {
    if(m_is_initialized!= true) return false;

    ULONG act;
    // We use this as a lock, wait until the flag is set and clear it if it is
    if(!m_flags.get(EVT_FLAG_PUBLISH_LOCK, TX_AND_CLEAR, &act, TX_WAIT_FOREVER)) return false;

    if(qapi_Net_MQTT_Publish(m_handle, topic, msg, msg_len, qos, retain) != QAPI_OK) return false;

    // Wait for publish to finish (set by callback)
    m_flags.get(EVT_FLAG_PUBLISH_DONE, TX_AND_CLEAR, &act, TX_WAIT_FOREVER);
    // Set the flag to allow the next thread to enter
    m_flags.set(EVT_FLAG_PUBLISH_LOCK);
    return true;
}

bool MQTT_Client::publish(const char* topic, const uint8_t* msg, int32_t qos, bool retain) noexcept {
    return publish(topic, msg, strnlen(reinterpret_cast<const char*>(msg), QAPI_NET_MQTT_MAX_TOPIC_LEN), qos, retain);
}

bool MQTT_Client::set_connect_info(const struct connect_info* info) noexcept {
    // TODO: Check consistency
    m_info = info;
    return true;
}

void ReconnectCB(NetworkManager::constate state, void* arg) {
    auto instance = reinterpret_cast<MQTT_Client*>(arg);
    if(state == NetworkManager::constate::connected) {
        instance->connect();
    }
}

bool MQTT_Client::enable_autoreconnect(bool reconnect) noexcept {
    if(reconnect) {
        return Network.add_constate_cb(&ReconnectCB, this);
    } else {
        return Network.remove_constate_cb(&ReconnectCB, this);
    }
}

bool MQTT_Client::connect() noexcept {
    if(m_info == nullptr) return false;
    if(m_debug_enabled) TRACE("connect\r\n");
    qapi_Net_MQTT_Config_t config;
	const char* addr;
	char buf[16];
	memset(&config, 0x00, sizeof(config));
	config.remote.sa_family = AF_INET;
	int res = qapi_Net_DNSc_Reshost(m_info->host, &config.remote);
	if(res != 0) {
        if(m_debug_enabled) TRACE("DNS Request failed: %d\r\n", res);
        return false;
	}
    addr = inet_ntop(config.remote.sa_family, &config.remote.sa_data, buf, sizeof(buf));
    if(addr == NULL) {
        if(m_debug_enabled) TRACE("inet_ntop failed\r\n");
        return false;
    }
	
    if(m_debug_enabled) TRACE("connecting to: %s %s\r\n", m_info->host, addr);

    config.local.sa_family = AF_INET;
    config.remote.sa_port = htons(m_info->port);
    config.nonblocking_connect = true;
    config.client_id_len = strnlen(m_info->client_id, QAPI_NET_MQTT_MAX_CLIENT_ID_LEN);
    memcpy(config.client_id, m_info->client_id, config.client_id_len);
    config.client_id_len = 5;
    config.keepalive_duration = m_info->keepalive_duration;
    config.clean_session = m_info->clean_session ? 1 : 0;
    config.username = (uint8_t*)m_info->username;
    config.username_len = strlen((const char*)config.username);
    config.password = (uint8_t*)m_info->password;
    config.password_len = strlen((const char*)config.password);
    if(m_info->lw) {
        config.will_message = (uint8_t*)m_info->lw->message;
        config.will_message_len = m_info->lw->message_len;
        config.will_qos = m_info->lw->qos;
        config.will_retained = m_info->lw->retained;
        config.will_topic = (uint8_t*)m_info->lw->topic;
        config.will_topic_len = strlen(m_info->lw->topic);
    }

	res = qapi_Net_MQTT_Connect(m_handle, &config);
	if(res != QAPI_OK) {
        TRACE("failed to connect mqtt client\r\n");
        return false;
    }
    
    if(m_debug_enabled) TRACE("connecting mqtt client\r\n");
    
    return true;
}

bool MQTT_Client::disconnect() noexcept {
    if(m_handle == nullptr) return false;
    if(m_debug_enabled) TRACE("disconnect\r\n");

    auto res = qapi_Net_MQTT_Disconnect(m_handle);
    if(res != QAPI_OK) {
        if(m_debug_enabled) TRACE("failed to disconnect mqtt client\r\n");
        return false;
    }
    return true;
}