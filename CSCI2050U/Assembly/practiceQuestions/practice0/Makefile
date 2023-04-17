all: practice.asm
	yasm -a x86 -m amd64 -g dwarf2 -f elf64 -o practice.o practice.asm
	gcc -m64 -no-pie -o main.out practice.o

clean:
	rm *.out
	rm *.o
