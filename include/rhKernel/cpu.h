/*
 * Copyright (C) Sefer Ergün
 * 
 * Author: Sefer Ergün
 * 
 * Last Update: 05.02.2013
 */
#ifndef _CPU_H_
#define _CPU_H_

#include <rhKernel/system.h>
#include <klibc/stdarg.h>

typedef enum
{
	//Theese flag bits are registered in EDX
	FPU 		= 0,  //Onboard FPU
	VME 		= 1,  //Virtual Mode Extensions
	DE 			= 2,  //Debuging Extensions
	PSE 		= 3,  //Page Size Extensions
	TSC 		= 4,  //Time Stamp Counter
	MSR 		= 5,  //Model Specified Registers
	PAE 		= 6,  //Physical Adress Extensions
	MCE 		= 7,  //Machine Check Exception
	CX 			= 8,  //CMPXCHG8 Instruction Supported 
	APIC 		= 9,  //On-chip APIC Hardware Supported
	RESERVED 	= 10,
	SEP 		= 11, //Fast System Call
	MTRR 		= 12, //Memory Type Ranger Register
	PGE 		= 13, //Page Global Enable
	MCA 		= 14, //Machine Check Architecture
	CMOV 		= 15, //Conditional Move Instructions
	PAT 		= 16, //Page Attribute Table
	PSE_36 		= 17, //36-bit Page Size Extension
	PSN 		= 18, //Processor serial number is present and enabled
	CLFSH 		= 19, //CLFlush Instructıon Supported
	RESERVED_1 	= 20,
	DS 			= 21, //Debug Store
	ACPI 		= 22, //Thermal Monitor and Software Controlled Clock Facilities supported
	MMX 		= 23, //Intel Architecture MMX supported
	FXSR 		= 24, //Fast floating point save and restore
	SSE 		= 25, //Streaming SIMD extensions supported
	SSE2 		= 26, //Streaning SIMD extensions 2 supported
	SS 			= 27, //Self-snoop
	HTT 		= 28, //Hyper-Threading Technology supported
	TM 			= 29, //Thermal Monitor Supported
	RESERVED_2  = 30,
	RESERVED_3  = 31,
	
	//Theese flag bits are registered in ECX
	PNI 		= 32, // Prescott New Instructions(SSE3) Suported
	PCLMUL		= 33, //CLMUL Instructions Supported
	DTES64		= 34, //64-bit Debug Storage Supported
	MONITOR		= 35, //MONITOR and MWAIT instructions Supported
	DSCPL		= 36, //CPL Qualified Debug Store
	VMX			= 37, //Virtual Machine Extensions
	SMX			= 38, //Safer Mode Extensions
	EST			= 39, //Enchanced SpeedStep
	TM2			= 40, //Thermal Monitor 2
	SSSE3		= 41, //Supplemental Streaming SIMD Extensions 3 Supported
	CID			= 42, //L1 Context ID
	RESERVED_4	= 43,
	FMA			= 44, //Fused Multiply Add
	CX16		= 45, //CMPXCHG16B (Guess what ...:)
	XTPR		= 46, //xTPR Update Controll
	PDCM		= 47, //Perform and Debug Capability
	RESERVED_5	= 48,
	PCID		= 49, //Process Context Identifiers
	DCA			= 50, //Direct Cache Access
	SSE4_1		= 51, //Streaming Extensions 4.1
	SSE4_2		= 52, //Streaming Extensions 4.2
	X2APIC		= 53, //Extended xAPIC Support
	MOVBE		= 54, //MOVBE Instruction
	POPCNT		= 55, //POPCNT Instruction
	TSCDEADLINE	= 56, //Time Stamp Counter Deadline
	AES			= 57, //AES Instruction Extensions
	XSAVE		= 58, //XSAVE/XSTOR States Supported
	OSXSAVE		= 59, //OS Enabled Extended Stage Managment Supported
	AVX			= 60, //Advanced Vector Extensions
	F16C		= 61, //16-bit Floating Conversion Instruction
	RDRAND		= 62, //RDRAND Instructions Supported
	RESERVED_6 	= 63
}CPU_FEATURES;
typedef struct
{
	char *vendor_name;
	int supported_features;
}cpu_info_t;

//You may wonder why I did like this
//Because you should not change main cpu_info_t structure
//Your own cpu_info_t structure will copy of main one not pointer of main one
RHAPI void getCpuInfo(cpu_info_t *cpuinfo);
RHAPI void cpu_detect();
typedef enum
{
	CPU_GETSUPPORTED_FEATURES = 0xAB,
	CPU_GETFEATURE_STRING,
	CPU_GETPROCESSOR_FAMILY,
	CPU_GETVENDOR_STRING,
	CPU_GETFINFORMATION_LIST
}CPU_GETSTRING_TYPE;
RHAPI rhkbool cpuid_controllfeature(int feature);

#endif /*_CPU_H_*/
