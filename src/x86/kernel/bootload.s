[BITS 32]
KERNEL_BASE	equ 0xC0000000
STACKSIZE equ 0x4000


[extern gKernelEnd]
[section .multiboot]
; This part MUST be 4byte aligned, so we solve that issue using 'ALIGN 4'
ALIGN 4
mboot:
    ; Multiboot macros to make a few lines later more readable
	MULTIBOOT_PAGE_ALIGN	equ 1<<0
    MULTIBOOT_MEMORY_INFO	equ 1<<1
    MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO 
    MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

    ; This is the GRUB Multiboot header. A boot signature
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM
    dd mboot
    
[SECTION .text]
[EXTERN k_main]
[GLOBAL start]
start:
	mov esp, kernel_stack + STACKSIZE
	
	;Save eax
	mov ecx, eax
	mov eax, gaInitPageDir - KERNEL_BASE
	mov cr3, eax
	mov eax, cr0
	or eax, 0x80010000
	mov cr0, eax
		
	lgdt [GDTptr]
	mov ax, 0x10 ; Data segment
	mov ss, ax
	mov es, ax
	mov ds, ax
	mov gs, ax
	mov fs, ax
	jmp 0x08:.higherHalfKernel
.higherHalfKernel:
	;Restroe eax
	mov eax, ecx
    push ebx ;multiboot information
    push eax ;magic number
 	call k_main
	cli
.hlt:
	hlt
	jmp .hlt


%include "asm/x86/gdt.inc"
%include "asm/x86/idt.inc"
%include "asm/x86/isr.inc"
%include "asm/x86/irq.inc"

[SECTION .data]
%include "asm/x86/trickGDT.inc"
[section .initpd]
%include "asm/x86/hh_paging.inc"
[SECTION .bss]
[GLOBAL kernel_stack]
ALIGN 4096
kernel_stack:
	resb STACKSIZE

