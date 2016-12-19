#pragma once

#include <GL/glew.h>

class Texture {
public:
    ~Texture();
    void bind();
    void bind(GLuint unit);
    void unbind();
private:
    GLuint id;
    GLuint width;
    GLuint height;
    GLuint format;

    Texture(GLuint width, GLuint height, unsigned char* image, GLuint format);
    void destroy();

    friend class ResourceManager;
};
