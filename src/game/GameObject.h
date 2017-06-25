#pragma once

#include "../graphics/Texture.h"
#include "../graphics/SpriteRenderer.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class GameObject {
public:
    GameObject(const glm::vec2& position,
               const glm::vec2& size,
               const glm::vec3& color,
               Texture* sprite);
    virtual ~GameObject();

    virtual void render(const SpriteRenderer& renderer);

    // getters
    const glm::vec2& position() const { return position_; };
    const glm::vec2& size() const { return size_; };
    const glm::vec3& color() const { return color_; };

    // setters
    void position(const glm::vec2& position) { position_ = position; }
    void positionX(float x) { position_.x = x; }
    void positionY(float y) { position_.y = y; }
    void updatePositionX(float delta) { position_.x += delta; }
    void updatePositionY(float delta) { position_.y += delta; }

    void size(const glm::vec2& size) { size_ = size; }
    void sizeX(float x) { size_.x = x; }
    void sizeY(float y) { size_.y = y; }
    void updateSizeX(float delta) { size_.x += delta; }
    void updateSizeY(float delta) { size_.y += delta; }

    void color(const glm::vec3& color) { color_ = color; }

protected:
    glm::vec2 position_;        // top-left position
    glm::vec2 size_;
    glm::vec3 color_;
    Texture* sprite_;
};
