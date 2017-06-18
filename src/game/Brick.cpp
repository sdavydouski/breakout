#include "Brick.h"
#include <iostream>

Brick::Brick(const glm::vec2& position,
             const glm::vec2& size,
             const glm::vec3& color,
             Texture* sprite,
             bool isSolid)
    : GameObject(position, size, color, sprite), isSolid_(isSolid), isDestroyed_(false) {
    //std::cout << "Brick constructor" << std::endl;
}

Brick::~Brick() {
    //std::cout << "Brick destructor" << std::endl;
}
