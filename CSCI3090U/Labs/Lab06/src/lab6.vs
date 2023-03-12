/*
 *  Simple vertex shader for Lab 6
 */

#version 330 core

in vec4 vPosition;

uniform mat4 modelView;
uniform mat4 projection;

void main(void) {

	vec4 pos = projection * modelView * vPosition;
	gl_PointSize = (1.0 - pos.z/pos.w) * 64.0;
	gl_Position = pos;
}