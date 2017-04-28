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

Game::Game(std::shared_ptr<Window> window)
    : window(window), gameState(GameState::GAME_ACTIVE) {
    std::cout << "Game constructor" << std::endl;

    this->initGL();
    this->init(this->window->getWidth(), this->window->getHeight());
}

Game::~Game() {
    std::cout << "Game destructor" << std::endl;
}

void Game::input(GLfloat delta) {
    this->inputManager.pollEvents();
}

void Game::update(GLfloat delta) {

}

void Game::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->spriteRenderer.renderSprite(this->resourceManager.getTexture("awesomeFace"),
                                      glm::vec2(200, 200),
                                      glm::vec2(300, 400),
                                      glm::vec3(0.0f, 1.0f, 0.0f),
                                      glm::radians(45.0f));

    this->window->swapBuffers();
}

void Game::init(int width, int height) {
    auto shader = this->resourceManager.createShaderProgram("sprite",
                                                            Shader(ShaderType::VERTEX,
                                                                   "../resources/shaders/sprite/shader.vert"),
                                                            Shader(ShaderType::FRAGMENT,
                                                                   "../resources/shaders/sprite/shader.frag"));
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width),
                                      static_cast<GLfloat>(height), 0.0f,
                                      -1.0f, 1.0f);
    shader->use();
    shader->setUniform("projection", projection);
    shader->setUniform("image", 0);

    this->spriteRenderer.init(shader);
    this->resourceManager.createTexture("awesomeFace",
                                        "../resources/textures/awesome_face.png",
                                        512, 512, 4, GL_RGBA);
}

void Game::initGL() {
    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
