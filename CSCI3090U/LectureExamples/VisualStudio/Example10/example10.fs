/*
 *  Simple fragment shader for the first
 *  texture example.  Just look up the texture
 *  value at the current text coordinate
 */

#version 330 core

in vec2 texCoord;
uniform sampler2D tex;

in vec3 normal;
in vec4 position;
uniform vec3 eye;

void main(void) {
	vec3 N;
	// vec3 Lposition = vec3(500.0, 500.0, 500.0);
	vec3 Lposition = vec3(texCoord.x, texCoord.y, 0.0);
	vec4 colour = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 Lcolour = vec4(1.0, 1.0, 1.0, 1.0);
	vec3 H;
	float diffuse;
	float specular;
	float n = 100.0;
	vec3 L;

	N = normalize(normal);
	L = normalize(Lposition - position.xyz);
	H = normalize(L + vec3(0.0, 0.0, 1.0));
	diffuse = dot(N,L);
	if(diffuse < 0.0) {
		diffuse = 0.0;
		specular = 0.0;
	} else {
		specular = pow(max(0.0, dot(N,H)),n);
	}

	gl_FragColor = min(0.3*texture(tex, texCoord) + texture(tex,texCoord)*diffuse*Lcolour + Lcolour*specular, vec4(1.0));
	gl_FragColor.a = colour.a;

}