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

#include "../../config.h"

void constate_changed(netmgr_constate_t s, void* a) {
	(void)a;
	TRACE("constate=%d\r\n", s);
	if(s == NETMGR_connected) {
		TRACE("connected to the internet\r\n");
	}
}

int dam_app_start(void)
{
	if(boot_cfg() != 0) return TX_SUCCESS;
	if(debug_init() != 0) return TX_SUCCESS;
	debug_printf("\033[2J\033[1;1H"); // Clear console

	TRACE("waiting some time\r\n");
	qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true);
	TRACE("starting network\r\n");
	if(netmgr_init() != TX_SUCCESS) {
		TRACE("failed to init network manager\r\n");
		return TX_SUCCESS;
	}
	netmgr_set_autoreconnect(false);
	netmgr_add_constate_cb(constate_changed, NULL);
	TRACE("connecting to network\r\n");
	if(netmgr_connect(APN, USER, PASS) != 0) {
		TRACE("failed to start connecting to network\r\n");
		return TX_SUCCESS;
	}

	TRACE("init done\r\n");

	return TX_SUCCESS;
}
