#version 330 core
/*
 *  Simple vertex shader for example two
 */

in vec4 vPosition;
uniform mat4 model;

void main() {

	gl_Position = model * vPosition;

}