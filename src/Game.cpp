#include "Game.h"
#include "GameState.h"
#include "ResourceManager.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "ShaderType.h"
#include "Window.h"
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Game::Game(int width, int height, bool isFullScreen)
    : gameState(GameState::GAME_ACTIVE) {
    std::cout << "Game constructor" << std::endl;

    this->windowManager.startUp();
    this->inputManager.startUp();
    this->resourceManager.startUp();

    this->initWindow(width, height, isFullScreen);
    this->initGL();
    this->initResources();
}

Game::~Game() {
    std::cout << "Game destructor" << std::endl;

    this->resourceManager.shutDown();
    this->inputManager.shutDown();
    this->windowManager.shutDown();
}

void Game::input(GLfloat delta) {
    this->inputManager.pollEvents(delta);

    if (this->inputManager.isKeyPressed(GLFW_KEY_A) || this->inputManager.isKeyPressed(GLFW_KEY_LEFT)) {
        if (this->player->position.x >= this->player->boundaries.x) {
            this->player->position.x -= this->player->velocity * delta;
            if (this->ball->isStuck) {
                this->ball->position.x -= this->player->velocity * delta;
            }
        }
    }
    if (this->inputManager.isKeyPressed(GLFW_KEY_D) || this->inputManager.isKeyPressed(GLFW_KEY_RIGHT)) {
        if (this->player->position.x <= this->player->boundaries.y) {
            this->player->position.x += this->player->velocity * delta;
            if (this->ball->isStuck) {
                this->ball->position.x += this->player->velocity * delta;
            }
        }
    }

    if (this->inputManager.isKeyPressed(GLFW_KEY_SPACE)) {
        this->ball->isStuck = false;
    }
}

void Game::update(GLfloat delta) {
    this->ball->move(glm::vec4(0.0f, this->window->getWidth(), 0.0f, this->window->getHeight()), delta);
}

void Game::render() {
    if (this->gameState == GameState::GAME_ACTIVE) {
        this->spriteRenderer.renderSprite(this->resourceManager.getTexture("background"),
                                          glm::vec2(0.0f, 0.0f),
                                          glm::vec2(this->window->getWidth(), this->window->getHeight()));

        this->levels[this->currentLevel]->render(this->spriteRenderer);
        this->player->render(this->spriteRenderer);
        this->ball->render(this->spriteRenderer);
    }

    this->window->swapBuffers();
}

bool Game::isExiting() {
    return this->window->isClosing();
}

void Game::initWindow(int width, int height, bool isFullScreen) {
    this->window = this->windowManager.createWindow(width, height, "Breakout", isFullScreen);

    this->inputManager.addKeyHandler("exit", [this](float delta) {
        if (this->inputManager.isKeyPressed(GLFW_KEY_ESCAPE)) {
            this->window->setIsShouldClose(true);
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
    auto shader = this->resourceManager.createShaderProgram("sprite",
                                                            Shader(ShaderType::VERTEX,
                                                                   "../resources/shaders/sprite/shader.vert"),
                                                            Shader(ShaderType::FRAGMENT,
                                                                   "../resources/shaders/sprite/shader.frag"));
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->window->getWidth()),
                                      static_cast<GLfloat>(this->window->getHeight()), 0.0f,
                                      -1.0f, 1.0f);
    shader->use();
    shader->setUniform("projection", projection);
    shader->setUniform("image", 0);

    this->spriteRenderer.init(shader);

    this->resourceManager.createTexture("background",
                                        "../resources/textures/background.jpg",
                                        1600, 900);
    this->resourceManager.createTexture("face",
                                        "../resources/textures/awesome_face.png",
                                        512, 512, 4, GL_RGBA);
    this->resourceManager.createTexture("block",
                                        "../resources/textures/block.png",
                                        128, 128);
    this->resourceManager.createTexture("block_solid",
                                        "../resources/textures/block_solid.png",
                                        128, 128);
    this->resourceManager.createTexture("paddle",
                                        "../resources/textures/paddle.png",
                                        512, 128, 4, GL_RGBA);

    this->levels.push_back(std::shared_ptr<GameLevel>(new GameLevel(
            "../resources/levels/1.txt", this->window->getWidth(), this->window->getHeight() / 2)));
    this->levels.push_back(std::shared_ptr<GameLevel>(new GameLevel(
            "../resources/levels/2.txt", this->window->getWidth(), this->window->getHeight() / 2)));
    this->levels.push_back(std::shared_ptr<GameLevel>(new GameLevel(
            "../resources/levels/3.txt", this->window->getWidth(), this->window->getHeight() / 2)));
    this->levels.push_back(std::shared_ptr<GameLevel>(new GameLevel(
            "../resources/levels/4.txt", this->window->getWidth(), this->window->getHeight() / 2)));
    this->currentLevel = 0;

    glm::vec2 playerSize = glm::vec2(120, 20);
    glm::vec2 playerPosition = glm::vec2(
            this->window->getWidth() / 2 - playerSize.x / 2,
            this->window->getHeight() - playerSize.y
    );

    this->player = std::shared_ptr<Player>(new Player(playerPosition,
                                                      playerSize,
                                                      glm::vec3(1.0f),
                                                      this->resourceManager.getTexture("paddle"),
                                                      500.0f,
                                                      glm::vec2(0, this->window->getWidth() - playerSize.x)
                                           )
    );

    float ballRadius = 15.0f;
    glm::vec2 ballVelocity = glm::vec2(200.0f, -500.0f);

    this->ball = std::shared_ptr<Ball>(new Ball(playerPosition + glm::vec2(playerSize.x / 2 - ballRadius,
                                                                           -2 * ballRadius),
                                                ballRadius,
                                                glm::vec3(1.0f),
                                                this->resourceManager.getTexture("face"),
                                                ballVelocity
                                       )
    );
}
