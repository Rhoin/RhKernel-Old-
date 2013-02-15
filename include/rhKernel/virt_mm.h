
#ifndef _VIRT_MM_H_
#define _VIRT_MM_H_

#include <rhKernel/typedefs.h>

#define PG_DIR_INDEX(x) ((x >> 22) & 0x3FF) 
#define PG_TABLE_INDEX(x) ( (x >> 12) & 0x3FF)
#define PG_GET_PHYS(x) ( *x & ~0xFFF)

#define PAGE_PRESENT   0x1
#define PAGE_WRITE     0x2
#define PAGE_USER      0x4
#define PAGE_MASK      0xFFFFF000
#define PAGE_SIZE 0x1000 //4 kb

#define INVLPG(addr)	__asm__ __volatile__ ("invlpg (%0)"::"r"(addr))

#define PAGE_TABLE_ADDR	0xD0000000
#define PAGE_DIR_ADDR	0xD8000000

#define MM_STACK_BASE 0xF0000000
#define MM_STACK_TOP 0xFC000000

RHAPI uint32_t gaInitPageDir[1024];
RHAPI uint32_t gaInitTableDir[1024];

typedef uint32_t virt_addr;


//For avoiding Page Fault because of Higher Half Kernel Design
RHAPI void MMVirt_paging_preinstall();
RHAPI void MMVirt_paging_install();
RHAPI void map(uint32_t virtaddr, uint32_t physaddr, uint32_t flags);
RHAPI rhkbool isPagingActive();
#endif /*_VIRT_MM_H_*/
