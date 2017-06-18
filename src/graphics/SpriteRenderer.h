#pragma once

#include "../Singleton.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class SpriteRenderer: public Singleton<SpriteRenderer> {
public:
    void init(ShaderProgram* shaderProgram);
    void renderSprite(const Texture* texture,
                      const glm::vec2& position,
                      const glm::vec2& size = glm::vec2(10, 10),
                      const glm::vec3& color = glm::vec3(1.0f),
                      GLfloat rotate = 0.0f) const;

    // setters
    void shaderProgram(ShaderProgram* shaderProgram) { shaderProgram_ = shaderProgram; };

private:
    ShaderProgram* shaderProgram_;
    GLuint VAO_;
    GLuint VBO_;

    SpriteRenderer();
    ~SpriteRenderer();

friend Singleton;
};
