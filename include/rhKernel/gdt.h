/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
#ifndef _GDT_H_
#define _GDT_H_
#include <rhKernel/system.h>
struct gdt_entry_s
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
}__attribute__((packed));
typedef struct gdt_entry_s gdt_entry_t;

struct gdt_ptr_s
{
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));

typedef struct gdt_ptr_s gdt_ptr_t;

gdt_ptr_t gp;
gdt_entry_t gent[5];

RHAPI void gdt_init();
RHAPI void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
RHAPI void gdt_flush(uint32_t gp);

#endif /*_GDT_H_*/
