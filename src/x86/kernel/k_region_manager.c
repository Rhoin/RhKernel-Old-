#include <rhKernel/region_manager.h>

#define FREE_REGION_END 	0xD8000000
#define PGTABLE_REGION_END 0xFC000000
#define HEAP_REGION_END 	0xFFFFFFFF

region_header_t reg_header[4];

RHAPI uint32_t gKernelEnd;

uint32_t *rfree_ptr;
uint32_t *rpg_ptr;
//uint32_t *rheap_ptr;

uint32_t pgtable_addr;
uint32_t pgdir_addr;

__kmalloc malloc;
__kfree free;

rhkbool regionmanager_init()
{
	//Kernel region
	reg_header[KERNEL_REGION].id 		= KERNEL_REGION;
	reg_header[KERNEL_REGION].start 	= ((KERNEL_BASE + 0xFFF) & 0xFFFF000);
	reg_header[KERNEL_REGION].end 		= ((gKernelEnd + 0xFFF) & 0xFFFF000);
	reg_header[KERNEL_REGION].size  	= reg_header[KERNEL_REGION].end - reg_header[KERNEL_REGION].start;
	
	//Free region
	reg_header[FREE_REGION].id 			= FREE_REGION;
	reg_header[FREE_REGION].start 		= reg_header[KERNEL_REGION].end;
	reg_header[FREE_REGION].end 		= (FREE_REGION_END & 0xFFFF000);
	reg_header[FREE_REGION].size  		= reg_header[FREE_REGION].end - reg_header[FREE_REGION].start;
	
	//Page Table region
	reg_header[PGTABLE_REGION].id 		= PGTABLE_REGION;
	reg_header[PGTABLE_REGION].start 	= reg_header[FREE_REGION].end;
	reg_header[PGTABLE_REGION].end 		= (PGTABLE_REGION_END & 0xFFFF000);
	reg_header[PGTABLE_REGION].size  	= reg_header[PGTABLE_REGION].end - reg_header[PGTABLE_REGION].start;
	
	//Heap region
	reg_header[HEAP_REGION].id 			= HEAP_REGION;
	reg_header[HEAP_REGION].start 		= reg_header[PGTABLE_REGION].end;
	reg_header[HEAP_REGION].end 		= (HEAP_REGION_END & 0xFFFF000);
	reg_header[HEAP_REGION].size  		= reg_header[HEAP_REGION].end - reg_header[HEAP_REGION].start;
	
	region_setAllocator(rfree_alloc, NULL);
	
	rfree_ptr 	= (uint32_t*)reg_header[FREE_REGION].start;
	rpg_ptr 	= (uint32_t*)reg_header[PGTABLE_REGION].start;
	//rheap_ptr = (uint32_t*)reg_header[HEAP_REGION].start;
	
	pgtable_addr = rpg_ptr;
	rpg_ptr += ((0x00F00000 + 0xFFF) & 0xFFFF000);
	pgdir_addr = rpg_ptr;
	
	printStatusMessage("Initializing Region Manager...",STATUS_DONE);
	
}

uint32_t rget_pagetable_addr()
{
	return pgtable_addr;
}

RHAPI int32_t getCurX();

void *rfree_alloc(size_t _size)
{
	if((_size + rfree_ptr) > reg_header[FREE_REGION].end)
	{
		if(getCurX() > 0)
			putch('\n');
			
		printf("Out of free region memory!");
		return NULL;
	}
	
	void * p = rfree_ptr;
	rfree_ptr += _size;
	return p;
}

void getRegionHeader(region_header_t *hdr, int32_t id)
{
	*hdr = reg_header[id];
}

void *region_request_alloc(size_t _size)
{
	return malloc(_size);
}

void region_request_free(void *_ptr)
{
	free(_ptr);
}

void region_setAllocator(__kmalloc _malloc, __kfree _free)
{
	malloc 	= _malloc;
	free 	= _free;
}
