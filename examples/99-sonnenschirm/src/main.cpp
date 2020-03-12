#include <stdlib.h>

#include "stdint.h"
extern "C" {
#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_timer.h"
#include "qapi/qapi_socket.h"
#include "qapi/qapi_ns_utils.h"
#include "qapi/qapi_dnsc.h"
#include "qapi/qapi_mqtt.h"
#include "qapi/qapi_dam.h"
}
#include "util/debug.h"
#include "util/trace.h"
#include "util/NetworkManager.h"
#include "util/GNSS_Client.h"
#include "util/MQTT_Client.h"
#include "util/I2C_Master.h"
#include "util/NTP_Client.h"
#include "util/BME280.h"
#include "util/PSM.h"
#include "util/time.h"
#include "util/htons.h"
#include "util/init_config.h"
#include "util/Analog.h"
#include "util/VatManager.h"
#include "util/GPIO.h"
#include "stdio.h"


#include "tx_api.h"

#include "config.h"

#define TRACE_TAG "main"

static MQTT_Client mqtt_client;
static GNSS_Client gnss_client;
static NTP_Client ntp_client;
static BME280 bme;

INIT_DISABLE_SAFETY_DELAY();

const struct MQTT_Client::connect_info mqtt_info {
	MQTT_HOST,
	1884,
	MQTT_CLIENTID,
	30,
	false,
	(const char*)(MQTT_USER),
	(const char*)(MQTT_PASS),
	NULL
};

time_t get_and_update_time() {
	time_t current_time = 0;
	VAT.get_cclk(&current_time);
	// Before 2020 is invalid
	if(current_time <= 1577836800)
		current_time = 0;
	GNSS_Client::location loc;
	memset(&loc, 0, sizeof(loc));
	bool gpsfix = gnss_client.get_last_fix(&loc);
	TRACE("gpsfix = %d\r\n", gpsfix ? 1:0);
	bool shouldupdate_time = gpsfix;
	if(gpsfix) current_time = loc.timestamp / 1000;
	if(current_time == 0) {
		if(ntp_client.sync()) {
			current_time = ntp_client.get_time();
			shouldupdate_time = true;
			TRACE("got time from ntp\r\n");
		} else {
			TRACE("failed to get gps fix or ntp response\r\n");
		}
	}

	if(shouldupdate_time) VAT.set_cclk(current_time);

	return current_time;
}

