/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
 
#ifdef X

#include <rhKernel/phys_mm.h>

/*Codes are temp.I will change them to linked list system or buddy/zone system*/

#define RAM_AVAILABLE 1

phys_addr stack_cur_pos = MM_STACK_BASE;
phys_addr stack_limit = MM_STACK_BASE;
phys_addr low_limit;

//TODO: This is temp.Change IT!
void MMPhys_install(multiboot_info_t *mbt)
{
	uint32_t start = 0;
	uint32_t end = 0;
	uint32_t page = 0;
	low_limit = NULL;
	curFrame = NULL;
	prevFrame = NULL;
	multiboot_memory_map_t *mmap = (multiboot_memory_map_t*)mbt->mmap_addr;
	
	while(mmap < mbt->mmap_addr + mbt-> mmap_length)
	{
		if(mmap->type == RAM_AVAILABLE)
		{
			start = mmap->addr;
			end = start + mmap->len;
			if(low_limit == NULL)
			{
				low_limit = start;
			}
			start = (start + 0xFFF) & PAGE_MASK;
			end &= PAGE_MASK;
			
			for(;start < end; start += PAGE_SIZE)
			{
				MMPhys_free_page(start);
			}
		}
		mmap = ( (uint32_t)mmap + mmap->size + sizeof(uint32_t) );
	}
}

void MMPhys_free_page(phys_addr addr)
{
	if(low_limit > addr)
		return;
	
	if(stack_limit <= stack_cur_pos)
	{
		if((stack_limit >= MM_STACK_TOP) || ((stack_limit + PAGE_SIZE) >= MM_STACK_TOP))
		{
			panic("Reached stack limit!");
		}
		map(stack_limit,addr,PAGE_PRESENT|PAGE_WRITE);
		stack_limit += PAGE_SIZE;
	}
	else
	{
		phys_addr *stack = (phys_addr*)stack_cur_pos;
		*stack = addr;
		stack_cur_pos += sizeof(phys_addr);
	}
}

phys_addr MMPhys_alloc_page()
{
	if(isPagingActive())
	{
		if(stack_cur_pos == low_limit)
		{
			panic("Out of memory");
		}
		
		stack_cur_pos -= sizeof(phys_addr);
		phys_addr *stack = (phys_addr*)stack_cur_pos;
		
		return *stack;
	}
	else
	{
		stack_cur_pos += PAGE_SIZE;
	}
}

uint32_t count;
void *curFrame;

void pmm_freeframe(phys_addr base,phys_addr end)
{
	curFrame = (*phys_addr)base;
	base += PAGE_SIZE;
	
	
}

#endif
