#include <rhKernel/console_cmds.h>

void console_cmd_exit(const char *str)
{
	asm("cli\n"
		"hlt");
}


void console_cmd_version(const char *str)
{
	printf("RhKernel Version v%i.%i.%i\n",RHK_MAJOR_VER,RHK_MINOR_VER,RHK_REVISION_VER);
	printf("Copyright (C) Sefer \"Rhoin\" Ergun\n");
}


void console_cmd_help(const char *str)
{
	printf("exit - Halts system\nversion - Gives version of kernel\nclear - Clears screen\nhelp - Get available commands\n");
}


void console_cmd_clear(const char *str)
{
	clearScr();
	moveCur(0,0);
}

void console_cmd_memmap(const char *str)
{
	const char *memMap_s[] =
	{
		"Available",
		"Reserved",
		"ACPI Reclaim",
		"ACPI NVS Memory"
	};
	RHAPI multiboot_info_t *gMbt;
	multiboot_info_t *mbt = gMbt;
	memory_map_t *mmap = (memory_map_t*)(mbt->mmap_addr);
	int i = 0;
	while(mmap < mbt->mmap_addr + mbt->mmap_length)
	{
		if(mmap->type > 4)
			mmap->type = 1;
			
		printf("region %i: start: 0x%x%x length (bytes): 0x%x%x type: %i (%s)\n", i, 
			mmap->base_addr_upper, mmap->base_addr_lower,
			mmap->lenght_upper,mmap->lenght_lower,
			mmap->type, memMap_s[mmap->type-1]);

		mmap->size += sizeof(uint32_t);
		mmap = (memory_map_t*) ( (unsigned int)mmap + mmap->size);
		i++;
	}
}

void console_cmd_echo(const char *str)
{
	char *ptr = strpbrk(str," ");
	if(ptr)
	{
		*ptr++ = '\0';
	}
	printf(ptr);
	putch('\n');
}

void console_cmd_install_cmds()
{
	REG_CMD(console_cmd_clear,CONSOLE_CMD_ID_CLEAR);
	REG_CMD(console_cmd_help,CONSOLE_CMD_ID_HELP);
	REG_CMD(console_cmd_version,CONSOLE_CMD_ID_VERSION);
	REG_CMD(console_cmd_exit,CONSOLE_CMD_ID_EXIT);
	REG_CMD(console_cmd_memmap,CONSOLE_CMD_ID_MEMMAP);
	REG_CMD(console_cmd_echo,CONSOLE_CMD_ID_ECHO);
}
