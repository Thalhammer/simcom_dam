#include "util/trace.h"
#include "util/GNSS_Client.h"

#include "tx_api.h"

#define TRACE_TAG "main"

extern "C"
int dam_app_start(void)
{
	// Init location manager
	GNSS_Client client;
	client.set_debug_enabled(true);
	if(!client.begin()) {
		TRACE("failed to init gnss\r\n");
		return 0;
	}

	// Wait for fix
	if(!client.await_fix()) {
		TRACE("failed to await fix\r\n");
		return 0;
	}

	TRACE("got fix, shutting down and exiting\r\n");

	if(!client.end()) {
		TRACE("failed to end gnss client\r\n");
		return 0;
	}

	return TX_SUCCESS;
}
