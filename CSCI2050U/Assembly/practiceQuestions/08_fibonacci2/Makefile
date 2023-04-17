all: fib_func.asm
	yasm -a x86 -m amd64 -g dwarf2 -f elf64 -o fib_func.o fib_func.asm
	gcc -m64 -no-pie -o fib_func.out fib_func.o

clean:
	rm *.out
	rm *.o

run:
	./fib_func.out
