#pragma once

#include "Singleton.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Texture.h"
#include <GL/glew.h>
#include <memory>
#include <map>
#include <string>

class ResourceManager: public Singleton<ResourceManager> {
public:
    void startUp();
    void shutDown();

    std::shared_ptr<ShaderProgram> createShaderProgram(const std::string& name,
                                                       const Shader& vertexShader,
                                                       const Shader& fragmentShader);
    std::shared_ptr<Texture> createTexture(const std::string& name,
                                           const std::string& path,
                                           GLuint width,
                                           GLuint height,
                                           GLint channels = 3,
                                           GLuint format = GL_RGB);

    // getters
    const std::shared_ptr<ShaderProgram> shaderProgram(const std::string& name) {
        return shaderPrograms_[name];
    }

    const std::shared_ptr<Texture> texture(const std::string& name) {
        return textures_[name];
    }

private:
    std::map<std::string, std::shared_ptr<ShaderProgram>> shaderPrograms_;
    std::map<std::string, std::shared_ptr<Texture>> textures_;

    ResourceManager();
    ~ResourceManager();

friend Singleton;
};
