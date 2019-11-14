#pragma once

typedef struct {
	const char* urc;
	int(*cb)(const char*, const char*);
} urc_handler_entry_t;

extern int vat_init(void);
extern void vat_write(const char* msg);
extern int vat_execute(const char* msg);
extern int vat_execute_res(const char* msg, char* res, int reslen);
extern int vat_execute_cb(const char* msg, char* res, int reslen, int(*result_fn)(const char*, void*), void* data);
extern int vat_register_urc(const urc_handler_entry_t* entries, int nentries);
