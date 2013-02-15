#ifndef _VSPRINTF_H_
#define _VSPRINTF_H_

#include <rhKernel/typedefs.h>
#include <klibc/stdarg.h>

RHAPI int32_t vsprintf(char *_buff, const char *_fmt,va_list _val);

#endif /*_VSPRINTF_H_*/
