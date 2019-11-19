#pragma once
#include <stdint.h>
#include "time.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PHONE_MAX_LENGTH 20

typedef struct {
    char sender[PHONE_MAX_LENGTH];
    uint8_t sender_type;
    uint8_t pid;
    uint8_t dcs;
    qapi_time_julian_type scts;
    // Length of text in bytes
    uint16_t text_len;
    // Text is the message content converted to utf-8.
    // The maximum size for 7bit messages is 320 bytes because each char might result in up to two utf8 chars,
    // 160 for 8bit and
    // 240 for UCS2 because each ucs2 char can be upto 3 utf8 chars.
    uint8_t text[321];
} sms_delivery_message_t;

typedef struct {
    char smsc[PHONE_MAX_LENGTH];
    uint8_t smsc_type;
    uint8_t mti;
    union {
        sms_delivery_message_t delivery;
    };
} sms_message_t;

//typedef void(*netmgr_constate_cb_t)(netmgr_constate_t s);

extern int smsmgr_init(void);
extern int smsmgr_read(int id, int markread, sms_message_t* msg);
extern int smsmgr_list(int storeid, int markread, void(*cb)(sms_message_t*));

#ifdef __cplusplus
}
#endif