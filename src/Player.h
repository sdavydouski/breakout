#pragma once

#include "GameObject.h"
#include "InputManager.h"
#include <glm/vec2.hpp>
#include <memory>

class Player: public GameObject {
public:
    Player(const glm::vec2& position,
           const glm::vec2& size,
           const glm::vec3& color,
           std::shared_ptr<Texture> sprite,
           float velocity,
           const glm::vec2& boundaries);
    ~Player();
private:
    float velocity;
    glm::vec2 boundaries;

    InputManager& inputManager = InputManager::Instance();
};
