#include "PostProcessor.h"
#include "PostProcessingEffect.h"
#include <glm/vec2.hpp>
#include <stdexcept>
#include <iostream>

PostProcessor::PostProcessor(ShaderProgram *shaderProgram, GLuint framebufferWidth, GLuint framebufferHeight)
    : shaderProgram_(shaderProgram), framebufferWidth_(framebufferWidth), framebufferHeight_(framebufferHeight), effects_(0) {

    this->initFBOs();
    this->initVAO();
    this->initShaderUniforms();
}

PostProcessor::~PostProcessor() {
    glDeleteFramebuffers(1, &MSFBO_);
    glDeleteFramebuffers(1, &FBO_);
    glDeleteRenderbuffers(1, &RBO_);
    glDeleteTextures(1, &textureId_);
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}

void PostProcessor::beginRender() const {
    glBindFramebuffer(GL_FRAMEBUFFER, MSFBO_);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void PostProcessor::endRender() const {
    // Now resolve multisampled color-buffer into intermediate FBO to store to texture
    glBindFramebuffer(GL_READ_FRAMEBUFFER, MSFBO_);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO_);
    glBlitFramebuffer(0, 0, framebufferWidth_, framebufferHeight_, 0, 0, framebufferWidth_, framebufferHeight_, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    // Binds both READ and WRITE framebuffer to default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::render(GLfloat time, GLfloat scale) {
    shaderProgram_->use();
    shaderProgram_->setUniform("time", time);
    shaderProgram_->setUniform("scale", scale);
    shaderProgram_->setUniform("chaos", effects_ & PostProcessingEffect::Chaos);
    shaderProgram_->setUniform("confuse", effects_ & PostProcessingEffect::Confuse);
    shaderProgram_->setUniform("shake", effects_ & PostProcessingEffect::Shake);

    // Render textured quad
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId_);
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void PostProcessor::enableEffects(int effects) {
    if (effects & PostProcessingEffect::Chaos) effects_ |= PostProcessingEffect::Chaos;
    if (effects & PostProcessingEffect::Confuse) effects_ |= PostProcessingEffect::Confuse;
    if (effects & PostProcessingEffect::Shake) effects_ |= PostProcessingEffect::Shake;
}

void PostProcessor::disableEffects(int effects) {
    if (effects & PostProcessingEffect::Chaos) effects_ &= ~PostProcessingEffect::Chaos;
    if (effects & PostProcessingEffect::Confuse) effects_ &= ~PostProcessingEffect::Confuse;
    if (effects & PostProcessingEffect::Shake) effects_ &= ~PostProcessingEffect::Shake;
}

void PostProcessor::initFBOs() {
    // Initialize framebuffer/renderbuffer objects
    glGenFramebuffers(1, &MSFBO_);
    glGenFramebuffers(1, &FBO_);
    glGenRenderbuffers(1, &RBO_);

    // Initialize renderbuffer storage with a multisampled color buffer (don't need a depth/stencil buffer)
    glBindFramebuffer(GL_FRAMEBUFFER, MSFBO_);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO_);
    // Allocate storage for render buffer object
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_RGB, framebufferWidth_, framebufferHeight_);
    // Attach MS render buffer object to framebuffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, RBO_);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Failed to initialize MSFBO" << std::endl;
        throw std::runtime_error("Failed to initialize MSFBO");
    }

    // Also initialize the FBO/texture to blit multisampled color-buffer to;
    // used for shader operations (for postprocessing effects)
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    this->initTexture();
    // Attach texture to framebuffer as its color attachment
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId_, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Failed to initialize FBO" << std::endl;
        throw std::runtime_error("Failed to initialize FBO");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::initTexture() {
    glGenTextures(1, &textureId_);
    glBindTexture(GL_TEXTURE_2D, textureId_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, framebufferWidth_, framebufferHeight_, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void PostProcessor::initVAO() {
    GLfloat quad[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
        1.0f,  1.0f, 1.0f, 1.0f,
    };

    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void PostProcessor::initShaderUniforms() {
    shaderProgram_->use();

    shaderProgram_->setUniform("scene", 0);

    auto offset = 1.0f / 300.0f;     // just random offset
    glm::vec2 offsets[] = {
        { -offset,  offset  },  // top-left
        {  0.0f,    offset  },  // top-center
        {  offset,  offset  },  // top-right
        { -offset,  0.0f    },  // center-left
        {  0.0f,    0.0f    },  // center-center
        {  offset,  0.0f    },  // center - right
        { -offset, -offset  },  // bottom-left
        {  0.0f,   -offset  },  // bottom-center
        {  offset, -offset  }   // bottom-right
    };
    shaderProgram_->setUniform("offsets", 9, offsets);

    GLint edgeKernel[] = {
        -1, -1, -1,
        -1,  8, -1,
        -1, -1, -1
    };
    shaderProgram_->setUniform("edgeKernel", 9, edgeKernel);

    GLfloat blurKernel[9] = {
        1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
        2.0f / 16.0f, 4.0f / 16.0f,  2.0f / 16.0f,
        1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
    };
    shaderProgram_->setUniform("blurKernel", 9, blurKernel);

    shaderProgram_->end();
}

void PostProcessor::resize(Extent framebufferSize)
{
    glDeleteFramebuffers(1, &MSFBO_);
    glDeleteFramebuffers(1, &FBO_);
    glDeleteRenderbuffers(1, &RBO_);
    glDeleteTextures(1, &textureId_);

    framebufferWidth_ = framebufferSize.width;
    framebufferHeight_ = framebufferSize.height;
    initFBOs();
}
