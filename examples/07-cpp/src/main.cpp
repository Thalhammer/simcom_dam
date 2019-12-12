#if __cplusplus
extern "C" {
#endif
#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi_timer.h"
#include "util/debug.h"
#include "util/trace.h"
#include "util/boot_cfg.h"

#include "tx_api.h"
#if __cplusplus
}
#endif
#define TRACE_TAG "main"

int i = 0;

struct test {
	test() { i = 123456789; }
};

static test gobj;

#if __cplusplus
extern "C"
#endif
int dam_app_start(void)
{
	TRACE("i=%d\r\n", i);
	TRACE("done\r\n");

	return TX_SUCCESS;
}
