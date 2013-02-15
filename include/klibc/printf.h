#ifndef _PRINT_H_
#define _PRINT_H_

#include <rhKernel/typedefs.h>
#include <klibc/stdarg.h>

RHAPI void puts(const char *_str);
RHAPI int32_t printf(const char *_fmt,...);

#endif /*_PRINT_H_*/
