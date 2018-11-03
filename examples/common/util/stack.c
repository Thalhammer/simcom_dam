
void * __stack_chk_guard = (void *)(0xDEADBEEF);

void __stack_chk_fail(void)
{
	// Endless loop on stack corruption
	// We should cause a module reset here but I have no idea how to do this....
	while(1);
}
