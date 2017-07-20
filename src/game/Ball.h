#pragma once

#include "GameObject.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Ball: public GameObject {
public:
    Ball(const glm::vec2& position,
         float radius,
         const glm::vec3& color,
         Texture* sprite,
         const glm::vec2& velocity,
         const glm::vec4& boundaries);
    ~Ball();

    void update(float delta);

    // getters
    float radius() const { return radius_; }
    const glm::vec2& velocity() const { return velocity_; }
    bool isStuck() const { return isStuck_; }
    bool isSticky() const { return isSticky_; }
    bool isPassingThrough() const { return isPassingThrough_; }
    const glm::vec4& boundaries() const { return boundaries_; }

    // setters
    void velocity(const glm::vec2& velocity) { velocity_ = velocity; }
    void velocity(float scale) { velocity_ *= scale; }
    void velocityX(float x) { velocity_.x = x; }
    void velocityY(float y) { velocity_.y = y; }
    void isStuck(bool isStuck) { isStuck_ = isStuck; }
    void isSticky(bool isSticky) { isSticky_ = isSticky; }
    void isPassingThrough(bool isPassingThrough) { isPassingThrough_ = isPassingThrough; }

private:
    float radius_;
    glm::vec2 velocity_;
    bool isStuck_;
    bool isSticky_;
    bool isPassingThrough_;
    glm::vec4 boundaries_;
};
