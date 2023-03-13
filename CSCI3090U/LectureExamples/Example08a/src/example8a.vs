#version 330 core
/*
 *  Simple vertex shader for example six
 */

in vec4 vPosition;
in vec3 vNormal;
uniform mat4 modelView;
uniform mat4 projection;
uniform mat3 normalMat;
out vec3 normal;

void main() {

	gl_Position = projection * modelView * vPosition;
	normal = normalMat* vNormal;
}