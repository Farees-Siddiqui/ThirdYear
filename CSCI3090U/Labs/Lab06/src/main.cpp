/************************************************
 *
 *             Example 8
 *
 *  This example uses the vase model plus
 *  a texture map loaded from a file to
 *  illustrate the basic process of texture
 *  mapping.
 *
 ************************************************/

// #include <Windows.h>
#include <gl/glew.h>
#define GLFW_DLL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shaders.h"
#include <stdio.h>
#include <iostream>
#include "FreeImage/FreeImage.h"
#include <random>

GLuint program;			// shader programs
GLuint objVAO;			// the data to be displayed
GLuint ibuffer;

double theta, phi;
double r;

glm::mat4 projection;	// projection matrix
float eyex, eyey, eyez;	// eye position

GLuint texName;			// texture name

const int np = 200;

struct textureStruct {
	int height;
	int width;
	int bytes;
	unsigned char *data;
};

/*
 *  The loadImage function loads an image from a jpeg
 *  file that will be used as a texture
 */
 
textureStruct* loadImage(char *filename) {
	int i,j;
	FIBITMAP *bitmap;
	BYTE *bits;
	int width;
	int height;
	int bytes;
	unsigned char *data;
	textureStruct *result;
	int k;

	result = new textureStruct();

	bitmap = FreeImage_Load(FIF_JPEG, filename, JPEG_DEFAULT);
	height = FreeImage_GetHeight(bitmap);
	width = FreeImage_GetWidth(bitmap);
	bytes = FreeImage_GetBPP(bitmap)/8;
	printf("image size: %d %d %d\n",width, height, bytes);
	data = new unsigned char[width*height*bytes];
	result->height = height;
	result->width = width;
	result->bytes = bytes;
	result->data = data;

	k = 0;
	for(j=0; j<height; j++) {
		bits = FreeImage_GetScanLine(bitmap,j);
			for(i=0; i<width; i++) {
				data[k++] = bits[FI_RGBA_RED];
				data[k++] = bits[FI_RGBA_GREEN];
				data[k++] = bits[FI_RGBA_BLUE];
				bits += 3;
			}
	}
	FreeImage_Unload(bitmap);
	return(result);
}


/*
 *  The init procedure creates the OpenGL data structures
 *  that contain a list of random points, compiles our
 *  shader program and links the shader programs to
 *  the data.
 */

void init() {
	GLuint vbuffer;
	GLint vPosition;
	int vs;
	int fs;
	GLfloat *vertices;
	GLuint *indices;
	int i;
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(-2.0,2.0);

	textureStruct *texture;

	glGenVertexArrays(1, &objVAO);
	glBindVertexArray(objVAO);

	vertices = new GLfloat[4*np];

	/*
	 *  generate np random points in space
	 */
	for(i=0; i<np; i++) {
		vertices[4*i] = distribution(generator);
		vertices[4*i+1] = distribution(generator);
		vertices[4*i+2] = distribution(generator);
		vertices[4*i+3] = 1.0;
	}

	indices = new GLuint[np];
	for(i=0; i<np; i++)
		indices[i] = i;

	/*
	 *  load the vertex coordinate data
	 */
	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, 4*np*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4*np*sizeof(GLfloat), vertices);
	
	/*
	 *  load the vertex indexes
	 */
	glGenBuffers(1, &ibuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, np*sizeof(GLuint), indices, GL_STATIC_DRAW);

	/*
	 *  compile and build the shader program
	 */
	
	vs = buildShader(GL_VERTEX_SHADER, (char*)"../src/lab6.vs");
	fs = buildShader(GL_FRAGMENT_SHADER, (char*)"../src/lab6b.fs");
	program = buildProgram(vs,fs,0);

	/*
	 *  link the vertex coordinates to the vPosition
	 *  variable in the vertex program.  
	 */
	glUseProgram(program);
	vPosition = glGetAttribLocation(program,"vPosition");
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);

	/*
	 *  Create the texture.
	 */

	texture = loadImage((char*)"../src/star.jpg");
    
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height,
		0, GL_RGB,GL_UNSIGNED_BYTE,  texture->data);
	glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

}

/*
 *  Executed each time the window is resized,
 *  usually once at the start of the program.
 */
void framebufferSizeCallback(GLFWwindow *window, int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).

	if (h == 0)
		h = 1;

	float ratio = 1.0f * w / h;

	glfwMakeContextCurrent(window);

	glViewport(0, 0, w, h);

	projection = glm::perspective(0.7f, ratio, 1.0f, 800.0f);

}

/*
 *  This procedure is called each time the screen needs
 *  to be redisplayed
 */
void display() {
	glm::mat4 view;
	int modelViewLoc;
	int projectionLoc;
	int normalLoc;
	int eyeLoc;

	view = glm::lookAt(glm::vec3(eyex, eyey, eyez),
					glm::vec3(0.0,0.0,0.0),
					glm::vec3(0.0f, 1.0f, 0.0f));


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	modelViewLoc = glGetUniformLocation(program,"modelView");
	glUniformMatrix4fv(modelViewLoc, 1, 0, glm::value_ptr(view));
	projectionLoc = glGetUniformLocation(program,"projection");
	glUniformMatrix4fv(projectionLoc, 1, 0, glm::value_ptr(projection));

	glBindTexture(GL_TEXTURE_2D, texName);

	glBindVertexArray(objVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);

	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glDrawElements(GL_POINTS, np, GL_UNSIGNED_INT, NULL);

}

/*
 *  Called each time a key is pressed on
 *  the keyboard.
 */
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		phi -= 0.1;
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		phi += 0.1;
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		theta += 0.1;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		theta -= 0.1;

	eyex = (float)(r*sin(theta)*cos(phi));
	eyey = (float)(r*sin(theta)*sin(phi));
	eyez = (float)(r*cos(theta));

}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char **argv) {
	GLFWwindow *window;
	/*
	 *  initialize glut, set some parameters for
	 *  the application and create the window
	 */
	 // start by setting error callback in case something goes wrong

	glfwSetErrorCallback(error_callback);

	// initialize glfw

	if (!glfwInit()) {
		fprintf(stderr, "can't initialize GLFW\n");
	}

	// create the window used by our application

	window = glfwCreateWindow(512, 512, "Laboratory Six", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// establish framebuffer size change and input callbacks

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glfwSetKeyCallback(window, key_callback);

	/*
	 *  initialize glew
	 */
	glfwMakeContextCurrent(window);
	GLenum error = glewInit();
	if(error != GLEW_OK) {
		printf("Error starting GLEW: %s\n",glewGetErrorString(error));
		exit(0);
	}

	eyex = 0.0;
	eyey = 0.0;
	eyez = 5.0;

	theta = 0.5;
	phi = 1.5;
	r = 5.0;

	init();

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0,0.0,0.0,1.0);
	glViewport(0, 0, 512, 512);

	projection = glm::perspective(0.7f, 1.0f, 1.0f, 800.0f);

	glfwSwapInterval(1);

	// GLFW main loop, display model, swapbuffer and check for input

	while (!glfwWindowShouldClose(window)) {
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


}