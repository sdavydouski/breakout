#include "GameObject.h"
#include <iostream>

GameObject::GameObject(const glm::vec2& position,
                       const glm::vec2& size,
                       const glm::vec3& color,
                       std::shared_ptr<Texture> sprite)
    : position_(position), size_(size), color_(color), sprite_(sprite) {
    //std::cout << "GameObject constructor" << std::endl;
}

GameObject::~GameObject() {
    //std::cout << "GameObject destructor" << std::endl;
}

void GameObject::render(const SpriteRenderer& renderer) {
    renderer.renderSprite(sprite_, position_, size_, color_);
}
