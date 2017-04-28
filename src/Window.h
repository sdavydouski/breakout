#pragma once

#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    ~Window();
    bool isClosing();
    void setIsShouldClose(bool isShouldClose);
    void makeContextCurrent();
    void swapBuffers();

    int getWidth();
    int getHeight();
private:
    int width;
    int height;
    std::string title;
    bool isFullScreen;
    bool vsync;
    GLFWwindow* window;

    Window(int width, int height, const std::string& title, bool isFullScreen, bool vsync);
    void destroy();
    void setupEventHandlers();

friend class WindowManager;
};
