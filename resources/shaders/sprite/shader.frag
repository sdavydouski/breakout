#version 330 core

in vec2 uv;
out vec4 finalColor;

uniform sampler2D image;
uniform vec3 color;

void main() {
    finalColor = vec4(color, 1.0f) * texture(image, uv);
}
