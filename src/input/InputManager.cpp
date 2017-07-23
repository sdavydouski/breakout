#include "InputManager.h"
#include "EventHandlers.h"
#include <GLFW/glfw3.h>

void InputManager::startUp() {
    // For consistency
}

void InputManager::shutDown() {
    keyHandlers_.clear();
}

void InputManager::pollEvents(float delta) {
    glfwPollEvents();

    for (const auto& keyHandler : keyHandlers_) {
        keyHandler.second(delta);
    }
}

void InputManager::processKeyEvent(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        keys_[key] = true;
    } else if (action == GLFW_RELEASE) {
        keys_[key] = false;
        processedKeys_[key] = false;
    }
}

void InputManager::addKeyHandler(const std::string& name, KeyHandler keyHandler) {
    keyHandlers_[name] = keyHandler;
}

void InputManager::removeKeyHandler(const std::string& name) {
    keyHandlers_.erase(name);
}
