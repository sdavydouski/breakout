#pragma once

#include "EventHandlers.h"
#include <map>
#include <string>

class InputManager {
public:
    static InputManager& Instance();
    // Copy constructor
    InputManager(const InputManager&) = delete;
    // Move constructor
    InputManager(const InputManager&&) = delete;
    // Copy assignment
    InputManager& operator =(const InputManager&) = delete;
    // Move assignment
    InputManager& operator =(const InputManager&&) = delete;

    void startUp();
    void shutDown();

    void pollEvents();
    void processKeyEvent(int key, int scancode, int action, int mods);

    void addKeyHandler(const std::string& name, KeyHandler keyHandler);
    void removeKeyHandler(const std::string& name);
private:
    std::map<std::string, KeyHandler> keyHandlers;

    InputManager();
    ~InputManager();
};
