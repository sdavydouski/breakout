#pragma once

#include "graphics/Extent.h"
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
    bool pollResize();  // Not a getter!

    // getters
    int width() const { return width_; }
    int height() const { return height_; }
    Extent getFramebufferSize() const;

private:
    int width_;
    int height_;
    std::string title_;
    bool isFullScreen_;
    bool vsync_;
    GLFWwindow* window_;
    bool resized_;

    Window(int width, int height, const std::string& title, bool isFullScreen, bool vsync);
    void destroy();
    void setupEventHandlers();
    static void framebufferSizeCallback(GLFWwindow*, int width, int height);

friend class WindowManager;
};
