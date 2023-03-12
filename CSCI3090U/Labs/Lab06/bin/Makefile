all: compile link

compile:
	gcc -I../include -c ../src/*.cpp

link: 
	g++ *.o -o Lab05 -L../lib -lglfw3dll -lopengl32 -lgdi32 -lglew32 -lm -lfreeimage

clean: 
	rm *.o
	rm *.exe
