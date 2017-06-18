#pragma once

#include <GL/glew.h>
#include "game/GameState.h"
#include "graphics/SpriteRenderer.h"
#include "ResourceManager.h"
#include "input/InputManager.h"
#include "WindowManager.h"
#include "Window.h"
#include "game/GameLevel.h"
#include "game/Player.h"
#include "game/Ball.h"
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
    GameState gameState_;
    Window* window_;
    std::vector<std::unique_ptr<GameLevel>> levels_;
    int currentLevel_;

    std::unique_ptr<Player> player_;
    std::unique_ptr<Ball> ball_;

    WindowManager& windowManager_ = WindowManager::Instance();
    InputManager& inputManager_ = InputManager::Instance();
    ResourceManager& resourceManager_ = ResourceManager::Instance();

    SpriteRenderer& spriteRenderer_ = SpriteRenderer::Instance();

    void initWindow(int width, int height, bool isFullScreen);
    void initGL();
    void initResources();

    void checkCollisions();
};
