#include <rhKernel/rhKernel.h>

void cpuid_intel();
//void cpuid_amd();

#define CPUID(in, eax, ebx, ecx, edx) \
	__asm__("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(in) );
	

rhkbool isFeatureSupported[64];
//char *cpu_type;
//const char *cpu_family;
char cpu_features_s[64];
//char cpu_brand_s[64];
int32_t cpu_features;

const char *cpu_features_list_s[] =
{
	//Theese flag bits are registered in EDX
	"FPU ",  		//Onboard FPU
	"VME ",  		//Virtual Mode Extensions
	"DE ",  		//Debuging Extensions
	"PSE ",  		//Page Size Extensions
	"TSC ",  		//Time Stamp Counter
	"MSR ",  		//Model Specified Registers
	"PAE ",  		//Physical Adress Extensions
	"MCE ",  		//Machine Check Exception
	"CX ",  		//CMPXCHG8 Instruction Supported 
	"APIC ",  		//On-chip APIC Hardware Supported
	"RESERVED ",
	"SEP ", 		//Fast System Call
	"MTRR ", 		//Memory Type Ranger Register
	"PGE ", 		//Page Global Enable
	"MCA " , 		//Machine Check Architecture
	"CMOV ", 		//Conditional Move Instructions
	"PAT ", 		//Page Attribute Table
	"PSE_36 ", 		//36-bit Page Size Extension
	"PSN ", 		//Processor serial number is present and enabled
	"CLFSH ", 		//CLFlush Instructıon Supported
	"RESERVED_1 ",
	"DS ", 			//Debug Store
	"ACPI ", 		//Thermal Monitor and Software Controlled Clock Facilities Supported
	"MMX ", 		//Intel Architecture MMX supported
	"FXSR ", 		//Fast floating point save and restore
	"SSE " , 		//Streaming SIMD extensions supported
	"SSE2 ", 		//Streaning SIMD extensions 2 supported
	"SS ", 			//Self-snoop
	"HTT ", 		//Hyper-Threading Technology supported
	"TM ", 			//Thermal Monitor Supported
	"RESERVED_2 ",
	"RESERVED_3 ",
	
	//Theese flag bits are registered in ECX
	"PNI ", 		// Prescott New Instructions(SSE3) Suported
	"PCLMUL ", 		//CLMUL Instructions Supported
	"DTES64 ", 		//64-bit Debug Storage Supported
	"MONITOR ", 	//MONITOR and MWAIT instructions Supported
	"DSCPL ", 		//CPL Qualified Debug Store
	"VMX ",			//Virtual Machine Extensions
	"SMX ", 		//Safer Mode Extensions
	"EST ", 		//Enchanced SpeedStep
	"TM2 ", 		//Thermal Monitor 2
	"SSSE3 ", 		//Supplemental Streaming SIMD Extensions 3 Supported
	"CID ", 		//L1 Context ID
	"RESERVED_4 ",
	"FMA ", 		//Fused Multiply Add
	"CX16 ", 		//CMPXCHG16B (Guess what ...:)
	"XTPR ", 		//xTPR Update Controll
	"PDCM ", 		//Perform and Debug Capability
	"RESERVED_5 ",
	"PCID ", 		//Process Context Identifiers
	"DCA ", 		//Direct Cache Access
	"SSE4_1 ", 		//Streaming Extensions 4.1
	"SSE4_2 ", 		//Streaming Extensions 4.2
	"X2APIC ", 		//Extended xAPIC Support
	"MOVBE ", 		//MOVBE Instruction
	"POPCNT ", 		//POPCNT Instruction
	"TSCDEADLINE ", //Time Stamp Counter Deadline
	"AES ", 		//AES Instruction Extensions
	"XSAVE ", 		//XSAVE/XSTOR States Supported
	"OSXSAVE ", 	//OS Enabled Extended Stage Managment Supported
	"AVX ", 		//Advanced Vector Extensions
	"F16C ", 		//16-bit Floating Conversion Instruction
	"RDRAND ", 		//RDRAND Instructions Supported
	"RESERVED_6 ",
};

char *Intel[] = {
	"Brand ID Not Supported.", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Intel(R) Pentium(R) III Xeon(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) III processor-M", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Xeon(R) Processor", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) 4 processor-M", 
	"Mobile Intel(R) Pentium(R) Celeron(R) processor", 
	"Reserved", 
	"Mobile Genuine Intel(R) processor", 
	"Intel(R) Celeron(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Celeron(R) processor", 
	"Mobile Geniune Intel(R) processor", 
	"Intel(R) Pentium(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor"
};

