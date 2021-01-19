#version 150

const int number_of_targets = 100;

uniform float time;
uniform vec2 resolution;
uniform vec2 targets[number_of_targets];

out vec4 outputColor;

void main() {

  vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);
  vec3 color = vec3(0.0);
  for(int i = 0; i < number_of_targets; i++){

    vec2 t = vec2(targets[i].x, -targets[i].y) / min(resolution.x, resolution.y) * 2.0;
    t.xy += vec2(-resolution.x, resolution.y) / min(resolution.x, resolution.y);

    float v = 0.02 / length(p - t);
    vec3 c = vec3(smoothstep(0.01, 1.0, v));
    color += c;
  }

  outputColor = vec4(color, 1.0);
}