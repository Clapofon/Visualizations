#pragma once

#include "InteractiveItem.h"

#include "../Engine/AudioEngine.h"

#include <random>

class Bucket : public InteractiveItem
{
public:
	Bucket(const std::string& texture, glm::vec4 destRect, Engine::Camera* camera);
	~Bucket();

	void init(Engine::AudioEngine audioEngine);
	void interract();
	void onDraw(Engine::SpriteBatch& batch, Engine::ParticleSystem2D* particleSystem);
	void onUpdate(Engine::AudioEngine audioEngine, Engine::QuestSystem& qSystem, double deltaTime);

private:
	bool m_bucketReady = false;
	int m_amt = 0;
	std::mt19937 m_rng;
	int m_smokeSound = -1;
};

