// (C) Sefer "Rhoin" Ergün
#include <rhKernel/typedefs.h>
#include <klibc/printf.h>
#include <klibc/stdarg.h>

void puts(const char *_str)
{
	int32_t i = 0;
	while(_str[i])
	{
		putch(_str[i++]);
	}
}

int printf(const char *_fmt, ...)
{
	if(_fmt == NULL)
	{
		return -1;
	}
	
	char *buff;
	memset(buff, 0, strlen(_fmt) + 1);
	
	va_list val;
	va_start(val,_fmt);
	if(vsprintf(buff,_fmt,val) < 0)
	{
		return -1;
	}
	va_end(val);
	puts(buff);
	
	return 1;
}
