#pragma once

#include "../Engine/IGameScene.h"
#include "../Engine/IMainGame.h"
#include "../Engine/Camera.h"
#include "../Engine/GLSLProgram.h"
#include "../Engine/SpriteBatch.h"
#include "../Engine/Collider2D.h"
#include "../Engine/Collision.h"
#include "../Engine/AudioEngine.h"

#include <sstream>

class CreditsScene : public Engine::IGameScene
{
public:
	CreditsScene();
	~CreditsScene();

	int getNextScreenIndex() const override;
	int getPreviousScreenIndex() const override;

	void build() override;
	void destroy() override;

	void onEntry() override;
	void onExit() override;

	void update(double deltaTime) override;
	void draw() override;


	

private:
	void handleInput(double deltaTime);
	void reset();

	Engine::Camera m_camera;
	Engine::GLSLProgram m_fontShader;
	Engine::SpriteBatch m_batch;

	//std::stringstream m_stringStream;

	glm::vec2 m_screenDims = glm::vec2(0, 0);

	int m_padding = 40;
	double m_speed = 1.0;

	double m_yPos = -600.0;

	Engine::Collider2D m_collider = Engine::Collider2D(0, 0, 0, 0);
	Engine::Collider2D m_trigger = Engine::Collider2D(0, 0, 0, 0);
};

