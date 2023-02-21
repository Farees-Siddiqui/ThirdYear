/************************************************
 *
 *             Example Six
 *
 *  An example showing how tiny obj loader can
 *  be used to load an obj file.  In this case
 * the object is the Blender Monkey
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
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.h"
#include <stdio.h>
#include "tiny_obj_loader.h"
#include <iostream>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

glm::vec3 camera_position = glm::vec3(-0.1f, -5.0f, -0.5f);

glm::vec3 camera_up = glm::vec3(0.0f, 0.0f, 1.0f);

glm::vec3 camera_front = glm::vec3(0.0f, 1.0f, 0.0f);

float camera_speed = 0.05f;

/*
 * The following structure represents a single mesh in the scene
*/
struct Mesh {
	GLuint vbuffer;		// vertex buffer name
	GLuint ibuffer;		// index buffer name
	GLuint triangles;	// number of triangles
	GLuint64 vbytes;	// size of vertices in bytes
	GLuint program;		// program for drawing the mesh
	glm::mat4 model;	// model transformation for the mesh
};

std::vector<Mesh*> Model;	// list of meshes in the scene

double theta, phi;
double r;

float cx, cy, cz;

glm::mat4 projection;	// projection matrix
float eyex, eyey, eyez;	// eye position

/*
 *  The loadObject procedure loads an object from an OBJ
 *  file and creates a mesh structure for it.  It also
 *  sets up the buffers for vertex information and indices.
 *  The parameter to this procedure is the file name for the model.
 */

Mesh* loadOBJ(char* filename) {
	GLuint vbuffer;
	GLuint ibuffer;
	GLuint objVAO;
	GLfloat* vertices;
	GLfloat* normals;
	GLuint* indices;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	int nv;
	int nn;
	int ni;
	int i;
	float xmin, ymin, zmin;
	float xmax, ymax, zmax;
	float dx, dy, dz;
	float scale;
	int triangles;
	Mesh* mesh;

	glGenVertexArrays(1, &objVAO);
	glBindVertexArray(objVAO);

	/*  Load the obj file */

	std::string err = tinyobj::LoadObj(shapes, materials, filename, 0);

	if (!err.empty()) {
		std::cerr << err << std::endl;
		return(NULL);
	}

	/*  Retrieve the vertex coordinate data */

	nv = shapes[0].mesh.positions.size();
	vertices = new GLfloat[nv];
	for (i = 0; i < nv; i++) {
		vertices[i] = shapes[0].mesh.positions[i];
	}

	/*
	 *  Find the range of the x, y and z
	 *  coordinates.
	 */

	xmin = ymin = zmin = 1000000.0;
	xmax = ymax = zmax = -1000000.0;
	for (i = 0; i < nv / 3; i++) {
		if (vertices[3 * i] < xmin)
			xmin = vertices[3 * i];
		if (vertices[3 * i] > xmax)
			xmax = vertices[3 * i];
		if (vertices[3 * i + 1] < ymin)
			ymin = vertices[3 * i + 1];
		if (vertices[3 * i + 1] > ymax)
			ymax = vertices[3 * i + 1];
		if (vertices[3 * i + 2] < zmin)
			zmin = vertices[3 * i + 2];
		if (vertices[3 * i + 2] > zmax)
			zmax = vertices[3 * i + 2];
	}

	/*
	 *  Scales the vertices so the longest axis is unit length
	*/
	
	dx = xmax - xmin;
	dy = ymax - ymin;
	dz = zmax - zmin;

	scale = dx;
	if (dy > scale)
		scale = dy;
	if (dz > scale)
		scale = dz;

	scale = 1.0 / scale;
	for (i = 0; i < nv; i++) {
		vertices[i] = vertices[i] * scale;
	}
	
	/*  Retrieve the vertex normals */

	nn = shapes[0].mesh.normals.size();
	normals = new GLfloat[nn];
	for (i = 0; i < nn; i++) {
		normals[i] = shapes[0].mesh.normals[i];
	}

	/*  Retrieve the triangle indices */

	ni = shapes[0].mesh.indices.size();
	triangles = ni / 3;
	indices = new GLuint[ni];
	for (i = 0; i < ni; i++) {
		indices[i] = shapes[0].mesh.indices[i];
	}

	/*
	 *  load the vertex coordinate data
	 */
	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, (nv + nn) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, nv * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, nv * sizeof(GLfloat), nn * sizeof(GLfloat), normals);

	/*
	 *  load the vertex indexes
	 */
	glGenBuffers(1, &ibuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ni * sizeof(GLuint), indices, GL_STATIC_DRAW);

	/*
	 *  Allocate the mesh structure and fill it in
	*/
	mesh = new Mesh();
	mesh->vbuffer = vbuffer;
	mesh->ibuffer = ibuffer;
	mesh->triangles = triangles;
	mesh->vbytes = nv * sizeof(GLfloat);

	delete[] vertices;
	delete[] normals;
	delete[] indices;

	return(mesh);
}

