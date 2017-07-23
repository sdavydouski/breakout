#pragma once

#include "../Singleton.h"
#include "EventHandlers.h"
#include <map>
#include <string>

// GLFW3 defines 348 different key codes
const int NUMBER_OF_KEY_CODES = 348;

class InputManager: public Singleton<InputManager> {
public:
    void startUp();
    void shutDown();

    void pollEvents(float delta);
    void processKeyEvent(int key, int scancode, int action, int mods);

    void addKeyHandler(const std::string& name, KeyHandler keyHandler);
    void removeKeyHandler(const std::string& name);

    bool isKeyPressed(int key) {
        return keys_[key];
    }

    bool isKeyProcessed(int key) {
        return processedKeys_[key];
    }

    void setProcessedKey(int key) {
        processedKeys_[key] = true;
    }
private:
    std::map<std::string, KeyHandler> keyHandlers_;
    bool keys_[NUMBER_OF_KEY_CODES];
    bool processedKeys_[NUMBER_OF_KEY_CODES];
};
