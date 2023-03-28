TARGET=example1

$(TARGET) : main.o Shaders.o
	c++ -o $(TARGET) main.o Shaders.o -lglfw -lGLEW -lGLU -lGL -lm

main.o: Shaders.h

Shaders.o: Shaders.h

clean:
	rm $(TARGET) main.o Shaders.o
