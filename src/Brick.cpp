#include "Brick.h"

Brick::Brick(const glm::vec2& position,
             const glm::vec2& size,
             const glm::vec3& color,
             std::shared_ptr<Texture> sprite,
             bool isSolid)
    : GameObject(position, size, color, sprite), isSolid(isSolid), isDestroyed(false) {}

bool Brick::getIsSolid() const {
    return this->isSolid;
}

bool Brick::getIsDestroyed() const {
    return this->isDestroyed;
}

void Brick::setIsDestroyed(bool isDestroyed) {
    this->isDestroyed = isDestroyed;
};
