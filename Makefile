OBJS := obj/*.o
all:kernel.bin

kernel.bin:
	cd obj
	ld -Tsrc/x86/kernel/link.ld $(OBJS) -o kernel.bin
	mv kernel.bin -t bin
	cd ..

