#include "GameObject.h"
#include <iostream>

GameObject::GameObject(const glm::vec2& position,
                       const glm::vec2& size,
                       const glm::vec3& color,
                       std::shared_ptr<Texture> sprite)
    : position(position), size(size), color(color), sprite(sprite) {
    std::cout << "GameObject constructor" << std::endl;
}

GameObject::~GameObject() {
    std::cout << "GameObject destructor" << std::endl;
}

void GameObject::render(const SpriteRenderer& renderer) {
    renderer.renderSprite(this->sprite, this->position, this->size, this->color);
}
