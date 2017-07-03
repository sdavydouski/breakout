#pragma once

#include "Singleton.h"
#include "utils/AudioFile.h"
#include <GL/glew.h>
#include <string>

class FileManager: public Singleton<FileManager> {
public:
    std::string readAsText(const std::string& path) const;
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
