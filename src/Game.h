#pragma once

#include "game/GameState.h"
#include "graphics/SpriteRenderer.h"
#include "graphics/TextRenderer.h"
#include "ResourceManager.h"
#include "input/InputManager.h"
#include "WindowManager.h"
#include "audio/AudioManager.h"
#include "Window.h"
#include "game/GameLevel.h"
#include "game/PowerUp.h"
#include "game/Player.h"
#include "game/Ball.h"
#include "graphics/ParticleEmitter.h"
#include "graphics/PostProcessor.h"
#include <GL/glew.h>
#include <memory>
#include <vector>

class Game {
public:
    Game(int width, int height, bool isFullScreen);
    ~Game();

    void input(GLfloat delta);
    void update(GLfloat delta);
    void render();

    void reset();

    bool isExiting() const;
private:
    GameState gameState_;
    GLint lives_;
    Window* window_;
    glm::vec2 scales_;
    std::vector<std::unique_ptr<GameLevel>> levels_;
    GLint currentLevel_;
    std::vector<std::unique_ptr<PowerUp>> powerUps_;

    std::unique_ptr<Player> player_;
    std::unique_ptr<Ball> ball_;

    WindowManager& windowManager_ = WindowManager::Instance();
    InputManager& inputManager_ = InputManager::Instance();
    ResourceManager& resourceManager_ = ResourceManager::Instance();
    AudioManager& audioManager_ = AudioManager::Instance();

    SpriteRenderer& spriteRenderer_ = SpriteRenderer::Instance();
    TextRenderer& textRenderer_ = TextRenderer::Instance();

    std::unique_ptr<ParticleEmitter> particleEmitter_;
    std::unique_ptr<PostProcessor> postProcessor_;

    void initWindow(int width, int height, bool isFullScreen);
    void initGL();
    void initResources();

    void checkCollisions();
    void spawnPowerUps(const Brick& brick);
};
