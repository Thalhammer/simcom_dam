#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	const char* urc;
	int(*cb)(const char*, const char*);
} urc_handler_entry_t;

extern int vat_init(void);
extern void vat_write(const char* msg);
extern int vat_execute(const char* msg);
extern int vat_execute_res(const char* msg, char* res, int reslen);
extern int vat_execute_cb(const char* msg, char* res, int reslen, int(*result_fn)(const char*, void*), void* data);
extern int vat_register_urcs(const urc_handler_entry_t* entries, int nentries);
extern int vat_register_urc(const char* urc, int(*cb)(const char*, const char*));

#ifdef __cplusplus
}
#endif