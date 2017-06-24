#include "Game.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Shader.h"
#include "graphics/ShaderType.h"
#include "Window.h"
#include "physics/Collision.h"
#include "physics/Direction.h"
#include "physics/CollisionDetector.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tuple>
#include <cmath>
#include <iostream>

const glm::vec2 INITIAL_BALL_VELOCITY(200.0f, -550.0f);
float INITIAL_PLAYER_VELOCITY = 500.0f;

GLfloat shakeTime = 0.0f;

Game::Game(int width, int height, bool isFullScreen)
    : gameState_(GameState::GAME_ACTIVE) {
    std::cout << "Game constructor" << std::endl;

    windowManager_.startUp();
    inputManager_.startUp();
    resourceManager_.startUp();

    this->initWindow(width, height, isFullScreen);
    this->initGL();
    this->initResources();
}

Game::~Game() {
    std::cout << "Game destructor" << std::endl;

    resourceManager_.shutDown();
    inputManager_.shutDown();
    windowManager_.shutDown();
}

void Game::input(GLfloat delta) {
    inputManager_.pollEvents(delta);
    float velocity = player_->velocity() * delta;

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
}

void Game::update(GLfloat delta) {
    ball_->update(delta);
    particleEmitter_->update(delta, *ball_, 5, glm::vec2(ball_->radius() / 2));
    this->checkCollisions();

    if (shakeTime > 0.0f) {
        shakeTime -= delta;
        if (shakeTime <= 0.0f) {
            postProcessor_->disableEffects(PostProcessingEffect::Shake);
        }
    }
}

void Game::render() {
    if (gameState_ == GameState::GAME_ACTIVE) {
        postProcessor_->beginRender();

        spriteRenderer_.renderSprite(resourceManager_.texture("background"),
                                     glm::vec2(0.0f, 0.0f),
                                     glm::vec2(window_->width(), window_->height()));

        levels_[currentLevel_]->render(spriteRenderer_);
        player_->render(spriteRenderer_);
        particleEmitter_->render();
        ball_->render(spriteRenderer_);

        postProcessor_->endRender();
        postProcessor_->render(glfwGetTime());
    }

    window_->swapBuffers();
}

bool Game::isExiting() {
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
    auto spriteShader = resourceManager_.createShaderProgram("sprite",
                                                             Shader(ShaderType::VERTEX,
                                                                     "../resources/shaders/sprite/shader.vert"),
                                                             Shader(ShaderType::FRAGMENT,
                                                                     "../resources/shaders/sprite/shader.frag"));
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(window_->width()),
                                      static_cast<GLfloat>(window_->height()), 0.0f,
                                      -1.0f, 1.0f);
    spriteShader->use();
    spriteShader->setUniform("projection", projection);
    spriteShader->setUniform("sprite", 0);

    spriteRenderer_.init(spriteShader);

    auto particleShader = resourceManager_.createShaderProgram("particle",
                                                               Shader(ShaderType::VERTEX,
                                                                      "../resources/shaders/particle/shader.vert"),
                                                               Shader(ShaderType::FRAGMENT,
                                                                      "../resources/shaders/particle/shader.frag"));
    particleShader->use();
    particleShader->setUniform("projection", projection);
    particleShader->setUniform("sprite", 0);

    resourceManager_.createShaderProgram("postprocessing",
                                         Shader(ShaderType::VERTEX,
                                                "../resources/shaders/postprocessing/shader.vert"),
                                         Shader(ShaderType::FRAGMENT,
                                                "../resources/shaders/postprocessing/shader.frag"));

    resourceManager_.createTexture("background",
                                   "../resources/textures/background.jpg",
                                   1600, 900);
    resourceManager_.createTexture("face",
                                   "../resources/textures/awesome_face.png",
                                   512, 512, 4, GL_RGBA);
    resourceManager_.createTexture("block",
                                   "../resources/textures/block.png",
                                   128, 128);
    resourceManager_.createTexture("block_solid",
                                   "../resources/textures/block_solid.png",
                                   128, 128);
    resourceManager_.createTexture("paddle",
                                   "../resources/textures/paddle.png",
                                   512, 128, 4, GL_RGBA);
    resourceManager_.createTexture("particle",
                                   "../resources/textures/particle.png",
                                   500, 500, 4, GL_RGBA);

    particleEmitter_ = std::make_unique<ParticleEmitter>(resourceManager_.shaderProgram("particle"),
                                                         resourceManager_.texture("particle"),
                                                         500);
    postProcessor_ = std::make_unique<PostProcessor>(resourceManager_.shaderProgram("postprocessing"),
                                                     window_->width(), window_->height());

    levels_.push_back(std::make_unique<GameLevel>(
        "../resources/levels/1.txt", window_->width(), window_->height() / 2));
    levels_.push_back(std::make_unique<GameLevel>(
        "../resources/levels/2.txt", window_->width(), window_->height() / 2));
    levels_.push_back(std::make_unique<GameLevel>(
        "../resources/levels/3.txt", window_->width(), window_->height() / 2));
    levels_.push_back(std::make_unique<GameLevel>(
        "../resources/levels/4.txt", window_->width(), window_->height() / 2));
    currentLevel_ = 0;

    glm::vec2 playerSize = glm::vec2(120, 20);
    glm::vec2 playerPosition = glm::vec2(
            window_->width() / 2 - playerSize.x / 2,
            window_->height() - playerSize.y
    );

    player_ = std::make_unique<Player>(playerPosition,
                                       playerSize,
                                       glm::vec3(1.0f),
                                       resourceManager_.texture("paddle"),
                                       INITIAL_PLAYER_VELOCITY,
                                       glm::vec2(0, window_->width() - playerSize.x));

    float ballRadius = 15.0f;

    ball_ = std::make_unique<Ball>(playerPosition + glm::vec2(playerSize.x / 2 - ballRadius, -2 * ballRadius),
                                   ballRadius,
                                   glm::vec3(1.0f),
                                   resourceManager_.texture("face"),
                                   INITIAL_BALL_VELOCITY,
                                   glm::vec4(0.0f, window_->width(), 0.0f, window_->height()));
}