char *Intel_Other[] = {
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Celeron(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved"
};
void cpu_detect()
{
	uint32_t ebx = 0, empty = 0;
	CPUID(empty, empty, ebx, empty, empty);
	
	if(ebx != NULL)
	{
		switch(ebx)
		{
			//Intel Magic Number
			//Means Genu
			case 0x756E6547:
				//vendor_name = "Intel";
				cpuid_intel();
				break;
			//AMD Magic Number
			//Means Auth
			case 0x68747541:
				//vendor_name = "AMD";
				//cpuid_amd();
				break;
			default:
				//vendor_name = "Unknown";
				break;
		}
		printStatusMessage("Detecting CPU information...",STATUS_DONE);
	}
	else
	{
		printStatusMessage("Detecting CPU information...",STATUS_FAILED);
		printf("It seems your cpu does not supports CPUID opcode");
	}
}

void getCpuInfo(cpu_info_t *cpuinfo)
{
}

void cpuid_intel()
{
	uint32_t eax,ebx,ecx,edx;
	
	asm("cpuid":"=a"(eax),"=b"(ebx),"=c"(ecx),"=d"(edx):"a"(1));
	
	//int32_t stepping = eax & 0xF;
	//int32_t model_num = (eax >> 4) & 0xF;
	//int32_t family = (eax >> 8) & 0xF;
	//int32_t type = (eax >> 12) & 0x3;
	//int32_t brand = ebx & 0xff;
	//int32_t extended_model = (eax >> 16) & 0xF;
	//int32_t extended_family = (eax >> 20) & 0xFF;
	uint32_t ecxflags = ecx;
	uint32_t edxflags = edx;
	//uint32_t signature = eax;
	
	/*switch(type)
	{
		case 0:
		cpu_type = "Original OEM";
		break;
		
		case 1:
		cpu_type = "OverDrive";
		break;
		
		case 2:
		cpu_type = "Dual-Processor";
		break;
		
		case 3:
		//Reserved
		break;
	}
	
	switch(family)
	{
		//case 3:
		//cpu_family = "i386";
		//I have to reset cpuid instruction for detecting i386
		//For now I dont know how to do it
		//And I'm not planing to support i386
		case 4:
		cpu_family = "i486";
		break;
		
		case 5:
		cpu_family = "Pentium";
		break;
		
		case 6:
		cpu_family = "Pentium Pro";
		break;
		
		case 15:
		cpu_family = "Pentium 4";
		break;
	}*/
	
	int i;
	for(i = 0; i <= 31; i++)
	{	
		if( (i != RESERVED) && (i != RESERVED_1) && (i != RESERVED_2) && (i != RESERVED_3) )
		{
			if( ((edxflags >> i) & 0x1) == NULL)
			{
				isFeatureSupported[i] = FALSE;
			}
			else
			{
				isFeatureSupported[i] = TRUE;
				cpu_features |= (i);
				strcat(cpu_features_s, cpu_features_list_s[i]);
			}
		}
	}

	for(i = 32; i <= 63; i++)
	{	
		if( (i != RESERVED_4) && (i != RESERVED_5) && (i != RESERVED_6))
		{
			if( ((ecxflags >> (i - 32)) & 0x1) == NULL)
			{
				isFeatureSupported[i] = FALSE;
			}
			else
			{
				isFeatureSupported[i] = TRUE;
				cpu_features |= (i);
				strcat(cpu_features_s,cpu_features_list_s[i]);
			}
		}
	}
	/*CPUID(0x80000000,max_eax,blank,blank,blank);

	char *tempstr1[17];
	char *tempstr[17];
	char *tempstr2[17];
	if(max_eax >= 0x80000004) {
		
		if(max_eax >= 0x80000002) {
			CPUID(0x80000002, eax, ebx, ecx, edx);
			sprintRegs(tempstr,eax, ebx, ecx, edx);
			//printRegs(eax, ebx, ecx, edx);
			//printf(tempstr);
		}
		if(max_eax >= 0x80000003) {
			CPUID(0x80000003, eax, ebx, ecx, edx);
			sprintRegs(tempstr1, eax, ebx, ecx, edx);
			//printRegs(eax, ebx, ecx, edx);
		}
		if(max_eax >= 0x80000004) {
			CPUID(0x80000004, eax, ebx, ecx, edx);
			sprintRegs(tempstr2, eax, ebx, ecx, edx);
			//printRegs(eax, ebx, ecx, edx);
		}
		strcat(cpu_brand_s,tempstr);
		strcat(cpu_brand_s,tempstr1);
		strcat(cpu_brand_s,tempstr2);
	}
	else if(brand > 0)
	{
		if(brand < 0x18)
		{
			if(signature == 0x000006B1 || signature == 0x00000F13)
			{
				strcat(cpu_brand_s,Intel[brand]);
			}
			else
			{
				strcat(cpu_brand_s,Intel_Other[brand]);
			}
		}
		else
		{
			//Reserved
		}
	}*/
	
	
}
rhkbool cpuid_controllfeature(int feature)
{
	return isFeatureSupported[feature];
}
