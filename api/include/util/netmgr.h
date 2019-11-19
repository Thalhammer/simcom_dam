#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	NETMGR_initiated,
	NETMGR_connecting,
	NETMGR_connected,
	NETMGR_disconnected
} netmgr_constate_t;

typedef void(*netmgr_constate_cb_t)(netmgr_constate_t s, void*);

extern int netmgr_init(void);
extern int netmgr_add_constate_cb(netmgr_constate_cb_t cb, void* arg);
extern int netmgr_remove_constate_cb(netmgr_constate_cb_t cb, void* arg);
extern int netmgr_connect(const char* APN, const char* user, const char* pw);
extern int netmgr_reconnect(void);
extern void netmgr_dump_status(void);
extern netmgr_constate_t netmgr_get_state(void);
extern void netmgr_set_autoreconnect(int s);

#ifdef __cplusplus
}
#endif