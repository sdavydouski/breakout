#include "InputManager.h"
#include "EventHandlers.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>

InputManager::InputManager() {
    std::cout << "InputManager constructor" << std::endl;
}

InputManager::~InputManager() {
    std::cout << "InputManager destructor" << std::endl;
}

void InputManager::startUp() {
    // For consistency
}

void InputManager::shutDown() {
    this->keyHandlers.clear();
}

void InputManager::pollEvents() {
    glfwPollEvents();
}

void InputManager::processKeyEvent(int key, int scancode, int action, int mods) {
    for (const auto& keyHandler : this->keyHandlers) {
        keyHandler.second(key, scancode, action, mods);
    }
}

void InputManager::addKeyHandler(const std::string& name, KeyHandler keyHandler) {
    this->keyHandlers[name] = keyHandler;
}

void InputManager::removeKeyHandler(const std::string& name) {
    this->keyHandlers.erase(name);
}
