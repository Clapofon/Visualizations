#pragma once

#include "InteractiveItem.h"

class Shelf : public InteractiveItem
{
public:
	Shelf(const std::string& texture, glm::vec4 destRect, Engine::Camera* camera);
	~Shelf();

	void interract();
	void onDraw(Engine::SpriteBatch& batch, Engine::ParticleSystem2D* particleSystem);
	void onUpdate(Engine::AudioEngine audioEngine, Engine::QuestSystem& qSystem, double deltaTime);

private:
	bool m_destroyed = false;
};

