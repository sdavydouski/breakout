#pragma once

#include <glm/vec2.hpp>
#include "Collision.h"
#include "Direction.h"
#include "../game/GameObject.h"
#include "../game/Ball.h"

class CollisionDetector {
public:
    static Collision checkCollision(const Ball& ball, const GameObject& gameObject);
    static bool checkCollision(const GameObject& one, const GameObject& two);
private:
    static Direction getVectorDirection(const glm::vec2& target);
};
