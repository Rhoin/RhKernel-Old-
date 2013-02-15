/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
#ifndef _IRQ_H_
#define _IRQ_H_

#include <rhKernel/isr.h>

#define IRQ0 	0 	//Timer
#define IRQ1 	1 	//Keyboard
#define IRQ2 	2 	//Cascade for 8259A Slave controller
#define IRQ3 	3 	//Serial port 2
#define IRQ4 	4 	//Serial port 1
#define IRQ5 	5 	//AT systems: Parallel Port 2. PS/2 systems: reserved
#define IRQ6 	6 	//Diskette drive
#define IRQ7 	7 	//Parallel Port 1
#define IRQ8 	8 	//CMOS Real time clock
#define IRQ9 	9  	//CGA vertical retrace
#define IRQ10 	10 	//Reserved
#define IRQ11 	11	//Reserved
#define IRQ12 	12  //AT systems: reserved. PS/2: auxiliary device
#define IRQ13 	13  //FPU
#define IRQ14 	14  //HDD controller
#define IRQ15 	15  //Reserved


#define REG_IRQ_HANDLER(irqid,handler) irq_install_handler(irqid,handler)
#define DEL_IRQ_HANDLER(irqid) irq_uninstall_handler(irqid)

//Theese are decleared in asm/x86/irq.inc
RHAPI void irq0();
RHAPI void irq1();
RHAPI void irq2();
RHAPI void irq3();
RHAPI void irq4();
RHAPI void irq5();
RHAPI void irq6();
RHAPI void irq7();
RHAPI void irq8();
RHAPI void irq9();
RHAPI void irq10();
RHAPI void irq11();
RHAPI void irq12();
RHAPI void irq13();
RHAPI void irq14();
RHAPI void irq15();


/*
 * 
 * name: void irq_init()
 * 
 * Do not use it! idt_install() calls it!
 */
RHAPI void irq_init();

/*
 * 
 * name: void irq_remap()
 * 
 * Do not use it! idt_install() calls it!
 */
RHAPI void irq_remap();

//Handler for irq.
//It loads irq routines
RHAPI void irq_handler(regs_t r);

//Install irq handler to irq routine
//Ex: Keyboard,timer....
RHAPI void irq_install_handler(uint8_t num, handle_t handle);

//Uninstalls handler from irq routine
RHAPI void irq_uninstall_handler(uint8_t num);

//Controlls if handler is installed in rounitine
RHAPI rhkbool irq_controllRoutine(int8_t num);

#endif /*_IRQ_H_*/
