/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
 
#ifndef _ISR_H_
#define _ISR_H_
#include <rhKernel/system.h>
//Nasty long function prototypes
RHAPI void isr0();
RHAPI void isr1();
RHAPI void isr2();
RHAPI void isr3();
RHAPI void isr4();
RHAPI void isr5();
RHAPI void isr6();
RHAPI void isr7();
RHAPI void isr8();
RHAPI void isr9();
RHAPI void isr10();
RHAPI void isr11();
RHAPI void isr12();
RHAPI void isr13();
RHAPI void isr14();
RHAPI void isr15();
RHAPI void isr16();
RHAPI void isr17();
RHAPI void isr18();
RHAPI void isr19();
RHAPI void isr20();
RHAPI void isr21();
RHAPI void isr22();
RHAPI void isr23();
RHAPI void isr24();
RHAPI void isr25();
RHAPI void isr26();
RHAPI void isr27();
RHAPI void isr28();
RHAPI void isr29();
RHAPI void isr30();
RHAPI void isr31();
RHAPI void isr32();
typedef struct
{
   uint32_t ds;                  // Data segment selector
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
   uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
}regs_t;

typedef void (*handle_t)(regs_t r);

//ISRs handler
RHAPI void isr_handler(regs_t r);
RHAPI void isr_install_interrupt(int32_t num, handle_t handle);
RHAPI void isr_uninstall_interrupt(int32_t num);
//DONT USE IT
//idt_init automaticly loads it
RHAPI void isr_init();

#endif /*_ISR_H_*/
