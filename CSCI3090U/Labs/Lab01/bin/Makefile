all: compile link

compile:
	g++ -I../include -c ../src/*.cpp 

link: 
	g++ *.o -o Lab01 -L../lib -lglfw3dll -lopengl32 -lgdi32 -lglew32 -lglu32 -lm

clean: 
	rm *.exe
	rm *.o