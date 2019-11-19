#include "util/htons.h"

uint32_t htonl (uint32_t x)
{
	const uint8_t* in = (const uint8_t*)&x;
	uint32_t res;
	uint8_t* out = (uint8_t*)&res;
	out[0] = in[3];
	out[1] = in[2];
	out[2] = in[1];
	out[3] = in[0];
	return res;
}

uint16_t htons (uint16_t x)
{
	const uint8_t* in = (const uint8_t*)&x;
	uint16_t res;
	uint8_t* out = (uint8_t*)&res;
	out[0] = in[1];
	out[1] = in[0];
	return res;
}
