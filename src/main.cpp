// glew header must be included before glfw header
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Singleton.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Game.h"

WindowManager& windowManager = WindowManager::Instance();
InputManager& inputManager = InputManager::Instance();
ResourceManager& resourceManager = ResourceManager::Instance();

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* argv[]) {
    windowManager.startUp();
    inputManager.startUp();
    resourceManager.startUp();

    auto window = windowManager.createWindow(WIDTH, HEIGHT, "Breakout");

    inputManager.addKeyHandler("exit", [&window](int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            window->setIsShouldClose(true);
        }
    });

    Game breakout(window);

    GLfloat delta;
    GLfloat lastFrame = (GLfloat) glfwGetTime();

    while (!window->isClosing()) {
        // Calculate delta time
        GLfloat currentFrame = (GLfloat) glfwGetTime();
        delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        breakout.input(delta);
        breakout.update(delta);
        breakout.render();
    }

    resourceManager.shutDown();
    inputManager.shutDown();
    windowManager.shutDown();

    return EXIT_SUCCESS;
}
