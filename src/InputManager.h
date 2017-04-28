#pragma once

#include "Singleton.h"
#include "EventHandlers.h"
#include <map>
#include <string>

class InputManager: public Singleton<InputManager> {
public:
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

friend Singleton;
};
