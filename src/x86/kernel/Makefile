CC := gcc
CCFLAGS := -I../../../include/ -Wall -O -fno-stack-protector -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin 
ASM := nasm
ASMFLAGS := -felf -I../../../include/
CSOURCES = $(wildcard *.c)
ASOURCES = $(wildcard *.s)
COBJS := $(CSOURCES:.c=.o)
AOBJS := $(ASOURCES:.s=.o)
OBJS := $(AOBJS) $(COBJS)


%.o: %.c
	$(CC) $(CCFLAGS) -c $<
	
%.o: %.s
	$(ASM) $(ASMFLAGS) $<

move: $(OBJS)
	mv *.o -t ../../../obj/
	
	
