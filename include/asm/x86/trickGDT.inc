;Higher half kernel design
[GLOBAL trickGDT]
GDT_SIZE	equ	(1+2*2+1)*8
trickGDT:
	dd 0x00000000, 0x00000000	; 00 NULL Entry
	dd 0x0000FFFF, 0x00CF9A00	; 08 PL0 Code
	dd 0x0000FFFF, 0x00CF9200	; 10 PL0 Data
	dd 0x0000FFFF, 0x00CFFA00	; 18 PL3 Code
	dd 0x0000FFFF, 0x00CFF200	; 20 PL3 Data
	
[GLOBAL GDTptr]
GDTptr:
	dw GDT_SIZE - 1
	dd trickGDT
