#pragma once

#include "GameObject.h"

class Brick: public GameObject {
public:
    Brick(const glm::vec2& position,
          const glm::vec2& size,
          const glm::vec3& color,
          std::shared_ptr<Texture> sprite,
          bool isSolid = false);

    bool getIsSolid() const;
    bool getIsDestroyed() const;
    void setIsDestroyed(bool isDestroyed);
private:
    bool isSolid;
    bool isDestroyed;
};
