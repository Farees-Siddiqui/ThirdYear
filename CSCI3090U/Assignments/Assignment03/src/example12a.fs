/*
 *  Simple fragment sharder for Part 1: Reflection and Refraction
 */

#version 330 core

in vec3 normal;
in vec3 position;
in vec2 tc;
uniform samplerCube tex;
uniform vec4 colour;
uniform vec3 Eye;
uniform vec3 light;
uniform vec4 material;

void main() {
	vec3 tc;
	tc = reflect(position - Eye, normal);

	vec3 refraction = refract(normalize(position - Eye), normalize(normal), 1.5); 
	
	float theta = dot(normalize(normal + light), normalize(Eye)); 
    float Ro = pow((-0.5/2.5),3);
    float R = Ro + (1-Ro)*pow((1-cos(theta)),5);

	gl_FragColor = texture(tex, tc) * R + texture(tex, refraction) * (1 - R);
	// gl_FragColor = texture(tex,tc);

}