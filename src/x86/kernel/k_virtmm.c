/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
 
#include <rhKernel/virt_mm.h>
#include <rhKernel/region_manager.h>

uint32_t page_table_addr;

void MMVirt_paging_preinstall()
{
	page_table_addr = rget_pagetable_addr();
	//Identify paging
	gaInitPageDir[page_table_addr >> 22] = ((uint32_t)&gaInitPageDir - KERNEL_BASE) | 3;
	INVLPG(page_table_addr);
	printStatusMessage("Pre-Initializing Paging...",STATUS_DONE);
}
#ifdef X



rhkbool _isPagingActive = FALSE;

#define PageTable (uint32_t*)PAGE_TABLE_ADDR

virt_addr MMVirt_alloc(phys_addr addr)
{
	if(PageTable[PG_DIR_INDEX(addr)] != NULL)
	{
	}
	else if(PageTable[PG_DIR_INDEX(addr)] == NULL)
	{
		phys_addr p = PMM_ALLOCPAGE();
		
		if(p == NULL)
		{
			return 0;
		}
		
		PageTable
		
	}
	
}
rhkbool isPagingActive()
{
	return _isPagingActive;
}

#endif
