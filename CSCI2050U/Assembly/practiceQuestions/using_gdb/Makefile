all: debug.asm
	yasm -a x86 -m amd64 -g dwarf2 -f elf64 -o debug.o debug.asm
	gcc -no-pie -m64 -o debug.out debug.o
