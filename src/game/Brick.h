#pragma once

#include "GameObject.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Brick: public GameObject {
public:
    Brick(const glm::vec2& position,
          const glm::vec2& size,
          const glm::vec3& color,
          Texture* sprite,
          bool isSolid = false);
    ~Brick();

    // getters
    bool isSolid() const { return isSolid_; }
    bool isDestroyed() const { return isDestroyed_; }

    // setters
    void isDestroyed(bool isDestroyed) { isDestroyed_ = isDestroyed; }

private:
    bool isSolid_;
    bool isDestroyed_;
};
