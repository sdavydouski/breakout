// glew header must be included before glfw header
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "WindowManager.h"
#include "FileManager.h"
#include "Window.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "ShaderType.h"
#include "Texture.h"

WindowManager& windowManager = WindowManager::Instance();
FileManager& fileManager = FileManager::Instance();

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* argv[]) {
    windowManager.startUp();
    auto window = windowManager.createWindow(WIDTH, HEIGHT, "Breakout");

    glewExperimental = GL_TRUE;
    glewInit();

    // Rectangle
    GLfloat vertices[] = {
            // Positions         // Texture coordinates
            0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // Top right
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // Bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // Bottom left
            -0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // Top left
    };
    GLuint indices[] = {
            0, 1, 3, // First triangle
            1, 2, 3  // Second triangle
    };

    // Setting up buffers
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ShaderProgram shader(
        Shader(ShaderType::VERTEX, fileManager.readAsText("../resources/shaders/basic/shader.vert")),
        Shader(ShaderType::FRAGMENT, fileManager.readAsText("../resources/shaders/basic/shader.frag"))
    );

    GLuint textureWidth = 512;
    GLuint textureHeight = 512;
    Texture woodenContainer(textureWidth,
                            textureHeight,
                            fileManager.readImage("../resources/textures/wooden_container.jpg",
                                                   textureWidth, textureHeight, 3),
                            GL_RGB);
    Texture awesomeFace(textureWidth,
                        textureHeight,
                        fileManager.readImage("../resources/textures/awesome_face.png",
                                              textureWidth, textureHeight, 4),
                        GL_RGBA);

    while (!window->isClosing()) {
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        woodenContainer.bind(0);
        shader.setUniform("texture1", 0);
        awesomeFace.bind(1);
        shader.setUniform("texture2", 1);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        window->swapBuffers();
    }

    // Clean up all the resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    windowManager.shutDown();

    return EXIT_SUCCESS;
}
