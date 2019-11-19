#define ULONG unsigned long

extern ULONG (*_txm_module_kernel_call_dispatcher)(ULONG type, ULONG param_1, ULONG param_2, ULONG param3);

typedef struct {
	ULONG arg3;
	ULONG arg4;
} args_t;

ULONG  _txm_module_system_call4( ULONG request, ULONG param_1, ULONG param_2, ULONG param_3, ULONG param_4) {
	args_t a;
	a.arg3 = param_3;
	a.arg4 = param_4;

	return _txm_module_kernel_call_dispatcher(request, param_1, param_2, (ULONG)&a);
}
