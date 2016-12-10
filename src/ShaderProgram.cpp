#include "ShaderProgram.h"
#include <GL/glew.h>
#include <iostream>

ShaderProgram::ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader) {
    std::cout << "ShaderProgram constructor" << std::endl;

    this->id = glCreateProgram();

    glAttachShader(this->id, vertexShader.getId());
    glAttachShader(this->id, fragmentShader.getId());

    glLinkProgram(this->id);

    this->checkLinkageStatus();
}

ShaderProgram::~ShaderProgram() {
    std::cout << "ShaderProgram destructor" << std::endl;
    this->end();
    glDeleteProgram(this->id);
}

void ShaderProgram::use() {
    glUseProgram(this->id);
}

void ShaderProgram::end() {
    glUseProgram(0);
}

void ShaderProgram::checkLinkageStatus() {
    GLint success;
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);

    if (!success) {
        const int MAX_BUFFER_SIZE = 256;
        GLchar infoLog[MAX_BUFFER_SIZE];

        glGetProgramInfoLog(this->id, MAX_BUFFER_SIZE, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
    }
}

GLint ShaderProgram::getUniformLocation(const std::string &name) {
    GLint location = glGetUniformLocation(this->id, name.c_str());

    if (location == -1) {
        std::cerr << "Unable to find uniform " << name
                  << ". It is either not declared or not used." << std::endl;
    }

    return location;
}
