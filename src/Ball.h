#pragma once

#include "GameObject.h"
#include <glm/vec4.hpp>

class Ball: public GameObject {
public:
    Ball(const glm::vec2& position,
         float radius,
         const glm::vec3& color,
         std::shared_ptr<Texture> sprite,
         const glm::vec2& velocity);
    ~Ball();

    void move(const glm::vec4& boundaries, float delta);
//private:
    glm::vec2 velocity;
    float radius;
    bool isStuck;
};
