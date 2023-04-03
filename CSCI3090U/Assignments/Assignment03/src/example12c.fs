/*
 *  Simple fragment sharder for Part 3: Diffuse reflection part2
 */

#version 330 core

in vec3 normal;
in vec3 position;
in vec2 tc;
uniform samplerCube tex;
uniform samplerCube tex2;
uniform vec4 colour;
uniform vec3 Eye;
uniform vec3 light;
uniform vec4 material;
float sum_dot = 0.0;
vec4 sum_weight = vec4(0.0, 0.0, 0.0, 0.0);

int num = 1235;
int a = 141;
int c = 28411;
int m = 134456;

float rand() {
	float f;
	num = (a*num+c) % m;
	f = (num+0.0)/m;
	return((f-0.5)*2.0);
}

void main() {
	vec3 tc;
	vec3 temp;
	int i = 0;
	vec4 final;
    tc = reflect(position - Eye, normal);

	for(int i = 0; i < 500; i++){
        vec3 random = vec3(rand(), rand(), rand());
        if (dot(random, normal) > 0) {
            sum_weight += texture(tex, (random + tc)/2) * dot(random, normal);
            sum_dot += dot(random, normal);
        }
    }

    gl_FragColor = sum_weight / sum_dot; 

}