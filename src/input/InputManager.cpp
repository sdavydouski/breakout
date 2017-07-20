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
    keyHandlers_.clear();
}

void InputManager::pollEvents(float delta) {
    delta_ = delta;
    glfwPollEvents();

    for (const auto& keyHandler : keyHandlers_) {
        keyHandler.second(delta_);
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

bool InputManager::isKeyPressed(int key) {
    return keys_[key];
}

bool InputManager::isKeyProcessed(int key) {
    return processedKeys_[key];
}


void InputManager::setProcessedKey(int key) {
    processedKeys_[key] = true;
}

