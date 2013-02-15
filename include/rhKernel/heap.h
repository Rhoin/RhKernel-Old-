/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 07.02.2013
 */

#ifndef _HEAP_H_
#define _HEAP_H_

#include <rhKernel/system.h>
#include <rhKernel/region_manager.h>

RHAPI void *kmalloc(size_t _size);
RHAPI void  kfree(void *ptr);

#endif /*_HEAP_H_*/
