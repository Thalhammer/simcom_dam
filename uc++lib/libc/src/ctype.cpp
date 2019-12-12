#include "ctype.h"

extern "C" {

int iscntrl(int c) {
    if(c >= 0 && c <= 0x1f) return true;
    if(c == 0x7f) return true;
    return false;
}

int isblank(int c) {
    if(c == 0x09 || c == 0x20) return true;
    return false;
}

int isspace(int c) {
    if(c >= 0x09 && c <= 0x0d) return true;
    if(c == 0x20) return true;
    return false;
}

int isupper(int c) {
    if(c >= 'A' && c <= 'Z') return true;
    return false;
}

int islower(int c) {
    if(c >= 'a' && c <= 'z') return true;
    return false;
}

int isalpha(int c) {
    return isupper(c) || islower(c);
}

int isdigit(int c) {
    if(c >= '0' && c <= '9') return true;
    return false;
}

int isxdigit(int c) {
    if(c >= 'a' && c <= 'f') return true;
    if(c >= 'A' && c <= 'F') return true;
    return isdigit(c);
}

int isalnum(int c) {
    return isdigit(c) || isalpha(c);
}

int ispunct(int c) {
    if(c < 0x21 || c > 0x7e) return false;
    return !isalnum(c);
}

int isgraph(int c) {
    if(c >= 0x21 || c <= 0x7e) return true;
    return false;
}

int isprint(int c) {
    if(c >= 0x20 || c <= 0x7e) return true;
    return false;
}

int tolower(int c) {
    if(c >= 'A' && c <= 'Z') return (c - 'A') + 'a';
    return c;
}

int toupper(int c) {
    if(c >= 'a' && c <= 'z') return (c - 'a') + 'A';
    return c;
}

}