/*
 *  Simple fragment shader for the first
 *  texture example.  Just look up the texture
 *  value at the current text coordinate
 */

#version 330 core

in vec2 texCoord;
uniform sampler2D tex;

void main(void) {

	gl_FragColor = texture(tex, texCoord);

}