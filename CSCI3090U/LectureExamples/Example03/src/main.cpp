/************************************************
 *
 *             Example Three
 *
 *  A  basic OpenGL program that draws a
 *  triangle on the screen with colour computed using
 *  a simple diffuse light model.  This program illustrates
 *  the addition of normal vectors to the vertex array.
 *
 ************************************************/

#ifdef WIN32
#include <Windows.h>
#endif
#include <GL/glew.h>
#define GLFW_DLL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.h"
#include <stdio.h>

GLuint program;			// shader programs
GLuint triangleVAO;		// the data to be displayed
float angle = 0.0;		// rotation angle and its initial value
int window;				// ID of the window we are using
GLuint ibuffer;

/*
 *  The init procedure creates the OpenGL data structures
 *  that contain the triangle geometry, compiles our
 *  shader program and links the shader programs to
 *  the data.
 */

void init() {
	GLuint vbuffer;
	GLint vPosition;
	GLint vNormal;
	int vs;
	int fs;

	glGenVertexArrays(1, &triangleVAO);
	glBindVertexArray(triangleVAO);

	GLfloat vertices[3][2] = {	// coordinates of triangle vertices
		{ -0.5, -0.5 },
		{  0.0,  0.5},
		{  0.5, -0.5}
	};

	GLfloat normals[3][3] = {	// the normal vectors for each vertex
		{0.0, 0.0, 1.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, 1.0}
	};

	GLushort indexes[3] = { 0, 1, 2 };	// indexes of triangle vertices

	/*
	 *  load the vertex coordinate data and normal vectors
	 */
	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(normals), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(normals), normals);
	
	/*
	 *  load the vertex indexes
	 */
	glGenBuffers(1, &ibuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

	/*
	 *  compile and build the shader program
	 */
	vs = buildShader(GL_VERTEX_SHADER, (char*)"../src/example3.vs");
	fs = buildShader(GL_FRAGMENT_SHADER, (char*)"../src/example3.fs");
	program = buildProgram(vs,fs,0);

	/*
	 *  link the vertex coordinates to the vPosition
	 *  variable in the vertex program and the normal
	 *  vectors to the vNormal variable in the
	 *  vertext program.
	 */
	glUseProgram(program);
	vPosition = glGetAttribLocation(program,"vPosition");
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
	vNormal = glGetAttribLocation(program, "vNormal");
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (void*) sizeof(vertices));
	glEnableVertexAttribArray(vNormal);

}

/*
 *  This procedure is called each time the screen needs
 *  to be redisplayed
 */
void display() {
	glm::mat4 model;
	int modelLoc;

	model = glm::rotate(glm::mat4(1.0), angle, glm::vec3(0.0, 1.0, 0.0));

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
	modelLoc = glGetUniformLocation(program,"model");
	glUniformMatrix4fv(modelLoc, 1, 0, glm::value_ptr(model));

	glBindVertexArray(triangleVAO);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

}

void framebufferSizeCallback(GLFWwindow *window, int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).

	if (h == 0)
		h = 1;

	float ratio = 1.0f * w / h;

	glfwMakeContextCurrent(window);

	glViewport(0, 0, w, h);

}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char **argv) {
	GLFWwindow *window;

	// start by setting error callback in case something goes wrong

	glfwSetErrorCallback(error_callback);

	// initialize glfw

	if (!glfwInit()) {
		fprintf(stderr, "can't initialize GLFW\n");
	}

	// create the window used by our application

	window = glfwCreateWindow(512, 512, "Example Two", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// establish framebuffer size change and input callbacks

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	/*
	 *  initialize glew
	 */
	glfwMakeContextCurrent(window);
	GLenum error = glewInit();
	if(error != GLEW_OK) {
		printf("Error starting GLEW: %s\n",glewGetErrorString(error));
		exit(0);
	}

	init();

	glClearColor(1.0,1.0,1.0,1.0);

	glfwSwapInterval(1);

	// GLFW main loop, display model, swapbuffer and check for input

	while (!glfwWindowShouldClose(window)) {
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
		angle = angle + 0.01;
	}

	glfwTerminate();

}
