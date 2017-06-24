#version 330 core

in  vec2  uv;
out vec4  finalColor;

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
    // textureSample from texture offsets if using convolution matrix
    if(chaos || shake) {
        for(int i = 0; i < 9; i++) {
            textureSample[i] = vec3(texture(scene, uv.st + offsets[i]));
        }
    }
    // process effects
    if(chaos) {
        for(int i = 0; i < 9; i++) {
            finalColor += vec4(textureSample[i] * edgeKernel[i], 0.0f);
        }
        finalColor.a = 1.0f;
    }
    else if(confuse) {
        finalColor = vec4(1.0 - texture(scene, uv).rgb, 1.0);
    }
    else if(shake) {
        for(int i = 0; i < 9; i++) {
            finalColor += vec4(textureSample[i] * blurKernel[i], 0.0f);
        }
        finalColor.a = 1.0f;
    }
    else {
        finalColor =  texture(scene, uv);
    }
}
