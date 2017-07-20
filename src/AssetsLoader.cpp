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
    ResourceManager::Instance().createTexture("background",
       OFFSET + "resources/textures/background.jpg",
       1600, 900);
    ResourceManager::Instance().createTexture("face",
       OFFSET + "resources/textures/awesome_face.png",
       512, 512, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("block",
       OFFSET + "resources/textures/block.png",
       128, 128);
    ResourceManager::Instance().createTexture("block_solid",
       OFFSET + "resources/textures/block_solid.png",
       128, 128);
    ResourceManager::Instance().createTexture("paddle",
       OFFSET + "resources/textures/paddle.png",
       512, 128, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("particle",
       OFFSET + "resources/textures/particle.png",
       500, 500, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("speedUp",
       OFFSET + "resources/textures/powerups/powerup_speedup.png",
       512, 128, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("sticky",
       OFFSET + "resources/textures/powerups/powerup_sticky.png",
       512, 128, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("passThrough",
       OFFSET + "resources/textures/powerups/powerup_passthrough.png",
       512, 128, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("padSizeIncrease",
       OFFSET + "resources/textures/powerups/powerup_increase.png",
       512, 128, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("confuse",
       OFFSET + "resources/textures/powerups/powerup_confuse.png",
       512, 128, 4, GL_RGBA);
    ResourceManager::Instance().createTexture("chaos",
       OFFSET + "resources/textures/powerups/powerup_chaos.png",
       512, 128, 4, GL_RGBA);
}

void AssetsLoader::loadAudioFiles() {
    AudioManager::Instance().createSource("background", OFFSET + "resources/audio/background.ogg", true);
    AudioManager::Instance().createSource("bleep", OFFSET + "resources/audio/bleep.ogg", false);
    AudioManager::Instance().createSource("bleepPaddle", OFFSET + "resources/audio/bleep_paddle.ogg", false);
    AudioManager::Instance().createSource("solid", OFFSET + "resources/audio/solid.ogg", false);
    AudioManager::Instance().createSource("powerup", OFFSET + "resources/audio/powerup.ogg", false);
}
