/*
 * This code taken from Linux Source Code v1.0
 * And modified for compliant with gcc 4.x
 * All credits goes to Linus Torvalds
 * They are optimised very well
 * They will stay here until I understand inline assembly,and theese functions
 * */

#include <rhKernel/typedefs.h>
#include <klibc/string.h>
#include <klibc/stdarg.h>
inline char * strcpy(char *_dst, const char *_src)
{
	int32_t d0,d1,d2;
asm volatile("cld\n"
	"1:\tlodsb\n\t"
	"stosb\n\t"
	"testb %%al,%%al\n\t"
	"jne 1b"
	:"=&S" (d0), "=&D" (d1), "=&a" (d2):"0" (_src),"1" (_dst):"memory");
return _dst;
}

inline char* strncpy(char * _dst, const char *_src, size_t _count)
{
 char *tmp = _dst;
 
         while (_count) {
                 if ((*tmp = *_src) != 0)
                         _src++;
                 tmp++;
                 _count--;
         }
         return _dst;
}

inline char * strcat(char * _dst,const char * _src)
{
int d0, d1, d2, d3;
	asm volatile("repne\n\t"
		"scasb\n\t"
		"decl %1\n"
		"1:\tlodsb\n\t"
		"stosb\n\t"
		"testb %%al,%%al\n\t"
		"jne 1b"
		: "=&S" (d0), "=&D" (d1), "=&a" (d2), "=&c" (d3)
		: "0" (_src), "1" (_dst), "2" (0), "3" (0xffffffffu) : "memory");
	return _dst;
}

inline char * strncat(char * _dst, const char * _src, size_t _count)
{
int d0, d1, d2, d3;
	asm volatile("repne\n\t"
		"scasb\n\t"
		"decl %1\n\t"
		"movl %8,%3\n"
		"1:\tdecl %3\n\t"
		"js 2f\n\t"
		"lodsb\n\t"
		"stosb\n\t"
		"testb %%al,%%al\n\t"
		"jne 1b\n"
		"2:\txorl %2,%2\n\t"
		"stosb"
		: "=&S" (d0), "=&D" (d1), "=&a" (d2), "=&c" (d3)
		: "0" (_src), "1" (_dst), "2" (0), "3" (0xffffffffu), "g" (_count)
		: "memory");
	return _dst;
}

inline int strcmp(const char *_str1,const char * _str2)
{
	int d0, d1;
	int res;
	asm volatile("1:\tlodsb\n\t"
		"scasb\n\t"
		"jne 2f\n\t"
		"testb %%al,%%al\n\t"
		"jne 1b\n\t"
		"xorl %%eax,%%eax\n\t"
		"jmp 3f\n"
		"2:\tsbbl %%eax,%%eax\n\t"
		"orb $1,%%al\n"
		"3:"
		: "=a" (res), "=&S" (d0), "=&D" (d1)
		: "1" (_str1), "2" (_str2)
		: "memory");
	return res;
}

inline int strncmp(const char *_str1,const char *_str2, size_t _count)
{
	int res;
	int d0, d1, d2;
	asm volatile("1:\tdecl %3\n\t"
		"js 2f\n\t"
		"lodsb\n\t"
		"scasb\n\t"
		"jne 3f\n\t"
		"testb %%al,%%al\n\t"
		"jne 1b\n"
		"2:\txorl %%eax,%%eax\n\t"
		"jmp 4f\n"
		"3:\tsbbl %%eax,%%eax\n\t"
		"orb $1,%%al\n"
		"4:"
		: "=a" (res), "=&S" (d0), "=&D" (d1), "=&c" (d2)
		: "1" (_str1), "2" (_str2), "3" (_count)
		: "memory");
	return res;
}
inline char * strchr(const char *_str, char _chr)
{
int d0;
	char *res;
asm volatile("movb %%al,%%ah\n"
		"1:\tlodsb\n\t"
		"cmpb %%ah,%%al\n\t"
		"je 2f\n\t"
		"testb %%al,%%al\n\t"
		"jne 1b\n\t"
		"movl $1,%1\n"
		"2:\tmovl %1,%0\n\t"
		"decl %0"
		: "=a" (res), "=&S" (d0)
		: "1" (_str), "0" (_chr)
		: "memory");
return res;
}

inline size_t strspn(const char *_str, const char *_accept)
{
         const char *p;
         const char *a;
         size_t count = 0;
 
         for (p = _str; *p != '\0'; ++p) {
                 for (a = _accept; *a != '\0'; ++a) {
                         if (*p == *a)
                                 break;
                 }
                 if (*a == '\0')
                         return count;
                 ++count;
        }
        return count;
}

