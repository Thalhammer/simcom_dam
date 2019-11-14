#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"

#define VCB_PUTCHAR(x) do { \
	if(error == 0) buf[done++] = (x); \
	if(done == n) { \
		nchars += done; \
		error = cb(buf, done, param); \
		done = 0; \
	} \
} while(0)

int vcbprintf(char* buf, size_t n, int(*cb)(char*,size_t, void*), void* param, const char* format, va_list args) {
	int nchars = 0;
	uint32_t done = 0;
	int error = 0;

	while(*format != '\0')
	{
		if(*format == '%')
		{
			format++;

			switch (*format++)
			{
				case 'd': {
					int num = va_arg(args, int);
					char ibuf[16];
					itoa(num, ibuf, 10); 

					for(uint32_t i = 0; i < 16 && ibuf[i] != '\0'; i++)
					{
						VCB_PUTCHAR(ibuf[i]);
					}
					break;
				}
				case 'u': {
					unsigned int num = va_arg(args, unsigned int);
					char ibuf[16];
					itoa_unsigned(num, ibuf, 10); 

					for(uint32_t i = 0; i < 16 && ibuf[i] != '\0'; i++)
					{
						VCB_PUTCHAR(ibuf[i]);
					}
					break;
				}
				case 'f': {
					double num = va_arg(args, double);
					char ibuf[16 + 1 + 6];
					memset(ibuf, 0, sizeof(ibuf));
					itoa((int)num, ibuf, 10);

					// Remove integer part
					num = num - (int)num;
					ibuf[16] = '.';

					for(uint32_t i=0; i<5; i++) {
						int c = num*10;
						num = num*10 - c;
						ibuf[i + 17] = '0' + c;
					}

					for(uint32_t i = 0; i < sizeof(ibuf); i++)
					{
						if(ibuf[i] == '\0') continue;
						VCB_PUTCHAR(ibuf[i]);
					}
					break;
				}
				case 'x':
				case 'p': {
					uint32_t num = va_arg(args, uint32_t);
					uint8_t bytes[8];
					bytes[7] = num & 0x0000000f;
					bytes[6] = (num & 0x000000f0) >> 4;
					bytes[5] = (num & 0x00000f00) >> 8;
					bytes[4] = (num & 0x0000f000) >> 12;
					bytes[3] = (num & 0x000f0000) >> 16;
					bytes[2] = (num & 0x00f00000) >> 20;
					bytes[1] = (num & 0x0f000000) >> 24;
					bytes[0] = (num & 0xf0000000) >> 28;

					int i=0;
					for(; i<7 && bytes[i]==0; i++);
					for(; i < 8; i++)
					{
						uint8_t x = bytes[i];
						if(x > 9) VCB_PUTCHAR(('A' + x - 10));
						else VCB_PUTCHAR(('0' + x));
					}
					break;
				}
				case 's': {
					char* str = va_arg(args, char*);
					if(str == NULL) break;

					while(*str != '\0')
					{
						VCB_PUTCHAR(*str++);
					}
					break;
				}
				case 'c': {
					char ch = va_arg(args, int);
					VCB_PUTCHAR(ch);
					break;
				}
				case '%': {
					VCB_PUTCHAR('%');
				}
				default:
					break;
			}
		} else {
			VCB_PUTCHAR(*format++);
		}
	}
	if(error == 0) buf[done] = '\0';
	if(done != 0) {
		nchars += done;
		error = cb(buf, done, param);
		done = 0;
	}
	return nchars;
}
#undef VCB_PUTCHAR

static int vsnprintf_cb(char* buf, size_t done, void* param) {
	(void)buf;
	(void)done;
	(void)param;
	return 1;
}

int vsnprintf(char* s, size_t n, const char* format, va_list args) {
	uint32_t res = vcbprintf(s, n, vsnprintf_cb, NULL, format, args);
	if(res >= n) s[n-1] = '\0';
	else s[res] = '\0';
	return res;
}

int snprintf(char* s, size_t n, const char* format, ... ) {
	va_list args;
	va_start(args, format);
	int res = vsnprintf(s, n, format, args);
	va_end(args);
	return res;
}