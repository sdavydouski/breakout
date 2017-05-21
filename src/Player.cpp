#include "Player.h"
#include "InputManager.h"
#include <GLFW/glfw3.h>
#include <iostream>

Player::Player(const glm::vec2 &position,
               const glm::vec2 &size,
               const glm::vec3 &color,
               std::shared_ptr<Texture> sprite,
               float velocity,
               const glm::vec2& boundaries)
    : GameObject(position, size, color, sprite), velocity(velocity), boundaries(boundaries) {
    std::cout << "Player constructor" << std::endl;

    this->inputManager.addKeyHandler("movePaddle", [this](float delta) {
        if (this->inputManager.isKeyPressed(GLFW_KEY_A) || this->inputManager.isKeyPressed(GLFW_KEY_LEFT)) {
            if (this->position.x >= this->boundaries.x) {
                this->position.x -= this->velocity * delta;
            }
        }
        if (this->inputManager.isKeyPressed(GLFW_KEY_D) || this->inputManager.isKeyPressed(GLFW_KEY_RIGHT)) {
            if (this->position.x <= this->boundaries.y) {
                this->position.x += this->velocity * delta;
            }
        }
    });
}

Player::~Player() {
    std::cout << "Player destructor" << std::endl;
}
