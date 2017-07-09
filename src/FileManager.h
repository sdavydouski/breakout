#pragma once

#include "Singleton.h"
#include "audio/AudioFile.h"
#include <GL/glew.h>
#include <string>
#include <vector>

class FileManager: public Singleton<FileManager> {
public:
    std::string readAsText(const std::string& path) const;
    std::vector<unsigned char> readAsBinary(const std::string& path) const;
    unsigned char* readImage(const std::string& path,
                             GLint width,
                             GLint height,
                             GLint components,
                             bool flip = false) const;
    AudioFile readOggFile(const std::string& path) const;
private:
    FileManager();
    ~FileManager();

friend Singleton;
};
