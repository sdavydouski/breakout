#include "Ball.h"
#include <iostream>

Ball::Ball(const glm::vec2 &position,
           float radius,
           const glm::vec3 &color,
           std::shared_ptr<Texture> sprite,
           const glm::vec2& velocity)
    : GameObject(position, glm::vec2(2 * radius), color, sprite), radius(radius), velocity(velocity), isStuck(true) {
    std::cout << "Ball constructor" << std::endl;
}

Ball::~Ball() {
    std::cout << "Ball destructor" << std::endl;
}

void Ball::move(const glm::vec4& boundaries, float delta) {
    if (this->isStuck) return;

    this->position += this->velocity * delta;

    if (this->position.x <= boundaries.x) {
        this->velocity.x = -this->velocity.x;
        this->position.x = boundaries.x;
    } else if (this->position.x + this->size.x >= boundaries.y) {
        this->velocity.x = -this->velocity.x;
        this->position.x = boundaries.y - this->size.x;
    } else if (this->position.y <= boundaries.z) {
        this->velocity.y = -this->velocity.y;
        this->position.y = boundaries.z;
    } else if (this->position.y + this->size.y >= boundaries.w) {
        this->velocity.y = -this->velocity.y;
        this->position.y = boundaries.w - this->size.y;
    }
}
