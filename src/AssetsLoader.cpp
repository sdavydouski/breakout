#include "AssetsLoader.h"
#include "ResourceManager.h"
#include "audio/AudioManager.h"
#include "utils/globals.h"
#include <GL/glew.h>

void AssetsLoader::loadShaders() {
    ResourceManager::Instance().createShaderProgram("sprite",
         Shader(ShaderType::VERTEX,
                ASSETS_OFFSET + "resources/shaders/sprite/shader.vert"),
         Shader(ShaderType::FRAGMENT,
                ASSETS_OFFSET + "resources/shaders/sprite/shader.frag"));

    ResourceManager::Instance().createShaderProgram("text",
         Shader(ShaderType::VERTEX,
                ASSETS_OFFSET + "resources/shaders/textrendering/shader.vert"),
         Shader(ShaderType::FRAGMENT,
                ASSETS_OFFSET + "resources/shaders/textrendering/shader.frag"));

    ResourceManager::Instance().createShaderProgram("particle",
         Shader(ShaderType::VERTEX,
                ASSETS_OFFSET + "resources/shaders/particle/shader.vert"),
         Shader(ShaderType::FRAGMENT,
                ASSETS_OFFSET + "resources/shaders/particle/shader.frag"));

    ResourceManager::Instance().createShaderProgram("postprocessing",
         Shader(ShaderType::VERTEX,
                ASSETS_OFFSET + "resources/shaders/postprocessing/shader.vert"),
         Shader(ShaderType::FRAGMENT,
                ASSETS_OFFSET + "resources/shaders/postprocessing/shader.frag"));
}

void AssetsLoader::loadTextures() {
    ResourceManager::Instance().createTexture("background",
       ASSETS_OFFSET + "resources/textures/background.jpg",
       1600, 900);
    ResourceManager::Instance().createTexture("face",
       ASSETS_OFFSET + "resources/textures/awesome_face.png",
       512, 512, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("block",
       ASSETS_OFFSET + "resources/textures/block.png",
       128, 128);
    ResourceManager::Instance().createTexture("block_solid",
       ASSETS_OFFSET + "resources/textures/block_solid.png",
       128, 128);
    ResourceManager::Instance().createTexture("paddle",
       ASSETS_OFFSET + "resources/textures/paddle.png",
       512, 128, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("particle",
       ASSETS_OFFSET + "resources/textures/particle.png",
       500, 500, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("speedUp",
       ASSETS_OFFSET + "resources/textures/powerups/powerup_speedup.png",
       512, 128, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("sticky",
       ASSETS_OFFSET + "resources/textures/powerups/powerup_sticky.png",
       512, 128, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("passThrough",
       ASSETS_OFFSET + "resources/textures/powerups/powerup_passthrough.png",
       512, 128, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("padSizeIncrease",
       ASSETS_OFFSET + "resources/textures/powerups/powerup_increase.png",
       512, 128, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("confuse",
       ASSETS_OFFSET + "resources/textures/powerups/powerup_confuse.png",
       512, 128, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("chaos",
       ASSETS_OFFSET + "resources/textures/powerups/powerup_chaos.png",
       512, 128, 4, GL_RGBA);
}

void AssetsLoader::loadAudioFiles() {
    AudioManager::Instance().createSource("background", ASSETS_OFFSET + "resources/audio/background.ogg", true);
    AudioManager::Instance().createSource("bleep", ASSETS_OFFSET + "resources/audio/bleep.ogg", false);
    AudioManager::Instance().createSource("bleepPaddle", ASSETS_OFFSET + "resources/audio/bleep_paddle.ogg", false);
    AudioManager::Instance().createSource("solid", ASSETS_OFFSET + "resources/audio/solid.ogg", false);
    AudioManager::Instance().createSource("powerup", ASSETS_OFFSET + "resources/audio/powerup.ogg", false);
}
