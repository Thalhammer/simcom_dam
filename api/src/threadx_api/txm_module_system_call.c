#define ULONG unsigned long

extern ULONG (*_txm_module_kernel_call_dispatcher)(ULONG type, ULONG param_1, ULONG param_2, ULONG param3);

ULONG  _txm_module_system_call4( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4) {
	ULONG args[2];
	args[0] = param_3;
	args[1] = param_4;

	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)&args);
}

ULONG  _txm_module_system_call5( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5) {
	ULONG args[3];
	args[0] = param_3;
	args[1] = param_4;
	args[2] = param_5;

	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)&args);
}

ULONG  _txm_module_system_call6( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6) {
	ULONG args[4];
	args[0] = param_3;
	args[1] = param_4;
	args[2] = param_5;
	args[3] = param_6;

	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)&args);
}

ULONG  _txm_module_system_call7( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7) {
	ULONG args[5];
	args[0] = param_3;
	args[1] = param_4;
	args[2] = param_5;
	args[3] = param_6;
	args[4] = param_7;

	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)&args);
}

ULONG  _txm_module_system_call8( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8) {
	ULONG args[6];
	args[0] = param_3;
	args[1] = param_4;
	args[2] = param_5;
	args[3] = param_6;
	args[4] = param_7;
	args[5] = param_8;

	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)&args);
}

ULONG  _txm_module_system_call9( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9) {
	ULONG args[7];
	args[0] = param_3;
	args[1] = param_4;
	args[2] = param_5;
	args[3] = param_6;
	args[4] = param_7;
	args[5] = param_8;
	args[6] = param_9;

	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)&args);
}

ULONG  _txm_module_system_call10( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9, ULONG param_10) {
	ULONG args[8];
	args[0] = param_3;
	args[1] = param_4;
	args[2] = param_5;
	args[3] = param_6;
	args[4] = param_7;
	args[5] = param_8;
	args[6] = param_9;
	args[7] = param_10;

	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)&args);
}

ULONG  _txm_module_system_call11( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9, ULONG param_10, ULONG param_11) {
	ULONG args[9];
	args[0] = param_3;
	args[1] = param_4;
	args[2] = param_5;
	args[3] = param_6;
	args[4] = param_7;
	args[5] = param_8;
	args[6] = param_9;
	args[7] = param_10;
	args[8] = param_11;

	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)&args);
}

ULONG  _txm_module_system_call12( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9, ULONG param_10, ULONG param_11, ULONG param_12) {
	ULONG args[10];
	args[0] = param_3;
	args[1] = param_4;
	args[2] = param_5;
	args[3] = param_6;
	args[4] = param_7;
	args[5] = param_8;
	args[6] = param_9;
	args[7] = param_10;
	args[8] = param_11;
	args[9] = param_12;

	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)&args);
}
