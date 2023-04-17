all: practice1.asm
	yasm -a x86 -m amd64 -g dwarf2 -f elf64 -o main.o practice1.asm
	gcc -m64 -no-pie -o main.out main.o

clean:
	rm *.out
	rm *.o

run:
	./main.out