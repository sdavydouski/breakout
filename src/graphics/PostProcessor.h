#pragma once

#include <GL/glew.h>
#include "ShaderProgram.h"
#include "Texture.h"
#include "PostProcessingEffect.h"

class PostProcessor {
public:
    PostProcessor(ShaderProgram* shaderProgram, GLuint width, GLuint height);
    ~PostProcessor();

    // Prepares the postprocessor's framebuffer operations before rendering the game
    void beginRender();
    // Should be called after rendering the game, so it stores all the rendered data into a texture object
    void endRender();
    // Renders the PostProcessor texture quad (as a screen-encompassing large sprite)
    void render(GLfloat delta, GLfloat scale);

    void enableEffects(int effects);
    void disableEffects(int effects);
private:
    ShaderProgram* shaderProgram_;
    Texture* texture_;

    GLuint width_;
    GLuint height_;

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
