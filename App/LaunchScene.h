#pragma once

#include "../Engine/IGameScene.h"
#include "../Engine/GLSLProgram.h"
#include "../Engine/Camera.h"
#include "../Engine/SpriteBatch.h"

#include <sstream>


class LaunchScene : public Engine::IGameScene
{
public:
	LaunchScene();
	~LaunchScene();

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

	void handleInput(double deltaTime);
private:
	Engine::GLSLProgram m_shader;
	Engine::GLSLProgram m_fontShader;
	Engine::Camera m_camera;
	Engine::SpriteBatch m_batch;
	Engine::SpriteBatch m_fontBatch;

	std::stringstream m_stream;

	double m_elapsedTime = 0.0;
	bool m_canLeave = false;

	glm::vec2 m_screenDims = glm::vec2(0, 0);
};

