lowStart = start - 0xC0000000;
ENTRY(lowStart)
OUTPUT_FORMAT(elf32-i386)
SECTIONS
{
. = 0x100000;
	__load_addr = .;
	.multiboot : AT(ADDR(.multiboot)) {
		*(.multiboot)
	}
	
	. += 0xC0000000;
	
	.text ALIGN(0x1000): AT(ADDR(.text) - 0xC0000000) {
		*(.text)
	}
	
	.rodata ALIGN(0x1000): AT(ADDR(.rodata) - 0xC0000000) {
		*(.initpd)
		*(.rodata)
		*(.rdata)
	}
	
  .data ALIGN (0x1000) : AT(ADDR(.data) - 0xC0000000) {
		*(.data)
	}
  .bss : AT(ADDR(.bss) - 0xC0000000) {
		_sbss = .;
		*(COMMON)
		*(.bss)
		_ebss = .;
	}
	gKernelEnd = .;
}
