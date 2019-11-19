#pragma once

// CHECKS gpio3 and returns 0 if it is high and 1 if it is pulled low.
// if there is an error reading the gpio 2 is returned
// Use something like this to protect against reboot loops if you have a segfault in your init.
/*
int dam_app_start(void)
{
	// Early out if gpio3 is low or there was an error reading
	if(boot_cfg() != 0) return TX_SUCCESS;

	// Your program

	return TX_SUCCESS;
}
*/
#ifdef __cplusplus
extern "C" {
#endif
extern int boot_cfg(void);
#ifdef __cplusplus
}
#endif
