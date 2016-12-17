#pragma once

#include <string>

class FileManager {
public:
    static FileManager& Instance();
    // Copy constructor
    FileManager(const FileManager&) = delete;
    // Move constructor
    FileManager(FileManager&&) = delete;
    // Copy assignment
    FileManager& operator =(const FileManager&) = delete;
    // Move assignment
    FileManager& operator =(FileManager&&) = delete;

    std::string readAsText(const std::string& fileName) const;
private:
    FileManager();
    ~FileManager();
};
