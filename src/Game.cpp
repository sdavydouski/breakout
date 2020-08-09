#include "Game.h"
#include "graphics/ShaderProgram.h"
#include "graphics/PostProcessingEffect.h"
#include "Window.h"
#include "physics/Collision.h"
#include "physics/Direction.h"
#include "physics/CollisionDetector.h"
#include "utils/Random.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GLFW/glfw3.h"
#include "AssetsLoader.h"
#include <tuple>
#include <algorithm>

const int GAME_WIDTH = 960;
const int GAME_HEIGHT = 540;

const int LIVES = 5;

const glm::vec2 INITIAL_BALL_VELOCITY(200.0f, -550.0f);
const float INITIAL_PLAYER_VELOCITY = 600.0f;
const glm::vec2 PLAYER_SIZE = glm::vec2(150, 20);
const float BALL_RADIUS = 10.0f;

GLfloat shakeTime = 0.0f;

Game::Game(int width, int height, bool isFullScreen)
    : gameState_(GameState::GAME_MENU), lives_(LIVES), scales_(static_cast<float>(width) / GAME_WIDTH,
                                                               static_cast<float>(height) / GAME_HEIGHT) {
    windowManager_.startUp();
    inputManager_.startUp();
    resourceManager_.startUp();
    audioManager_.startUp();

    this->initWindow(width, height, isFullScreen);
    this->initGL();
    this->initResources();
    audioManager_.playSource("background");
}

Game::~Game() {
    audioManager_.shutDown();
    resourceManager_.shutDown();
    inputManager_.shutDown();
    windowManager_.shutDown();
}

void Game::input(GLfloat delta) {
    inputManager_.pollEvents(delta);

    switch(gameState_) {
    case GameState::GAME_MENU: {
        if (inputManager_.isKeyPressed(GLFW_KEY_ENTER) && !inputManager_.isKeyProcessed(GLFW_KEY_ENTER)) {
            inputManager_.setProcessedKey(GLFW_KEY_ENTER);
            gameState_ = GameState::GAME_ACTIVE;
        } else if (inputManager_.isKeyPressed(GLFW_KEY_W) && !inputManager_.isKeyProcessed(GLFW_KEY_W)) {
            inputManager_.setProcessedKey(GLFW_KEY_W);
            currentLevel_ = (currentLevel_ + 1) % levels_.size();
        } else if (inputManager_.isKeyPressed(GLFW_KEY_UP) && !inputManager_.isKeyProcessed(GLFW_KEY_UP)) {
            inputManager_.setProcessedKey(GLFW_KEY_UP);
            currentLevel_ = (currentLevel_ + 1) % levels_.size();
        } else if (inputManager_.isKeyPressed(GLFW_KEY_S) && !inputManager_.isKeyProcessed(GLFW_KEY_S)) {
            inputManager_.setProcessedKey(GLFW_KEY_S);
            currentLevel_ = currentLevel_ > 0 ? --currentLevel_ : levels_.size() - 1;
        } else if (inputManager_.isKeyPressed(GLFW_KEY_DOWN) && !inputManager_.isKeyProcessed(GLFW_KEY_DOWN)) {
            inputManager_.setProcessedKey(GLFW_KEY_DOWN);
            currentLevel_ = currentLevel_ > 0 ? --currentLevel_ : levels_.size() - 1;
        }
        break;
    }
    case GameState::GAME_ACTIVE: {
        auto velocity = player_->velocity() * delta;

        if (inputManager_.isKeyPressed(GLFW_KEY_A) || inputManager_.isKeyPressed(GLFW_KEY_LEFT)) {
            if (player_->position().x >= player_->boundaries().x) {
                player_->updatePositionX(-velocity);
                if (ball_->isStuck()) {
                    ball_->updatePositionX(-velocity);
                }
            }
        }
        if (inputManager_.isKeyPressed(GLFW_KEY_D) || inputManager_.isKeyPressed(GLFW_KEY_RIGHT)) {
            if (player_->position().x <= player_->boundaries().y) {
                player_->updatePositionX(velocity);
                if (ball_->isStuck()) {
                    ball_->updatePositionX(velocity);
                }
            }
        }

        if (inputManager_.isKeyPressed(GLFW_KEY_SPACE)) {
            ball_->isStuck(false);
        }
        break;
    }
    case GameState::GAME_WIN:
    case GameState::GAME_LOSE: {
        if (inputManager_.isKeyPressed(GLFW_KEY_ENTER) && !inputManager_.isKeyProcessed(GLFW_KEY_ENTER)) {
            inputManager_.setProcessedKey(GLFW_KEY_ENTER);
            gameState_ = GameState::GAME_MENU;
        }
        break;
    }}
}

