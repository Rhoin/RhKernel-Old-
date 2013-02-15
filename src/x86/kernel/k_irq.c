#include <rhKernel/rhKernel.h>

void *irq_routines[] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0
};
void irq_remap()
{
	//Re-maps irqs
	//Because IRQ 0-7 mapped to IDTs ISR 8-15
	//It gives General Protection fault if we dont re-map them
	//IRQ 0 to -> IDT 32
	//IRQ 15 to -> IDT 47
	outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

void irq_init()
{
	irq_remap();
	
	idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
	idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);
	idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E);
	idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E);
	idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E);
	idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E);
	idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E);
	idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E);
	idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E);
	idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E);
	idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
	idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
	idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
	idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
	idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
	idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);
	
	printStatusMessage("Loding IRQs...",STATUS_DONE);
}

void irq_handler(regs_t r)
{
	//If there is a routine
	//Handle it
	handle_t handle = irq_routines[r.int_no - 32];
	if(handle)
	{
		handle(r);
	}
	
	//If intterupt higher than 40
	//(means irq 8-15) we involed slave PIC
	//We send it EOI
	if(r.int_no >= 40)
	{
		outportb(0xA0, 0x20);
	}
	
	//We send EIO to master PIC
	outportb(0x20, 0x20);
}

//Install handle to routine
void irq_install_handler(uint8_t num, handle_t handle)
{
	irq_routines[num] = handle;
}

//Uninstall handler from routine
void irq_uninstall_handler(uint8_t num)
{
	irq_routines[num] = 0;
}

//Controlls if irq routine was installed
rhkbool irq_controllRoutine(int8_t num)
{
	handle_t hndl = irq_routines[num];
	
	return (hndl != NULL ? TRUE : FALSE);
}
