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
#include "Direction.h"
#include "Collision.h"
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

    Direction getVectorDirection(const glm::vec2& target);
    Collision checkCollision(const Ball& ball, const GameObject& brick);
    void checkCollisions();
};
