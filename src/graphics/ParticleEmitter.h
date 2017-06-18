#pragma once

#include "Texture.h"
#include "ShaderProgram.h"
#include "../game/GameObject.h"
#include "Particle.h"
#include <GL/glew.h>
#include <vector>

class ParticleEmitter {
public:
    ParticleEmitter(ShaderProgram* shaderProgram, Texture* texture, GLuint amount);
    ~ParticleEmitter();

    void update(float delta,
                const GameObject& object,
                int newParticles,
                const glm::vec2 offset = glm::vec2(0.0f));
    void render();
private:
    std::vector<Particle> particles_;
    GLuint amount_;
    ShaderProgram* shaderProgram_;
    Texture* texture_;

    GLuint VAO_;
    GLuint VBO_;

    GLuint getFirstUnusedParticle();
    void respawnParticle(const Particle& particle,
                         const GameObject& object,
                         const glm::vec2& offset = glm::vec2(0.0f));
};
