#include "SpriteRenderer.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <iostream>

SpriteRenderer::SpriteRenderer() {
    std::cout << "SpriteRenderer constructor" << std::endl;
}

SpriteRenderer::~SpriteRenderer() {
    std::cout << "SpriteRenderer destructor" << std::endl;

    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}

void SpriteRenderer::init(const std::shared_ptr<ShaderProgram> shaderProgram) {
    this->setShaderProgram(shaderProgram);

    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::setShaderProgram(const std::shared_ptr<ShaderProgram> shaderProgram) {
    this->shaderProgram = shaderProgram;
}

void SpriteRenderer::renderSprite(const std::shared_ptr<Texture> texture,
                                  const glm::vec2& position,
                                  const glm::vec2& size,
                                  const glm::vec3& color,
                                  GLfloat rotate) {
    this->shaderProgram->use();

    glm::mat4 model;
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->shaderProgram->setUniform("model", model);
    this->shaderProgram->setUniform("color", color);

    texture->bind();

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
