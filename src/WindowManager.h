#pragma once

#include "Window.h"
#include <memory>
#include <vector>

class WindowManager {
public:
    static WindowManager& Instance();
    // Copy constructor
    WindowManager(const WindowManager&) = delete;
    // Move constructor
    WindowManager(WindowManager&&) = delete;
    // Copy assignment
    WindowManager& operator =(const WindowManager&) = delete;
    // Move assignment
    WindowManager& operator =(WindowManager&&) = delete;

    void startUp();
    void shutDown();

    std::shared_ptr<Window> createWindow(int width,
                                         int height,
                                         const std::string& title,
                                         bool isFullScreen = false,
                                         bool vsync = true);
private:
    std::vector<std::shared_ptr<Window>> windows;

    WindowManager();
    ~WindowManager();
};
