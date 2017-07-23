#include "Ball.h"

Ball::Ball(const glm::vec2 &position,
           float radius,
           const glm::vec3 &color,
           Texture* sprite,
           const glm::vec2& velocity,
           const glm::vec4& boundaries)
    : GameObject(position, glm::vec2(2 * radius), color, sprite),
      radius_(radius), velocity_(velocity), isStuck_(true), isSticky_(false),
      isPassingThrough_(false), boundaries_(boundaries) {}

Ball::~Ball() {}

void Ball::update(float delta) {
    if (isStuck_) return;

    position_ += velocity_ * delta;

    if (position_.x <= boundaries_.x) {
        velocity_.x = -velocity_.x;
        position_.x = boundaries_.x;
    } else if (position_.x + size_.x >= boundaries_.y) {
        velocity_.x = -velocity_.x;
        position_.x = boundaries_.y - size_.x;
    } else if (position_.y <= boundaries_.z) {
        velocity_.y = -velocity_.y;
        position_.y = boundaries_.z;
    } else if (position_.y + size_.y >= boundaries_.w) {
        velocity_.y = -velocity_.y;
        position_.y = boundaries_.w - size_.y;
    }
}
