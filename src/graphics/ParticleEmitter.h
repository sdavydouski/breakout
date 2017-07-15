#pragma once

#include "Texture.h"
#include "ShaderProgram.h"
#include "Particle.h"
#include "../game/Ball.h"
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <vector>

class ParticleEmitter {
public:
    ParticleEmitter(ShaderProgram* shaderProgram, Texture* texture, GLuint amount);
    ~ParticleEmitter();

    void update(float delta,
                const Ball& object,
                int newParticles,
                const glm::vec2 offset = glm::vec2(0.0f));
    void render(float scale);
private:
    std::vector<Particle> particles_;
    GLuint amount_;
    ShaderProgram* shaderProgram_;
    Texture* texture_;

    GLuint VAO_;
    GLuint VBO_;

    GLuint lastUsedParticle_;

    GLuint getFirstUnusedParticle();
    void respawnParticle(Particle& particle,
                         const Ball& object,
                         const glm::vec2& offset = glm::vec2(0.0f));
};
