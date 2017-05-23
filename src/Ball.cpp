#include "Ball.h"
#include <iostream>

Ball::Ball(const glm::vec2 &position,
           float radius,
           const glm::vec3 &color,
           std::shared_ptr<Texture> sprite,
           const glm::vec2& velocity,
           const glm::vec4& boundaries)
    : GameObject(position, glm::vec2(2 * radius), color, sprite),
      radius(radius), velocity(velocity), isStuck(true), boundaries(boundaries) {
    std::cout << "Ball constructor" << std::endl;
}

Ball::~Ball() {
    std::cout << "Ball destructor" << std::endl;
}

void Ball::update(float delta) {
    if (this->isStuck) return;

    this->position += this->velocity * delta;

    if (this->position.x <= this->boundaries.x) {
        this->velocity.x = -this->velocity.x;
        this->position.x = this->boundaries.x;
    } else if (this->position.x + this->size.x >= this->boundaries.y) {
        this->velocity.x = -this->velocity.x;
        this->position.x = this->boundaries.y - this->size.x;
    } else if (this->position.y <= this->boundaries.z) {
        this->velocity.y = -this->velocity.y;
        this->position.y = this->boundaries.z;
    } else if (this->position.y + this->size.y >= this->boundaries.w) {
        this->velocity.y = -this->velocity.y;
        this->position.y = this->boundaries.w - this->size.y;
    }
}

const glm::vec2& Ball::getVelocity() const {
    return this->velocity;
}

float Ball::getRadius() const {
    return this->radius;
}

bool Ball::getIsStuck() const {
    return this->isStuck;
}

void Ball::setIsStuck(bool isStuck) {
    this->isStuck = isStuck;
}
