#include "stdio.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"

extern "C" int sprintf(char* str, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int r = vsnprintf(str, -1, fmt, args);
    va_end(args);
    return r;
}

extern "C" int snprintf(char* str, size_t len, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int r = vsnprintf(str, len, fmt, args);
    va_end(args);
    return r;
}

extern "C" int vsprintf(char* s, const char* fmt, va_list argp) {
    return vsnprintf(s, -1, fmt, argp);
}

extern "C" int vsnprintf(char* s, size_t len, const char* fmt, va_list argp) {
    struct helper {
        char* ptr;
        size_t max;
        size_t cur;
    };
    helper help;
    help.ptr = s;
    help.max = len;
    help.cur = 0;
    int res = vcbprintf(fmt, argp, [](char c, void* arg) {
        helper* h = static_cast<helper*>(arg);
        if(h->cur >= h->max - 1) return;
        h->ptr[h->cur] = c;
        h->cur++;
    }, &help);
    if(help.cur >= help.max - 1) return res;
    help.ptr[help.cur] = '\0';
    return res;
}

static int cb_puts(const char* str, void(*cb)(char, void*), void* cbarg, int maxlen=0, bool replace_nl = false) {
    int len = 0;
    while(*str && (maxlen == 0 || maxlen > len)) {
        char c = *str;
        str++;
        if(replace_nl && (c == '\n' || c == '\r')) {
            cb('\\', cbarg);
            len++;
            if(!(maxlen == 0 || maxlen > len)) break;
            cb(c == '\n' ? 'n' : 'r', cbarg);
            len++;
        } else {
            cb(c, cbarg);
            len++;
        }
    }
    return len;
}

typedef struct {
    char specifier;
    char length[2];
    bool left_justify;
    bool force_sign;
    bool pad_no_sign;
    bool hash_flag;
    bool zero_pad;
    int min_width; // -1 == as arg
    int precision; // -1 == as arg
} arginfo_t;

// Parses argument specifier at fmt into info and sets fmt to the first char after the specifier
bool parse_arginfo(const char** fmt, arginfo_t& info) {
    memset(&info, 0, sizeof(info));

    auto ptr = *fmt;
    // Parse flags
    while(*ptr) {
        if(*ptr == '-') info.left_justify = true;
        else if(*ptr == '+') info.force_sign = true;
        else if(*ptr == ' ') info.pad_no_sign = true;
        else if(*ptr == '#') info.hash_flag = true;
        else if(*ptr == '0') info.zero_pad = true;
        else break;
        ptr++;
    }
    // Parse width
    while(*ptr) {
        if(*ptr >= '0' && *ptr <= '9') {
            info.min_width *= 10;
            info.min_width += *ptr - '0';
        }
        else if(*ptr == '*') {
            info.min_width = -1;
            ptr++;
            break;
        }
        else break;
        ptr++;
    }
    if(*ptr == '.') {
        ptr++;
        // Parse precision
        while(*ptr) {
            if(*ptr >= '0' && *ptr <= '9') {
                info.precision *= 10;
                info.precision += *ptr - '0';
            }
            else if(*ptr == '*') {
                info.precision = -1;
                ptr++;
                break;
            }
            else break;
            ptr++;
        }
    }
    switch(*ptr) {
        case 'j':
        case 'z':
        case 't':
        case 'L':
        case 'h':
        case 'l':
            info.length[0] = *ptr;
            info.length[1] = 0;
            ptr++;
            break;
    }
    if((info.length[0] == 'h' || info.length[0] == 'l') && *ptr == info.length[0]) {
        info.length[1] = *ptr;
        ptr++;
    }
    if(*ptr) {
        info.specifier = *ptr;
        ptr++;
    } else return false;
    switch(info.specifier) {
        case 'd':
        case 'i':
        case 'u':
        case 'o':
        case 'x':
        case 'X':
        case 'f':
        case 'F':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
        case 'a':
        case 'A':
        case 'c':
        case 's':
        case 'p':
        case 'n':
        case '%':
            break;
        default:
            return false;
    }
    *fmt = ptr;

    // Fix float precision
    if((info.specifier == 'f' || info.specifier == 'F') && info.precision == 0) info.precision = 6;
    return true;
}

