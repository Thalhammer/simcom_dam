#pragma once

typedef struct {
	const char* urc;
	void(*cb)(const char*, const char*);
} urc_handler_entry_t;

extern void vat_init(void);
extern void vat_write(const char* msg);
extern int vat_execute(const char* msg);
extern int vat_execute_res(const char* msg, char* res, int reslen);
extern int vat_execute_urc(const char* msg, char* res, int reslen, urc_handler_entry_t* tentries, int tnentries);
extern int vat_register_urc(urc_handler_entry_t entries[], int nentries);
