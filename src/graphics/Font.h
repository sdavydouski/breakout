#pragma once

#include "stb_truetype.h"
#include <GL/glew.h>
#include <vector>

using Font = struct {
    const int size = 40;
    const int atlasWidth = 2048;
    const int atlasHeight = 2048;
    const int overSampleX = 4;
    const int overSampleY = 4;
    const char firstChar = 0;
    const int charCount = 127;
    std::vector<stbtt_packedchar> charInfo;
    GLuint textureId;
};
