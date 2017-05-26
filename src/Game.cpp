#include "Game.h"
#include "GameState.h"
#include "ResourceManager.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "ShaderType.h"
#include "Window.h"
#include "Direction.h"
#include "Collision.h"
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tuple>
#include <cmath>
#include <iostream>

const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
float INITIAL_PLAYER_VELOCITY = 500.0f;

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
    this->checkCollisions();
}

void Game::render() {
    if (gameState_ == GameState::GAME_ACTIVE) {
        spriteRenderer_.renderSprite(resourceManager_.texture("background"),
                                     glm::vec2(0.0f, 0.0f),
                                     glm::vec2(window_->width(), window_->height()));

        levels_[currentLevel_]->render(spriteRenderer_);
        player_->render(spriteRenderer_);
        ball_->render(spriteRenderer_);
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
    auto shader = resourceManager_.createShaderProgram("sprite",
                                                            Shader(ShaderType::VERTEX,
                                                                   "../resources/shaders/sprite/shader.vert"),
                                                            Shader(ShaderType::FRAGMENT,
                                                                   "../resources/shaders/sprite/shader.frag"));
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(window_->width()),
                                      static_cast<GLfloat>(window_->height()), 0.0f,
                                      -1.0f, 1.0f);
    shader->use();
    shader->setUniform("projection", projection);
    shader->setUniform("image", 0);

    spriteRenderer_.init(shader);

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

    levels_.push_back(std::shared_ptr<GameLevel>(new GameLevel(
            "../resources/levels/1.txt", window_->width(), window_->height() / 2)));
    levels_.push_back(std::shared_ptr<GameLevel>(new GameLevel(
            "../resources/levels/2.txt", window_->width(), window_->height() / 2)));
    levels_.push_back(std::shared_ptr<GameLevel>(new GameLevel(
            "../resources/levels/3.txt", window_->width(), window_->height() / 2)));
    levels_.push_back(std::shared_ptr<GameLevel>(new GameLevel(
            "../resources/levels/4.txt", window_->width(), window_->height() / 2)));
    currentLevel_ = 2;

    glm::vec2 playerSize = glm::vec2(120, 20);
    glm::vec2 playerPosition = glm::vec2(
            window_->width() / 2 - playerSize.x / 2,
            window_->height() - playerSize.y
    );

    player_ = std::shared_ptr<Player>(new Player(playerPosition,
                                                      playerSize,
                                                      glm::vec3(1.0f),
                                                      resourceManager_.texture("paddle"),
                                                      INITIAL_PLAYER_VELOCITY,
                                                      glm::vec2(0, window_->width() - playerSize.x)
                                           )
    );

    float ballRadius = 15.0f;

    ball_ = std::shared_ptr<Ball>(new Ball(playerPosition + glm::vec2(playerSize.x / 2 - ballRadius,
                                                                           -2 * ballRadius),
                                                ballRadius,
                                                glm::vec3(1.0f),
                                                resourceManager_.texture("face"),
                                                INITIAL_BALL_VELOCITY,
                                                glm::vec4(0.0f, window_->width(), 0.0f, window_->height())
                                       )
    );
}

Direction Game::getVectorDirection(const glm::vec2& target) {
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f),	// left
        glm::vec2(1.0f, 0.0f)	// right
    };

    float max = 0.0f;
    int bestMatch = -1;
    for (GLuint i = 0; i < 4; i++) {
        float dotProduct = glm::dot(glm::normalize(target), compass[i]);
        if (dotProduct > max) {
            max = dotProduct;
            bestMatch = i;
        }
    }

    return static_cast<Direction>(bestMatch);
}

// AABB - Circle collision
Collision Game::checkCollision(const Ball& ball, const GameObject& gameObject) {
    // Get center point circle first
    glm::vec2 center = ball.position() + ball.radius();
    // Calculate AABB info (center, half-extents)
    glm::vec2 aabbHalfExtents(gameObject.size().x / 2, gameObject.size().y / 2);
    glm::vec2 aabbCenter(
        gameObject.position().x + aabbHalfExtents.x,
        gameObject.position().y + aabbHalfExtents.y
    );
    // Get difference vector between both centers
    glm::vec2 difference = center - aabbCenter;
    glm::vec2 clamped = glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents);
    // Add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabbCenter + clamped;
    // Retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;

    return glm::length(difference) <= ball.radius() ?
               std::make_tuple(true, this->getVectorDirection(difference), difference) :
               std::make_tuple(false, Direction::UP, glm::vec2(0, 0));
}

void Game::checkCollisions() {
    for (Brick& brick : levels_[currentLevel_]->bricks()) {
        if (brick.isDestroyed()) continue;

        Collision collision = this->checkCollision(*ball_, brick);
        if (!std::get<0>(collision)) continue;      // if there is no collision...

        if (!brick.isSolid()) {
            brick.isDestroyed(true);
        }

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

    Collision collision = this->checkCollision(*ball_, *player_);
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