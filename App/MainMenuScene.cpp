#include "MainMenuScene.h"

#include "../Engine/IMainGame.h"
#include "../Engine/ResourceManager.h"

#include "ScreenIndices.h"

#include <SDL.h>
#include <glew.h>

#include <iostream>
#include <filesystem>

#include <imgui.h>

MainMenuScene::MainMenuScene()
{
	m_screenIndex = SCREEN_INDEX_MAINMENU_SCREEN;
}

MainMenuScene::~MainMenuScene()
{

}

int MainMenuScene::getNextScreenIndex() const
{
	return SCREEN_INDEX_GAMEPLAY_SCREEN;
}

int MainMenuScene::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_LAUNCH_SCREEN;
}

void MainMenuScene::build()
{
	//printf("build");
}

void MainMenuScene::destroy()
{
	//printf("destory");
}

void MainMenuScene::onEntry()
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

}

void MainMenuScene::onExit()
{
	m_game->getAudioEngine().StopAllChannels();
	m_game->getAudioEngine().ResetPositionAllChannels();
}

void MainMenuScene::update(double deltaTime)
{
	handleInput(deltaTime);
}

void MainMenuScene::draw()
{
	glActiveTexture(GL_TEXTURE0);
	m_shader.start();

	GLint textureLocation = m_shader.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);


	GLuint pLocation = m_shader.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));


	m_batch.begin();

	{
		// position the controls widget in the top-right corner
		ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(400, m_game->getWindowDimentions().y));

		// create a window and append into it
		ImGui::Begin("jebac disa", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize);

		ImGui::Dummy(ImVec2(0.0f, m_game->getWindowDimentions().y / 3));

		// buttons and most other widgets return true when clicked/edited/activated
		if (ImGui::Button("New Game", ImVec2(400, 50)))
		{
			m_currentState = Engine::ScreenState::CHANGE_NEXT;
		}
		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		if (ImGui::Button("Continue", ImVec2(400, 50)))
		{
			m_currentState = Engine::ScreenState::CHANGE_NEXT;
		}
		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		if (ImGui::Button("Load Game", ImVec2(400, 50)))
		{
			std::cout << "load game button clicked\n";
		}
		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		if (ImGui::Button("Quit", ImVec2(400, 50)))
		{
			m_currentState = Engine::ScreenState::EXIT_APPLICATION;
			std::cout << "quit button clicked\n";
		}

		ImGui::End();
	}

	m_batch.end();
	m_batch.renderBatch();

	m_shader.stop();

	drawUI();
}

void MainMenuScene::drawUI()
{
	drawUIFonts();
}

void MainMenuScene::drawUIFonts()
{
	m_fontShader.start();

	GLint textureLocation = m_fontShader.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);


	GLuint pLocation = m_fontShader.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_fontBatch.begin();


	m_fontBatch.end();

	m_fontBatch.renderBatch();
	m_fontShader.stop();
}

void MainMenuScene::handleInput(double deltaTime)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		m_game->onSDLEvent(event);
	}
}
