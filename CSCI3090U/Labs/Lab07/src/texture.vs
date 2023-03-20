/*
 *  Simple vertex shader for the first
 *  texture example.
 */

#version 330 core

in vec4 vPosition;
in vec2 vTexture;

uniform mat4 modelView;

out vec2 texCoord;

void main(void) {
	float angle = 1.0;
	mat2 rotationMatrix;
	rotationMatrix[0][0] = cos(angle);
	rotationMatrix[0][1] = -sin(angle);
	rotationMatrix[1][0] = sin(angle);
	rotationMatrix[1][1] = cos(angle);

	gl_Position = modelView * vPosition;
	// texCoord = vTexture*rotationMatrix;
	texCoord = vTexture;
}