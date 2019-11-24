#include "txm_module.h"
#include "util/trace.h"
#include "util/netmgr.h"

#define TRACE_TAG "main"

#include "config.h"

void constate_changed(netmgr_constate_t s, void* a) {
	(void)a;
	TRACE("constate=%d\r\n", s);
	if(s == NETMGR_connected) {
		TRACE("connected to the internet\r\n");
	}
}

int dam_app_start(void)
{
	debug_printf("\033[2J\033[1;1H"); // Clear console

	if(netmgr_init() != TX_SUCCESS) {
		TRACE("failed to init network manager\r\n");
		return TX_SUCCESS;
	}
	netmgr_set_autoreconnect(0);
	netmgr_add_constate_cb(constate_changed, NULL);
	TRACE("connecting to network\r\n");
	if(netmgr_connect(APN, USER, PASS) != 0) {
		TRACE("failed to start connecting to network\r\n");
		return TX_SUCCESS;
	}

	TRACE("init done\r\n");

	// Wait to prevent libc_exit
	while(1){ tx_thread_sleep(1000); }

	return TX_SUCCESS;
}