/*
 *  The loadProgram procedure reads the vertex and fragment programs
 *  compiles them, and load them to produce the complete GPU program.
 *  The parameters to this procedure and the file names for the vertex
 *  and fragment programs.
*/

GLuint loadProgram(char* vertex, char* fragment) {
	GLuint vs;
	GLuint fs;
	GLuint program;

	/*
	 *  compile and build the shader program
	 */
	vs = buildShader(GL_VERTEX_SHADER, vertex);
	fs = buildShader(GL_FRAGMENT_SHADER, fragment);
	program = buildProgram(vs, fs, 0);

	return(program);
}

/*
 *  The copyObject procedure makes a copy of an existing mesh.  This
 *  makes it easier to create multiple copies of an object.  The
 *  paraneter to this procedure is the mesh to be copied.
*/

Mesh* copyObject(Mesh* obj) {
	Mesh* result;

	result = new Mesh();
	*result = *obj;
	return(result);
}

Mesh* ground() {
	GLuint vao;
	GLuint vbuffer;
	GLuint ibuffer;
	GLint vPosition;
	Mesh* mesh;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat vertices[] = {
		-50.0f, -50.0f, -1.0f,
		 50.0f, -50.0f, -1.0f,
		 50.0f,  50.0f, -1.0f,
		-50.0f,  50.0f, -1.0f
	};

	GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ibuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	mesh = new Mesh();
	mesh->vbuffer = vbuffer;
	mesh->ibuffer = ibuffer;
	mesh->triangles =  2;
	mesh->vbytes = 0;

	return(mesh);
}

Mesh* cone(double radius, double height, int sides) {
    double* x;		// the x coordinates of the vertices
    double* y;		// the y coordinates of the vertices
    GLuint vao;
    double angle;
    double dangle;
    int i;
    GLfloat* vertices;	// vertices to be stored in the buffer
    GLuint* indices;	// triangle indices to be stored in the buffer
    int j;
    GLuint vbuffer;
    GLuint ibuffer;
    Mesh* mesh;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Compute the x and y coordinates of the vertices
    x = new double[sides];
    y = new double[sides];
    dangle = 6.28 / sides;
    angle = 0.0;
    for (i = 0; i < sides; i++) {
        x[i] = radius * cos(angle);
        y[i] = radius * sin(angle);
        angle += dangle;
    }

    vertices = new GLfloat[3 * (sides + 2)];
    j = 0;

    // Vertex at the tip of the cone
    vertices[j++] = 0.0;
    vertices[j++] = 0.0;
    vertices[j++] = height;

    // Vertices at the base of the cone
    for (i = 0; i < sides; i++) {
        vertices[j++] = x[i];
        vertices[j++] = y[i];
        vertices[j++] = 0.0;
    }
    vertices[j++] = 0.0;
    vertices[j++] = 0.0;
    vertices[j++] = 0.0;

    indices = new GLuint[3 * sides];
    j = 0;

    // Triangles connecting the tip to the base
    for (i = 0; i < sides; i++) {
        indices[j++] = 0;
        indices[j++] = i + 1;
        indices[j++] = i + 2;
    }
    indices[j-1] = 1; // wrap around to the first vertex at the base

    // Allocate the mesh structure and fill it in
    mesh = new Mesh();
    mesh->triangles = sides * 3;
    mesh->vbytes = 0;

    // Copy the vertices and indices into the appropriate buffers
    glGenBuffers(1, &vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * (sides + 2) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ibuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sides * sizeof(GLuint), indices, GL_STATIC_DRAW);

    mesh->vbuffer = vbuffer;
    mesh->ibuffer = ibuffer;

    return(mesh);
}



