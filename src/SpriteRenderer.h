#pragma once

#include "Singleton.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <memory>

class SpriteRenderer: public Singleton<SpriteRenderer> {
public:
    void init(const std::shared_ptr<ShaderProgram> shaderProgram);
    void renderSprite(const std::shared_ptr<Texture> texture,
                      const glm::vec2& position,
                      const glm::vec2& size = glm::vec2(10, 10),
                      const glm::vec3& color = glm::vec3(1.0f),
                      GLfloat rotate = 0.0f) const;

    // setters
    void shaderProgram(const std::shared_ptr<ShaderProgram> shaderProgram) { shaderProgram_ = shaderProgram; };

private:
    std::shared_ptr<ShaderProgram> shaderProgram_;
    GLuint VAO_;
    GLuint VBO_;

    SpriteRenderer();
    ~SpriteRenderer();

friend Singleton;
};
