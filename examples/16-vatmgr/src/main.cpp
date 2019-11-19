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
#include "txpp/byte_pool.h"

#define TRACE_TAG "main"

static int cpsi_handler(const char* urc, const char* val) {
	(void)urc;
	(void)val;
	TRACE("cpsi %s\r\n", val);
	return 0;
}

static int default_handler(const char* urc, const char* val) {
	TRACE("handle_default %s: %s\r\n", urc, val);
	return 0;
}

static const urc_handler_entry_t vat_entries[2] = {
	{ "CPSI", &cpsi_handler },
	{ NULL, &default_handler },
};

extern "C" int dam_app_start(void)
{
	vat_init();
	vat_register_urcs(vat_entries, sizeof(vat_entries)/sizeof(urc_handler_entry_t));

	TRACE("exec\r\n");
	int res = vat_execute("AT+CPSI?\r\n");
	res = vat_execute("AT+CCLK?\r\n");
	TRACE("res=%d\r\n", res);

	TRACE("done\r\n");
	return TX_SUCCESS;
}
