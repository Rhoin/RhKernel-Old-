/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 12.02.2013
 */

 
#ifndef _PANIC_H_
#define _PANIC_H_

#include <rhKernel/typedefs.h>
#include <klibc/stdarg.h>

#define panic(fmt,...) \
	panic_do(fmt,__FILE__,__LINE__,__func__,##__VA_ARGS__)

int32_t panic_do(const char *_fmt,const char *_file,uint32_t _line,const char *_func,...);

#endif /*_PANIC_H_*/