/*
 *  The buildModel procedure constructs the scene from the indivdual meshes.
*/
void buildModel() {
	Mesh* mesh;
	GLuint program;

	mesh = loadOBJ((char*)"../src/objects/drip_vase.obj");
	mesh->model = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, -0.7));
	mesh->model = glm::rotate(mesh->model, 1.57f, glm::vec3(1.0, 0.0, 0.0));
	mesh->model = glm::scale(mesh->model, glm::vec3(0.5, 0.5, 0.5));
	mesh->program = loadProgram((char*)"../src/shaders/vase.vs", (char*)"../src/shaders/vase.fs");
	Model.push_back(mesh);

	// Now load the Alien
	mesh = loadOBJ((char*)"../src/objects/Alien.obj");
	mesh->program = loadProgram((char*)"../src/shaders/alien.vs", (char*)"../src/shaders/alien.fs");
	mesh->model = glm::translate(glm::mat4(1.0), glm::vec3(-1.0, -1.0, -1.0));
	mesh->model = glm::rotate(mesh->model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	Model.push_back(mesh);

	// Make a copy of the Alien at a different location
	mesh = copyObject(mesh);
	mesh->model = glm::translate(glm::mat4(1.0), glm::vec3(1.0, 1.0, -1.0));
	mesh->model = glm::rotate(mesh->model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	Model.push_back(mesh);

	mesh = loadOBJ((char*)"../src/objects/monkey.obj");
	mesh->program = loadProgram((char*)"../src/shaders/monkey.vs", (char*)"../src/shaders/monkey.fs");
	mesh->model = glm::translate(glm::mat4(1.0), glm::vec3(0.7, 5.0, -0.1));
	Model.push_back(mesh);

	mesh = loadOBJ((char*)"../src/objects/bunny.obj");
	mesh->program = loadProgram((char*)"../src/shaders/bunny.vs", (char*)"../src/shaders/bunny.fs");
	mesh->model = glm::translate(glm::mat4(1.0), glm::vec3(-0.5, 1.0, -1.1));
	mesh->model = glm::rotate(mesh->model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mesh->model = glm::scale(mesh->model, glm::vec3(0.5, 0.5, 0.5));
	Model.push_back(mesh);

	mesh = ground();
	mesh->program = loadProgram((char*)"../src/shaders/ground.vs", (char*)"../src/shaders/ground.fs");
	mesh->model = glm::translate(glm::mat4(1.0), glm::vec3(1.0, -1.0, 0.0));
	Model.push_back(mesh);

	mesh = cone(0.5, 1.0, 105);
	mesh->program = loadProgram((char*)"../src/shaders/tree.vs", (char*)"../src/shaders/tree.fs");
	mesh->model = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 5.0, 0.6));
	Model.push_back(mesh);

	mesh = cone(0.5, 2.0, 105);
	mesh->program = loadProgram((char*)"../src/shaders/tree_trunk.vs", (char*)"../src/shaders/tree_trunk.fs");
	mesh->model = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 5.0, -0.9));
	Model.push_back(mesh);
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
	glm::mat4 modelViewPerspective;
	glm::mat3 normal;
	int modelLoc;
	int normalLoc;
	int i;
	Mesh* mesh;
	GLuint vPosition;
	GLuint vNormal;

	view = glm::lookAt(camera_position, camera_position + camera_front, camera_up);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Iterate through the model displaying each of the meshes

	for (i = 0; i < Model.size(); i++) {
		mesh = Model[i];
		glUseProgram(mesh->program);

		// Set up the position and normal attributes

		glBindBuffer(GL_ARRAY_BUFFER, mesh->vbuffer);
		vPosition = glGetAttribLocation(mesh->program, "vPosition");
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vPosition);
		vNormal = glGetAttribLocation(mesh->program, "vNormal");
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (void*)(mesh->vbytes));
		glEnableVertexAttribArray(vNormal);

		// Set up the transformation matrices for the vertices and normal vectors

		modelLoc = glGetUniformLocation(mesh->program, "model");
		modelViewPerspective = projection * view * mesh->model;
		glUniformMatrix4fv(modelLoc, 1, 0, glm::value_ptr(modelViewPerspective));
		normalLoc = glGetUniformLocation(mesh->program, "normalMat");
		normal = glm::transpose(glm::inverse(glm::mat3(view*mesh->model)));
		glUniformMatrix3fv(normalLoc, 1, 0, glm::value_ptr(normal));

		// Finally draw the mesh

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibuffer);
		glDrawElements(GL_TRIANGLES, 3 * mesh->triangles, GL_UNSIGNED_INT, NULL);
	}
}

