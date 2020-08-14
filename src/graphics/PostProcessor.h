#pragma once

#include <GL/glew.h>
#include "Extent.h"
#include "ShaderProgram.h"
#include "Texture.h"

class PostProcessor {
public:
    PostProcessor(ShaderProgram* shaderProgram, GLuint framebufferWidth, GLuint framebufferHeight);
    ~PostProcessor();

    // Prepares the postprocessor's framebuffer operations before rendering the game
    void beginRender() const;
    // Should be called after rendering the game, so it stores all the rendered data into a texture object
    void endRender() const;
    // Renders the PostProcessor texture quad (as a screen-encompassing large sprite)
    void render(GLfloat delta, GLfloat scale);

    void enableEffects(int effects);
    void disableEffects(int effects);

    // Recreate PostProcessor after window resize.
    void resize(Extent framebufferSize);

private:
    ShaderProgram* shaderProgram_;
    Texture* texture_;

    GLuint framebufferWidth_;
    GLuint framebufferHeight_;

    int effects_;

    GLuint MSFBO_;      // Multisampled Framebuffer Object
    GLuint FBO_;        // Framebuffer Object
    GLuint RBO_;        // Renderbuffer Object
    GLuint VAO_;        // Vertex Array Object
    GLuint VBO_;        // Vertex Buffer Object
    GLuint textureId_;

    void initFBOs();
    void initTexture();
    void initVAO();
    void initShaderUniforms();
};
