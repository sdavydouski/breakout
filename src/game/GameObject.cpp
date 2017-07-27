#include "GameObject.h"

GameObject::GameObject(const glm::vec2& position,
                       const glm::vec2& size,
                       const glm::vec3& color,
                       Texture* sprite)
    : position_(position), size_(size), color_(color), sprite_(sprite) {}

GameObject::~GameObject() {}

void GameObject::render(const SpriteRenderer& renderer) {
    renderer.renderSprite(sprite_, position_, size_, color_);
}
