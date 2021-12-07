#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::init(Engine::Camera* camera, Engine::AudioEngine audioEngine)
{
	glm::vec4 posAndDims = glm::vec4(m_pos, 64, 64);
	m_walkingSprite = new Engine::AnimatedSprite("assets/textures/dadziak_pixelart.png", posAndDims, glm::vec2(1, 6), 5, 1.0f, false);
	m_idleSprite = new Engine::AnimatedSprite("assets/textures/dadziak_spi_2.png", posAndDims, glm::vec2(1, 7), 6, 1.0f, false);
	m_colliders.push_back(Engine::Collider2D(0, 0, 32, 32));
	audioEngine.LoadSound("assets/sounds/player/walk.ogg", false, true, false);
	m_walkSound = audioEngine.playSound("assets/sounds/player/walk.ogg");
}

void Player::update(Engine::InputManager inputManager, Engine::AudioEngine audioEngine, double deltaTime /*Engine::ParticleSystem2D* particleSystem*/)
{
	m_prevPos = m_pos;

	if (inputManager.isKeyDown(SDLK_a))
	{
		m_pos.x -= 64.0f * deltaTime;
		m_animationState = PlayerAnimationState::WALKING;
		m_flip = true;
	}

	if (inputManager.isKeyDown(SDLK_d))
	{
		m_pos.x += 64.0f * deltaTime;
		m_animationState = PlayerAnimationState::WALKING;
		m_flip = false;
	}

	if (inputManager.isKeyDown(SDLK_s))
	{
		m_pos.y -= 64.0f * deltaTime;
		m_animationState = PlayerAnimationState::WALKING;
	}

	if (inputManager.isKeyDown(SDLK_w))
	{
		m_pos.y += 64.0f * deltaTime;
		m_animationState = PlayerAnimationState::WALKING;
	}

	if (inputManager.isKeyDown(SDLK_LSHIFT))
	{
		if (inputManager.isKeyDown(SDLK_a))
		{
			m_pos.x -= 128.0f * deltaTime;
			m_animationState = PlayerAnimationState::RUNNING;
		}

		if (inputManager.isKeyDown(SDLK_d))
		{
			m_pos.x += 128.0f * deltaTime;
			m_animationState = PlayerAnimationState::RUNNING;
		}

		if (inputManager.isKeyDown(SDLK_s))
		{
			m_pos.y -= 128.0f * deltaTime;
			m_animationState = PlayerAnimationState::RUNNING;
		}

		if (inputManager.isKeyDown(SDLK_w))
		{
			m_pos.y += 128.0f * deltaTime;
			m_animationState = PlayerAnimationState::RUNNING;
		}
	}
	
	if (m_prevPos == m_pos)
	{
		m_animationState = PlayerAnimationState::IDLE;
	}

	if (m_animationState != PlayerAnimationState::IDLE)
	{
		if (!audioEngine.IsPlaying(m_walkSound))
		{
			audioEngine.StartChannel(m_walkSound);
		}
	}

	if (m_animationState == PlayerAnimationState::IDLE)
	{
		if (audioEngine.IsPlaying(m_walkSound))
		{
			audioEngine.StopChannel(m_walkSound);
			audioEngine.ResetChannelPosition(m_walkSound);
		}
	}

	m_colliders[0].x = m_pos.x + 16;
	m_colliders[0].y = m_pos.y + 16;

	m_toxicity = glm::clamp(m_toxicity, 0.0f, 1.0f);

	//m_time += 0.1;

	//printf("time: %f\n", m_time);

	//float amt = m_time * deltaTime * 10.0;

	//m_pos.y += glm::sin(amt);
	//m_pos.x += glm::sin(amt + 3.14 / 2.0);

	m_walkingSprite->setPosition(m_pos);
	m_idleSprite->setPosition(m_pos);
}

void Player::draw(Engine::SpriteBatch& spriteBatch, float camScale)
{
	if (m_animationState == PlayerAnimationState::IDLE)
	{
		m_idleSprite->draw(spriteBatch, (m_flip) ? Engine::FlipType::FLIP_X : Engine::FlipType::NONE);
		m_idleSprite->playAnimation(1.0f / 60.0f);
	}
	else if (m_animationState == PlayerAnimationState::RUNNING)
	{
		m_walkingSprite->draw(spriteBatch, (m_flip) ? Engine::FlipType::FLIP_X : Engine::FlipType::NONE);
		m_walkingSprite->playAnimation(1.0f / 2.0f);
	}
	else if (m_animationState == PlayerAnimationState::JUMPING)
	{

	}
	else if (m_animationState == PlayerAnimationState::WALKING)
	{
		m_walkingSprite->draw(spriteBatch, (m_flip) ? Engine::FlipType::FLIP_X : Engine::FlipType::NONE);
		m_walkingSprite->playAnimation(1.0f / 10.0f);
	}
	else if (m_animationState == PlayerAnimationState::CROUCHING)
	{

	}
}