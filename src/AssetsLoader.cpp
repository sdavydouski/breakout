#include "AssetsLoader.h"
#include "ResourceManager.h"
#include "audio/AudioManager.h"
#include <GL/glew.h>

const std::string AssetsLoader::OFFSET = "../../../../";

void AssetsLoader::loadShaders() {
    ResourceManager::Instance().createShaderProgram("sprite",
         Shader(ShaderType::VERTEX,
                OFFSET + "resources/shaders/sprite/shader.vert"),
         Shader(ShaderType::FRAGMENT,
                OFFSET + "resources/shaders/sprite/shader.frag"));

    ResourceManager::Instance().createShaderProgram("text",
         Shader(ShaderType::VERTEX,
                OFFSET + "resources/shaders/textrendering/shader.vert"),
         Shader(ShaderType::FRAGMENT,
                OFFSET + "resources/shaders/textrendering/shader.frag"));

    ResourceManager::Instance().createShaderProgram("particle",
         Shader(ShaderType::VERTEX,
                OFFSET + "resources/shaders/particle/shader.vert"),
         Shader(ShaderType::FRAGMENT,
                OFFSET + "resources/shaders/particle/shader.frag"));

    ResourceManager::Instance().createShaderProgram("postprocessing",
         Shader(ShaderType::VERTEX,
                OFFSET + "resources/shaders/postprocessing/shader.vert"),
         Shader(ShaderType::FRAGMENT,
                OFFSET + "resources/shaders/postprocessing/shader.frag"));
}

void AssetsLoader::loadTextures() {
    // https://opengameart.org/content/sunset-temple-tiles
    ResourceManager::Instance().createTexture("background",
       OFFSET + "resources/textures/background.png",
       1914, 1080);
    // https://opengameart.org/content/pixel-art-tiles-from-last-escape
    ResourceManager::Instance().createTexture("ball",
       OFFSET + "resources/textures/ball.png",
       58, 58, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("block1",
       OFFSET + "resources/textures/block1.png",
       32, 32);
    ResourceManager::Instance().createTexture("block2",
        OFFSET + "resources/textures/block2.png",
        32, 32);
    ResourceManager::Instance().createTexture("block_solid",
       OFFSET + "resources/textures/block_solid.png",
        32, 32);
    ResourceManager::Instance().createTexture("paddle",
       OFFSET + "resources/textures/paddle.png",
       96, 32, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("particle",
       OFFSET + "resources/textures/particle.png",
       50, 50, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("powerUp",
        OFFSET + "resources/textures/powerup.png",
        16, 32, 4, GL_RGBA);
}

void AssetsLoader::loadAudioFiles() {
    // https://opengameart.org/content/tower-defense-theme
    AudioManager::Instance().createSource("background", OFFSET + "resources/audio/background.ogg", true);
    AudioManager::Instance().createSource("bleep", OFFSET + "resources/audio/bleep.ogg", false);
    AudioManager::Instance().createSource("bleepPaddle", OFFSET + "resources/audio/bleep_paddle.ogg", false);
    AudioManager::Instance().createSource("solid", OFFSET + "resources/audio/solid.ogg", false);
    AudioManager::Instance().createSource("powerup", OFFSET + "resources/audio/powerup.ogg", false);
}
