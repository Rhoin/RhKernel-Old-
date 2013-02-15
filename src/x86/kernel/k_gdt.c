#include <rhKernel/rhKernel.h>

void gdt_init()
{
	gp.limit = sizeof(gdt_entry_t) * 5 - 1;
	gp.base = (uint32_t)&gent;
	
	gdt_set_gate(0, 0, 0, 0, 0); //Null segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); //Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); //Data segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); //User code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); //User data segment
	
	gdt_flush( (uint32_t)&gp);
	
	printStatusMessage("Loading GDT...",STATUS_DONE);
	
}

void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gent[num].base_low    = (base & 0xFFFF);
	gent[num].base_middle = (base >> 16) & 0xFF;
	gent[num].base_high   = (base >> 24) & 0xFF;

	gent[num].limit_low   = (limit & 0xFFFF);
	gent[num].granularity = (limit >> 16) & 0x0F;

	gent[num].granularity |= gran & 0xF0;
	gent[num].access      = access;
}
