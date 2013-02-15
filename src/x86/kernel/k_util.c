/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
 
#include <rhKernel/rhKernel.h>

void printRegs(int32_t eax, int32_t ebx, int32_t ecx, int32_t edx)
{
	char str[16];
	
	int i;
	for(i = 0; i < 4; i++)
	{
		str[i] = eax >> (8 * i);
		str[i + 4] = ebx >> (8 * i);
		str[i + 8] = ecx >> (8 * i);
		str[i + 12] = edx >> (8 * i);
	}
	
	printf("%s\0\n",str);
}

void sprintRegs(char *str, int32_t eax, int32_t ebx, int32_t ecx, int32_t edx)
{	
	int i;
	str[16] = '\0';
	for(i = 0; i < 4; i++)
	{
		str[i] = eax >> (8 * i);
		str[i + 4] = ebx >> (8 * i);
		str[i + 8] = ecx >> (8 * i);
		str[i + 12] = edx >> (8 * i);
	}
}
