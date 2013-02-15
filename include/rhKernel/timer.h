#ifndef _TIMER_H_
#define _TIMER_H_

#include <rhKernel/system.h>

#define PIT_CMD_PORT 		0x43
#define PIT_CH1_DATA_PORT	0x42
#define PIT_CH2_DATA_PORT	0x41
#define PIT_CH0_DATA_PORT	0x40

#define PIT_USE_CH0			0x00
#define PIT_USE_CH1			0x40
#define PIT_USE_CH2			0x80
#define PIT_READBACK		0xC0

#define PIT_ACCESS_LATCH	0x00
#define PIT_ACCESS_LO		0x10
#define PIT_ACCESS_HI		0x20
#define PIT_ACCESS_LOHI		0x30

#define PIT_MODE_0			0x00
#define PIT_MODE_1			0x02
#define PIT_MODE_2			0x04
#define PIT_MODE_3			0x06
#define PIT_MODE_4			0x08
#define PIT_MODE_5			0x0A

RHAPI void timer_init(int32_t freq);
RHAPI int32_t getTickCount();
RHAPI void sleep(int32_t ms);
#endif /*_TIMER_H_*/
