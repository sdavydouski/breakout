#version 330 core

in vec2 uv;
out vec4 finalColor;

uniform sampler2D sprite;
uniform vec3 color;

void main() {
    finalColor = texture(sprite, uv) * vec4(color, 1.0f);
}
