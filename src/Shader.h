#pragma once

#include "ShaderType.h"
#include <GL/glew.h>

class Shader {
public:
    Shader(ShaderType type, const GLchar* source);
    ~Shader();

    GLuint getId() const;
private:
    GLuint id;

    void checkCompilationStatus();
};
