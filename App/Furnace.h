#pragma once

#include "InteractiveItem.h"

#include <random>

class Furnace : public InteractiveItem
{
public:
	Furnace(const std::string& texture, glm::vec4 destRect, Engine::Camera* camera);
	~Furnace();

	void interract();
	void onDraw(Engine::SpriteBatch& batch, Engine::ParticleSystem2D* particleSystem);
	void onUpdate(Engine::AudioEngine audioEngine, Engine::QuestSystem& qSystem, double deltaTime);

private:
	bool m_burningComplete = false;
	int m_amt = 0;
	double m_timer = 0.0;

	std::mt19937 m_rng;
};

