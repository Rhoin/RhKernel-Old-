CC := gcc
CCFLAGS := -I../../../include/  -Wall -O -fno-stack-protector -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin 
CSOURCES := $(wildcard *.c)
COBJS := $(CSOURCES:.c=.o)

%.o: %.c
	$(CC) $(CCFLAGS) -c $<
	
	
move: $(COBJS)
	mv *.o -t ../../../obj/
	
