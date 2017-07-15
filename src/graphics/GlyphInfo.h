#pragma once

#include <glm/vec2.hpp>

struct GlyphInfo {
    glm::vec2 size;
    glm::vec2 bearing;
    glm::vec2 uvs[2];
    int advance;

    float offsetX;
    float offsetY;
};
