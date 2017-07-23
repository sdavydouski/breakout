#include "Player.h"

Player::Player(const glm::vec2 &position,
               const glm::vec2 &size,
               const glm::vec3 &color,
               Texture* sprite,
               float velocity,
               const glm::vec2& boundaries)
    : GameObject(position, size, color, sprite), velocity_(velocity), boundaries_(boundaries) {}

Player::~Player() {}