inline size_t strcspn(const char *_str, const char *_reject)
{
         const char *p;
         const char *r;
         size_t count = 0;
 
         for (p = _str; *p != '\0'; ++p) {
                 for (r = _reject; *r != '\0'; ++r) {
                         if (*p == *r)
                                 return count;
                 }
                 ++count;
        }
        return count;
}


inline char * strpbrk(const char *_str1,const char *_str2)
{
		const char *str1;
         const char *str2;
         for (str1 = _str1; *str1 != '\0'; ++str1) {
                 for (str2 = _str2; *str2 != '\0'; ++str2) {
                         if (*str1 == *str2)
                                 return (char*)str1;
                 }
        }
        return NULL;
}

inline char * strstr(const char *_str1,const char *_str2)
{
int	d0, d1;
register char *__res;
__asm__ __volatile__(
	"movl %6,%%edi\n\t"
	"repne\n\t"
	"scasb\n\t"
	"notl %%ecx\n\t"
	"decl %%ecx\n\t"	/* NOTE! This also sets Z if searchstring='' */
	"movl %%ecx,%%edx\n"
	"1:\tmovl %6,%%edi\n\t"
	"movl %%esi,%%eax\n\t"
	"movl %%edx,%%ecx\n\t"
	"repe\n\t"
	"cmpsb\n\t"
	"je 2f\n\t"		/* also works for empty string, see above */
	"xchgl %%eax,%%esi\n\t"
	"incl %%esi\n\t"
	"cmpb $0,-1(%%eax)\n\t"
	"jne 1b\n\t"
	"xorl %%eax,%%eax\n\t"
	"2:"
	: "=a" (__res), "=&c" (d0), "=&S" (d1)
	: "0" (0), "1" (0xffffffff), "2" (_str1), "g" (_str2)
	: "dx", "di");
return __res;
}

inline size_t strlen(const char *_str)
{
int d0;
	size_t res;
	asm volatile("repne\n\t"
		"scasb"
		: "=c" (res), "=&D" (d0)
		: "1" (_str), "a" (0), "0" (0xffffffffu)
		: "memory");
	return ~res - 1;
}

inline char * strtok(char **_str,const char *_delim)
{
	char *sbegin = *_str;
	char *end;
	
	if(sbegin == NULL)
	{
		return NULL;
	}
	
	end = strpbrk(sbegin,_delim);
	
	if(end)
	{
		*end++ = '\0';
	}
	*_str = end;
	
	return sbegin;
	
}

inline void* memcpy(void* _dst, const void* _src, size_t _count) 
{
       char* dst8 = (char*)_dst;
       char* src8 = (char*)_src;

       while (_count--) {
           *dst8++ = *src8++;
       }
       return _dst;
}

