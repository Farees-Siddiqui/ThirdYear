#version 330 core
/*
 *  Simple vertex shader for example three
 */

in vec4 vPosition;
in vec3 vNormal;
uniform mat4 model;
out vec3 normal;

void main() {

	gl_Position = model * vPosition;
	normal = (model * vec4(vNormal,1.0)).xyz;

}