#pragma once

#include "Singleton.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include <GL/glew.h>
#include <memory>
#include <map>
#include <string>

class ResourceManager: public Singleton<ResourceManager> {
public:
    void startUp();
    void shutDown();

    ShaderProgram* createShaderProgram(const std::string& name,
                                       const Shader& vertexShader,
                                       const Shader& fragmentShader);
    Texture* createTexture(const std::string& name,
                           const std::string& path,
                           GLuint width,
                           GLuint height,
                           GLint channels = 3,
                           GLuint format = GL_RGB);

    // getters
    ShaderProgram* shaderProgram(const std::string& name) {
        return shaderPrograms_[name].get();
    }

    Texture* texture(const std::string& name) {
        return textures_[name].get();
    }

private:
    std::map<std::string, std::unique_ptr<ShaderProgram>> shaderPrograms_;
    std::map<std::string, std::unique_ptr<Texture>> textures_;
};
