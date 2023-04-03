/************************************************************
*
*                   Example 12
*
*  This is an example of environment maps used both a a
*  background and to simulate specular reflection in
*  the fragement shader.  The result is a shiny sphere
*  outside the Vancouver Convention Centre
*
*********************************************************/
#define GLM_FORCE_RADIANS

#ifdef WIN32
#include <Windows.h>
#endif
#include <GL/glew.h>
#define GLFW_DLL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define _USE_MATH_DEFINES 
#include <math.h>
#include <stdio.h>
#include "Shaders.h"
#include "tiny_obj_loader.h"
#include <iostream>
#include "texture.h"

float eyex, eyey, eyez;

double theta, phi;
double r;

GLuint program;
GLuint program2;

glm::mat4 projection;

GLuint objVAO;
GLuint cubeVAO;
GLuint objBuffer;
GLuint cubeBuffer;
int triangles;
GLuint envMap;

/*
 *  Create a cube object that will be the background
 *  for the scene.  The texture coordinates are
 *  computed in the fragment shader.
 */
void background() {
	GLuint vbuffer;
	GLint vPosition;
	GLint vNormal;
	GLfloat L = 7.0f;

	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);

	GLfloat vertices[8][4] = {
			{ -L, -L, -L, 1.0 },		//0
			{ -L, -L, L, 1.0 },		//1
			{ -L, L, -L, 1.0 },		//2
			{ -L, L, L, 1.0 },		//3
			{ L, -L, -L, 1.0 },		//4
			{ L, -L, L, 1.0 },		//5
			{ L, L, -L, 1.0 },		//6
			{ L, L, L, 1.0 }			//7
	};

	GLfloat normals[8][3] = {
			{ -1.0, -1.0, -1.0 },			//0
			{ -1.0, -1.0, 1.0 },			//1
			{ -1.0, 1.0, -1.0 },			//2
			{ -1.0, 1.0, 1.0 },				//3
			{ 1.0, -1.0, -1.0 },			//4
			{ 1.0, -1.0, 1.0 },				//5
			{ 1.0, 1.0, -1.0 },				//6
			{ 1.0, 1.0, 1.0 }				//7
	};

	GLuint indexes[36] = { 0, 1, 3, 0, 2, 3,
		0, 4, 5, 0, 1, 5,
		2, 6, 7, 2, 3, 7,
		0, 4, 6, 0, 2, 6,
		1, 5, 7, 1, 3, 7,
		4, 5, 7, 4, 6, 7 };


	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(normals), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(normals), normals);

	glGenBuffers(1, &cubeBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

	glUseProgram(program2);
	vPosition = glGetAttribLocation(program2, "vPosition");
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
	vNormal = glGetAttribLocation(program2, "vNormal");
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (void*) sizeof(vertices));
	glEnableVertexAttribArray(vNormal);

}

/*
 *  Read the sphere object from the obj file
 */
void init() {
	GLuint vbuffer;
	GLint vPosition;
	GLint vNormal;
	GLint vTex;
	GLuint tBuffer;
	GLfloat *vertices;
	GLfloat *normals;
	GLfloat *tex;
	GLuint *indices;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	int nv;
	int nn;
	int ni;
	int nt;
	int i;
	int verts;
	double x, y, z;
	double theta, phi;
	struct Cube *texture;

	glGenVertexArrays(1, &objVAO);
	glBindVertexArray(objVAO);

	/*  Load the obj file */

	std::string err = tinyobj::LoadObj(shapes, materials, "../src/sphere.obj", 0);

	if (!err.empty()) {
		std::cerr << err << std::endl;
		return;
	}

	/*  Retrieve the vertex coordinate data */

	nv = shapes[0].mesh.positions.size();
	vertices = new GLfloat[nv];
	for (i = 0; i<nv; i++) {
		vertices[i] = shapes[0].mesh.positions[i];
	}

	/*  Retrieve the vertex normals */

	nn = shapes[0].mesh.normals.size();
	normals = new GLfloat[nn];
	for (i = 0; i<nn; i++) {
		normals[i] = shapes[0].mesh.normals[i];
	}

	verts = nv / 3;
	nt = 2 * verts;
	tex = new GLfloat[nt];
	for (i = 0; i < verts; i++) {
		x = vertices[3 * i];
		y = vertices[3 * i + 1];
		z = vertices[3 * i + 2];
		
		theta = atan2(x,z);
		phi = atan2(y,sqrt(x*x + z*z));
		
		tex[2 * i] = (theta+M_PI) / (2 * M_PI);
		tex[2 * i] = fabs(theta) / M_PI;
		tex[2 * i + 1] = phi / M_PI;
	}

	/*  Retrieve the triangle indices */

	ni = shapes[0].mesh.indices.size();
	triangles = ni / 3;
	indices = new GLuint[ni];
	for (i = 0; i<ni; i++) {
		indices[i] = shapes[0].mesh.indices[i];
	}

	/*
	*  load the vertex coordinate data
	*/
	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, (nv + nn + nt)*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, nv*sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, nv*sizeof(GLfloat), nn*sizeof(GLfloat), normals);
	glBufferSubData(GL_ARRAY_BUFFER, (nv + nn)*sizeof(GLfloat), nt*sizeof(GLfloat), tex);

	/*
	*  load the vertex indexes
	*/
	glGenBuffers(1, &objBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ni*sizeof(GLuint), indices, GL_STATIC_DRAW);

	/*
	*  link the vertex coordinates to the vPosition
	*  variable in the vertex program.  Do the same
	*  for the normal vectors.
	*/
	glUseProgram(program);
	vPosition = glGetAttribLocation(program, "vPosition");
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
	vNormal = glGetAttribLocation(program, "vNormal");
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (void*)(nv*sizeof(GLfloat)));
	glEnableVertexAttribArray(vNormal);
	vTex = glGetAttribLocation(program, "vTex");
	glVertexAttribPointer(vTex, 2, GL_FLOAT, GL_FALSE, 0, (void*)((nv + nn)*sizeof(GLfloat)));
	glEnableVertexAttribArray(vTex);

	/*
	 *  Call loadCube to load a cube texture that will
	 *  be used as our environment map.
	 */
