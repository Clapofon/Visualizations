#include "LaunchScene.h"

#include "../Engine/IMainGame.h"
#include "../Engine/ResourceManager.h"

#include "ScreenIndices.h"

#include <SDL.h>
#include <glew.h>

#include <iostream>
#include <filesystem>

#include <imgui.h>

LaunchScene::LaunchScene()
{
	m_screenIndex = SCREEN_INDEX_LAUNCH_SCREEN;
}

LaunchScene::~LaunchScene()
{

}

int LaunchScene::getNextScreenIndex() const
{
	return SCREEN_INDEX_MAINMENU_SCREEN;
}

int LaunchScene::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void LaunchScene::build()
{
	//printf("build");
}

void LaunchScene::destroy()
{
	//printf("destory");
}

void LaunchScene::onEntry()
{
	m_shader = Engine::ResourceManager::getShader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
	m_fontShader = Engine::ResourceManager::getShader("assets/shaders/fontVertex.glsl", "assets/shaders/fontFragment.glsl");
	m_batch.init();
	m_fontBatch.init();
	m_screenDims = m_game->getWindowDimentions();
	m_camera.init(m_screenDims.x, m_screenDims.y);
	m_camera.setScale(1.0f);
	m_camera.setPosition(glm::vec2(0, 0));
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//m_game->getAudioEngine().LoadSound("assets/sounds/ambient/cyberpunk_credits_ambient.ogg", false, true, true);
	//m_game->getAudioEngine().playSound("assets/sounds/ambient/cyberpunk_credits_ambient.ogg");
}

void LaunchScene::onExit()
{
	m_game->getAudioEngine().StopAllChannels();
	m_game->getAudioEngine().ResetPositionAllChannels();
}

void LaunchScene::update(double deltaTime)
{
	handleInput(deltaTime);

	if (m_canLeave && m_game->getInputManager().isKeyPressed(SDLK_SPACE))
	{
		m_currentState = Engine::ScreenState::CHANGE_NEXT;
	}

	m_camera.update();
	m_elapsedTime += deltaTime;
	m_stream.str(std::string());
	m_stream << std::to_string(m_elapsedTime);

	if (m_elapsedTime > 20.0)
	{
		m_canLeave = true;
	}
}

void LaunchScene::draw()
{
	glActiveTexture(GL_TEXTURE0);
	m_shader.start();

	GLint textureLocation = m_shader.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);


	GLuint pLocation = m_shader.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));


	m_batch.begin();

	if (m_elapsedTime <= 3.0)
	{
		m_batch.draw(glm::vec4(-100, 0, 200, 200), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), Engine::ResourceManager::getTexture("assets/textures/papaj.png").id,
			1.0f, Engine::ColorRGBA8(255, 255, 255, 255));
	} 

	if (m_elapsedTime > 3.0 && m_elapsedTime <= 6.0)
	{
		m_batch.draw(glm::vec4(-128, 0, 256, 256), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), Engine::ResourceManager::getTexture("assets/textures/jd_engine.png").id,
			1.0f, Engine::ColorRGBA8(255, 255, 255, 255));
	}

	if (m_elapsedTime > 6.0 && m_elapsedTime <= 9.0)
	{
		m_batch.draw(glm::vec4(-128, 0, 256, 256), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), Engine::ResourceManager::getTexture("assets/textures/wiadro_nabite.png").id,
			1.0f, Engine::ColorRGBA8(255, 255, 255, 255));
	}

	if (m_elapsedTime > 9.0 && m_elapsedTime <= 15.0)
	{
		
	}

	if (m_elapsedTime > 15.0 && m_elapsedTime <= 20.0)
	{
		
	}

	if (m_elapsedTime > 20.0)
	{
		
	}

	m_batch.end();
	m_batch.renderBatch();

	m_shader.stop();

	drawUI();
}

void LaunchScene::drawUI()
{
	drawUIFonts();
}

