#include "util/smsmgr.h"
#include "util/trace.h"
#include "util/vatmgr.h"
#include "stdio.h"

#define TRACE_TAG "smsmgr"

int from_hex(uint8_t* out, size_t outlen, const char* in, size_t inlen) {
    if(inlen%2 != 0) return -1;
    if(outlen < inlen/2) return -2;
    for(size_t i=0; i<inlen; i+=2) {
        char c = in[i];
        if(c >= '0' && c <= '9') c = c-'0';
        else if(c >= 'a' && c <='f') c = c - 'a' + 10;
        else if(c >= 'A' && c <='F') c = c - 'A' + 10;
        else return -3;
        out[i/2] = c << 4;
        c = in[i + 1];
        if(c >= '0' && c <= '9') c = c-'0';
        else if(c >= 'a' && c <='f') c = c - 'a' + 10;
        else if(c >= 'A' && c <='F') c = c - 'A' + 10;
        else return -3;
        out[i/2] |= c;
    }
    return inlen/2;
}

int convert_bcd_to_string(char* out, size_t outlen, const uint8_t* in, size_t inlen) {
    static const char* const table = "0123456789*#abc\0";
    int i_out = 0;
    if(outlen < inlen*2 + 1) return -1;
    for(size_t i=0; i<inlen; i++) {
        uint8_t c = in[i];
        if((c & 0x0f) > 9) return -1;
        if(((c >> 4) & 0x0f) > 9 && i != inlen - 1) return -1;
        out[i_out++] = table[c & 0x0f];
        if(((c >> 4) & 0x0f) != 0x0f) out[i_out++] = table[(c>>4)&0x0f];
    }
    out[i_out] = '\0';
    return i_out;
}

int convert_7bit(const uint8_t* in, size_t in_bytes, uint8_t in_chars, uint8_t* out, size_t outlen) {
    (void)outlen; // TODO: Cancel if outlen reached
    size_t i_out = 0;
    size_t chars_out = 0;
    if(in_bytes != 0) out[i_out++] = in[0] & 0x7f;
    for(size_t i=1; i<in_bytes; i++) {
        if(i_out >= outlen - 1) break;
        uint32_t x = ((((uint32_t)in[i]) & 0xff) << 8) | (((uint32_t)in[i-1]) & 0xff);
        chars_out++;
        switch(i%7) {
            case 0: if(i_out < outlen) out[i_out] = (x >> 8) & 0x7f; break;
            case 1: if(i_out < outlen) out[i_out] = (x >> 7) & 0x7f; break;
            case 2: if(i_out < outlen) out[i_out] = (x >> 6) & 0x7f; break;
            case 3: if(i_out < outlen) out[i_out] = (x >> 5) & 0x7f; break;
            case 4: if(i_out < outlen) out[i_out] = (x >> 4) & 0x7f; break;
            case 5: if(i_out < outlen) out[i_out] = (x >> 3) & 0x7f; break;
            case 6:
                if(i_out < outlen) out[i_out] = (x >> 2) & 0x7f;
                i_out++;
                if(in_chars > chars_out || i != in_bytes-1) {
                    chars_out++;
                    if(i_out < outlen) out[i_out] = (x >> 9) & 0x7f;
                }
                break;
        }
        i_out++;
    }
    if(i_out < outlen) out[i_out] = '\0';
    else out[outlen - 1] = '\0';
    return i_out;
}

