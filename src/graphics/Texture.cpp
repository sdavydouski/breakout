#include "Texture.h"
#include <GL/glew.h>
#include <stb_image.h>

Texture::Texture(GLuint width, GLuint height, unsigned char* image, GLuint format)
    : width_(width), height_(height), format_(format) {
    glGenTextures(1, &id_);

    this->bind();

    glTexImage2D(GL_TEXTURE_2D, 0, format_, width_, height_, 0, format_, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    this->unbind();
}

Texture::~Texture() {
    // Empty destructor
}

void Texture::destroy() {
    glDeleteTextures(1, &id_);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::bind(GLuint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    this->bind();
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
