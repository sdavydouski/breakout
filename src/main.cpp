// glew header must be included before glfw header
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"

const int width = 800;
const int height = 600;
bool isFullScreen = false;

//const int width = 1920;
//const int height = 1080;
//bool isFullScreen = true;

int main(int argc, char* argv[]) {
    Game breakout(width, height, isFullScreen);

    GLfloat delta;
    auto lastFrame = static_cast<GLfloat>(glfwGetTime());

    while (!breakout.isExiting()) {
        // Calculate delta time
        auto currentFrame = static_cast<GLfloat>(glfwGetTime());
        delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        breakout.input(delta);
        breakout.update(delta);
        breakout.render();
    }

    return EXIT_SUCCESS;
}
