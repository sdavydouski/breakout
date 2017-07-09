#version 330 core

in vec2 uv;
out vec4 finalColor;

uniform sampler2D text;
uniform vec3 textColor;

void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, uv).r);
    finalColor = vec4(textColor, 1.0) * sampled;
}
