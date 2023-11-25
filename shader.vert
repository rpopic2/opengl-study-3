#version 330 core


layout (location = 0) in vec3 positions;
layout (location = 1) in vec3 _colors;

out vec3 colors;

uniform float scale;

void main() {
    gl_Position = vec4(positions * scale, 1.0);
    colors = _colors;
}

