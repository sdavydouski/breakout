#pragma once

#include <GL/glew.h>
#include "GameState.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "Window.h"
#include "GameLevel.h"
#include "Player.h"
#include "Ball.h"
#include <memory>
#include <vector>

class Game {
public:
    Game(int width, int height, bool isFullScreen);
    ~Game();

    void input(GLfloat delta);
    void update(GLfloat delta);
    void render();

    bool isExiting();
private:
    GameState gameState;
    std::shared_ptr<Window> window;
    std::vector<std::shared_ptr<GameLevel>> levels;
    int currentLevel;

    std::shared_ptr<Player> player;
    std::shared_ptr<Ball> ball;

    WindowManager& windowManager = WindowManager::Instance();
    InputManager& inputManager = InputManager::Instance();
    ResourceManager& resourceManager = ResourceManager::Instance();

    SpriteRenderer& spriteRenderer = SpriteRenderer::Instance();

    void initWindow(int width, int height, bool isFullScreen);
    void initGL();
    void initResources();
};
