/*
 *  Simple fragment shader for lab 6
 *  This shader uses a circle for our sprite, the colour
 *  is blended based on the distance from the center of the sprite
 */

#version 330 core

uniform sampler2D tex;

void main(void) {
	const vec4 colour1 = vec4(0.6, 0.0, 0.0, 1.0);
	const vec4 colour2 = vec4(0.9, 0.7, 1.0, 0.0);

	vec2 temp = gl_PointCoord - vec2(0.5);
	float f = dot(temp,temp);

	if(f > 0.25)
		discard;

	gl_FragColor = mix(colour1, colour2, smoothstep(0.1, 0.25, f));
}