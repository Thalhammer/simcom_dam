#include "stdio.h"
#include "stdlib.h"

int vcbprintf(char* buf, size_t n, int(*cb)(char*,size_t, void*), void* param, const char* format, va_list args) {
	int nchars = 0;
	int done = 0;
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

					for(int i = 0; i < 16 && ibuf[i] != '\0'; i++)
					{
						if(error == 0) buf[done++] = ibuf[i];
						if(done == n) {
							nchars += done;
							error = cb(buf, done, param);
							done = 0;
						}
					}
					break;
				}
				case 's': {
					char* str = va_arg(args, char*);

					while(*str != '\0')
					{
						if(error == 0) buf[done++] = *str++;
						if(done == n) {
							nchars += done;
							error = cb(buf, done, param);
							done = 0;
						}
					}
					break;
				}
				case 'c': {
					char ch = va_arg(args, int);
					if(error == 0) buf[done++] = ch;
					if(done == n) {
						nchars += done;
						error = cb(buf, done, param);
						done = 0;
					}
					break;
				}
				case '%': {
					if(error == 0) buf[done++] = '%';
					if(done == n) {
						nchars += done;
						error = cb(buf, done, param);
						done = 0;
					}
				}
				default:
					break;
			}
		} else {
			if(error == 0) buf[done++] = *format++;
			if(done == n) {
				nchars += done;
				error = cb(buf, done, param);
				done = 0;
			}
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

static int vsnprintf_cb(char* buf, size_t done, void* param) {
	return 1;
}

int vsnprintf(char* s, size_t n, const char* format, va_list args) {
	int res = vcbprintf(s, n, vsnprintf_cb, NULL, format, args);
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