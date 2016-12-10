#include "WindowManager.h"
#include <GLFW/glfw3.h>
#include <iostream>

WindowManager::WindowManager() {
    // Empty constructor
    std::cout << "WindowManager constructor" << std::endl;
}

WindowManager::~WindowManager() {
    // Empty destructor
    std::cout << "WindowManager destructor" << std::endl;
}

WindowManager &WindowManager::Instance() {
    static WindowManager instance;
    return instance;
}

void WindowManager::startUp() {
    // Setup error handling
    glfwSetErrorCallback([](int errorCode, const char* description) -> void {
        std::cerr << description << std::endl;
    });

    std::cout << glfwGetVersionString() << std::endl;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }

    // Using OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void WindowManager::shutDown() {
    for (auto window : this->windows) {
        window->destroy();
    }

    glfwTerminate();
}

std::shared_ptr<Window> WindowManager::createWindow(int width,
                                                    int height,
                                                    const std::string& title,
                                                    bool isFullScreen,
                                                    bool vsync) {
    std::shared_ptr<Window> window(new Window(
        width, height, title, isFullScreen, vsync
    ));
    this->windows.push_back(window);

    return window;
}
