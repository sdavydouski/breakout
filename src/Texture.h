#pragma once

#include <GL/glew.h>

class Texture {
public:
    ~Texture();
    void bind() const;
    void bind(GLuint unit) const;
    void unbind() const;
private:
    GLuint id_;
    GLuint width_;
    GLuint height_;
    GLuint format_;

    Texture(GLuint width, GLuint height, unsigned char* image, GLuint format);
    void destroy();

friend class ResourceManager;
};
