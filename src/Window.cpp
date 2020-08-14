#include "Window.h"
#include "input/InputManager.h"
#include "utils/FileManager.h"
#include <iostream>

Window::Window(int width, int height, const std::string& title, bool isFullScreen, bool vsync)
    : width_(width), height_(height), title_(title), isFullScreen_(isFullScreen), vsync_(vsync) {
    auto primaryMonitor = glfwGetPrimaryMonitor();

    window_ = isFullScreen ?
                  glfwCreateWindow(width, height, title.c_str(), primaryMonitor, nullptr) :
                  glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (window_ == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
     }

    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!isFullScreen) {
        // Center window on screen
        auto vidMode = glfwGetVideoMode(primaryMonitor);
        glfwSetWindowPos(window_,
                         (vidMode->width - width) / 2,
                         (vidMode->height - height) / 2);
    }

    // Create OpenGL context
    this->makeContextCurrent();

    // Enable v-sync
    if (vsync_) {
        glfwSwapInterval(1);
    }

    // Define the viewport dimensions
    int frameBufferWidth, frameBufferHeight;
    glfwGetFramebufferSize(window_, &frameBufferWidth, &frameBufferHeight);
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);

    glfwSetWindowUserPointer(window_, this);
    this->setupEventHandlers();
}

Extent Window::getFramebufferSize() const {
  int framebufferWidth;
  int framebufferHeight;
  glfwGetFramebufferSize(window_, &framebufferWidth, &framebufferHeight);
  return Extent{framebufferWidth, framebufferHeight};
}

bool Window::pollResize()
{
    auto result = resized_;
    resized_ = false;
    return result;
}

Window::~Window() {
    // Empty destructor
}

void Window::destroy() {
    glfwDestroyWindow(window_);
}

bool Window::isClosing() const {
    return static_cast<bool>(glfwWindowShouldClose(window_));
}

void Window::setIsShouldClose(bool isShouldClose) {
    glfwSetWindowShouldClose(window_, isShouldClose);
}

void Window::makeContextCurrent() {
    glfwMakeContextCurrent(window_);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window_);
}

void Window::setupEventHandlers() {
    glfwSetKeyCallback(window_, [](GLFWwindow* window,
                                                    int key,
                                                    int scancode,
                                                    int action,
                                                    int mods) {
        InputManager::Instance().processKeyEvent(key, scancode, action, mods);
    });
    glfwSetFramebufferSizeCallback(window_, framebufferSizeCallback);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    auto this_ptr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    this_ptr->resized_ = true;
}
