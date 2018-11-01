#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi_timer.h"
#include "qapi_tlmm.h"

#include "tx_api.h"

int dam_app_start(void)
{
	qapi_GPIO_ID_t     gpio_id;
	qapi_TLMM_Config_t tlmm_config;
	qapi_Status_t      status = QAPI_OK;
	
	memset(&tlmm_config, 0, sizeof(tlmm_config));
	tlmm_config.pin = 11; // Pin 11 is GPIO3
	tlmm_config.func = 0;
	tlmm_config.dir = QAPI_GPIO_OUTPUT_E;
	status = qapi_TLMM_Get_Gpio_ID( &tlmm_config, &gpio_id);

	if (status == QAPI_OK) {
		status = qapi_TLMM_Config_Gpio(gpio_id, &tlmm_config);
		if(status == QAPI_OK) {
			while(true) {
				status = qapi_TLMM_Drive_Gpio(gpio_id, tlmm_config.pin, QAPI_GPIO_HIGH_VALUE_E);
				tx_thread_sleep(60); // 60 seems to be about 1s
				status = qapi_TLMM_Drive_Gpio(gpio_id, tlmm_config.pin, QAPI_GPIO_LOW_VALUE_E);
				tx_thread_sleep(60); // 60 seems to be about 1s
			}
		}
	}

	return TX_SUCCESS;
}
