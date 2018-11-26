# MQTT Client

## Usage
Using the builtin MQTT client is actually quite easy. Take a look at example [06-mqtt](../examples/06-mqtt) to see a complete example, however I'll describe the general use here.
### Creating a new client instance
```
qapi_Net_MQTT_Hndl_t mqtt_client;
qapi_Net_MQTT_New(&mqtt_client);
```
### Setting up callbacks
You can setup callbacks for
* Connect status
* Subscribe result
* Publish done
* Message arrival

All callbacks should be configured before connecting.
```
void on_connect(qapi_Net_MQTT_Hndl_t mqtt, int32_t reason) {}
...
qapi_Net_MQTT_Set_Connect_Callback(handle, on_connect);
```

```
void on_subscribe(qapi_Net_MQTT_Hndl_t mqtt,
    int32_t reason,
    const uint8_t* topic,
    int32_t topic_length,
    int32_t qos,
    const void* sid) {}
...
qapi_Net_MQTT_Set_Subscribe_Callback(handle, on_subscribe);
```

```
void on_message(qapi_Net_MQTT_Hndl_t mqtt,
    int32_t reason,
    const uint8_t* topic,
    int32_t topic_length,
    const uint8_t* msg,
    int32_t msg_length,
    int32_t qos,
    const void* sid) {}
...
qapi_Net_MQTT_Set_Message_Callback(handle, on_message);
```

```
void on_publish(qapi_Net_MQTT_Hndl_t mqtt,
    enum QAPI_NET_MQTT_MSG_TYPES msgtype,
    int qos,
    uint16_t msg_id) {}
...
qapi_Net_MQTT_Set_Publish_Callback(handle, on_publish);
```
### Connecting
Once you are connected to the internet you can connect your mqtt client to a broker. In order to do that you need to fill an instance of `qapi_Net_MQTT_Config_t` and pass it to `qapi_Net_MQTT_Connect`.
```
qapi_Net_MQTT_Config_t config;
// Resolve hostname/ip address into config.remote and set port to your brokers port
config.nonblocking_connect = true;
memcpy(config.client_id, MQTT_CLIENTID, sizeof(MQTT_CLIENTID) - 1);
config.client_id_len = sizeof(MQTT_CLIENTID) - 1;
config.keepalive_duration = 30;
config.clean_session = true;
config.username = MQTT_USER;
config.username_len = strlen((const char*)config.username);
config.password = MQTT_PASS;
config.password_len = strlen((const char*)config.password);
```
The most important are `username`, `password` and `clientid`. There are also fields that allow for setting a last will/testament.
After setting up the config you can start connecting using a call to `qapi_Net_MQTT_Connect`.
```
qapi_Net_MQTT_Connect(mqtt_client, &config);
```
If you set `nonblocking_connect` to true, which I strongly recommend, the client will now try to connect to the broker in the background and after a short delay your connect callback will get called with the result state.
### Subscribe to a topic
Once connected you can subscribe to a topic:
```
int qos = 1;
qapi_Net_MQTT_Subscribe(mqtt, "test/topic", qos);
```
All three qos levels are supported.
### Publishing a message
```
const int qos = 1;
const bool retained = false;
qapi_Net_MQTT_Publish(mqtt, "test/reply", msg, msg_length, qos, retained);
```
Note that there is no persistence, so if the client can't send a qos 1/2 message before poweroff it will be gone forever.


## Problems
Although it works fine for simple applications and demos there are a number of problems:
* TLS does not work
* If TLS worked you could only use the default port (8883)
* Websocket tunneling is not supported at all

### TLS does not work
I could not get TLS to work. There are fields in the config structure to configure the TLS state, but whenever I try to setup TLS the client never finishes the connect phase. I ran tcpdump on my broker during connect and the client opens a tcp connection just fine but after that the connection is idle, until after some time mosquitto closes it because of timeout. The client never starts a tls handshake and it also does not send a regular mqtt connect packet. It just sits there doing nothing. I tried various TLS options but the behaviour did not change in any way. Encryption is a must in the modern world, so this is a huge deal breaker for me.

### TLS is restricted to port 8883
Even if I got TLS to work in the first place, you could only use it on port 8883, as the client seems to use the port number to decide if it connects using TLS or plain mqtt. This also means that you can't connect to a plain mqtt server if it listens on port 8883. Many people choose different ports in order to make scanning harder, which is not possible when using the builtin client.

### Websocket is not supported
Although not a huge problem, it is kind of standard for modern mqtt clients to support tunneling via websockets. The builtin client does not support websockets in any way.

## Other clients
A better way would be to port an existing library to this platform. TLS for raw sockets works fine, and the api is more or less standard, so porting an mqtt client library should not be a huge problem.