#pragma once

#include <glm/vec2.hpp>

struct GlyphInfo {
    glm::vec2 size;
    glm::vec2 uvs[2];

    float offsetX;
    float offsetY;
};
