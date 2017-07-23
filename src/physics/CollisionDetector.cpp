#include "CollisionDetector.h"
#include <glm/glm.hpp>
#include <numeric>

// AABB - Circle collision
Collision CollisionDetector::checkCollision(const Ball &ball, const GameObject &gameObject) {
    // Get center point circle first
    auto center = ball.position() + ball.radius();
    // Calculate AABB info (center, half-extents)
    glm::vec2 aabbHalfExtents(gameObject.size().x / 2, gameObject.size().y / 2);
    glm::vec2 aabbCenter(
            gameObject.position().x + aabbHalfExtents.x,
            gameObject.position().y + aabbHalfExtents.y
    );
    // Get difference vector between both centers
    auto difference = center - aabbCenter;
    auto clamped = glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents);
    // Add clamped value to AABB_center and we get the value of box closest to circle
    auto closest = aabbCenter + clamped;
    // Retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;

    return glm::length(difference) <= ball.radius() ?
           std::make_tuple(true, CollisionDetector::getVectorDirection(difference), difference) :
           std::make_tuple(false, Direction::UP, glm::vec2(0, 0));
}

// AABB - AABB collision
bool CollisionDetector::checkCollision(const GameObject& one, const GameObject& two) {
    // Collision x-axis
    auto collisionX = one.position().x + one.size().x >= two.position().x &&
                      two.position().x + two.size().x >= one.position().x;
    // Collision y-axis
    auto collisionY = one.position().y + one.size().y >= two.position().y &&
                      two.position().y + two.size().y >= one.position().y;
    // Collision only if on both axes
    return collisionX && collisionY;
}

Direction CollisionDetector::getVectorDirection(const glm::vec2 &target) {
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f),	// left
        glm::vec2(1.0f, 0.0f)	// right
    };

    auto max = 0.0f;
    auto bestMatch = -1;
    for (auto i = 0; i < compass->length(); i++) {
        auto dotProduct = glm::dot(glm::normalize(target), compass[i]);
        if (dotProduct > max) {
            max = dotProduct;
            bestMatch = i;
        }
    }

    return static_cast<Direction>(bestMatch);
}
