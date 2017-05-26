#include "Brick.h"

Brick::Brick(const glm::vec2& position,
             const glm::vec2& size,
             const glm::vec3& color,
             std::shared_ptr<Texture> sprite,
             bool isSolid)
    : GameObject(position, size, color, sprite), isSolid_(isSolid), isDestroyed_(false) {}