int convert_delivery_pdu_content(sms_message_t* msg, const uint8_t* data, size_t len) {
    if(len < 10) return -1;
    msg->delivery.pid = data[0];
    msg->delivery.dcs = data[1];
    char datestr[16];
    if(convert_bcd_to_string(datestr, sizeof(datestr), &data[2], 7) < 0) return -2;
    msg->delivery.scts.year = 2000 + (datestr[0]-'0')*10 + (datestr[1] - '0');
    msg->delivery.scts.month = (datestr[2]-'0')*10 + (datestr[3] - '0');
    msg->delivery.scts.day = (datestr[4]-'0')*10 + (datestr[5] - '0');
    msg->delivery.scts.hour = (datestr[6]-'0')*10 + (datestr[7] - '0');
    msg->delivery.scts.minute = (datestr[8]-'0')*10 + (datestr[9] - '0');
    msg->delivery.scts.second = (datestr[10]-'0')*10 + (datestr[11] - '0');
    int offset = (datestr[12]-'0')*10 + (datestr[13] - '0');
    (void)offset;
    //time_t unixtime = time_convert_gregorian_to_unix(msg->scts);
    //unixtime += (offset*15)*60;
    //msg->scts = time_convert_unix_to_gregorian(unixtime);

    if(msg->mti & 0x40) {
        // TODO: Handle user data header
        return -5;
    }

    size_t udl = data[9];
    uint8_t type = msg->delivery.dcs & 0x0c;
    if(type == 0) {
        size_t t = udl*7;
        udl = t/8;
        if(t%8 != 0) udl++;
    }
    else if(type != 0x04 && type != 0x08) return -3;
    if(10 + udl < len) return -4;
    if(type == 0) {
        int r = convert_7bit(&data[10], udl, data[9], msg->delivery.text, sizeof(msg->delivery.text));
        if(r < 0) return -5;
        msg->delivery.text_len = r;
    } else if(type == 0x04) {
        for(size_t i=0; i<udl; i++) {
            msg->delivery.text[i] = data[10 + i];
        }
        msg->delivery.text_len = udl;
        msg->delivery.text[udl] = '\0';
    } else if(type == 0x08) {
        // Convert UCS2 to utf8
        for(size_t i=0; i<udl; i++) {
            msg->delivery.text[i] = data[10 + i];
        }
        msg->delivery.text_len = udl;
        msg->delivery.text[udl] = '\0';
    }
    return 10 + udl;
}

int convert_sender(sms_message_t* msg, const uint8_t* data, size_t len) {
    if(len < 2) return -1;
    size_t slen = data[0];
    slen = (slen + 1)/2;
    if(len < 2 + slen) return -1;
    msg->delivery.sender_type = data[1];
    if(msg->delivery.sender_type != 0xd0) {
        if(convert_bcd_to_string(msg->delivery.sender, PHONE_MAX_LENGTH, &data[2], slen) < 0) return -2;
    } else if(msg->delivery.sender_type == 0xd0) {
        if(convert_7bit(&data[2], slen, slen, (uint8_t*)&msg->delivery.sender, PHONE_MAX_LENGTH) < 0) return -3;
    } else return -3;
    return slen + 2;
}

int convert_delivery_pdu(sms_message_t* msg, const uint8_t* data, size_t len) {
    int r = convert_sender(msg, data, len);
    if(r < 0) return r;
    r = convert_delivery_pdu_content(msg, &data[r], len - r);
    if(r < 0) return r;
    return 1;
}

int convert_pdu(sms_message_t* msg, const uint8_t* data, size_t len) {
    if(len < 1) return -1;
    size_t slen = data[0];
    if(len < 1 + slen) return -1;
    if(slen != 0) {
        msg->smsc_type = data[1];
        if(convert_bcd_to_string(msg->smsc, PHONE_MAX_LENGTH, &data[2], slen - 1) < 0) return -2;
    }
    msg->mti = data[slen + 1];
    switch(msg->mti & 0x03) {
        case 0: return convert_delivery_pdu(msg, &data[slen + 2], len - slen - 2);
        case 1: /* SUBMIT-REPORT pdu */ return -4;
        case 2: /* STATUS-REPORT pdu */ return -4;
        default:
        case 3: /* reserved */ return -4;
    }
}

static TX_BYTE_POOL* _smsmgr_pool = {0};
static UCHAR _smsmgr_pool_storage[2048] = {0};
static volatile int _smsmgr_init_done = TX_FALSE;
static sms_message_t* volatile _smsmgr_read_msg = NULL;
static void(*_smsmgr_list_cb)(sms_message_t*) = NULL;

