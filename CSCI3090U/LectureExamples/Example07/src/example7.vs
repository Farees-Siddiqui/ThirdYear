#version 330 core
/*
 *  Simple vertex shader for example five
 */

in vec4 vPosition;
uniform mat4 model;
uniform mat4 viewPerspective;

void main() {

	gl_Position = viewPerspective * model * vPosition;
	
}