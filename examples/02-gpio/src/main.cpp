#include <stdlib.h>
#include "txm_module.h"
#include "util/trace.h"
#include "util/GPIO.h"

#define TRACE_TAG "main"

extern "C"
int dam_app_start(void)
{
	GPIO& gpio = netlight;
	gpio.set_debug_enabled(true);
	if(!gpio.begin()) {
		TRACE("failed to begin gpio\r\n");
		return 0;
	}
	if(!gpio.reconfigure(true)) {
		TRACE("failed to reconfigure gpio\r\n");
		return 0;
	}
	
	while(true) {
		if(!gpio.drive(true)) {
			TRACE("failed to drive gpio high\r\n");
			return 0;
		}
		tx_thread_sleep(60); // 60 seems to be about 1s
		if(!gpio.drive(false)) {
			TRACE("failed to drive gpio low\r\n");
			return 0;
		}
		tx_thread_sleep(60); // 60 seems to be about 1s
	}
	return TX_SUCCESS;
}
