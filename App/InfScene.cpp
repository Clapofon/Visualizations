#include "InfScene.h"

#include "../Engine/IMainGame.h"
#include "../Engine/OBJLoader.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Quest.h"
#include "../Engine/Random.h"
#include "../Engine/ResourceManager.h"

#include "ScreenIndices.h"

#include <SDL.h>
#include <glew.h>

#include <iostream>
#include <filesystem>

#include <imgui.h>

InfScene::InfScene()
{
	m_screenIndex = SCREEN_INDEX_GAMEPLAY_SCREEN;
}

InfScene::~InfScene()
{

}

int InfScene::getNextScreenIndex() const
{
	return SCREEN_INDEX_CREDITS_SCREEN;
}

int InfScene::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_GAMEPLAY_SCREEN;
}

void InfScene::build()
{
	//printf("build");
}

void InfScene::destroy()
{
	//printf("destory");
}

void InfScene::onEntry()
{
	m_shader = Engine::ResourceManager::getShader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
	m_fontShader = Engine::ResourceManager::getShader("assets/shaders/fontVertex.glsl", "assets/shaders/fontFragment.glsl");

	m_batch.init();

	m_screenDims = m_game->getWindowDimentions();
	m_camera.init(m_screenDims.x, m_screenDims.y);
	m_camera.setScale(1.0f);
	m_camera.setPosition(glm::vec2(0, 0));

	m_particleSystem = new Engine::ParticleSystem2D(&m_camera);

	m_game->getAudioEngine().LoadSound("assets/sounds/ambient/barka.ogg", false, true, true);

	for (int i = 0; i < 100; ++i)
	{
		m_papaje.push_back(Papaj(i));
	}
}

void InfScene::onExit()
{
	m_game->getAudioEngine().StopAllChannels();
	m_game->getAudioEngine().ResetPositionAllChannels();

	m_papaje.clear();
}

void InfScene::update(double deltaTime)
{
	handleInput(deltaTime);
	m_camera.update();

	if (m_game->getInputManager().isKeyPressed(SDLK_1))
	{
		m_currentState = Engine::ScreenState::CHANGE_PREVIOUS;
	}

	if (m_game->getInputManager().isKeyPressed(SDLK_2))
	{
		m_currentState = Engine::ScreenState::CHANGE_NEXT;
	}

	if (m_game->getInputManager().isKeyPressed(SDLK_RIGHT))
	{
		m_currentVisualization = Visualization::VISUALIZATION_BROUN;
	}

	if (m_game->getInputManager().isKeyPressed(SDLK_LEFT))
	{
		m_currentVisualization = Visualization::VISUALIZATION_NEWTON_RAPHSON;
	}

	if (m_currentVisualization == Visualization::VISUALIZATION_BROUN)
	{
		for (int i = 0; i < m_papaje.size(); i++)
		{
			m_papaje[i].update(deltaTime, 200.0, m_screenDims, m_papaje);
		}
	}

	m_timer++;
	if (m_timer >= 30)
	{
		m_shouldNewton = true;
		m_timer = 0;
	}
}

double InfScene::estimatePi(int n, Engine::SpriteBatch& batch, glm::vec4 destRect)
{
	int overallPoints = 0;
	int pointsInCircle = 0;

	for (int i = 0; i < n; i++)
	{
		double x = Engine::Random::randDouble(0, 1);
		double y = Engine::Random::randDouble(0, 1);
		double distance = x * x + y * y;

		if (distance <= 1.0)
		{
			pointsInCircle++;
			batch.draw(glm::vec4(destRect.x + (x * destRect.z), destRect.y + (y * destRect.w), 50, 50), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
				Engine::ResourceManager::getTexture("assets/textures/papaj.png").id, 1.0f, Engine::ColorRGBA8(100, 255, 100, 255));
		}
		else
		{
			batch.draw(glm::vec4(destRect.x + (x * destRect.z), destRect.y + (y * destRect.w), 50, 50), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
				Engine::ResourceManager::getTexture("assets/textures/papaj.png").id, 1.0f, Engine::ColorRGBA8(255, 100, 100, 255));
		}
		overallPoints++;
	}

	return 4.0 * pointsInCircle / overallPoints;
}

void InfScene::draw()
{
	if (m_currentVisualization == Visualization::VISUALIZATION_BROUN)
	{
		visualizeBroun();
	}

	if (m_currentVisualization == Visualization::VISUALIZATION_NEWTON_RAPHSON)
	{
		visualizeNewtonRaphson();
	}
}

void InfScene::visualizeBroun()
{
	m_shader.start();

	GLint textureLocation = m_shader.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);


	GLuint pLocation = m_shader.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));


	m_batch.begin();

	glm::vec2 camPos = m_camera.getPosition();
	float camScale = m_camera.getScale();
	m_screenDims = m_game->getWindowDimentions();

	for (int i = 0; i < m_papaje.size(); i++)
	{
		m_papaje[i].draw(m_batch);
	}

	m_batch.draw(glm::vec4(-m_screenDims.x / 2, -m_screenDims.y / 2, m_screenDims.x, m_screenDims.y), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/bars.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	Engine::ResourceManager::getFont("assets/fonts/NotoSans-Regular.ttf", 64)->draw(m_batch, "WYPUSC NAS, CHCEMY ZJESC KREMOWKI!",
		glm::vec2(0, 400), glm::vec2(0.9 / camScale), 1.0f, Engine::ColorRGBA8(255, 255, 255, 255), Engine::Justification::MIDDLE);

	m_statStream.str(std::string());
	m_statStream << m_game->getStats();
	Engine::ResourceManager::getFont("assets/fonts/NotoSans-Regular.ttf", 24)->draw(m_batch, m_statStream.str().c_str(),
		glm::vec2(camPos.x - 0.45 * m_screenDims.x / camScale, camPos.y + 0.45 * m_screenDims.y / camScale),
		glm::vec2(0.75f / camScale), 1.0f,
		Engine::ColorRGBA8(255, 255, 255, 255), Engine::Justification::LEFT);

	m_batch.end();
	m_batch.renderBatch();

	m_shader.stop();
}

void InfScene::visualizeNewtonRaphson()
{
	m_shader.start();

	GLint textureLocation = m_shader.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);


	GLuint pLocation = m_shader.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));


	m_batch.begin();

	glm::vec2 camPos = m_camera.getPosition();
	float camScale = m_camera.getScale();
	m_screenDims = m_game->getWindowDimentions();
	

	m_pi = estimatePi(999, m_batch, glm::vec4(-500, -550, 1000, 1050));
	

	m_statStream.str(std::string());
	m_statStream << std::to_string(m_pi);

	Engine::ResourceManager::getFont("assets/fonts/NotoSans-Regular.ttf", 64)->draw(m_batch, m_statStream.str().c_str(), 
		glm::vec2((-m_screenDims.x / 2) + 50, (m_screenDims.y / 2) - 114), glm::vec2(1.0f), 1.0f,
		Engine::ColorRGBA8(255, 255, 255, 255));

	m_batch.end();
	m_batch.renderBatch();

	m_shader.stop();
}


void InfScene::handleInput(double deltaTime)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		m_game->onSDLEvent(event);
	}
}







