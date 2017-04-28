#pragma once

#include "GameState.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Window.h"
#include <GL/glew.h>
#include <memory>

class Game {
public:
    Game(std::shared_ptr<Window> window);
    ~Game();

    void input(GLfloat delta);
    void update(GLfloat delta);
    void render();

private:
    GameState gameState;
    std::shared_ptr<Window> window;

    InputManager& inputManager = InputManager::Instance();
    ResourceManager& resourceManager = ResourceManager::Instance();
    SpriteRenderer& spriteRenderer = SpriteRenderer::Instance();

    void init(int width, int height);
    void initGL();
};
