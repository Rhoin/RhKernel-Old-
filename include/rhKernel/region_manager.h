/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 12.02.2013
 */

#ifndef _REGION_MANAGER_H_
#define _REGION_MANAGER_H_

#include <rhKernel/system.h>

typedef void* (*__kmalloc)(size_t __size);
typedef void (*__kfree)(void *__ptr);

//Region IDs
#define KERNEL_REGION 	0
#define FREE_REGION   	1
#define PGTABLE_REGION  2
#define HEAP_REGION     3

typedef struct
{
	int32_t id;
	uint32_t start;
	uint32_t end;
	uint32_t size;
}region_header_t;


/*
 * 
 * name: rhkbool regionmanager_init()
 * 
 * Silice kernels memory into regions.There is a 4 region
 * KERNEL 	- For obviuos reason
 * FREE   	- For contiguous mem-chunks
 * PGTABLE  - For page tables
 * HEAP     - For heap.It will be used if pmm and vmm complete
 */
RHAPI rhkbool regionmanager_init();

/*
 * 
 * name: void *rfree_alloc(size_t _size)
 * 
 * For allocation mem chunk from FREE region.It can't be freed.
 * Don't use it untill pmm and vmm initialazition.
 * Before them kmalloc will be using it.
 */
RHAPI void *rfree_alloc(size_t _size);

/*
 * 
 * name: void getRegionHeader(region_header_t *hdr,int32_t id)
 * 
 * Get copy of region header.
 */
RHAPI void getRegionHeader(region_header_t *hdr,int32_t id);

/*
 * 
 * name: uint32_t rget_pagetable_addr()
 * 
 * Get page table adress from page table region.
 */
RHAPI uint32_t rget_pagetable_addr();

/*
 * 
 * name: void *region_request_alloc(size_t _size)
 * 
 * Request allocation from region manager by _size.
 */
RHAPI void *region_request_alloc(size_t _size);

/*
 * 
 * name: void region_request_free(void *_ptr)
 * 
 * Request free for _ptr from region manager
 */
RHAPI void region_request_free(void *_ptr);


/*
 * 
 * name: void region_setAllocator(__kmalloc _malloc, __kfree _free)
 * 
 * Set allocator funcs.
 */
RHAPI void region_setAllocator(__kmalloc _malloc, __kfree _free);

#endif /*_REGION_MANAGER_H_*/
