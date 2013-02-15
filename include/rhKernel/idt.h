/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
 
#ifndef _IDT_H_
#define _IDT_H_
#include <rhKernel/system.h>
struct idt_entry_s
{
	uint16_t base_low; //Low adress for when interrupt occurs
	uint16_t sel; //Segment selector
	uint8_t always0; //Always 0
	uint8_t flags; //Flags
	uint16_t base_high; //Upper adress
}__attribute__((packed));
typedef struct idt_entry_s idt_entry_t;

struct idt_ptr_s
{
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));
typedef struct idt_ptr_s idt_ptr_t;

idt_entry_t ient[256];
idt_ptr_t ip;

RHAPI void idt_init();
RHAPI void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
RHAPI void idt_flush(uint32_t ip);
RHAPI void reboot();
#endif /*_IDT_H_*/
