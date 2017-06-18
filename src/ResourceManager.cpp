#include "ResourceManager.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
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
    for (auto& shader : shaderPrograms_) {
        shader.second->destroy();
    }
    for (auto& texture : textures_) {
        texture.second->destroy();
    }
}

ShaderProgram* ResourceManager::createShaderProgram(const std::string& name,
                                                    const Shader& vertexShader,
                                                    const Shader& fragmentShader) {
    shaderPrograms_[name] = std::unique_ptr<ShaderProgram>(
        new ShaderProgram(vertexShader, fragmentShader)
    );

    return shaderPrograms_[name].get();
}

Texture* ResourceManager::createTexture(const std::string& name,
                                        const std::string& path,
                                        GLuint width,
                                        GLuint height,
                                        GLint channels,
                                        GLuint format) {
    unsigned char *image = FileManager::Instance().readImage(path, width, height, channels);

    textures_[name] = std::unique_ptr<Texture>(
        new Texture(width, height, image, format)
    );

    return textures_[name].get();
}
