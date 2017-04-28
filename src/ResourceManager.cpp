#include "ResourceManager.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Texture.h"
#include "FileManager.h"
#include <memory>
#include <string>
#include <iostream>

ResourceManager::ResourceManager() {
    std::cout << "ResourceManager constructor" << std::endl;
}

ResourceManager::~ResourceManager() {
    std::cout << "ResourceManager destructor" << std::endl;
}

void ResourceManager::startUp() {
    // For consistency
}

void ResourceManager::shutDown() {
    for (const auto& shader : this->shaderPrograms) {
        shader.second->destroy();
    }
    for (const auto& texture : this->textures) {
        texture.second->destroy();
    }
}

std::shared_ptr<ShaderProgram> ResourceManager::getShaderProgram(const std::string& name) {
    return this->shaderPrograms[name];
}

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string& name) {
    return this->textures[name];
}

std::shared_ptr<ShaderProgram> ResourceManager::createShaderProgram(const std::string& name,
                                                                    const Shader& vertexShader,
                                                                    const Shader& fragmentShader) {
    std::shared_ptr<ShaderProgram> shader(new ShaderProgram(
            vertexShader, fragmentShader
    ));
    this->shaderPrograms[name] = shader;

    return shader;
}

std::shared_ptr<Texture> ResourceManager::createTexture(const std::string& name,
                                                        const std::string& path,
                                                        GLuint width,
                                                        GLuint height,
                                                        GLint channels,
                                                        GLuint format) {
    unsigned char *image = FileManager::Instance().readImage(path, width, height, channels);

    std::shared_ptr<Texture> texture(new Texture(
            width, height, image, format
    ));
    this->textures[name] = texture;

    return texture;
}