extern "C" int vcbprintf(const char* fmt, va_list argp, void(*cb)(char, void*), void* cbarg) {
    int len = 0;
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            arginfo_t info;
            parse_arginfo(&fmt, info); // TODO: Check return
            if(info.min_width == -1) info.min_width = va_arg(argp, int);
            if(info.precision == -1) info.precision = va_arg(argp, int);
            if (info.specifier == '%') {
                cb('%', cbarg);
                len++;
            } else if (info.specifier == 'c') {
                char ch = va_arg(argp, int);
                cb(ch, cbarg);
                len++;
            } else if (info.specifier == 's') {
                const char* val = va_arg(argp, const char*);
                if(info.min_width != 0) {
                    int slen = strlen(val);
                    if(slen > info.precision && info.precision != 0) slen = info.precision;
                    if(info.min_width > slen && !info.left_justify) {
                        for(int i=0; i < info.min_width - slen; i++) {
                            cb(info.zero_pad ? '0' : ' ', cbarg);
                            len++;
                        }
                    }
                    info.precision = slen;
                }
                if(val == nullptr) len += cb_puts("<null>", cb, cbarg, info.precision);
                else len += cb_puts(val, cb, cbarg, info.precision, info.force_sign);
                if(info.min_width > info.precision && info.left_justify) {
                    for(int i=0; i < info.min_width - info.precision; i++) {
                        cb(info.zero_pad ? '0' : ' ', cbarg);
                        len++;
                    }
                }
            } else if (info.specifier == 'x' || info.specifier == 'p') {
                uint32_t val = va_arg(argp, uint32_t);
                if(info.hash_flag) {
                    cb('0', cbarg);
                    cb('x', cbarg);
                    len += 2;
                    if(info.min_width != 0) info.min_width -= 2;
                }
                if(info.min_width == 0) info.min_width = 1;
                char buf[8] = {0};
                for(int i=0; i<8; i++) {
                    buf[i] = (val >> (28-i*4)) & 0x0f;
                    if(buf[i] > 9) buf[i] += 'A' - 10;
                    else buf[i] += '0';
                }
                bool padding_done = false;
                for(int i=0; i<8; i++) {
                    if(!padding_done && buf[i] == '0' && i != 7) {
                        if(i < 8 - info.min_width) continue;
                        else if(!info.zero_pad) buf[i] = ' ';
                    } else padding_done = true;
                    cb(buf[i], cbarg);
                    len++;
                }
            } else if (info.specifier == 'u' || info.specifier == 'd' || info.specifier == 'i') {
                long long unsigned int val = 0;
                bool wasneg = false;
                if(info.specifier=='d' || info.specifier == 'i') {
                    long long int ival;
                    if(info.length[0] == 'l') {
                        ival = info.length[1] == 'l' ? va_arg(argp, long long int) : va_arg(argp, long int);
                    } else ival = va_arg(argp, int);
                    if(ival < 0) {
                        val = ival * -1;
                        wasneg = true;
                    } else val = ival;
                } else {
                    if(info.length[0] == 'l') {
                        // Somehow passing 64bit values is broken !?
                        val = info.length[1] == 'l' ? va_arg(argp, long long unsigned int) : va_arg(argp, long unsigned int);
                    } else val = va_arg(argp, unsigned int);
                }
                
                if(wasneg) {
                    cb('-', cbarg);
                    len++;
                } else if(info.force_sign) {
                    cb('+', cbarg);
                    len++;
                }
                char buf[22] = {0};
                for(int i=20; i >= 0; i--) {
                    buf[i] = (val % 10) + '0';
                    val /= 10;
                }
                bool padding_done = false;
                for(int i=0; i<21; i++) {
                    if(!padding_done && buf[i] == '0' && i != 20) {
                        if(i < 21 - info.min_width) continue;
                        else if(!info.zero_pad) buf[i] = ' ';
                    } else padding_done = true;
                    cb(buf[i], cbarg);
                    len++;
                }
            } else if (info.specifier == 'f' || info.specifier == 'F') {
                auto val = va_arg(argp, double);
                bool wasneg = false;
                if(val < 0) {
                    val*=-1;
                    wasneg = true;
                }
                
                if(wasneg) {
                    cb('-', cbarg);
                    len++;
                } else if(info.force_sign) {
                    cb('+', cbarg);
                    len++;
                }
                long long unsigned int ival = val;
                val = val - ival;
                char buf[22] = {0};
                int istart=20;
                for(; istart >= 0; istart--) {
                    buf[istart] = (ival % 10) + '0';
                    ival /= 10;
                    if(ival == 0) break;
                }
                bool padding_done = false;
                for(int i=0; i<21; i++) {
                    if(!padding_done && buf[i] == '0' && i != 20) {
                        if(i < 21 - info.min_width) continue;
                        else if(!info.zero_pad) buf[i] = ' ';
                    } else padding_done = true;
                    if(buf[i] != '\0') {
                        cb(buf[i], cbarg);
                        len++;
                    }
                }
                cb('.', cbarg);
                len++;
                // TODO: val == 0 may fail
                if(val == 0) {
                    cb('0' + (int)val, cbarg);
                    len++;
                }
                for(int i = 0; i<info.precision && val != 0; i++) {
                    val*=10;
                    cb('0' + (int)val, cbarg);
                    len++;
                    val = val - (int)val;
                }
            } else {
                len += cb_puts("Not implemented", cb, cbarg);
            }
        } else {
            cb(*fmt, cbarg);
            len++;
            fmt++;
        }
    }
    return len;
}