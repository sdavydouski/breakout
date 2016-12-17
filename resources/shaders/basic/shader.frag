#version 330 core

in vec2 uv;

out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    color = mix(texture(texture1, uv), texture(texture2, uv), 0.2);
}
