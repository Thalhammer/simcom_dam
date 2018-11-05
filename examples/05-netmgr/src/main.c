#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "util/debug.h"
#include "util/trace.h"
#include "util/netmgr.h"
#include "txm_module.h"
#include "util/boot_cfg.h"
#include "qapi/qapi_tlmm.h"
#include "qapi/qapi_timer.h"

#define TRACE_TAG "main"

#define APN "internet.telekom"
#define USER "congstar"
#define PASS "cs"

void constate_changed(netmgr_constate_t s) {
	if(s == NETMGR_connected) {
		TRACE("connected to the internet\r\n");
	}
}

int dam_app_start(void)
{
	if(boot_cfg() != 0) return TX_SUCCESS;
	if(debug_init() != 0) return TX_SUCCESS;

	TRACE("waiting some time\r\n");
	tx_thread_sleep(500);
	TRACE("starting network\r\n");
	if(netmgr_init() != 0) {
		TRACE("failed to init network manager\r\n");
		return TX_SUCCESS;
	}
	netmgr_set_autoreconnect(true);
	netmgr_set_constate_cb(constate_changed);
	TRACE("connecting to network\r\n");
	if(netmgr_connect(APN, USER, PASS) != 0) {
		TRACE("failed to start connecting to network\r\n");
		return TX_SUCCESS;
	}

	TRACE("init done\r\n");

	return TX_SUCCESS;
}