extern "C"
int dam_app_do_work(void)
{
	VAT.set_debug_enabled(true);
	PSM.set_debug_enabled(true);
	Network.set_debug_enabled(true);
	gnss_client.set_debug_enabled(true);
	mqtt_client.set_debug_enabled(true);
	Wire.set_debug_enabled(false);
	bme.set_debug_enabled(false);
	ntp_client.set_debug_enabled(false);

	// Turn on Wind sensor
	gpio4.set_debug_enabled(true);
	gpio4.drive(true);

	mqtt_client.begin();
	mqtt_client.set_connect_info(&mqtt_info);
	mqtt_client.enable_autoreconnect(true);

	VAT.begin();

	if(!Network.begin()
	|| !Network.set_autoreconnect(true)
	|| !Network.connect(APN, USER, PASS)) {
		TRACE("failed to init network manager\r\n");
		return TX_SUCCESS;
	}

	if(!gnss_client.begin()) {
		TRACE("failed to init gnss client\r\n");
		return TX_SUCCESS;
	}
	TRACE("GNSS initialized, waiting for fix\r\n");

	if(!PSM.begin()) {
		TRACE("failed to init psm\r\n");
		return TX_SUCCESS;
	}

	if(!bme.begin(&Wire)) {
		TRACE("failed to init bme280 sensor\r\n");
	}

	if(!gnss_client.await_fix(6000)) {
		TRACE("failed to get fix in time\r\n");
	}

	for(size_t i=0; i<1000 && Network.get_state() != NetworkManager::constate::connected; i++)
		tx_thread_sleep(10);
	if(Network.get_state() != NetworkManager::constate::connected) {
		TRACE("failed to get network connection\r\n");
		return TX_SUCCESS;
	}
	
	if(!mqtt_client.await_connected(1000)) {
		TRACE("failed to connect to mqtt\r\n");
		mqtt_client.disconnect();
		mqtt_client.end();
		gnss_client.end();
		return TX_SUCCESS;
	}

	time_t current_time = get_and_update_time();

	int32_t vbati;
	if(!ADC_VBATT.read(&vbati)) {
		TRACE("failed to read vbat\r\n");
		vbati = 0;
	}
	float vbat = vbati / 1000.0;

	int rssi = -1;
	VAT.get_csq(&rssi);

	time_gregorian_type ctime = time_convert_unix_to_gregorian(current_time);
	TRACE("%02d.%02d.%02d %02d:%02d:%02d\r\n", ctime.day, ctime.month, ctime.year, ctime.hour, ctime.minute, ctime.second);

	char buf[1024];
	memset(buf, 0, sizeof(buf));
	auto len = snprintf(buf, sizeof(buf), 
		"["
		"{\"bn\":\"values:\", \"bt\":%lu, \"n\":\"vbat\", \"u\":\"V\", \"v\":%.5f},"
		"{\"t\":0, \"n\":\"rssi\", \"u\":\"\", \"v\":%d}",
		current_time,
		vbat,
		rssi);

	// We have a gps position, so use it
	{
		GNSS_Client::location loc;
		memset(&loc, 0, sizeof(loc));
		if(gnss_client.get_last_fix(&loc)) {
			len += snprintf(&buf[len], sizeof(buf) - len,
				","
				"{\"t\":0, \"n\":\"latitude\", \"u\":\"\", \"v\":%.5f},"
				"{\"t\":0, \"n\":\"longitude\", \"u\":\"\", \"v\":%.5f},"
				"{\"t\":0, \"n\":\"locaccuracy\", \"u\":\"m\", \"v\":%.1f}",
				loc.latitude,
				loc.longitude,
				loc.accuracy);
		}
	}
	gnss_client.end();

	// We have environment data, so use it
	if(bme.is_initialized()) {
		if(!bme.read_sensors()) {
			TRACE("failed to read bme sensor\r\n");
		} else {
			len += snprintf(&buf[len], sizeof(buf) - len,
				","
				"{\"t\":0, \"n\":\"temperature\", \"u\":\"Celsius\", \"v\":%.2f},"
				"{\"t\":0, \"n\":\"humidity\", \"u\":\"%%\", \"v\":%.2f},"
				"{\"t\":0, \"n\":\"pressure\", \"u\":\"Pa\", \"v\":%.2f}",
				bme.get_temperature(),
				bme.get_humidity(),
				bme.get_pressure());
		}
	}

	int32_t total = 0;
	for(int i=0; i < 1000; i++) {
		int32_t adc;
		if(!ADC_EXTERNAL.read(&adc)) {
			TRACE("failed to read wind\r\n");
			adc = 0;
		}
		total += adc;
	}
	total /= 1000;
	gpio4.drive(false);
	len += snprintf(&buf[len], sizeof(buf) - len,
		","
		"{\"t\":0, \"n\":\"wind\", \"u\":\"kmH\", \"v\":%d}",
		(int)total);

	len += snprintf(&buf[len], sizeof(buf) - len, "]");
	
	TRACE("%s\r\n", buf);
	
	if(mqtt_client.is_connected()) {
		if(!mqtt_client.publish(MQTT_SENML_TOPIC, buf, len, 1, false)) {
			TRACE("failed to publish mqtt message\r\n");
		}
		TRACE("publish done\r\n");
	}
	mqtt_client.disconnect();
	mqtt_client.end();
	return TX_SUCCESS;
}

extern "C"
int dam_app_start(void)
{
	dam_app_do_work();
	TRACE("done\r\n");
	while(true) {
		if(!PSM.enter_psm(600)) {
			TRACE("psm enter failed\r\n");
		}
		TRACE("modem_sleep=%d\r\n", qapi_force_modem_sleep(0));
		tx_thread_sleep(100);
	}
}