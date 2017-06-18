#pragma once

#include "Collision.h"
#include "Direction.h"
#include "../game/GameObject.h"
#include "../game/Ball.h"

class CollisionDetector {
public:
    static Collision checkCollision(const Ball& ball, const GameObject& gameObject);
private:
    static Direction getVectorDirection(const glm::vec2& target);
};
