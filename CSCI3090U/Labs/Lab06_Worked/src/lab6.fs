/*
 *  Simple fragment shader for lab 6
 *  This fragment shader uses a texture for our sprite
 */

#version 330 core

uniform sampler2D tex;

void main(void) {

	gl_FragColor = texture(tex, gl_PointCoord);

}