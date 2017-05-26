#include "Shader.h"
#include "ShaderType.h"
#include "FileManager.h"
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

Shader::Shader(ShaderType type, const std::string& path) {
    std::cout << "Shader constructor" << std::endl;

    std::string source = FileManager::Instance().readAsText(path);

    id_ = glCreateShader(type);

    const GLchar* shaderSource = source.c_str();
    glShaderSource(id_, 1, &shaderSource, nullptr);
    glCompileShader(id_);

    this->checkCompilationStatus();
}

Shader::~Shader() {
    std::cout << "Shader destructor" << std::endl;
    glDeleteShader(id_);
}

void Shader::checkCompilationStatus() {
    GLint success;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLint LOG_LENGTH;
        glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &LOG_LENGTH);

        std::vector<GLchar> errorLog((GLuint) LOG_LENGTH);

        glGetShaderInfoLog(id_, LOG_LENGTH, nullptr, &errorLog[0]);
        std::cerr << &errorLog[0] << std::endl;
        throw std::runtime_error("Shader compilation failed");
    }
}
