#version 330 core

in vec3 colors;

out vec4 frag_color;

void main() {
    frag_color = vec4(colors, 1.0);
}

