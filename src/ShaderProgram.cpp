#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) {
    std::cout << "ShaderProgram constructor" << std::endl;

    this->id = glCreateProgram();

    glAttachShader(this->id, vertexShader.getId());
    glAttachShader(this->id, fragmentShader.getId());

    glLinkProgram(this->id);

    this->checkLinkageStatus();
}

ShaderProgram::~ShaderProgram() {
    // Empty destructor
    std::cout << "ShaderProgram destructor" << std::endl;
}

void ShaderProgram::destroy() {
    std::cout << "ShaderProgram destroy()" << std::endl;
    this->end();
    glDeleteProgram(this->id);
}

void ShaderProgram::use() {
    glUseProgram(this->id);
}

void ShaderProgram::end() {
    glUseProgram(0);
}

void ShaderProgram::setUniform(const std::string& name, GLboolean value) {
    glUniform1i(this->getUniformLocation(name), value);
}

void ShaderProgram::setUniform(const std::string& name, GLint value) {
    glUniform1i(this->getUniformLocation(name), value);
}

void ShaderProgram::setUniform(const std::string& name, GLuint value) {
    glUniform1i(this->getUniformLocation(name), value);
}

void ShaderProgram::setUniform(const std::string& name, GLfloat value) {
    glUniform1f(this->getUniformLocation(name), value);
}

void ShaderProgram::setUniform(const std::string& name, glm::vec2 value) {
    glUniform2f(this->getUniformLocation(name), value.x, value.y);
}

void ShaderProgram::setUniform(const std::string& name, glm::vec3 value) {
    glUniform3f(this->getUniformLocation(name), value.x, value.y, value.z);
}

void ShaderProgram::setUniform(const std::string& name, glm::vec4 value) {
    glUniform4f(this->getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void ShaderProgram::setUniform(const std::string& name, glm::mat2 value) {
    glUniformMatrix2fv(this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string& name, glm::mat3 value) {
    glUniformMatrix3fv(this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string& name, glm::mat4 value) {
    glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::checkLinkageStatus() {
    GLint success;
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);

    if (!success) {
        GLint LOG_LENGTH;
        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &LOG_LENGTH);

        std::vector<GLchar> errorLog((GLuint) LOG_LENGTH);

        glGetProgramInfoLog(this->id, LOG_LENGTH, nullptr, &errorLog[0]);
        std::cerr << &errorLog[0] << std::endl;
        throw std::runtime_error("Shader program linkage failed");
    }
}

GLint ShaderProgram::getUniformLocation(const std::string& name) {
    GLint location = glGetUniformLocation(this->id, name.c_str());

    if (location == -1) {
        std::cerr << "Unable to find uniform " << name
                  << ". It is either not declared or not used." << std::endl;
    }

    return location;
}
