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
#include "perlin.h"
#include "FreeImage.h"

#define WIDTH 512
#define HEIGHT 512

unsigned char image[WIDTH][HEIGHT][3];


GLuint program;		// shader programs
GLuint triangleVAO; // the data to be displayed
float angle = 0.0;
double theta, phi; // user's position  on a sphere centered on the object
double r;		   // radius of the sphere
GLuint ibuffer;

glm::mat4 projection;	// projection matrix
float eyex, eyey, eyez; // eye position

/*
 *  The init procedure creates the OpenGL data structures
 *  that contain the triangle geometry, compiles our
 *  shader program and links the shader programs to
 *  the data.
 */

void makeImage(float f) {
    float vec[2];
    int i, j;
    float dx, dy;
    float n;

    dx = f/WIDTH;
    dy = f/HEIGHT;
    vec[0] = vec[1] = 0.0;
    for(i=0; i<WIDTH; i++) {
        vec[0] = i*dx;
        for(j=0; j<HEIGHT; j++) {
            vec[1] = j*dy;
            n = noise2(vec);
            n = 0.5*n + 0.5;
            image[i][j][0] = 256*n;
            image[i][j][1] = 256*n;
            image[i][j][2] = 256*n;
        }
    }
}

void saveImage(char *filename) {
    int i;
    int j;
    FIBITMAP *bitmap;
    BYTE *bits;
    bitmap = FreeImage_Allocate(WIDTH, HEIGHT, 24);
    for(j=0; j<HEIGHT; j++) {
        bits = FreeImage_GetScanLine(bitmap,j);
            for(i=0; i<WIDTH; i++) {
            bits[FI_RGBA_RED] = image[j][i][0];
            bits[FI_RGBA_GREEN] = image[j][i][1];
            bits[FI_RGBA_BLUE] = image[j][i][2];
            bits += 3;
        }
    }
    FreeImage_Save(FIF_PNG, bitmap, filename, PNG_DEFAULT);
}

void init()
{
	GLuint vbuffer;
	GLint vPosition;
	GLint vNormal;
	int vs;
	int fs;

	glGenVertexArrays(1, &triangleVAO);
	glBindVertexArray(triangleVAO);

	// GLfloat vertices[3][2] = {	// coordinates of triangle vertices
	// 	{ -0.5, -0.5 },
	// 	{  0.0,  0.5},
	// 	{  0.5, -0.5}
	// };

	// GLfloat normals[3][3] = {
	// 	{0.0, 0.0, 1.0},
	// 	{0.0, 0.0, 1.0},
	// 	{0.0, 0.0, 1.0}
	// };

	// GLushort indexes[3] = { 0, 1, 2 };	// indexes of triangle vertices

	GLfloat vertices[8][4] = {
		{-1.0, -1.0, -1.0, 1.0}, // 0
		{-1.0, -1.0, 1.0, 1.0},	 // 1
		{-1.0, 1.0, -1.0, 1.0},	 // 2
		{-1.0, 1.0, 1.0, 1.0},	 // 3
		{1.0, -1.0, -1.0, 1.0},	 // 4
		{1.0, -1.0, 1.0, 1.0},	 // 5
		{1.0, 1.0, -1.0, 1.0},	 // 6
		{1.0, 1.0, 1.0, 1.0}	 // 7
	};

	GLfloat normals[8][3] = {
		{-1.0, -1.0, -1.0}, // 0
		{-1.0, -1.0, 1.0},	// 1
		{-1.0, 1.0, -1.0},	// 2
		{-1.0, 1.0, 1.0},	// 3
		{1.0, -1.0, -1.0},	// 4
		{1.0, -1.0, 1.0},	// 5
		{1.0, 1.0, -1.0},	// 6
		{1.0, 1.0, 1.0}		// 7
	};

	GLushort indexes[36] = {0, 1, 3, 0, 2, 3,
							0, 4, 5, 0, 1, 5,
							2, 6, 7, 2, 3, 7,
							0, 4, 6, 0, 2, 6,
							1, 5, 7, 1, 3, 7,
							4, 5, 7, 4, 6, 7};

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
	vs = buildShader(GL_VERTEX_SHADER, (char *)"../src/example4.vs");
	fs = buildShader(GL_FRAGMENT_SHADER, (char *)"../src/example4.fs");
	program = buildProgram(vs, fs, 0);

	/*
	 *  link the vertex coordinates to the vPosition
	 *  variable in the vertex program
	 */
	glUseProgram(program);
	vPosition = glGetAttribLocation(program, "vPosition");
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
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
	int projLoc;
	int veinLoc;
	int baseLoc;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);

	model = glm::rotate(glm::mat4(1.0), angle, glm::vec3(0.0, 1.0, 0.0));

	view = glm::lookAt(glm::vec3(eyex, eyey, eyez),
					   glm::vec3(0.0f, 0.0f, 0.0f),
					   glm::vec3(0.0f, 1.0f, 0.0f));

	// glm::mat3 normal = glm::transpose(glm::inverse(glm::mat3(view * model)));

	modelViewPerspective = model * view;

	glUseProgram(program);
	modelLoc = glGetUniformLocation(program, "modelView");
	glUniformMatrix4fv(modelLoc, 1, 0, glm::value_ptr(modelViewPerspective));
	projLoc = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(projLoc, 1, 0, glm::value_ptr(projection));

	veinLoc = glGetUniformLocation(program, "veinColour");
	glUniform4f(veinLoc, 0.8, 0.8, 0.8, 1);

	baseLoc = glGetUniformLocation(program, "baseColour");
	glUniform4f(baseLoc, 0.2, 0.2, 0.8, 1);


	glBindVertexArray(triangleVAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, NULL);
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
		phi -= 0.1;
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		phi += 0.1;
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		theta += 0.1;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		theta -= 0.1;

	eyex = (float)(r * sin(theta) * cos(phi));
	eyey = (float)(r * sin(theta) * sin(phi));
	eyez = (float)(r * cos(theta));
}

void error_callback(int error, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char **argv)
{
	float f;
	f = 10.0;

	if (argc > 1)
	{
		f = atof(argv[1]);
	}

	printf("f = %f\n", f);
	makeImage(f);
	saveImage("perlin.png");
	GLFWwindow *window;

	// start by setting error callback in case something goes wrong

	glfwSetErrorCallback(error_callback);

	// initialize glfw

	if (!glfwInit())
	{
		fprintf(stderr, "can't initialize GLFW\n");
	}

	// create the window used by our application

	window = glfwCreateWindow(512, 512, "Lab01", NULL, NULL);
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
	glClearColor(1.0, 1.0, 1.0, 0.8);
	glViewport(0, 0, 512, 512);

	projection = glm::perspective(0.7f, 1.0f, 1.0f, 100.0f);

	init();

	eyex = 0.0;
	eyez = 10.0;
	eyey = 0.0;

	theta = 1.5;
	phi = 1.5;
	r = 10.0;

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
