#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_timer.h"
#include "qapi/qapi_dam.h"
#include "util/debug.h"
#include "util/trace.h"
#include "util/boot_cfg.h"

#include "tx_api.h"

#define TRACE_TAG "main"

char vat_buffer[2049];

void vat_dtr(void) {
	unsigned short res;
	do{
		memset(vat_buffer, 0, sizeof(vat_buffer));
		res = qapi_DAM_Visual_AT_Output(vat_buffer, sizeof(vat_buffer)-1);
		if(res != 0) TRACE("received %d bytes: %s\r\n", (int)res, vat_buffer);
	} while(res != 0);
}

void vat_write(const char* msg) {
	int res = qapi_DAM_Visual_AT_Input(msg, strlen(msg));
	if(res != 0) TRACE("failed to write AT command\r\n");
}

int dam_app_start(void)
{
	int res = QAPI_OK;
	//if(boot_cfg() != 0) return TX_SUCCESS;
	if(debug_init() != QAPI_OK) return TX_SUCCESS;
	TRACE("waiting some time\r\n");
	qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true);
	TRACE("init\r\n");

	res = qapi_DAM_Visual_AT_Open((void*)vat_dtr);

	vat_write("ATE0\r\n");
	vat_write("AT+CPSI?\r\n");

	TRACE("done\r\n");
	return TX_SUCCESS;
}
