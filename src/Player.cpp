#include "Player.h"
#include <iostream>

Player::Player(const glm::vec2 &position,
               const glm::vec2 &size,
               const glm::vec3 &color,
               std::shared_ptr<Texture> sprite,
               float velocity,
               const glm::vec2& boundaries)
    : GameObject(position, size, color, sprite), velocity_(velocity), boundaries_(boundaries) {
    std::cout << "Player constructor" << std::endl;
}

Player::~Player() {
    std::cout << "Player destructor" << std::endl;
}
