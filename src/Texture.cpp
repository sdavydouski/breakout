#include "Texture.h"
#include <GL/glew.h>
#include <stb_image.h>
#include <iostream>

Texture::Texture(GLuint width, GLuint height, unsigned char *image, GLuint format)
    : width(width), height(height), format(format) {
    std::cout << "Texture constructor" << std::endl;

    glGenTextures(1, &this->id);

    this->bind();

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    this->unbind();

    stbi_image_free(image);
}

Texture::~Texture() {
    // Empty destructor
    std::cout << "Texture destructor" << std::endl;
}

void Texture::destroy() {
    std::cout << "Texture destroy()" << std::endl;
    glDeleteTextures(1, &this->id);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::bind(GLuint unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    this->bind();
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
