/*
 *  Simple vertex shader for the first
 *  texture example.
 */

#version 330 core

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexcoord;

uniform mat4 modelView;
uniform mat4 projection;
uniform mat3 normalMat;

out vec2 texCoord;
out vec3 normal;

void main(void) {

	gl_Position = projection * modelView * vPosition;
	normal = normalMat * vNormal;
	texCoord = vTexcoord*4;

}