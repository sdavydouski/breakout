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
private:
    GLuint id_;

    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
    void destroy();

    void checkLinkageStatus();
    GLint getUniformLocation(const std::string& name);

friend class ResourceManager;
};
