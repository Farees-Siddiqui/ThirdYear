#version 330 core
/*
 *  Simple fragment sharder for example one
 */


uniform vec2 u_resolution;

void main() {

  vec2 st = gl_FragCoord.xy/u_resolution.xy;

  vec3 color1 = vec3(1.9,0.55,0);
  vec3 color2 = vec3(0.226,0.000,0.615);

  float mixValue = distance(st,vec2(0,1));
  vec3 color = mix(color1,color2,mixValue);

  gl_FragColor = vec4(color,mixValue);
}