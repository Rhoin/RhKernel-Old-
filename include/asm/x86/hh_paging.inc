;Higher half kernel design
[GLOBAL gaInitPageDir]
align 4096
gaInitPageDir:
	dd	gaInitPageTable-KERNEL_BASE+3	; 0x000 - Low kernel
	times 0x300-0x000-1	dd	0
	dd	gaInitPageTable-KERNEL_BASE+3	; 0xC00 - High kernel
	times 0x3F0-0x300-1	dd	0
	dd	gaInitPageDir-KERNEL_BASE+3 	; 0xFC0 - Fractal
	times 0x400-0x3F0-1	dd	0
align 4096
gaInitPageTable:
	%assign i 0
	%rep 1024
	dd	i*0x1000+3
	%assign i i+1
	%endrep
