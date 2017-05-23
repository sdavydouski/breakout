#pragma once

#include "Texture.h"
#include "SpriteRenderer.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <memory>

class GameObject {
public:
    GameObject(const glm::vec2& position,
               const glm::vec2& size,
               const glm::vec3& color,
               std::shared_ptr<Texture> sprite);
    virtual ~GameObject();

    virtual void render(const SpriteRenderer& renderer);

    const glm::vec2& getSize() const;

    // top-left position
    glm::vec2 position;
protected:
    glm::vec2 size;
    glm::vec3 color;
    std::shared_ptr<Texture> sprite;
};
