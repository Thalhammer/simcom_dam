#pragma once
#include <stdint.h>

extern uint32_t htonl(uint32_t hostlong);
extern uint16_t htons(uint16_t hostshort);
#define ntohl(n) htonl(n)
#define ntohs(n) htons(n)
