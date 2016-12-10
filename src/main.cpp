// glew header must be included before glfw header
#include <GL/glew.h>
#include "WindowManager.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

WindowManager& windowManager = WindowManager::Instance();

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* argv[]) {
    windowManager.startUp();
    auto window = windowManager.createWindow(WIDTH, HEIGHT, "Breakout");

    glewExperimental = GL_TRUE;
    glewInit();

    // Creating a triangle...
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    // ...Setting up buffers...
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // ...Preparing shaders...
    const GLchar* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main() {\n"
        "gl_Position = vec4(position.x, position.y, position.z, 1.f);\n"
    "}\0";
    const GLchar* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main() {\n"
        "color = vec4(0.f, 0.75f, 1.f, 1.f);\n"
    "}\n\0";

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while(!window->isClosing()) {
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        window->swapBuffers();
    }

    // Clean up all the resources
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    windowManager.shutDown();

    return EXIT_SUCCESS;
}
