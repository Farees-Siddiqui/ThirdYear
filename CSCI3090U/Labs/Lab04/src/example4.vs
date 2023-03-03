#version 330 core 
in vec4 vPosition; 
in vec3 vNormal; 
out vec3 normal; 
uniform mat4 model; 
uniform mat4 viewPerspective; 
uniform mat3 normalMat; 
 
void main() {  
	gl_Position = viewPerspective * model * vPosition; 
	normal = normalMat * vNormal;  
} 