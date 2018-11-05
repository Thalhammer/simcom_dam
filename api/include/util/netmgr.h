#pragma once

typedef enum {
	NETMGR_initiated,
	NETMGR_connecting,
	NETMGR_connected,
	NETMGR_disconnected
} netmgr_constate_t;

typedef void(*netmgr_constate_cb_t)(netmgr_constate_t s);

extern int netmgr_init(void);
extern void netmgr_set_constate_cb(netmgr_constate_cb_t cb);
extern int netmgr_connect(const char* APN, const char* user, const char* pw);
extern int netmgr_reconnect(void);
extern void netmgr_dump_status(void);
extern int netmgr_is_connected(void);
extern void netmgr_set_autoreconnect(int s);
