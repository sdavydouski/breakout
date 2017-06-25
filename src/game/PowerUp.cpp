#include "PowerUp.h"
#include <iostream>

// The size of a PowerUp block
const glm::vec2 SIZE(60, 20);
// Velocity a PowerUp block has when spawned
const glm::vec2 VELOCITY(0.0f, 150.0f);

PowerUp::PowerUp(const glm::vec2& position,
                 const glm::vec3& color,
                 Texture* sprite,
                 PowerUpType type,
                 GLfloat duration)
    : GameObject(position, SIZE, color, sprite),
      velocity_(VELOCITY), type_(type), duration_(duration), isActivated_(false), isDestroyed_(false) {
    std::cout << "PowerUp constructor" << std::endl;

}

PowerUp::~PowerUp() {
    std::cout << "PowerUp destructor" << std::endl;
}

void PowerUp::update(float delta, Player& player, Ball& ball, PostProcessor& postProcessor) {
    position_ += velocity_ * delta;
    if (!isActivated_) return;

    duration_ -= delta;

    if (duration_ <= 0.0f) {
        isActivated_ = false;
        // Deactivate effects
        switch (type_) {
            case PowerUpType::Sticky: {
                ball.isSticky(false);
                player.color(glm::vec3(1.0f));
                break;
            }
            case PowerUpType::PassThrough: {
                ball.isPassingThrough(false);
                ball.color(glm::vec3(1.0f));
                break;
            }
            case PowerUpType::Confuse: {
                postProcessor.disableEffects(PostProcessingEffect::Confuse);
                break;
            }
            case PowerUpType::Chaos: {
                postProcessor.disableEffects(PostProcessingEffect::Chaos);
                break;
            }
        }
    }
}

void PowerUp::activate(Player& player, Ball& ball, PostProcessor& postProcessor) {
    isActivated_ = true;
    isDestroyed_ = true;

    switch (type_) {
        case PowerUpType::SpeedUp: {
            ball.velocity(1.2f);
            break;
        }
        case PowerUpType::Sticky: {
            ball.isSticky(true);
            player.color(glm::vec3(1.0f, 0.5f, 1.0f));
            break;
        }
        case PowerUpType::PassThrough: {
            ball.isPassingThrough(true);
            ball.color(glm::vec3(1.0f, 0.5f, 0.5f));
            break;
        }
        case PowerUpType::PadSizeIncrease: {
            player.updateSizeX(50);
            break;
        }
        case PowerUpType::Confuse: {
            postProcessor.enableEffects(PostProcessingEffect::Confuse);
            break;
        }
        case PowerUpType::Chaos: {
            postProcessor.enableEffects(PostProcessingEffect::Chaos);
            break;
        }
    }
}
