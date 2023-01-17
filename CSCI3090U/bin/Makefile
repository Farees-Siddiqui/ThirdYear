all:
    compile link

compile:
    clang++ -I../include -c ../src/*.cpp

link:
    clang++ *.o -o Lab01 -L../lib -lglfw3

clean:
	rm *.o
    rm *.out
