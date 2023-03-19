#version 420 core
/*
 *  Simple fragment sharder for laboratory two
 */

in vec3 normal;
in vec4 position;
uniform vec3 eye;
out vec4 FragColor;

layout(std140, binding=1) uniform Light {
	vec4 Lposition;
	vec4 Lcolour;
	vec4 spotDirection;
	float spotCutoff;
	float spotExp;
	bool spotlight;
};

layout (std140, binding=2) uniform Material {
	vec4 Mcolour;
	float n;
};

void main() {
	vec3 N;
	float spotCos;
	float atten;
	vec3 H;
	float diffuse;
	float specular;
	vec3 L;
	vec3 e;

	N = normalize(normal);
	L = normalize(vec3(Lposition) - position.xyz);
	e = normalize(eye - position.xyz);
	H = normalize(L + e);
	spotCos = dot(L, vec3(normalize(spotDirection)));
	if (spotlight) {
		if(spotCos < spotCutoff) {
			atten = 0;
		} else {
			atten = pow(spotCos,spotExp);
		}
	} else {
		atten = 1.0;
		L = vec3(1.0, 1.0, 0.0);
		L = normalize(L);
		H = normalize(L + vec3(0.0, 0.0, 1.0));
	}
	diffuse = dot(N,L) * atten;
	if(diffuse < 0.0) {
		diffuse = 0.0;
		specular = 0.0;
	} else {
		specular = pow(max(0.0, dot(N,H)),n) * atten;
	}

	FragColor = min(0.3*Mcolour + diffuse*Mcolour*Lcolour + Lcolour*specular, vec4(1.0));
	FragColor.a = Mcolour.a;
}