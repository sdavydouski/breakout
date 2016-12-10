#pragma once

#include "Shader.h"
#include <GL/glew.h>
#include <string>

class ShaderProgram {
public:
    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
    ~ShaderProgram();

    void use();
    void end();
private:
    GLuint id;

    void checkLinkageStatus();
    GLint getUniformLocation(const std::string& name);
};
