#pragma once

#include "ShaderType.h"
#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader(ShaderType type, const std::string& path);
    ~Shader();

    // getters
    GLuint id() const { return id_; };

private:
    GLuint id_;

    void checkCompilationStatus() const;
};
