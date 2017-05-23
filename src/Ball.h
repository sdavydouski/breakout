#pragma once

#include "GameObject.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

class Ball: public GameObject {
public:
    Ball(const glm::vec2& position,
         float radius,
         const glm::vec3& color,
         std::shared_ptr<Texture> sprite,
         const glm::vec2& velocity,
         const glm::vec4& boundaries);
    ~Ball();

    void update(float delta);

    const glm::vec2& getVelocity() const;
    float getRadius() const;
    bool getIsStuck() const;
    void setIsStuck(bool isStuck);
private:
    glm::vec2 velocity;
    float radius;
    bool isStuck;

    glm::vec4 boundaries;
};
