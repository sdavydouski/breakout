#pragma once

#include "ShaderProgram.h"
#include "Shader.h"
#include "Texture.h"
#include <GL/glew.h>
#include <memory>
#include <map>
#include <string>

class ResourceManager {
public:
    static ResourceManager& Instance();
    // Copy constructor
    ResourceManager(const ResourceManager&) = delete;
    // Move constructor
    ResourceManager(const ResourceManager&&) = delete;
    // Copy assignment
    ResourceManager& operator =(const ResourceManager&) = delete;
    // Move assignment
    ResourceManager& operator =(const ResourceManager&&) = delete;

    void startUp();
    void shutDown();

    std::shared_ptr<ShaderProgram> getShader(const std::string& name);
    std::shared_ptr<Texture> getTexture(const std::string& name);

    std::shared_ptr<ShaderProgram> createShader(const std::string& name,
                                                const Shader& vertexShader,
                                                const Shader& fragmentShader);
    std::shared_ptr<Texture> createTexture(const std::string& name,
                                           GLuint width,
                                           GLuint height,
                                           unsigned char* image,
                                           GLuint format = GL_RGB);
private:
    std::map<std::string, std::shared_ptr<ShaderProgram>> shaders;
    std::map<std::string, std::shared_ptr<Texture>> textures;

    ResourceManager();
    ~ResourceManager();
};
