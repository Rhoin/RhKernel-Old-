/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
 
#include <rhKernel/rhKernel.h>

multiboot_info_t *gMbt;

rhkbool multiboot_setup(uint32_t magic,multiboot_info_t *mbt)
{
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		printStatusMessage("Detecting Multiboot Compliant...",STATUS_FAILED);
		printf("Error:Invalid magic number: 0x%x\n",magic);
		return FALSE;
	}
	gMbt = mbt;
	printStatusMessage("Detecting Multiboot Compliant...",STATUS_DONE);
	return TRUE;
}