void Game::update(GLfloat delta) {
    player_->boundaries(glm::vec2(0, window_->width() - player_->size().x));
    ball_->update(delta);
    particleEmitter_->update(delta, *ball_, 5, glm::vec2(ball_->radius() / 2));
    this->checkCollisions();

    if (shakeTime > 0.0f) {
        shakeTime -= delta;
        if (shakeTime <= 0.0f) {
            postProcessor_->disableEffects(PostProcessingEffect::Shake);
        }
    }

    for (auto& powerUp: powerUps_) {
        powerUp->update(delta, *player_.get(), *ball_.get(), *postProcessor_.get());
    }
    powerUps_.erase(std::remove_if(powerUps_.begin(), powerUps_.end(),
            [](std::unique_ptr<PowerUp> const& powerUp) { return powerUp->isDestroyed() && !powerUp->isActivated(); }
        ),
        powerUps_.end());

    if (gameState_ == GameState::GAME_ACTIVE && levels_[currentLevel_]->isCompleted()) {
        this->reset();
        gameState_ = GameState::GAME_WIN;
    }

    if (ball_->position().y >= window_->height() - ball_->size().y) {
        lives_--;
        if (lives_ < 0) {
            this->reset();
            postProcessor_->enableEffects(PostProcessingEffect::Chaos);
            gameState_ = GameState::GAME_LOSE;
        }
    }
}

void Game::render() {
    if (gameState_ == GameState::GAME_ACTIVE || gameState_ == GameState::GAME_MENU) {
        postProcessor_->beginRender();

        spriteRenderer_.renderSprite(resourceManager_.texture("background"),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(window_->width(), window_->height())
        );

        levels_[currentLevel_]->render(spriteRenderer_);
        player_->render(spriteRenderer_);
        particleEmitter_->render(ball_->radius());
        ball_->render(spriteRenderer_);

        for (auto& powerUp : powerUps_) {
            if (!powerUp->isDestroyed()) {
                powerUp->render(spriteRenderer_);
            }
        }
    }

    textRenderer_.renderText("Lives: " + std::to_string(lives_),
        glm::vec2(10.0f, 30.f) * scales_,
        glm::vec3(1.0f), 0.6f * glm::length(scales_));

    postProcessor_->endRender();
    postProcessor_->render(static_cast<GLfloat>(glfwGetTime()), glm::length(scales_));

    if (gameState_ == GameState::GAME_MENU) {
        postProcessor_->disableEffects(PostProcessingEffect::Chaos);
        textRenderer_.renderText("Press ENTER to start", 
                                 glm::vec2(GAME_WIDTH / 2 - 240, GAME_HEIGHT / 2 - 20) * scales_, 
                                 glm::vec3(1.0f), 0.6f * glm::length(scales_));
        textRenderer_.renderText("Press W or S to select level", 
                                 glm::vec2(GAME_WIDTH / 2 - 215, GAME_HEIGHT / 2 + 20) * scales_, 
                                 glm::vec3(1.0f), 0.4f * glm::length(scales_));
    } else if (gameState_ == GameState::GAME_WIN) {
        textRenderer_.renderText("You WON!!!", 
                                 glm::vec2(GAME_WIDTH / 2 - 110, GAME_HEIGHT / 2) * scales_, 
                                 glm::vec3(0.0f, 1.0f, 0.0f), 0.7f * glm::length(scales_));
        textRenderer_.renderText("Press ENTER to retry or ESC to quit", 
                                 glm::vec2(GAME_WIDTH / 2 - 260, GAME_HEIGHT / 2 + 20) * scales_, 
                                 glm::vec3(1.0f, 1.0f, 0.0f), 0.4f * glm::length(scales_));
    } else if (gameState_ == GameState::GAME_LOSE) {
        textRenderer_.renderText("You LOST...", 
                                 glm::vec2(GAME_WIDTH / 2 - 110, GAME_HEIGHT / 2) * scales_, 
                                 glm::vec3(1.0f, 0.0f, 0.0f), 0.7f * glm::length(scales_));
        textRenderer_.renderText("Press ENTER to retry or ESC to quit", 
                                 glm::vec2(GAME_WIDTH / 2 - 260, GAME_HEIGHT / 2 + 20) * scales_, 
                                 glm::vec3(1.0f, 1.0f, 0.0f), 0.4f * glm::length(scales_));
    }

    window_->swapBuffers();
}

