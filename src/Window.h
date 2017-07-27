#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    ~Window();
    bool isClosing() const;
    void setIsShouldClose(bool isShouldClose);
    void makeContextCurrent();
    void swapBuffers();

    // getters
    int width() const { return width_; }
    int height() const { return height_; }

private:
    int width_;
    int height_;
    std::string title_;
    bool isFullScreen_;
    bool vsync_;
    GLFWwindow* window_;

    Window(int width, int height, const std::string& title, bool isFullScreen, bool vsync);
    void destroy();
    void setupEventHandlers();

friend class WindowManager;
};
