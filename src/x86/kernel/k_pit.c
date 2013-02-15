/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
 
#include <rhKernel/rhKernel.h>
#include <rhKernel/timer.h>

int32_t tick = 0;
void timer_handle(regs_t r)
{
	tick++;
}

void sleep(int32_t ms)
{
	while(ms != NULL)
	{
		ms--;
	}
}
void timer_init(int32_t freq)
{
	REG_IRQ_HANDLER(IRQ0, timer_handle);
	
	uint32_t divisor = 1193180 / freq;
	 
	outportb(PIT_CMD_PORT, PIT_USE_CH0 | PIT_ACCESS_LOHI | PIT_MODE_3);
	
	uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );
	
	outportb(PIT_CH0_DATA_PORT, l);
	outportb(PIT_CH0_DATA_PORT, h);
	
	printStatusMessage("Loading Timer...",STATUS_DONE);
}

int32_t getTickCount()
{
	return tick;
}