/*
 *  Called each time a key is pressed on
 *  the keyboard.
 */


// Add a flag to keep track of whether the key is being held down
int keyA_held = 0, keyD_held = 0, keyW_held = 0, keyS_held = 0;

// Change the key callback function to set the flags when the keys are pressed or released
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_A)
    {
        if (action == GLFW_PRESS)
            keyA_held = 1;
        if (action == GLFW_RELEASE)
            keyA_held = 0;
    }
    if (key == GLFW_KEY_D)
    {
        if (action == GLFW_PRESS)
            keyD_held = 1;
        if (action == GLFW_RELEASE)
            keyD_held = 0;
    }
    if (key == GLFW_KEY_W)
    {
        if (action == GLFW_PRESS)
            keyW_held = 1;
        if (action == GLFW_RELEASE)
            keyW_held = 0;
    }
    if (key == GLFW_KEY_S)
    {
        if (action == GLFW_PRESS)
            keyS_held = 1;
        if (action == GLFW_RELEASE)
            keyS_held = 0;
    }
}

// Change the update_variables function to move the camera based on the key inputs
void update_variables() {
    if (keyA_held) {
        // Rotate the camera front vector around the camera up vector to the left
        camera_front = glm::rotate(camera_front, camera_speed/2, camera_up);
    }
    if (keyD_held) {
        // Rotate the camera front vector around the camera up vector to the right
        camera_front = glm::rotate(camera_front, -camera_speed/2, camera_up);
    }
    if (keyW_held) {
        // Move the camera forward along the camera front vector
        camera_position += camera_speed * camera_front;
    }
    if (keyS_held) {
        // Move the camera backward along the camera front vector
        camera_position -= camera_speed * camera_front;
    }
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

	window = glfwCreateWindow(768, 768, "Assignment 01", NULL, NULL);

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
	
	buildModel();

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.603, 0.882, 0.956, 0.8);
	glViewport(0, 0, 768, 768);

	projection = glm::perspective(0.7f, 1.0f, 1.0f, 800.0f);

	glfwSwapInterval(1);

	// GLFW main loop, display model, swapbuffer and check for input

	while (!glfwWindowShouldClose(window)) {
		std::cout << "camera_front = (" << camera_front.x << ", " << camera_front.y << ", " << camera_front.z << ")" << std::endl;
		display();
		update_variables();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

}
