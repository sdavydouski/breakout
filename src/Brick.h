#pragma once

#include "GameObject.h"

class Brick: public GameObject {
public:
    Brick(const glm::vec2& position,
          const glm::vec2& size,
          const glm::vec3& color,
          std::shared_ptr<Texture> sprite,
          bool isSolid = false);
private:
    bool isSolid;
    bool isDestroyed;
};
