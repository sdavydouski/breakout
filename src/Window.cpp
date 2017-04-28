#include "Window.h"
#include "InputManager.h"
#include <GLFW/glfw3.h>
#include <iostream>

Window::Window(int width, int height, const std::string& title, bool isFullScreen, bool vsync)
    : width(width), height(height), title(title), isFullScreen(isFullScreen), vsync(vsync) {
    std::cout << "Window constructor" << std::endl;

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

    this->window = isFullScreen ?
                   glfwCreateWindow(width, height, title.c_str(), primaryMonitor, nullptr) :
                   glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (this->window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
    }

    if (!isFullScreen) {
        // Center window on screen
        auto vidMode = glfwGetVideoMode(primaryMonitor);
        glfwSetWindowPos(this->window,
                         (vidMode->width - width) / 2,
                         (vidMode->height - height) / 2);
    }

    // Create OpenGL context
    this->makeContextCurrent();

    // Enable v-sync
    if (vsync) {
        glfwSwapInterval(1);
    }

    // Define the viewport dimensions
    int frameBufferWidth, frameBufferHeight;
    glfwGetFramebufferSize(this->window, &frameBufferWidth, &frameBufferHeight);
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);

    this->setupEventHandlers();
}

Window::~Window() {
    // Empty destructor
    std::cout << "Window destructor" << std::endl;
}

void Window::destroy() {
    glfwDestroyWindow(this->window);
}

bool Window::isClosing() {
    return (bool) glfwWindowShouldClose(this->window);
}

void Window::setIsShouldClose(bool isShouldClose) {
    glfwSetWindowShouldClose(this->window, isShouldClose);
}

void Window::makeContextCurrent() {
    glfwMakeContextCurrent(this->window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(this->window);
}

int Window::getWidth() {
    return this->width;
}

int Window::getHeight() {
    return this->height;
}

void Window::setupEventHandlers() {
    glfwSetKeyCallback(this->window, [](GLFWwindow* window,
                                                    int key,
                                                    int scancode,
                                                    int action,
                                                    int mods) {
        InputManager::Instance().processKeyEvent(key, scancode, action, mods);
    });
}
