#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

#include <rhKernel/globals.h>
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef uint32_t size_t;
typedef int8_t BYTE;
typedef uint32_t UBYTE;

typedef enum
{
	TRUE = 0x1,
	FALSE = 0x0
}boolean;

typedef boolean rhkbool;
#endif /*_TYPEDEFS_H_*/
