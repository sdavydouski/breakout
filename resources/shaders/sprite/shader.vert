#version 330 core

// <vec2 position, vec2 texCoords>
layout (location = 0) in vec4 vertex;

out vec2 uv;

uniform mat4 model;
uniform mat4 projection;

void main() {
    uv = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 0.0f, 1.0f);
}
