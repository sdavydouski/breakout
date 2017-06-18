#version 330 core

in vec2 uv;
out vec4 finalColor;

uniform sampler2D sprite;
uniform vec4 particleColor;

void main() {
    finalColor = texture(sprite, uv) * particleColor;
}
