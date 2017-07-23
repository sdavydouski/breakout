#pragma once

#include "../audio/AudioFile.h"
#include <GL/glew.h>
#include <string>
#include <vector>

class FileManager {
public:
    static std::string readAsText(const std::string& path);
    static std::vector<unsigned char> readAsBinary(const std::string& path);
    static unsigned char* readImage(const std::string& path,
                                    GLint width,
                                    GLint height,
                                    GLint components,
                                    bool flip = false);
    static AudioFile readOggFile(const std::string& path);
};
