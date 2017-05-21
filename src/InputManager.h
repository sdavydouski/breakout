#pragma once

#include "Singleton.h"
#include "EventHandlers.h"
#include <map>
#include <string>

class InputManager: public Singleton<InputManager> {
public:
    void startUp();
    void shutDown();

    void pollEvents(float delta);
    void processKeyEvent(int key, int scancode, int action, int mods);

    void addKeyHandler(const std::string& name, KeyHandler keyHandler);
    void removeKeyHandler(const std::string& name);

    bool isKeyPressed(int key);
private:
    std::map<std::string, KeyHandler> keyHandlers;
    float delta;
    bool keys[348];             // GLFW3 defines 348 different key codes

    InputManager();
    ~InputManager();

friend Singleton;
};
