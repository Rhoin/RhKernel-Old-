/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
 
#ifdef X

#include <system.h>

#define INDEX_BIT(x) (x/32)
#define OFFSET_BIT(x) (x%32)
//How many frames can we have?
uint32_t nframes;
uint32_t *pFrames;
page_dir_t *kerneldir;
page_dir_t *curdir;
RHAPI uint32_t place_addr;
void setFrame(uint32_t _addr)
{
	pFrames[INDEX_BIT(_addr / FRAME_BLOCK_SIZE)] |= 1 << OFFSET_BIT(_addr / FRAME_BLOCK_SIZE);
}

void clearFrame(uint32_t _addr)
{
	pFrames[INDEX_BIT(_addr / FRAME_BLOCK_SIZE)] &= ~(1 << OFFSET_BIT(_addr / FRAME_BLOCK_SIZE));
}

int testFrame(uint32_t _addr)
{
	return pFrames[INDEX_BIT(_addr / FRAME_BLOCK_SIZE)] & (1 << OFFSET_BIT(_addr / FRAME_BLOCK_SIZE) );
}

uint32_t getFirstFrame()
{
	int i;
	for(i = 0;i < INDEX_BIT(nframes);i++)
	{
		if( pFrames[i] != 0xFFFFFFFF)
		{
			int j;
			for(j = 0;j < 32;j++)
			{
				int32_t bit = 1 << j;
				if( !(pFrames[j] & bit))
				{
					return 32*i+j;
				}
			}
		}
	}
	return -1;
}

rhkbool allocFrame(page_t *pg, rhkbool isRw,rhkbool isKernel)
{
	if(pg->frame != 0)
	{
		//It means frame is already allocated
		return FALSE;
	}
	else
	{
		uint32_t idx = getFirstFrame();
		
		if(idx == -1)
		{
			//No more frame left
			return FALSE;
		}
		
		setFrame(idx * FRAME_BLOCK_SIZE);
		pg->present = TRUE;
		pg->rw = (isRw)?TRUE:FALSE;
		pg->usermode = (isKernel)?TRUE:FALSE;
		pg->frame = idx;
	}
	return TRUE;
}

rhkbool deAllocFrame(page_t *pg)
{
	if(!pg->frame)
	{
		//Page is not allocated
		return FALSE;
	}
	else
	{
		clearFrame(pg->frame);
		pg->frame = 0x0;
		
	}
}

void paging_init()
{
	uint32_t memsize = getTotalMem();
	
	nframes = memsize / FRAME_BLOCK_SIZE;
	pFrames = (uint32_t)malloc(INDEX_BIT(nframes));
	memset(pFrames,0,INDEX_BIT(nframes));
	
	kerneldir = (page_dir_t*)malloc_a(sizeof(page_dir_t));
	curdir = kerneldir;
	
	//You may ask why I didnt use for loop
	//Because kernel end will change.If I use for lopp dont take effect from kernel
	//end change.Which can give us unexcepted results
	int i = 0;
	while(i < place_addr)
	{
		allocFrame(getFrame(i,TRUE,kerneldir),FALSE,FALSE);
		i += FRAME_BLOCK_SIZE;
	}
	
	//isr_install_interrupt(16,page_handle);
	
	paging_changedir(kerneldir);
}

void paging_changedir(page_dir_t *dir)
{
	curdir = dir;
	__asm__ __volatile__("mov %0, %%cr3"::"r"(&dir->tablesPhys));
	uint32_t cr0;
	__asm__ __volatile__("mov %%cr0, %0":"=r"(cr0));
	cr0 |= 0x80000000; // Enable paging!
	__asm__ __volatile__("mov %0, %%cr0"::"r"(cr0));
}

page_t *getFrame(uint32_t addr, rhkbool make, page_dir_t *dir)
{
	uint32_t index = addr / FRAME_BLOCK_SIZE;
	uint32_t table_index = index / 1024;
	
	if(!dir->tables[table_index])
	{
		return &dir->tables[table_index]->pages[index % 1024];
	}
	else if(make)
	{
		uint32_t temp;
		dir->tables[table_index] = (page_table_t*)malloc_ap(sizeof(page_table_t),&temp);
		dir->tables[table_index] = temp | 0x7;
		return &dir->tables[table_index]->pages[index%1024];
	}
	else
	{
		return 0;
	}
}

#endif
