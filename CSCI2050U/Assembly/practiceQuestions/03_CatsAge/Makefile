all: main.asm
	yasm -a x86 -m amd64 -g dwarf2 -f elf64 -o main.o main.asm
	gcc -m64 -no-pie -o main.out main.o

clean:
	rm *.out
	rm *.o
