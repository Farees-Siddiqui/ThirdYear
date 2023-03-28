#version 330 core
/*
 *  Simple vertex shader for example one
 */

in vec4 vPosition;

void main() {

	gl_Position = vPosition;

}