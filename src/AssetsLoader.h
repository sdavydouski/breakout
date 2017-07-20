#pragma once

#include <string>

class AssetsLoader {
public:
    static void loadShaders();
    static void loadTextures();
    static void loadAudioFiles();

    static const std::string OFFSET;
};
