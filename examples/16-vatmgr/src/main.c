#include <stdlib.h>
#include <string.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_timer.h"
#include "util/debug.h"
#include "util/trace.h"
#include "util/boot_cfg.h"
#include "util/vatmgr.h"

#include "tx_api.h"

#define TRACE_TAG "main"

static void cpsi_handler(const char* urc, const char* val) {
	TRACE("cpsi %s\r\n", val);
}

static void default_handler(const char* urc, const char* val) {
	TRACE("%s: %s\r\n", urc, val);
}

static urc_handler_entry_t vat_entries[] = {
	{ "CPSI", cpsi_handler },
	{ NULL, default_handler },
};

int dam_app_start(void)
{
	//if(boot_cfg() != 0) return TX_SUCCESS;
	if(debug_init() != QAPI_OK) return TX_SUCCESS;
	TRACE("waiting some time\r\n");
	qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true);
	TRACE("init\r\n");

	vat_init();
	vat_register_urc(vat_entries, sizeof(vat_entries) / sizeof(urc_handler_entry_t));

	TRACE("exec\r\n");
	int res = vat_execute("AT+CPSI?\r\n");
	//int res = vat_execute("AT\r\n");
	TRACE("res=%d\r\n", res);

	TRACE("done\r\n");
	return TX_SUCCESS;
}
