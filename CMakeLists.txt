cmake_minimum_required(VERSION 3.2)
project(breakout)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCES src/main.cpp src/WindowManager.cpp src/WindowManager.h src/Window.cpp src/Window.h src/Shader.cpp src/Shader.h src/ShaderType.h src/ShaderProgram.cpp src/ShaderProgram.h src/FileManager.cpp src/FileManager.h src/Texture.cpp src/Texture.h src/ResourceManager.cpp src/ResourceManager.h src/InputManager.cpp src/InputManager.h src/EventHandlers.h src/Game.cpp src/Game.h src/GameState.h src/SpriteRenderer.cpp src/SpriteRenderer.h src/Singleton.h src/GameObject.cpp src/GameObject.h src/Brick.cpp src/Brick.h src/GameLevel.cpp src/GameLevel.h src/Player.cpp src/Player.h)

# GLFW build configuration

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(externals/glfw)

# end
# ------------------------
# GLEW build configuration

add_subdirectory(externals/glew)
include_directories(externals/glew/include)
add_library(glew STATIC externals/glew/src/glew.c)
add_definitions(-DGLEW_STATIC)

# end
# ------------------------
# Header-only libraries

include_directories(externals/glm)
include_directories(externals/stb)

# end

add_executable(breakout ${SOURCES})

target_link_libraries(breakout glfw glew ${OPENGL_LIBRARY})
