#include "Shader.h"
#include "ShaderType.h"
#include "../utils/FileManager.h"
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vector>

Shader::Shader(ShaderType type, const std::string& path) {
    auto source = FileManager::readAsText(path);

    id_ = glCreateShader(type);

    auto shaderSource = source.c_str();
    glShaderSource(id_, 1, &shaderSource, nullptr);
    glCompileShader(id_);

    this->checkCompilationStatus();
}

Shader::~Shader() {
    glDeleteShader(id_);
}

void Shader::checkCompilationStatus() const {
    GLint success;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLint LOG_LENGTH;
        glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &LOG_LENGTH);

        std::vector<GLchar> errorLog(static_cast<GLuint>(LOG_LENGTH));

        glGetShaderInfoLog(id_, LOG_LENGTH, nullptr, &errorLog[0]);
        std::cerr << "Shader compilation failed" << std::endl << &errorLog[0] << std::endl;
    }
}
