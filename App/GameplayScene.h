#pragma once

#include "../Engine/IGameScene.h"
#include "../Engine/Camera.h"
#include "../Engine/GLSLProgram.h"
#include "../Engine/SpriteBatch.h"
#include "../Engine/Minimap.h"
#include "../Engine/FrameBuffer.h"
#include "../Engine/Tilemap.h"
#include "../Engine/Collision.h"
#include "../Engine/Collider2D.h"
#include "../Engine/QuestSystem.h"

#include "Player.h"
#include "Furnace.h"
#include "Bucket.h"
#include "Shelf.h"

#include <sstream>

enum class GameplayState
{
	PLAY,
	MENU,
	INVENTORYMENU
};

class GameplayScene : public Engine::IGameScene
{
public:
	GameplayScene();
	~GameplayScene();

	int getNextScreenIndex() const override;
	int getPreviousScreenIndex() const override;

	void build() override;
	void destroy() override;

	void onEntry() override;
	void onExit() override;

	void update(double deltaTime) override;
	void draw() override;

	void drawUI();

	void drawUIFonts();
	void drawUIBackground();

	void handleInput(double deltaTime);
private:

	void setupQuests();
	void loadMusic(const std::string& musicDirectory);
	void renderImGuiQuestMenuSection();

	Engine::GLSLProgram m_shader;
	Engine::GLSLProgram m_fontShader;
	Engine::SpriteBatch m_batch;
	Engine::SpriteBatch m_fontBatch;
	Engine::SpriteBatch m_uiBatch;
	Engine::SpriteBatch m_minimapBatch;
	Engine::SpriteBatch m_playerBatch;
	Engine::Camera m_camera;
	Engine::Minimap* m_minimap = nullptr;
	Engine::FrameBuffer* m_framebuffer = nullptr;
	Engine::Tilemap m_tilemap;
	Engine::QuestSystem m_questSystem;
	Engine::ParticleSystem2D* m_particleSystem = nullptr;

	Engine::FlipType m_flipType;

	std::vector<std::string> m_musicList;

	Furnace m_furnace = Furnace("assets/textures/items/furnace_idle.png", glm::vec4(100, -100, 32, 73), &m_camera);
	Bucket m_bucket = Bucket("assets/textures/wiadro_nabite.png", glm::vec4(200, -200, 32, 32), &m_camera);
	Shelf m_shelf = Shelf("assets/textures/items/shelf.png", glm::vec4(300, -300, 128, 32), &m_camera);

	int channelId = 0;
	double m_time = 0.0f;
	glm::vec2 m_pos = glm::vec2(125, -125);
	float m_amt = 0.0f;
	float m_angle = 0.0f;
	
	glm::vec2 m_screenDims = glm::vec2(0, 0);

	std::vector<Engine::Collider2D> m_colliders;

	std::stringstream m_statStream;

	Player m_player;

	bool m_menuDisplay = false;
	bool m_inventoryMenuDisplay = false;
	bool m_cameraLock = true;
	bool m_vomitMiniGame = false;
	bool m_drawQuests = false;


	GameplayState m_gameplayState = GameplayState::PLAY;
};