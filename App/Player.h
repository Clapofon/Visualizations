#pragma once

#include <SDL.h>
#include <random>

#include "../Engine/InputManager.h"
#include "../Engine/Input.hpp"
#include "../Engine/Camera.h"
#include "../Engine/AudioEngine.h"
#include "../Engine/ParticleSystem2D.h"
#include "../Engine/Collider2D.h"

enum class PlayerAnimationState
{
    WALKING,
    RUNNING,
    IDLE,
    JUMPING,
    CROUCHING
};

class Player
{
public:
    Player();
    ~Player();

    void init(Engine::Camera* camera, Engine::AudioEngine audioEngine);
    void update(Engine::InputManager inputManager, Engine::AudioEngine audioEngine, double deltaTime /*Engine::ParticleSystem2D* particleSystem*/);
    void draw(Engine::SpriteBatch& spriteBatch, float camScale);

    glm::vec2 getPosition() { return m_pos; }
    Engine::Collider2D getCollider() { return m_colliders[0]; }
    float getToxicity() { return m_toxicity; }

    void setToxicity(float amt) { m_toxicity = amt; }

private:

    PlayerAnimationState m_animationState = PlayerAnimationState::IDLE;
    glm::vec2 m_pos = glm::vec2(-100, 50);
    glm::vec2 m_prevPos = glm::vec2(0);

    Engine::AnimatedSprite* m_walkingSprite = nullptr;
    Engine::AnimatedSprite* m_idleSprite = nullptr;

    int m_level = 2137;
    float m_toxicity = 0.75f;
    float m_health = 2137.0f;
    double m_time = 0.0;
    int m_walkSound = -1;

    std::vector<Engine::Collider2D> m_colliders;

    bool m_flip = false;
};
