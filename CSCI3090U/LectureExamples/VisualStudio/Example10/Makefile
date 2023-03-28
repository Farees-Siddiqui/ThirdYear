TARGET=example10

$(TARGET) : main.o Shaders.o tiny_obj_loader.o
	c++ -o $(TARGET) main.o Shaders.o tiny_obj_loader.o -lfreeimage -lglfw -lGLEW -lGLU -lGL -lm

main.o: Shaders.h

Shaders.o: Shaders.h

tiny_obj_loader.o: tiny_obj_loader.cc
	c++ -c -o tiny_obj_loader.o tiny_obj_loader.cc

clean:
	rm $(TARGET) main.o Shaders.o tiny_obj_loader.o