void LaunchScene::drawUIFonts()
{
	m_fontShader.start();

	GLint textureLocation = m_fontShader.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);


	GLuint pLocation = m_fontShader.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_fontBatch.begin();

	if (m_elapsedTime <= 3.0)
	{
		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 64)->draw(
			m_fontBatch,
			"WADOWICE MONSTERS",
			glm::vec2(0, -100),
			glm::vec2(0.7f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);
	}

	if (m_elapsedTime > 3.0 && m_elapsedTime <= 6.0)
	{
		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 64)->draw(
			m_fontBatch,
			"JD ENGINE",
			glm::vec2(0, -100),
			glm::vec2(0.7f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);
	}

	if (m_elapsedTime > 6.0 && m_elapsedTime <= 9.0)
	{
		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 64)->draw(
			m_fontBatch,
			"I TE INNE",
			glm::vec2(0, -100),
			glm::vec2(0.7f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);
	}

	if (m_elapsedTime > 9.0 && m_elapsedTime <= 15.0)
	{
		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_fontBatch,
			"Wszystkie przedstawione w grze wydarzenia, sytuacje, oraz postaci (wraz z ich imionami i nazwiskami) sa prawdziwe.",
			glm::vec2(0, 50),
			glm::vec2(0.7f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_fontBatch,
			"Podobienstwo do prawdziwych osob lub innych bytow rzeczywistych orazwykorzystanie prawdziwych marek, budynkow, pojazdow,",
			glm::vec2(0, 18),
			glm::vec2(0.7f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_fontBatch,
			"produktow lub obiektow jest calkowicie nie przypadkowa. Zawartosc gry ma sluzyc okreslonym celow artystycznym,",
			glm::vec2(0, -14),
			glm::vec2(0.7f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_fontBatch,
			"a jej tworcy popieraja, pochwalaja oraz promuja wyrazane w niej poglady oraz prezentowane produkty, tresci i zachowania",
			glm::vec2(0, -45),
			glm::vec2(0.7f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);
	}

	if (m_elapsedTime > 15.0 && m_elapsedTime <= 20.0)
	{
		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_fontBatch,
			"OSTREZENIE PRZED EPILEPSJA",
			glm::vec2(0, 50),
			glm::vec2(0.8f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_fontBatch,
			"W trakcie gry napotkasz roznego rodzaju efekty wizualne (na przyklad migoczace rzygi w scenach rzygania), ktore u niewielkiej",
			glm::vec2(0, 18),
			glm::vec2(0.7f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_fontBatch,
			"grupy osob moga wywolac ataki padaczki lub utraty przytomnosci, Jesli Ty lub ktokolwiek z Twojej rodziny wykazywal kiedykolwiek",
			glm::vec2(0, -14),
			glm::vec2(0.7f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_fontBatch,
			"objawy epilepsji w warunkach migoczacych rzygow, na wszelki wypadek poradz sie lekarza przed rozpoczeciem przygody",
			glm::vec2(0, -45),
			glm::vec2(0.7f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_fontBatch,
			"w grze Worcella 4D.",
			glm::vec2(0, -77),
			glm::vec2(0.7f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);
	}

	if (m_elapsedTime > 20.0)
	{
		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 300)->draw(
			m_fontBatch,
			"WORCELLA 4D",
			glm::vec2(0, 0),
			glm::vec2(1.0f),
			0.9f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);
		
		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 48)->draw(
			m_fontBatch,
			"NACISNIJ [ SPACJA ], ABY KONTYNUOWAC",
			glm::vec2((m_screenDims.x / 2) - 150, (-m_screenDims.y / 2) + 150),
			glm::vec2(0.7f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::RIGHT);
	}

	m_fontBatch.end();

	m_fontBatch.renderBatch();
	m_fontShader.stop();
}

void LaunchScene::handleInput(double deltaTime)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		m_game->onSDLEvent(event);
	}
}