void Game::checkCollisions() {
    // check collisions with the bricks
    for (auto& brick : levels_[currentLevel_]->bricks()) {
        if (brick->isDestroyed()) continue;

        Collision collision = CollisionDetector::checkCollision(*ball_, *brick.get());
        if (!std::get<0>(collision)) continue;      // if there is no collision...

        if (!brick->isSolid()) {
            brick->isDestroyed(true);
        }

        shakeTime = 0.2f;
        postProcessor_->enableEffects(PostProcessingEffect::Shake);

        // Collision resolution
        Direction direction = std::get<1>(collision);
        glm::vec2 difference = std::get<2>(collision);

        if (direction == Direction::LEFT || direction == Direction::RIGHT) {
			ball_->velocityX(-ball_->velocity().x);        // Reverse horizontal velocity
            // Relocate
            float penetration = ball_->radius() - std::abs(difference.x);
            if (direction == Direction::LEFT) {
				ball_->updatePositionX(penetration);       // Move ball to right
            } else {
				ball_->updatePositionX(-penetration);      // Move ball to left
            }
        } else {
            ball_->velocityY(-ball_->velocity().y);
            float penetration = ball_->radius() - std::abs(difference.y);
            if (direction == Direction::UP) {
				ball_->updatePositionY(-penetration);      // Move ball back up
            } else {
                ball_->updatePositionY(penetration);       // Move ball back down
            }
        }
    }

    // check collision with the paddle
    Collision collision = CollisionDetector::checkCollision(*ball_, *player_);
    if (std::get<0>(collision) && !ball_->isStuck()) {
        // Check where it hit the board, and change velocity based on where it hit the board
        float centerBoard = player_->position().x + player_->size().x / 2;
        float distance = (ball_->position().x + ball_->radius()) - centerBoard;
        float percentage = distance / (player_->size().x / 2);

        // Then move accordingly
        float strength = 2.0f;
        glm::vec2 oldVelocity = ball_->velocity();
        ball_->velocityX(INITIAL_BALL_VELOCITY.x * percentage * strength);
        ball_->velocityY(-1 * std::abs(ball_->velocity().y));
        ball_->velocity(glm::normalize(ball_->velocity()) * glm::length(oldVelocity));
    }
}
