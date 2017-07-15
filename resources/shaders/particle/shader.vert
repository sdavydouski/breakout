#version 330 core

// <vec2 position, vec2 texCoords>
layout (location = 0) in vec4 vertex;

out vec2 uv;

uniform mat4 projection;
uniform vec2 offset;
uniform float scale;

void main() {
    uv = vertex.zw;
    gl_Position = projection * vec4(vertex.xy * scale + offset, 0.0f, 1.0f);
}
