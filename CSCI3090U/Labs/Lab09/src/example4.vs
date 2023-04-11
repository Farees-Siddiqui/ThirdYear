#version 330 core

uniform mat4 modelView;
uniform mat4 projection;

in vec4 vPosition;

out vec3 texCoord;

void main() {
	gl_Position = projection * modelView * vPosition;
	texCoord = vPosition.xyz;
}