void Game::reset() {
    levels_[currentLevel_]->reset();
    
    auto playerSize = PLAYER_SIZE * scales_;
    auto playerPosition = glm::vec2(
        window_->width() / 2 - playerSize.x / 2,
        window_->height() - playerSize.y
    );
    player_->size(playerSize);
    player_->position(playerPosition);
    player_->color(glm::vec3(1.0f));
    
    auto ballRadius = BALL_RADIUS * glm::length(scales_);
    ball_->position(playerPosition + glm::vec2(playerSize.x / 2 - ballRadius, -2 * ballRadius));
    ball_->color(glm::vec3(1.0f));
    ball_->velocity(INITIAL_BALL_VELOCITY * scales_);
    ball_->isStuck(true);
    ball_->isSticky(false);
    ball_->isPassingThrough(false);
    
    postProcessor_->disableEffects(PostProcessingEffect::Chaos | 
                                   PostProcessingEffect::Confuse | 
                                   PostProcessingEffect::Shake);

    powerUps_.clear();

    lives_ = LIVES;
}

bool Game::isExiting() const {
    return window_->isClosing();
}

void Game::initWindow(int width, int height, bool isFullScreen) {
    window_ = windowManager_.createWindow(width, height, "Breakout", isFullScreen);

    inputManager_.addKeyHandler("exit", [this](float delta) {
        if (inputManager_.isKeyPressed(GLFW_KEY_ESCAPE)) {
            window_->setIsShouldClose(true);
        }
    });
}

