#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) {
    id_ = glCreateProgram();

    glAttachShader(id_, vertexShader.id());
    glAttachShader(id_, fragmentShader.id());

    glLinkProgram(id_);

    this->checkLinkageStatus();
}

ShaderProgram::~ShaderProgram() {
    // Empty destructor
}

void ShaderProgram::destroy() {
    this->end();
    glDeleteProgram(id_);
}

void ShaderProgram::use() {
    glUseProgram(id_);
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

void ShaderProgram::setUniform(const std::string& name, const glm::vec2& value) {
    glUniform2f(this->getUniformLocation(name), value.x, value.y);
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec3& value) {
    glUniform3f(this->getUniformLocation(name), value.x, value.y, value.z);
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec4& value) {
    glUniform4f(this->getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat2& value) {
    glUniformMatrix2fv(this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat3& value) {
    glUniformMatrix3fv(this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& value) {
    glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string& name, GLsizei count, GLboolean* values) {
    glUniform1iv(this->getUniformLocation(name), count, (GLint*) values);
}

void ShaderProgram::setUniform(const std::string& name, GLsizei count, GLint* values) {
    glUniform1iv(this->getUniformLocation(name), count, values);
}

void ShaderProgram::setUniform(const std::string& name, GLsizei count, GLuint* values) {
    glUniform1iv(this->getUniformLocation(name), count, (GLint*) values);
}

void ShaderProgram::setUniform(const std::string& name, GLsizei count, GLfloat* values) {
    glUniform1fv(this->getUniformLocation(name), count, values);
}

void ShaderProgram::setUniform(const std::string& name, GLsizei count, const glm::vec2* values) {
    glUniform2fv(this->getUniformLocation(name), count, &values[0].x);
}

void ShaderProgram::setUniform(const std::string& name, GLsizei count, const glm::vec3* values) {
    glUniform3fv(this->getUniformLocation(name), count, &values[0].x);
}

void ShaderProgram::setUniform(const std::string& name, GLsizei count, const glm::vec4* values) {
    glUniform4fv(this->getUniformLocation(name), count, &values[0].x);
}

void ShaderProgram::setUniform(const std::string& name, GLsizei count, const glm::mat2* values) {
    glUniformMatrix2fv(this->getUniformLocation(name), count, GL_FALSE, &values[0][0].x);
}

void ShaderProgram::setUniform(const std::string& name, GLsizei count, const glm::mat3* values) {
    glUniformMatrix3fv(this->getUniformLocation(name), count, GL_FALSE, &values[0][0].x);
}

void ShaderProgram::setUniform(const std::string& name, GLsizei count, const glm::mat4* values) {
    glUniformMatrix4fv(this->getUniformLocation(name), count, GL_FALSE, &values[0][0].x);
}

void ShaderProgram::checkLinkageStatus() const {
    GLint success;
    glGetProgramiv(id_, GL_LINK_STATUS, &success);

    if (!success) {
        GLint LOG_LENGTH;
        glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &LOG_LENGTH);

        std::vector<GLchar> errorLog((GLuint) LOG_LENGTH);

        glGetProgramInfoLog(id_, LOG_LENGTH, nullptr, &errorLog[0]);
        std::cerr << "Shader program linkage failed" << std::endl << &errorLog[0] << std::endl;
    }
}

GLint ShaderProgram::getUniformLocation(const std::string& name) const {
    auto location = glGetUniformLocation(id_, name.c_str());

    if (location == -1) {
        std::cerr << "Unable to find uniform " << name
                  << ". It is either not declared or not used." << std::endl;
    }

    return location;
}