#ifdef WIN32
	texture = loadCube("../VancouverConventionCentre");
#else
	texture = loadCube((char*)(char*)"../VancouverConventionCentre");
#endif
	glGenTextures(1, &envMap);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, envMap);
	for (i = 0; i<6; i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, texture->width, texture->height,
			0, GL_RGB, GL_UNSIGNED_BYTE, texture->data[i]);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


}

void framebufferSizeCallback(GLFWwindow *window, int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).

	if (h == 0)
		h = 1;

	float ratio = 1.0f * w / h;

	glfwMakeContextCurrent(window);

	glViewport(0, 0, w, h);

	projection = glm::perspective(0.7f, ratio, 1.0f, 100.0f);

}

void display(void) {
	glm::mat4 view;
	int viewLoc;
	int projLoc;
	int colourLoc;
	int eyeLoc;
	int lightLoc;
	int materialLoc;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program2);

	view = glm::lookAt(glm::vec3(eyex, eyey, eyez),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f));

	/*
	 *  start by displaying the background cube
	 */
	viewLoc = glGetUniformLocation(program2, "modelView");
	glUniformMatrix4fv(viewLoc, 1, 0, glm::value_ptr(view));
	projLoc = glGetUniformLocation(program2, "projection");
	glUniformMatrix4fv(projLoc, 1, 0, glm::value_ptr(projection));
	eyeLoc = glGetUniformLocation(program2, "Eye");
	glUniform3f(eyeLoc, eyex, eyey, eyez);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeBuffer);
	glBindTexture(GL_TEXTURE_CUBE_MAP, envMap);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	glUseProgram(program);

	/*
	 *  now display the sphere
	 */
	viewLoc = glGetUniformLocation(program, "modelView");
	glUniformMatrix4fv(viewLoc, 1, 0, glm::value_ptr(view));
	projLoc = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(projLoc, 1, 0, glm::value_ptr(projection));

	colourLoc = glGetUniformLocation(program, "colour");
	glUniform4f(colourLoc, 1.0, 0.0, 0.0, 1.0);
	eyeLoc = glGetUniformLocation(program, "Eye");
	glUniform3f(eyeLoc, eyex, eyey, eyez);
	lightLoc = glGetUniformLocation(program, "light");
	glUniform3f(lightLoc, 1.0, 1.0, 1.0);
	materialLoc = glGetUniformLocation(program, "material");
	glUniform4f(materialLoc, 0.3, 0.7, 0.7, 150.0);
	
	glBindVertexArray(objVAO);
	glDrawElements(GL_TRIANGLES, 3*triangles, GL_UNSIGNED_INT, NULL);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_A && action == GLFW_REPEAT)
		phi += 0.1;
	if (key == GLFW_KEY_D && action == GLFW_REPEAT)
		phi -= 0.1;
	if (key == GLFW_KEY_W && action == GLFW_REPEAT)
		theta += 0.1;
	if (key == GLFW_KEY_S && action == GLFW_REPEAT)
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
	int fs;
	int vs;
	int user;
	char vertexName[256];
	char fragmentName[256];
	char *fragment;
	char *vertex;
	GLFWwindow *window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "can't initialize GLFW\n");
	}

	window = glfwCreateWindow(512, 512, "Example Twelve", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "can't create window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		printf("Error starting GLEW: %s\n", glewGetErrorString(error));
		exit(0);
	}

	if (argc < 3) {
		printf("usage: viewer vertex_suffix fragment_suffix\n");
		exit(0);
	}
	vertex = argv[1];
	fragment = argv[2];

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glViewport(0, 0, 512, 512);

	projection = glm::perspective(0.7f, 1.0f, 1.0f, 200.0f);

	/*
	 *  there are two programs, one for the background
	 *  and one for the sphere
	 */
	sprintf(vertexName, "../src/example12%s.vs", vertex);
	vs = buildShader(GL_VERTEX_SHADER, vertexName);
	sprintf(fragmentName, "../src/example12%s.fs", fragment);
	fs = buildShader(GL_FRAGMENT_SHADER, fragmentName);
	program = buildProgram(vs, fs, 0);
	vs = buildShader(GL_VERTEX_SHADER, (char*)"../src/cube.vs");
	fs = buildShader(GL_FRAGMENT_SHADER, (char*)"../src/cube.fs");
	program2 = buildProgram(vs, fs, 0);
	dumpProgram(program, (char*)"Example 10 shader program");
	init();
	background();

	eyex = 0.0;
	eyez = 0.0;
	eyey = 5.0;

	theta = 1.5;
	phi = 1.5;
	r = 5.0;

	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window)) {
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

}
