#define ULONG unsigned long

extern ULONG (*_txm_module_kernel_call_dispatcher)(ULONG type, ULONG param_1, ULONG param_2, ULONG param3);

typedef struct {
	ULONG arg3;
	ULONG arg4;
	ULONG arg5;
	ULONG arg6;
	ULONG arg7;
	ULONG arg8;
	ULONG arg9;
	ULONG arg10;
	ULONG arg11;
	ULONG arg12;
} args_t;

ULONG  _txm_module_system_call12( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4, ULONG param_5, ULONG param_6, ULONG param_7, ULONG param_8, ULONG param_9, ULONG param_10, ULONG param_11, ULONG param_12) {
	args_t a;
	a.arg3 = param_3;
	a.arg4 = param_4;
	a.arg5 = param_5;
	a.arg6 = param_6;
	a.arg7 = param_7;
	a.arg8 = param_8;
	a.arg9 = param_9;
	a.arg10 = param_10;
	a.arg11 = param_11;
	a.arg12 = param_12;

	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)&a);
}
