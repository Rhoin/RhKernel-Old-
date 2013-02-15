#include <rhKernel/rhKernel.h>

void idt_init()
{
	ip.limit = sizeof(idt_entry_t) * 256 - 1;
	ip.base = (uint32_t)&ient;
	
	memset(&ient, 0, sizeof(idt_entry_t) * 256);
	
	isr_init();	
	irq_init();
	idt_flush((uint32_t)&ip);
	
	printStatusMessage("Loading IDTs...",STATUS_DONE);
}

void reboot()
{
	unsigned int a = NULL;
	idt_flush((uint32_t)&a);
}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	ient[num].base_low = base & 0xFFFF;
	ient[num].base_high = ( base >> 16) & 0xFFFF;
	
	ient[num].sel = sel;
	ient[num].always0 = 0; //Alwaysss 0 :)
	ient[num].flags = flags;
}


