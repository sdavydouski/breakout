#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

FileManager::FileManager() {
    // Empty constructor
    std::cout << "FileManager constructor" << std::endl;
}

FileManager::~FileManager() {
    // Empty destructor
    std::cout << "FileManager destructor" << std::endl;
}

FileManager &FileManager::Instance() {
    static FileManager instance;
    return instance;
}

std::string FileManager::readAsText(const std::string &fileName) const {
    std::string content{""};
    std::ifstream file(fileName);

    if (file.is_open()) {
        std::stringstream stream;
        // Read file's buffer contents into stream
        stream << file.rdbuf();
        file.close();
        // Convert stream into string
        content = stream.str();
    } else {
        std::cerr << "Unable to open file " << fileName << std::endl;
    }

    return content;
}
