#pragma once

#include <GL/glew.h>

class Texture {
public:
    Texture(GLuint width, GLuint height, unsigned char* image, GLuint format = GL_RGB);
    ~Texture();
    void bind();
    void bind(GLuint unit);
    void unbind();
private:
    GLuint id;
    GLuint width;
    GLuint height;
    GLuint format;
};
