#include "ParticleEmitter.h"
#include <iostream>

ParticleEmitter::ParticleEmitter(ShaderProgram *shaderProgram,
                                 Texture *texture,
                                 GLuint amount)
    : shaderProgram_(shaderProgram), texture_(texture), amount_(amount) {
    std::cout << "ParticleEmitter constructor" << std::endl;


}

ParticleEmitter::~ParticleEmitter() {
    std::cout << "ParticleEmitter destructor" << std::endl;
}

void ParticleEmitter::update(float delta,
                             const GameObject& object,
                             int newParticles,
                             const glm::vec2 offset) {

}

void ParticleEmitter::render() {

}

GLuint ParticleEmitter::getFirstUnusedParticle() {
    return 0;
}

void ParticleEmitter::respawnParticle(const Particle& particle,
                                      const GameObject& object,
                                      const glm::vec2& offset) {

}
