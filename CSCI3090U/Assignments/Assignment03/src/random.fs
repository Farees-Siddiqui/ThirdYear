/*
 *  Simple fragment sharder for Lab 2
 */

#version 330 core

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
	
	num = int((normal.x*normal.y + normal.x*normal.z) * 123456);
	num = num % m;

}

void main() {
	vec3 tc;
	vec3 temp;
	int i = 0;
	vec4 final;
	num = int((normal.x*normal.y + normal.x*normal.z) * 123456);
	num = num % m;
	temp.x = rand();
	temp.y = rand();
	temp.z = rand();
	while (i < 500) {
		if ((dot(temp.x, normal.x) > 0) && (dot(temp.y, normal.y) > 0) && (dot(temp.z,normal.z) > 0)) {

			total += dot(normalize(temp), normalize(normal));
			final += texture(tex2, normalize(normal) * dot(normalize(temp),

			normalize(normal)));
			i++;
		}
		temp.x = rand();
		temp.y = rand();
		temp.z = rand();
	}
	final = final / total;
	tc = reflect(position - Eye, normal);
	gl_FragColor = final;
}