static int cmgr_handler(const char* urc, const char* val) {
	if(urc != NULL) {
		TRACE("URC %s: %s\r\n", urc, val);
	} else {
		TRACE("cmgr pdu: %s\r\n", val);

        int len = strlen(val);
        uint8_t* buf = NULL;
        if(tx_byte_allocate(_smsmgr_pool, &buf, len + 1, TX_NO_WAIT) != TX_SUCCESS || buf == NULL) {
			TRACE("failed to alloc memory for pdu\r\n");
			return 1;
		}

        len = from_hex(buf, len, val, len);
        if(len < 0) {
            tx_byte_release(buf);
            TRACE("from_hex failed %d\r\n", len);
            return 1;
        }

        len = convert_pdu(_smsmgr_read_msg, buf, len);
        tx_byte_release(buf);
        if(len < 0) {
            TRACE("convert_pdu failed %d\r\n", len);
            return 0;
        }
        _smsmgr_read_msg = NULL;
	}
	return 1;
}

static int cmgl_handler(const char* urc, const char* val) {
	if(urc != NULL) {
		TRACE("URC %s: %s\r\n", urc, val);
	} else {
		TRACE("cmgl pdu: %s\r\n", val);

        int len = strlen(val);
        uint8_t* buf = NULL;
        if(tx_byte_allocate(_smsmgr_pool, &buf, len + 1, TX_NO_WAIT) != TX_SUCCESS || buf == NULL) {
			TRACE("failed to alloc memory for pdu\r\n");
			return 1;
		}

        len = from_hex(buf, len, val, len);
        if(len < 0) {
            tx_byte_release(buf);
            TRACE("from_hex failed %d\r\n", len);
            return 1;
        }

        sms_message_t msg;
        len = convert_pdu(&msg, buf, len);
        tx_byte_release(buf);
        if(len < 0) {
            TRACE("convert_pdu failed %d\r\n", len);
            return 0;
        }
        if(_smsmgr_list_cb != NULL)
            _smsmgr_list_cb(&msg);
	}
	return 1;
}

int smsmgr_init(void) {
    if(_smsmgr_init_done) return QAPI_OK;
	TRACE("smsmgr is initialising\r\n");
    vat_init();
    if(!vat_execute("AT+CMGF=0\r\n")) {
        TRACE("failed to init smsmgr: failed to set pdu mode\r\n");
        return -1;
    }
    if(!vat_execute("AT+CNMI?\r\n")) {
        TRACE("failed to init smsmgr: failed to query cnmi mode\r\n");
        return -1;
    }

    vat_register_urc("CMGR", cmgr_handler);
    vat_register_urc("CMGL", cmgl_handler);

    if(txm_module_object_allocate((void**)&_smsmgr_pool, sizeof(TX_BYTE_POOL)) != TX_SUCCESS) return QAPI_ERR_NO_MEMORY;
	if(tx_byte_pool_create(_smsmgr_pool, "smsmgr_pool", _smsmgr_pool_storage, 2048) != TX_SUCCESS) {
        txm_module_object_deallocate(_smsmgr_pool);
        return QAPI_ERR_NO_MEMORY;
    }
    _smsmgr_init_done = TX_TRUE;
	return QAPI_OK;
}

int smsmgr_read(int id, int markread, sms_message_t* msg) {
	char buf[20];
	memset(buf, 0, sizeof(buf));
	snprintf(buf, sizeof(buf), "AT+CMGR=%d,%d\r\n", id, markread == TX_TRUE ? 0:1);
    _smsmgr_read_msg = msg;
	int ret = vat_execute(buf);
    if(!ret) return -1;
    if(_smsmgr_read_msg != NULL) {
        _smsmgr_read_msg = NULL;
        return 0;
    } else return 1;
    return 0;
}


int smsmgr_list(int storeid, int markread, void(*cb)(sms_message_t*)) {
    char buf[20];
	memset(buf, 0, sizeof(buf));
	snprintf(buf, sizeof(buf), "AT+CMGL=%d,%d\r\n", storeid, markread == TX_TRUE ? 0:1);
    _smsmgr_list_cb = cb;
	int ret = vat_execute(buf);
    if(!ret) return -1;
    _smsmgr_list_cb = NULL;
    return 0;
}