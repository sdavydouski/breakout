cmake_minimum_required(VERSION 3.2)
project(breakout)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCES src/main.cpp src/WindowManager.cpp src/WindowManager.h src/Window.cpp src/Window.h src/graphics/Shader.cpp src/graphics/Shader.h src/graphics/ShaderType.h src/graphics/ShaderProgram.cpp src/graphics/ShaderProgram.h src/utils/FileManager.cpp src/utils/FileManager.h src/graphics/Texture.cpp src/graphics/Texture.h src/ResourceManager.cpp src/ResourceManager.h src/input/InputManager.cpp src/input/InputManager.h src/input/EventHandlers.h src/Game.cpp src/Game.h src/game/GameState.h src/graphics/SpriteRenderer.cpp src/graphics/SpriteRenderer.h src/Singleton.h src/game/GameObject.cpp src/game/GameObject.h src/game/Brick.cpp src/game/Brick.h src/game/GameLevel.cpp src/game/GameLevel.h src/game/Player.cpp src/game/Player.h src/game/Ball.cpp src/game/Ball.h src/physics/Direction.h src/physics/Collision.h src/physics/CollisionDetector.cpp src/physics/CollisionDetector.h src/graphics/Particle.h src/graphics/ParticleEmitter.cpp src/graphics/ParticleEmitter.h src/graphics/PostProcessor.cpp src/graphics/PostProcessor.h src/graphics/PostProcessingEffect.h src/game/PowerUp.cpp src/game/PowerUp.h src/game/PowerUpType.h src/utils/Random.cpp src/utils/Random.h src/audio/AudioManager.h src/audio/AudioManager.cpp src/audio/AudioFile.h src/graphics/TextRenderer.h src/graphics/TextRenderer.cpp src/graphics/Font.h src/graphics/GlyphInfo.h)

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
# OpenAL build configuration

add_subdirectory(externals/openal-soft)
include_directories(externals/openal-soft/include)

# end
# ------------------------
# Header-only libraries

include_directories(externals/glm)
include_directories(externals/stb)

# end

add_executable(breakout ${SOURCES})

target_link_libraries(breakout glfw glew OpenAL ${OPENGL_LIBRARY})
