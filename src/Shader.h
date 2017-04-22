#pragma once

#include "ShaderType.h"
#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader(ShaderType type, const std::string& path);
    ~Shader();

    GLuint getId() const;
private:
    GLuint id;

    void checkCompilationStatus();
};