inline void * memmove(void *_dst,const void *_src, size_t _count)
{
int d0,d1,d2,d3,d4,d5;
	char *ret = _dst;

	__asm__ __volatile__(
		/* Handle more 16bytes in loop */
		"cmp $0x10, %0\n\t"
		"jb	1f\n\t"

		/* Decide forward/backward copy mode */
		"cmp %2, %1\n\t"
		"jb	2f\n\t"

		/*
		 * movs instruction have many startup latency
		 * so we handle small size by general register.
		 */
		"cmp  $680, %0\n\t"
		"jb 3f\n\t"
		/*
		 * movs instruction is only good for aligned case.
		 */
		"mov %1, %3\n\t"
		"xor %2, %3\n\t"
		"and $0xff, %3\n\t"
		"jz 4f\n\t"
		"3:\n\t"
		"sub $0x10, %0\n\t"

		/*
		 * We gobble 16byts forward in each loop.
		 */
		"3:\n\t"
		"sub $0x10, %0\n\t"
		"mov 0*4(%1), %3\n\t"
		"mov 1*4(%1), %4\n\t"
		"mov  %3, 0*4(%2)\n\t"
		"mov  %4, 1*4(%2)\n\t"
		"mov 2*4(%1), %3\n\t"
		"mov 3*4(%1), %4\n\t"
		"mov  %3, 2*4(%2)\n\t"
		"mov  %4, 3*4(%2)\n\t"
		"lea  0x10(%1), %1\n\t"
		"lea  0x10(%2), %2\n\t"
		"jae 3b\n\t"
		"add $0x10, %0\n\t"
		"jmp 1f\n\t"

		/*
		 * Handle data forward by movs.
		 */
		".p2align 4\n\t"
		"4:\n\t"
		"mov -4(%1, %0), %3\n\t"
		"lea -4(%2, %0), %4\n\t"
		"shr $2, %0\n\t"
		"rep movsl\n\t"
		"mov %3, (%4)\n\t"
		"jmp 11f\n\t"
		/*
		 * Handle data backward by movs.
		 */
		".p2align 4\n\t"
		"6:\n\t"
		"mov (%1), %3\n\t"
		"mov %2, %4\n\t"
		"lea -4(%1, %0), %1\n\t"
		"lea -4(%2, %0), %2\n\t"
		"shr $2, %0\n\t"
		"std\n\t"
		"rep movsl\n\t"
		"mov %3,(%4)\n\t"
		"cld\n\t"
		"jmp 11f\n\t"

		/*
		 * Start to prepare for backward copy.
		 */
		".p2align 4\n\t"
		"2:\n\t"
		"cmp  $680, %0\n\t"
		"jb 5f\n\t"
		"mov %1, %3\n\t"
		"xor %2, %3\n\t"
		"and $0xff, %3\n\t"
		"jz 6b\n\t"

		/*
		 * Calculate copy position to tail.
		 */
		"5:\n\t"
		"add %0, %1\n\t"
		"add %0, %2\n\t"
		"sub $0x10, %0\n\t"

		/*
		 * We gobble 16byts backward in each loop.
		 */
		"7:\n\t"
		"sub $0x10, %0\n\t"

		"mov -1*4(%1), %3\n\t"
		"mov -2*4(%1), %4\n\t"
		"mov  %3, -1*4(%2)\n\t"
		"mov  %4, -2*4(%2)\n\t"
		"mov -3*4(%1), %3\n\t"
		"mov -4*4(%1), %4\n\t"
		"mov  %3, -3*4(%2)\n\t"
		"mov  %4, -4*4(%2)\n\t"
		"lea  -0x10(%1), %1\n\t"
		"lea  -0x10(%2), %2\n\t"
		"jae 7b\n\t"
		/*
		 * Calculate copy position to head.
		 */
		"add $0x10, %0\n\t"
		"sub %0, %1\n\t"
		"sub %0, %2\n\t"

		/*
		 * Move data from 8 bytes to 15 bytes.
		 */
		".p2align 4\n\t"
		"1:\n\t"
		"cmp $8, %0\n\t"
		"jb 8f\n\t"
		"mov 0*4(%1), %3\n\t"
		"mov 1*4(%1), %4\n\t"
		"mov -2*4(%1, %0), %5\n\t"
		"mov -1*4(%1, %0), %1\n\t"

		"mov  %3, 0*4(%2)\n\t"
		"mov  %4, 1*4(%2)\n\t"
		"mov  %5, -2*4(%2, %0)\n\t"
		"mov  %1, -1*4(%2, %0)\n\t"
		"jmp 11f\n\t"

		/*
		 * Move data from 4 bytes to 7 bytes.
		 */
		".p2align 4\n\t"
		"8:\n\t"
		"cmp $4, %0\n\t"
		"jb 9f\n\t"
		"mov 0*4(%1), %3\n\t"
		"mov -1*4(%1, %0), %4\n\t"
		"mov  %3, 0*4(%2)\n\t"
		"mov  %4, -1*4(%2, %0)\n\t"
		"jmp 11f\n\t"

		/*
		 * Move data from 2 bytes to 3 bytes.
		 */
		".p2align 4\n\t"
		"9:\n\t"
		"cmp $2, %0\n\t"
		"jb 10f\n\t"
		"movw 0*2(%1), %%dx\n\t"
		"movw -1*2(%1, %0), %%bx\n\t"
		"movw %%dx, 0*2(%2)\n\t"
		"movw %%bx, -1*2(%2, %0)\n\t"
		"jmp 11f\n\t"

		/*
		 * Move data for 1 byte.
		 */
		".p2align 4\n\t"
		"10:\n\t"
		"cmp $1, %0\n\t"
		"jb 11f\n\t"
		"movb (%1), %%cl\n\t"
		"movb %%cl, (%2)\n\t"
		".p2align 4\n\t"
		"11:"
		: "=&c" (d0), "=&S" (d1), "=&D" (d2),
		  "=r" (d3),"=r" (d4), "=r"(d5)
		:"0" (_count),
		 "1" (_src),
		 "2" (_dst)
		:"memory");

	return ret;
}


inline void * memchr(const void *_str, char _chr, size_t _count)
{
	int d0;
	void *res;
	if (!_count)
		return NULL;
	asm volatile("repne\n\t"
		"scasb\n\t"
		"je 1f\n\t"
		"movl $1,%0\n"
		"1:\tdecl %0"
		: "=D" (res), "=&c" (d0)
		: "a" (_chr), "0" (_str), "1" (_count)
		: "memory");
	return res;
}

void *memset(void *_src, int _val, size_t _count)
{
          char *src = _src;
  
         /* Truncate c to 8 bits */
        _val = (_val & 0xFF);
        
         /* Simple, byte oriented memset or the rest of count. */
         while (_count--)
                 *src++ = _val;
 
         return _src;
}

