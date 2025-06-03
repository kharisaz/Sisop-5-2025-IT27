build:
	@echo Building EorzeOS...
	@make -s prepare bootloader stdlib shell kernel link

prepare:
	@mkdir -p bin
	@dd if=/dev/zero of=bin/floppy.img bs=512 count=2880

bootloader:
	@nasm bootloader.asm -f bin -o bin/bootloader.bin

stdlib:
	@gcc -m32 -c std_lib.c -o bin/std_lib.o

shell:
	@gcc -m32 -c shell.c -o bin/shell.o

kernel:
	@gcc -m32 -c kernel.c -o bin/kernel.o
	@nasm kernel.asm -f elf -o bin/kernel_asm.o

link:
	@ld -m elf_i386 -Ttext 0x1000 bin/kernel.o bin/kernel_asm.o bin/std_lib.o bin/shell.o -o bin/kernel.bin
	@cat bin/bootloader.bin bin/kernel.bin > bin/floppy.img
