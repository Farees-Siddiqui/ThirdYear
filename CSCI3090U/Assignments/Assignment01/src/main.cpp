/************************************************
 *
 *             Example Four
 *
 *  A basic OpenGL program that draws a
 *  triangle on the screen in perspective with
 *  simple control over the eye position.
 *  This program illustrates the construction of
 *  perspective and viewing transformations.
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
#include <iostream>

GLuint program;		// shader programs
GLuint program2;
GLuint triangleVAO; // the data to be displayed
float angle = 0.0;
double theta, phi; // user's position  on a sphere centered on the object
double r;		   // radius of the sphere
GLuint ibuffer;

glm::mat4 projection;	// projection matrix
float eyex, eyey, eyez; // eye position
bool swtch = false;
/*
 *  The init procedure creates the OpenGL data structures
 *  that contain the triangle geometry, compiles our
 *  shader program and links the shader programs to
 *  the data.
 */

void init()
{
	GLuint vbuffer;
	GLint vPosition;
	GLint vNormal;
	int vs;
	int fs;

	glGenVertexArrays(1, &triangleVAO);
	glBindVertexArray(triangleVAO);

	GLfloat vertices[4][3] = {
		{ -50.0f, 0.0,-50.0f},
		{  50.0f, 0.0,-50.0f},
		{  50.0f, 0.0, 50.0f},
		{ -50.0f, 0.0, 50.0f}
	};

	GLfloat normals[4][3] = {
		{0.0, 0.0, 1.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, 1.0}
	};

	GLushort indexes[6] = { 0, 1, 2, 0, 2, 3};

	/*
	 *  load the vertex coordinate data
	 */
	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(normals), NULL, GL_STATIC_DRAW);
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
	vs = buildShader(GL_VERTEX_SHADER, (char *)"../src/example5.vs");
	fs = buildShader(GL_FRAGMENT_SHADER, (char *)"../src/example5.fs");
	
	int fs2, vs2;

	program = buildProgram(vs, fs, 0);


	vs2 = buildShader(GL_VERTEX_SHADER, (char *)"../src/example2.vs");
	fs2 = buildShader(GL_FRAGMENT_SHADER, (char *)"../src/example2.fs");
	program2 = buildProgram(vs2, fs2, 0);

	/*
	 *  link the vertex coordinates to the vPosition
	 *  variable in the vertex program
	 */
	glUseProgram(program);
	vPosition = glGetAttribLocation(program, "vPosition");
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
	vNormal = glGetAttribLocation(program, "vNormal");
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (void *)sizeof(vertices));
	glEnableVertexAttribArray(vNormal);
}

void framebufferSizeCallback(GLFWwindow *window, int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).

	if (h == 0)
		h = 1;

	float ratio = 1.0f * w / h;

	glfwMakeContextCurrent(window);

	glViewport(0, 0, w, h);

	projection = glm::perspective(0.7f, ratio, 1.0f, 100.0f);
}

/*
 *  This procedure is called each time the screen needs
 *  to be redisplayed
 */
void display()
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 modelViewPerspective;
	int modelLoc;
	int normalLoc;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);

	model = glm::rotate(glm::mat4(1.0), angle, glm::vec3(0.0, 1.0, 0.0));

	view = glm::lookAt(glm::vec3(eyex, eyey, eyez),
					   glm::vec3(0.0f, 0.0f, 0.0f),
					   glm::vec3(0.0f, 0.0f, -1.0f));

	glm::mat3 normal = glm::transpose(glm::inverse(glm::mat3(view * model)));

	modelViewPerspective = projection * view * model;

	glUseProgram(program);
	modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, 0, glm::value_ptr(modelViewPerspective));
	normalLoc = glGetUniformLocation(program, "normalMat");
	glUniformMatrix3fv(normalLoc, 1, 0, glm::value_ptr(normal));

	glBindVertexArray(triangleVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

	GLuint newVAO;
	glGenVertexArrays(1, &newVAO);
	glBindVertexArray(newVAO);

	GLfloat vertices2[3][3] = {	// coordinates of triangle vertices
		{ 0.0,  800.0, 0.0 },
		{ 400.0,800.0, 0.0},
		{  800.0, 800.0, 0.0}
	};

	GLushort indexes2[3] = { 0, 1, 2 };


	GLuint vbuffer2, ibuffer2;
	GLint vPosition2;

	/*
	 *  load the vertex coordinate data
	 */
	glGenBuffers(1, &vbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices2), vertices2);
	
	/*
	 *  load the vertex indexes
	 */
	glGenBuffers(1, &ibuffer2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes2), indexes2, GL_STATIC_DRAW);

	/*
	 *  link the vertex coordinates to the vPosition
	 *  variable in the vertex program
	 */
	glUseProgram(program2);
	vPosition2 = glGetAttribLocation(program2,"vPosition");
	glVertexAttribPointer(vPosition2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition2);

	glBindVertexArray(newVAO);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

}

/*
 *  Called each time a key is pressed on
 *  the keyboard.
 */

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		swtch = !swtch;
	// if (key == GLFW_KEY_D && action == GLFW_PRESS)
	// 	phi += 0.1;
	// if (key == GLFW_KEY_W && action == GLFW_PRESS)
	// 	theta += 0.1;
	// if (key == GLFW_KEY_S && action == GLFW_PRESS)
	// 	theta -= 0.1;

	// eyex = (float)(r * sin(theta) * cos(phi));
	// eyey = (float)(r * sin(theta) * sin(phi));
	// eyez = (float)(r * cos(theta));
}

void error_callback(int error, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << "Mouse position: (" << xpos << ", " << ypos << ")" << std::endl;
}

int main(int argc, char **argv)
{
	GLFWwindow *window;
	std::cout << argv[0] << std::endl;

	// start by setting error callback in case something goes wrong

	glfwSetErrorCallback(error_callback);

	// initialize glfw

	if (!glfwInit())
	{
		fprintf(stderr, "can't initialize GLFW\n");
	}

	// create the window used by our application

	window = glfwCreateWindow(800, 800, "Assignment One", NULL, NULL);
	glEnable(GL_DEPTH_TEST);

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
	if (error != GLEW_OK)
	{
		printf("Error starting GLEW: %s\n", glewGetErrorString(error));
		exit(0);
	}

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.603, 0.882, 0.956, 0.8);
	glViewport(0, 0, 900, 900);

	projection = glm::perspective(0.4f, 1.0f, 1.0f, 100.0f);

	init();

	eyex = 0.0;
	eyez = 65.0;
	eyey = -15.0;

	// theta = 0;
	// phi = 1.5;
	// r = 10.0;

	glfwSwapInterval(1);

	// GLFW main loop, display model, swapbuffer and check for input

	while (!glfwWindowShouldClose(window))
	{
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
