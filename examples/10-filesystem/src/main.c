#include <stdlib.h>

#include "qapi/qapi_types.h"
#include "qapi/qapi.h"
#include "qapi/qapi_status.h"
#include "qapi/qapi_timer.h"
#include "qapi/qapi_fs.h"
#include "util/debug.h"
#include "util/trace.h"
#include "util/boot_cfg.h"

#include "tx_api.h"

#define TRACE_TAG "main"

int dam_app_start(void)
{
	if(boot_cfg() != 0) return TX_SUCCESS;
	if(debug_init() != QAPI_OK) return TX_SUCCESS;
	TRACE("waiting some time\r\n");
	qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true);
	TRACE("init\r\n");

	// Write a file
	int fd;
	int status = qapi_FS_Open_With_Mode("testfile.txt",
		QAPI_FS_O_WRONLY_E | QAPI_FS_O_CREAT_E | QAPI_FS_O_TRUNC_E,
		QAPI_FS_S_IRUSR_E | QAPI_FS_S_IWUSR_E | QAPI_FS_S_IRGRP_E | QAPI_FS_S_IWGRP_E  | QAPI_FS_S_IROTH_E | QAPI_FS_S_IWOTH_E,
		&fd);
	if(status != QAPI_OK) {
		TRACE("failed to create file: %d\r\n", status);
		return TX_SUCCESS;
	}

	const char* samplecontent = "Hello Filesystem\n";
	uint32_t written;
	uint32_t len = strlen(samplecontent);
	while(len != 0) {
		status = qapi_FS_Write(fd, (uint8_t*)samplecontent, len, &written);
		if(status != QAPI_OK) {
			TRACE("failed to write content: %d\r\n", status);
			return TX_SUCCESS;
		} else {
			TRACE("wrote %d bytes\r\n", written);
		}
		samplecontent += written;
		len -= written;
	}

	status = qapi_FS_Close(fd);
	if(status != QAPI_OK) {
		TRACE("failed to close file\r\n");
		return TX_SUCCESS;
	}

	status = qapi_FS_Open("testfile.txt", QAPI_FS_O_RDONLY_E, &fd);
	if(status != QAPI_OK) {
		TRACE("failed to open file: %d\r\n", status);
		return TX_SUCCESS;
	}

	char buf[65];
	uint32_t read;
	do {
		status = qapi_FS_Read(fd, (uint8_t*)buf, 64, &read);
		if(status != QAPI_OK) {
			TRACE("failed to read content: %d\r\n", status);
			return TX_SUCCESS;
		}
		if(read != 0) {
			buf[read] = '\0';
			TRACE("read %d bytes: \"%s\"\r\n", read, buf);
		}
	} while(read != 0);

	status = qapi_FS_Close(fd);
	if(status != QAPI_OK) {
		TRACE("failed to close file\r\n");
		return TX_SUCCESS;
	}

	TRACE("done\r\n");
	return TX_SUCCESS;
}
