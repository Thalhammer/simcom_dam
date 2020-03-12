#include "txm_module.h"
#include "util/trace.h"
#include "util/NetworkManager.h"

#define TRACE_TAG "main"

#include "config.h"

void constate_changed(NetworkManager::constate s, void* a) {
	(void)a;
	TRACE("constate=%d\r\n", s);
	if(s == NetworkManager::constate::connected) {
		TRACE("connected to the internet\r\n");
	}
}

extern "C"
int dam_app_start(void)
{
	Network.set_debug_enabled(true);
	/*if(!Network.set_autoreconnect(true)) {
		TRACE("failed to set autoreconnect\r\n");
		return TX_SUCCESS;
	}*/
	if(!Network.add_constate_cb(constate_changed, NULL)) {
		TRACE("failed to add callback\r\n");
		return TX_SUCCESS;
	}
	TRACE("connecting to network\r\n");
	if(!Network.connect(APN, USER, PASS)) {
		TRACE("failed to start connecting to network\r\n");
		return TX_SUCCESS;
	}

	TRACE("init done\r\n");

	// Wait to prevent libc_exit
	while(1){
		tx_thread_sleep(100);
		Network.dump_status();
	}

	return TX_SUCCESS;
}
