#include "Shader.h"
#include "ShaderType.h"
#include <GL/glew.h>
#include <iostream>
#include <string>

Shader::Shader(ShaderType type, const std::string& source) {
    std::cout << "Shader constructor" << std::endl;

    this->id = glCreateShader(type);

    const GLchar* shaderSource = source.c_str();
    glShaderSource(this->id, 1, &shaderSource, nullptr);
    glCompileShader(this->id);

    this->checkCompilationStatus();
}

Shader::~Shader() {
    std::cout << "Shader destructor" << std::endl;
    glDeleteShader(this->id);
}

GLuint Shader::getId() const {
    return this->id;
}

void Shader::checkCompilationStatus() {
    GLint success;
    glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);

    if (!success) {
        const int MAX_BUFFER_SIZE = 256;
        GLchar infoLog[MAX_BUFFER_SIZE];

        glGetShaderInfoLog(this->id, MAX_BUFFER_SIZE, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
    }
}
