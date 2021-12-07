#pragma once

#include "../Engine/Collision.h"
#include "../Engine/Collider2D.h"
#include "../Engine/SpriteBatch.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/InputManager.h"
#include "../Engine/Camera.h"
#include "../Engine/ParticleSystem2D.h"
#include "../Engine/AudioEngine.h"
#include "../Engine/QuestSystem.h"

class InteractiveItem
{
public:
	InteractiveItem(const std::string& texture, glm::vec4 destRect, Engine::Camera* camera);
	~InteractiveItem();

	virtual void interract() = 0;
	void update(const Engine::Collider2D& collider, Engine::InputManager inputManager, Engine::AudioEngine audioEngine, Engine::QuestSystem& qSystem, double deltaTime);
	void draw(Engine::SpriteBatch& batch, Engine::ParticleSystem2D* particleSystem);
	void drawFonts(Engine::SpriteBatch& batch, float resScale);
	void drawUIBackground(Engine::SpriteBatch& batch);
	virtual void onDraw(Engine::SpriteBatch& batch, Engine::ParticleSystem2D* particleSystem) = 0;
	virtual void onUpdate(Engine::AudioEngine audioEngine, Engine::QuestSystem& qSystem, double deltaTime) = 0;
	void addTextureAtlas(const std::string& textureAtlas, const glm::vec4& destRect, const glm::vec2& rowsAndCols, int maxIndex, double duration, 
		int startingIndex, bool filtering);

protected:

	Engine::GLTexture m_texture;
	Engine::Collider2D m_collider = Engine::Collider2D(0, 0, 0, 0);
	Engine::Camera* m_camera;

	std::vector<Engine::AnimatedSprite> m_textureAtlases;
	
	bool m_drawStaticTexture = true;
	bool m_canInterract = false;

	glm::vec2 m_pos = glm::vec2(0, 0);
	glm::vec2 m_dimentions = glm::vec2(0, 0);

	glm::vec4 m_buttonDestRect = glm::vec4(0, 0, 0, 0);
};

