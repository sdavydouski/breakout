#version 330 core

in vec2 uv;
out vec4 finalColor;

uniform sampler2D scene;
uniform vec2 offsets[9];
uniform int edgeKernel[9];
uniform float blurKernel[9];

uniform bool chaos;
uniform bool confuse;
uniform bool shake;

void main() {
    finalColor = vec4(0.0f);
    vec3 textureSample[9];

    if (chaos || shake) {
        for(int i = 0; i < 9; i++) {
            if (confuse) {
                textureSample[i] = vec3(1.0f - texture(scene, uv.st + offsets[i]));
            } else {
                textureSample[i] = vec3(texture(scene, uv.st + offsets[i]));
            }
        }
    }

    // process effects
    if (chaos) {
        for(int i = 0; i < 9; i++) {
            finalColor += vec4(textureSample[i] * edgeKernel[i], 0.0f);
        }
        finalColor.a = 1.0f;
    }

    if (shake) {
        for(int i = 0; i < 9; i++) {
            finalColor += vec4(textureSample[i] * blurKernel[i], 0.0f);
        }
        finalColor.a = 1.0f;
    }

    if (confuse && !chaos && !shake) {
        finalColor = vec4(1.0f - texture(scene, uv).rgb, 1.0);
    }

    // no effects
    if (!confuse && !chaos && !shake) {
        finalColor =  texture(scene, uv);
    }
}
