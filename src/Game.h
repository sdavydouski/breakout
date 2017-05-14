#pragma once

#include <GL/glew.h>
#include "GameState.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "Window.h"
#include <memory>

class Game {
public:
    Game(int width, int height);
    ~Game();

    void input(GLfloat delta);
    void update(GLfloat delta);
    void render();

    bool isExiting();
private:
    GameState gameState;
    std::shared_ptr<Window> window;

    WindowManager& windowManager = WindowManager::Instance();
    InputManager& inputManager = InputManager::Instance();
    ResourceManager& resourceManager = ResourceManager::Instance();

    SpriteRenderer& spriteRenderer = SpriteRenderer::Instance();

    void initWindow(int width, int height);
    void initGL();
    void initResources();
};
