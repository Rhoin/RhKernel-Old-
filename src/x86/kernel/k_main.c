/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
 
#include <rhKernel/rhKernel.h>


RHAPI uint32_t gKernelEnd;
void outportb(uint16_t _port, uint8_t _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

uint8_t inportb(uint16_t _port)
{
   uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

uint16_t inportw(uint16_t _port)
{
   uint16_t rv;
   __asm__ __volatile__ ("inw %1, %0" : "=a" (rv) : "dN" (_port));
   return rv;
}


int k_main(uint32_t magic,multiboot_info_t *mbt)
{
	vid_init();
	if(!multiboot_setup(magic,mbt))
	{
		return 0;
	}
	gdt_init();
	idt_init();
	regionmanager_init();
	MMVirt_paging_preinstall();
	asm volatile("sti");
	timer_init(5);
	cpu_detect();
	if(keyboard_init())
	{
		console_cmd_install_cmds();
		rhkbool quit = FALSE;
		char buff[128];
		while(quit != TRUE)
		{
			getCmd(buff,128);
			
			parseCmd(buff);
		}
	}
	else
	{
		for(;;);
	}
	
	return 0;
}