void Game::initGL() {
    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::initResources() {
    AssetsLoader::loadShaders();

    auto spriteShader = resourceManager_.shaderProgram("sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(window_->width()),
                                      static_cast<GLfloat>(window_->height()), 0.0f,
                                      -1.0f, 1.0f);
    spriteShader->use();
    spriteShader->setUniform("projection", projection);
    spriteShader->setUniform("sprite", 0);

    spriteRenderer_.init(spriteShader);

    auto textRenderingShader = resourceManager_.shaderProgram("text");
    textRenderingShader->use();
    textRenderingShader->setUniform("projection", projection);
    textRenderer_.init(AssetsLoader::OFFSET + "resources/fonts/PixelScreen.ttf", textRenderingShader);

    auto particleShader = resourceManager_.shaderProgram("particle");
    particleShader->use();
    particleShader->setUniform("projection", projection);
    particleShader->setUniform("sprite", 0);

    AssetsLoader::loadTextures();
    AssetsLoader::loadAudioFiles();

    particleEmitter_ = std::make_unique<ParticleEmitter>(resourceManager_.shaderProgram("particle"),
                                                         resourceManager_.texture("particle"),
                                                         500);
    auto framebufferSize = window_->getFramebufferSize();
    postProcessor_ = std::make_unique<PostProcessor>(resourceManager_.shaderProgram("postprocessing"),
                                                     framebufferSize.width, framebufferSize.height);

    levels_.push_back(std::make_unique<GameLevel>(
        AssetsLoader::OFFSET + "resources/levels/1.txt", window_->width(), window_->height() / 2));
    levels_.push_back(std::make_unique<GameLevel>(
        AssetsLoader::OFFSET + "resources/levels/2.txt", window_->width(), window_->height() / 2));
    levels_.push_back(std::make_unique<GameLevel>(
        AssetsLoader::OFFSET + "resources/levels/3.txt", window_->width(), window_->height() / 2));
    levels_.push_back(std::make_unique<GameLevel>(
        AssetsLoader::OFFSET + "resources/levels/4.txt", window_->width(), window_->height() / 2));
    currentLevel_ = 0;

    auto playerSize = PLAYER_SIZE * scales_;
    auto playerPosition = glm::vec2(
        window_->width() / 2 - playerSize.x / 2,
        window_->height() - playerSize.y
    );

    player_ = std::make_unique<Player>(playerPosition,
                                       playerSize,
                                       glm::vec3(1.0f),
                                       resourceManager_.texture("paddle"),
                                       INITIAL_PLAYER_VELOCITY * scales_.x,
                                       glm::vec2(0, window_->width() - playerSize.x));

    auto ballRadius = BALL_RADIUS * glm::length(scales_);

    ball_ = std::make_unique<Ball>(playerPosition + glm::vec2(playerSize.x / 2 - ballRadius, -2 * ballRadius),
                                   ballRadius,
                                   glm::vec3(1.0f),
                                   resourceManager_.texture("ball"),
                                   INITIAL_BALL_VELOCITY * scales_,
                                   glm::vec4(0.0f, window_->width(), 0.0f, window_->height()));
}

void Game::checkCollisions() {
    // check collisions with the bricks
    for (auto& brick : levels_[currentLevel_]->bricks()) {
        if (brick->isDestroyed()) continue;

        auto collision = CollisionDetector::checkCollision(*ball_, *brick.get());
        if (!std::get<0>(collision)) continue;      // if there is no collision...

        if (brick->isSolid()) {
            audioManager_.playSource("solid");
            shakeTime = 0.2f;
            postProcessor_->enableEffects(PostProcessingEffect::Shake);
        } else {
            audioManager_.playSource("bleep");
            brick->isDestroyed(true);
            this->spawnPowerUps(*brick);
        }

        if (ball_->isPassingThrough()) continue;

        // Collision resolution
        auto direction = std::get<1>(collision);
        auto difference = std::get<2>(collision);

        if (direction == Direction::LEFT || direction == Direction::RIGHT) {
			ball_->velocityX(-ball_->velocity().x);        // Reverse horizontal velocity
            // Relocate
            auto penetration = ball_->radius() - std::abs(difference.x);
            if (direction == Direction::LEFT) {
				ball_->updatePositionX(penetration);       // Move ball to right
            } else {
				ball_->updatePositionX(-penetration);      // Move ball to left
            }
        } else {
            ball_->velocityY(-ball_->velocity().y);
            auto penetration = ball_->radius() - std::abs(difference.y);
            if (direction == Direction::UP) {
				ball_->updatePositionY(-penetration);      // Move ball back up
            } else {
                ball_->updatePositionY(penetration);       // Move ball back down
            }
        }
    }

    // check collision with the paddle
    auto collision = CollisionDetector::checkCollision(*ball_, *player_);
    if (std::get<0>(collision) && !ball_->isStuck()) {
        audioManager_.playSource("bleepPaddle");
        // Check where it hit the board, and change velocity based on where it hit the board
        auto centerBoard = player_->position().x + player_->size().x / 2;
        auto distance = (ball_->position().x + ball_->radius()) - centerBoard;
        auto percentage = distance / (player_->size().x / 2);

        // Then move accordingly
        auto strength = 2.0f;
        glm::vec2 oldVelocity = ball_->velocity();
        ball_->velocityX(INITIAL_BALL_VELOCITY.x * scales_.x * percentage * strength);
        ball_->velocityY(-1 * std::abs(ball_->velocity().y));
        ball_->velocity(glm::normalize(ball_->velocity()) * glm::length(oldVelocity));

        ball_->isStuck(ball_->isSticky());
    }

    // check collision between powerups and the paddle
    for (auto& powerup : powerUps_) {
        if (powerup->isDestroyed()) continue;

        if (powerup->position().y >= window_->height()) {
            powerup->isDestroyed(true);
        }

        if (CollisionDetector::checkCollision(*player_, *powerup.get())) {
            audioManager_.playSource("powerup");
            powerup->activate(*player_.get(), *ball_.get(), *postProcessor_.get(), scales_);
        }
    }
}

void Game::spawnPowerUps(const Brick& brick) {
    auto size = glm::vec2(30, 60) * scales_;
    auto velocity = glm::vec2(0.0f, 150.0f) * scales_;

    if (Random::chance(50)) {   // 1 in 50 chance
        powerUps_.push_back(std::make_unique<PowerUp>(brick.position(), size, glm::vec3(0.5f, 0.5f, 1.0f), 
            resourceManager_.texture("powerUp"), velocity, PowerUpType::SpeedUp, 0.0f));
    }
    if (Random::chance(50)) {
        powerUps_.push_back(std::make_unique<PowerUp>(brick.position(), size, glm::vec3(1.0f, 0.5f, 1.0f), 
            resourceManager_.texture("powerUp"), velocity, PowerUpType::Sticky, 20.0f));
    }
    if (Random::chance(50)) {
        powerUps_.push_back(std::make_unique<PowerUp>(brick.position(), size, glm::vec3(0.5f, 1.0f, 0.5f), 
            resourceManager_.texture("powerUp"), velocity, PowerUpType::PassThrough, 10.0f));
    }
    if (Random::chance(50)) {
        powerUps_.push_back(std::make_unique<PowerUp>(brick.position(), size, glm::vec3(1.0f, 0.6f, 0.4), 
            resourceManager_.texture("powerUp"), velocity, PowerUpType::PadSizeIncrease, 0.0f));
    }

    // Negative powerups should spawn more often
    if (Random::chance(15)) {
        powerUps_.push_back(std::make_unique<PowerUp>(brick.position(), size, glm::vec3(1.0f, 0.3f, 0.3f), 
            resourceManager_.texture("powerUp"), velocity, PowerUpType::Confuse, 15.0f));
    }
    if (Random::chance(15)) {
        powerUps_.push_back(std::make_unique<PowerUp>(brick.position(), size, glm::vec3(0.9f, 0.25f, 0.25f), 
            resourceManager_.texture("powerUp"), velocity, PowerUpType::Chaos, 15.0f));
    }
}
