#pragma once

#include "Shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class ShaderProgram {
public:
    ~ShaderProgram();

    void use();
    void end();

    void setUniform(const std::string& name, GLboolean value);
    void setUniform(const std::string& name, GLint value);
    void setUniform(const std::string& name, GLuint value);
    void setUniform(const std::string& name, GLfloat value);
    void setUniform(const std::string& name, glm::vec2 value);
    void setUniform(const std::string& name, glm::vec3 value);
    void setUniform(const std::string& name, glm::vec4 value);
    void setUniform(const std::string& name, glm::mat2 value);
    void setUniform(const std::string& name, glm::mat3 value);
    void setUniform(const std::string& name, glm::mat4 value);
    void setUniform(const std::string& name, GLsizei count, GLboolean* values);
    void setUniform(const std::string& name, GLsizei count, GLint* values);
    void setUniform(const std::string& name, GLsizei count, GLuint* values);
    void setUniform(const std::string& name, GLsizei count, GLfloat* values);
    void setUniform(const std::string& name, GLsizei count, glm::vec2* values);
    void setUniform(const std::string& name, GLsizei count, glm::vec3* values);
    void setUniform(const std::string& name, GLsizei count, glm::vec4* values);
    void setUniform(const std::string& name, GLsizei count, glm::mat2* values);
    void setUniform(const std::string& name, GLsizei count, glm::mat3* values);
    void setUniform(const std::string& name, GLsizei count, glm::mat4* values);
private:
    GLuint id_;

    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
    void destroy();

    void checkLinkageStatus();
    GLint getUniformLocation(const std::string& name);

friend class ResourceManager;
};
