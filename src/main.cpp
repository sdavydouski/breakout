// glew header must be included before glfw header
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"

const int width = 1920;
const int height = 1080;
bool isFullScreen = true;

int main(int argc, char* argv[]) {
    Game breakout(width, height, isFullScreen);

    GLfloat delta;
    GLfloat lastFrame = (GLfloat) glfwGetTime();

    while (!breakout.isExiting()) {
        // Calculate delta time
        GLfloat currentFrame = (GLfloat) glfwGetTime();
        delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        breakout.input(delta);
        breakout.update(delta);
        breakout.render();
    }

    return EXIT_SUCCESS;
}
