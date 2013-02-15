 
#ifndef _COMMON_H_
#define _COMMON_H_
#include <rhKernel/system.h>
#include <rhKernel/multiboot.h>

typedef struct
{
	uint32_t size;
	uint32_t base_addr_lower, base_addr_upper;
	uint32_t lenght_lower, lenght_upper;
	uint32_t type;
}memory_map_t;

RHAPI void outportb(uint16_t _port, uint8_t _data);
RHAPI uint8_t inportb(uint16_t _port);
RHAPI uint16_t inportw(uint16_t _port);
RHAPI rhkbool multiboot_setup(uint32_t magic,multiboot_info_t *mbt);
//Prints registers to screen
RHAPI void printRegs(int32_t eax, int32_t ebx, int32_t ecx, int32_t edx);

//Prints registers to string
//String size at least must be 16(count from 0)
RHAPI void sprintRegs(char *str, int32_t eax, int32_t ebx, int32_t ecx, int32_t edx);

#endif /*_COMMON_H_*/
