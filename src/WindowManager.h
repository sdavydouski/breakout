#pragma once

#include "Singleton.h"
#include "Window.h"
#include <memory>
#include <vector>

class WindowManager: public Singleton<WindowManager> {
public:
    void startUp();
    void shutDown();

    Window* createWindow(int width,
                         int height,
                         const std::string& title,
                         bool isFullScreen = false,
                         bool vsync = true);
private:
    std::vector<std::unique_ptr<Window>> windows_;
};
