#pragma once

#include "../Engine/IGameScene.h"
#include "../Engine/SpriteBatch.h"
#include "../Engine/GLSLProgram.h"
#include "../Engine/Camera.h"
#include "../Engine/ParticleSystem2D.h"
#include "../Engine/AnimatedSprite.h"

#include "Papaj.h"

#include <sstream>

enum class Visualization
{
	VISUALIZATION_BROUN,
	VISUALIZATION_NEWTON_RAPHSON
};

class InfScene : public Engine::IGameScene
{
public:
	InfScene();
	~InfScene();

	int getNextScreenIndex() const override;
	int getPreviousScreenIndex() const override;

	void build() override;
	void destroy() override;

	void onEntry() override;
	void onExit() override;

	void update(double deltaTime) override;
	void draw() override;


	void handleInput(double deltaTime);
private:

	double estimatePi(int n, Engine::SpriteBatch& batch, glm::vec4 destRect);

	void visualizeBroun();
	void visualizeNewtonRaphson();

	Visualization m_currentVisualization = Visualization::VISUALIZATION_NEWTON_RAPHSON;

	Engine::GLSLProgram m_shader;
	Engine::GLSLProgram m_fontShader;
	Engine::SpriteBatch m_batch;
	Engine::Camera m_camera;
	Engine::ParticleSystem2D* m_particleSystem = nullptr;
	Engine::FlipType m_flipType = Engine::FlipType::NONE;

	glm::vec2 m_screenDims = glm::vec2(0, 0);
	glm::vec2 m_coords = glm::vec2(0, 0);
	glm::vec2 m_papajCoords = glm::vec2(0, 0);

	std::vector<Papaj> m_papaje;

	std::stringstream m_statStream;

	bool m_drawBroun = false;
	bool m_shouldNewton = true;
	int m_timer = 0;

	double m_pi = 0.0;
};

