#include "Shelf.h"

#include "../Engine/ResourceManager.h"

Shelf::Shelf(const std::string& texture, glm::vec4 destRect, Engine::Camera* camera) : InteractiveItem(texture, destRect, camera)
{

}

Shelf::~Shelf()
{

}

void Shelf::interract()
{
	m_destroyed = !m_destroyed;
}

void Shelf::onDraw(Engine::SpriteBatch& batch, Engine::ParticleSystem2D* particleSystem)
{
	if (m_destroyed)
	{
		batch.draw(glm::vec4(m_pos, m_dimentions), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), Engine::ResourceManager::getTexture("assets/textures/items/shelf_destroyed.png", false).id, 1.0f,
			Engine::ColorRGBA8(255, 255, 255, 255));
	}
}

void Shelf::onUpdate(Engine::AudioEngine audioEngine, Engine::QuestSystem& qSystem, double deltaTime)
{

}