#include "ResourceManager.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Texture.h"
#include <memory>
#include <string>
#include <iostream>

ResourceManager::ResourceManager() {
    // Empty constructor
    std::cout << "ResourceManager constructor" << std::endl;
}

ResourceManager::~ResourceManager() {
    // Empty destructor
    std::cout << "ResourceManager destructor" << std::endl;
}

ResourceManager &ResourceManager::Instance() {
    static ResourceManager instance;
    return instance;
}

void ResourceManager::startUp() {
    // For consistency
}

void ResourceManager::shutDown() {
    for (const auto& shader : this->shaders) {
        shader.second->destroy();
    }
    for (const auto& texture : this->textures) {
        texture.second->destroy();
    }
}

std::shared_ptr<ShaderProgram> ResourceManager::getShader(const std::string &name) {
    return this->shaders[name];
}

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string &name) {
    return this->textures[name];
}

std::shared_ptr<ShaderProgram> ResourceManager::createShader(const std::string& name,
                                                             const Shader& vertexShader,
                                                             const Shader& fragmentShader) {
    std::shared_ptr<ShaderProgram> shader(new ShaderProgram(
            vertexShader, fragmentShader
    ));
    this->shaders[name] = shader;

    return shader;
}

std::shared_ptr<Texture> ResourceManager::createTexture(const std::string& name,
                                                        GLuint width,
                                                        GLuint height,
                                                        unsigned char* image,
                                                        GLuint format) {
    std::shared_ptr<Texture> texture(new Texture(
            width, height, image, format
    ));
    this->textures[name] = texture;

    return texture;
}
