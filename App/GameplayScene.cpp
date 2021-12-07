#include "GameplayScene.h"

#include "../Engine/IMainGame.h"
#include "../Engine/OBJLoader.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Quest.h"
#include "../Engine/Random.h"

#include "ScreenIndices.h"

#include <SDL.h>
#include <glew.h>

#include <iostream>
#include <filesystem>

#include <imgui.h>

GameplayScene::GameplayScene()
{
	m_screenIndex = SCREEN_INDEX_GAMEPLAY_SCREEN;
}

GameplayScene::~GameplayScene()
{

}

int GameplayScene::getNextScreenIndex() const
{
	return SCREEN_INDEX_INF_SCREEN;
}

int GameplayScene::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_MAINMENU_SCREEN;
}

void GameplayScene::build()
{
	//printf("build");
}

void GameplayScene::destroy()
{
	//printf("destory");
}

void GameplayScene::onEntry()
{
	m_shader = Engine::ResourceManager::getShader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
	m_fontShader = Engine::ResourceManager::getShader("assets/shaders/fontVertex.glsl", "assets/shaders/fontFragment.glsl");
	m_batch.init();
	m_fontBatch.init();
	m_minimapBatch.init();
	m_playerBatch.init();
	m_uiBatch.init();
	m_screenDims = m_game->getWindowDimentions();
	glm::vec2 camPos = m_camera.getPosition();
	m_camera.init(m_screenDims.x, m_screenDims.y);
	m_camera.setScale(5.0f);
	m_camera.setPosition(glm::vec2(50, 50));
	m_player.init(&m_camera, m_game->getAudioEngine());
	m_particleSystem = new Engine::ParticleSystem2D(&m_camera);

	m_framebuffer = new Engine::FrameBuffer(glm::vec2(m_screenDims.x, m_screenDims.y), glm::vec2(350, 350));

	glm::vec2 minimapPos = glm::vec2(camPos.x + 0.32 * m_screenDims.x, camPos.y + 0.22 * m_screenDims.y);
	m_minimap = new Engine::Minimap(minimapPos, glm::vec2(250, 250), m_framebuffer->getTexture(), &m_camera);
	m_minimap->init();

	m_tilemap.addMap("assets/maps/dom_karlosa.tmx", glm::vec2(0, 0));

	setupQuests();
	
	loadMusic("assets/sounds/music_box");
	m_game->getAudioEngine().LoadSound("assets/sounds/ambient/barka.ogg", false, true, true);

	m_furnace.addTextureAtlas("assets/textures/items/furnace.png", glm::vec4(0, 0, 32, 73), glm::vec2(1, 3), 2, 1.0f, 0, false);
	m_bucket.init(m_game->getAudioEngine());
}

void GameplayScene::onExit()
{
	m_game->getAudioEngine().StopAllChannels();
	m_game->getAudioEngine().ResetPositionAllChannels();

	m_framebuffer->cleanUp();
	delete m_minimap;
	delete m_framebuffer;
}

void GameplayScene::update(double deltaTime)
{
	handleInput(deltaTime);

	//m_camera.setPosition(m_papajCoords + glm::vec2(25, 15));

	if (m_game->getInputManager().isKeyPressed(SDLK_ESCAPE))
	{
		m_menuDisplay = !m_menuDisplay;
	}
	m_menuDisplay ? m_gameplayState = GameplayState::MENU : m_gameplayState = GameplayState::PLAY;

	if (m_gameplayState != GameplayState::MENU)
	{
		if (m_game->getInputManager().isKeyPressed(SDLK_m))
		{
			m_inventoryMenuDisplay = !m_inventoryMenuDisplay;
		}
		m_inventoryMenuDisplay ? m_gameplayState = GameplayState::INVENTORYMENU : m_gameplayState = GameplayState::PLAY;
	}

	if (m_gameplayState == GameplayState::PLAY)
	{
		if (m_game->getInputManager().isKeyPressed(SDLK_x))
		{
			m_camera.setPosition(glm::vec2(2137, 2137));
			m_vomitMiniGame = true;
		}

		if (m_game->getInputManager().isKeyPressed(SDLK_c))
		{
			m_cameraLock = !m_cameraLock;
		}

		if (m_game->getInputManager().isKeyDown(SDLK_p))
		{
			m_camera.setScale(m_camera.getScale() + 0.5f * deltaTime);
		}

		if (m_game->getInputManager().isKeyDown(SDLK_o))
		{
			m_camera.setScale(m_camera.getScale() - 0.5f * deltaTime);
		}

		if (m_game->getInputManager().isKeyPressed(SDLK_DOWN))
		{
			m_questSystem.previous();
		}

		if (m_game->getInputManager().isKeyPressed(SDLK_UP))
		{
			m_questSystem.next();
		}

		if (m_game->getInputManager().isKeyPressed(SDLK_RETURN))
		{
			m_questSystem.getCurrentQuest().setCurrentObjectiveAsCompleted();
		}

		if (m_game->getInputManager().isKeyPressed(SDLK_PAGEUP))
		{
			m_player.setToxicity(m_player.getToxicity() + 0.1);
		}

		if (m_game->getInputManager().isKeyPressed(SDLK_PAGEDOWN))
		{
			m_player.setToxicity(m_player.getToxicity() - 0.1);
		}

		if (m_game->getInputManager().isKeyPressed(SDLK_9))
		{
			m_game->getAudioEngine().playSound("assets/sounds/music_box/szklanki.ogg");
		}

		if (m_game->getInputManager().isKeyPressed(SDLK_8))
		{
			m_game->getAudioEngine().playSound("assets/sounds/ambient/barka.ogg", Engine::Vector3({0, 0, 0}), -20.0f);
		}

		if (m_game->getInputManager().isKeyPressed(SDLK_7))
		{
			m_game->getAudioEngine().playSound("assets/sounds/music_box/moje_miasto_to_bialystok.ogg");
		}


		if (m_game->getInputManager().isKeyPressed(SDLK_6))
		{
			channelId = m_game->getAudioEngine().playSound("assets/sounds/music_box/mr_bombastic_bass_boosted.ogg");
			printf("channel: %d\n", channelId);
		}

		if (m_game->getInputManager().isKeyPressed(SDLK_b))
		{
			m_game->getAudioEngine().StopAllChannels();
		}

		if (m_game->getInputManager().isKeyPressed(SDLK_SPACE))
		{
			m_game->getAudioEngine().StartAllChannels();
		}

		if (m_game->getInputManager().isKeyPressed(SDLK_n))
		{
			m_game->getAudioEngine().ResetPositionAllChannels();
		}


		if (m_cameraLock)
		{
			m_camera.setPosition(m_player.getPosition() + glm::vec2(32));
		}

		m_player.update(m_game->getInputManager(), m_game->getAudioEngine(), deltaTime);
		m_camera.update();
		m_tilemap.update(m_player.getCollider());

		m_time += 0.1;
		m_amt = m_time * deltaTime * 10.0;

		m_furnace.update(m_player.getCollider(), m_game->getInputManager(), m_game->getAudioEngine(), m_questSystem, deltaTime);
		m_bucket.update(m_player.getCollider(), m_game->getInputManager(), m_game->getAudioEngine(), m_questSystem, deltaTime);
		m_shelf.update(m_player.getCollider(), m_game->getInputManager(), m_game->getAudioEngine(), m_questSystem, deltaTime);

		m_particleSystem->update(deltaTime);
	}

	
	

	if (m_game->getInputManager().isKeyPressed(SDLK_1))
	{
		m_currentState = Engine::ScreenState::CHANGE_NEXT;
	}


	/*if (m_game->getInputManager().isKeyPressed(SDLK_ESCAPE))
	{

		ObjectiveState state = m_questSystem.getCurrentQuest().getCurrentObjective().getState();
		std::string stateName = "nie dziala cos";
		if (state == ObjectiveState::PENDING)
		{
			stateName = "pending";
		}
		else if (state == ObjectiveState::COMPLETED)
		{
			stateName = "completed";
		}
		if (state == ObjectiveState::COMPLETED)
		{
			stateName = "completed";
		}
		else if (state == ObjectiveState::FAILED)
		{
			stateName = "failed";
		}
		else
		{
			stateName = "czemu to nie dziala";
		}

		printf("Objective State Before: %s\n", stateName.c_str());
		m_questSystem.getCurrentQuest().getCurrentObjective().setState(ObjectiveState::COMPLETED);
		m_questSystem.getCurrentQuest().setObjectiveState("Polacz skladniki w boza calosc", ObjectiveState::CURRENT);
		state = m_questSystem.getCurrentQuest().getCurrentObjective().getState();
		if (state == ObjectiveState::PENDING)
		{
			stateName = "pending";
		}
		if (state == ObjectiveState::COMPLETED)
		{
			stateName = "completed";
		}
		if (state == ObjectiveState::CURRENT)
		{
			stateName = "current";
		}
		printf("Objective State After: %s\n", stateName.c_str());
		printf("Quest: %s\n", m_questSystem.getCurrentQuest().getName().c_str());
		printf("Obj: %s\n", m_questSystem.getCurrentQuest().getCurrentObjective().getName().c_str());
		printf("State: %d\n", state);
	}*/
}

void GameplayScene::draw()
{

	glActiveTexture(GL_TEXTURE0);
	m_shader.start();

	GLint textureLocation = m_shader.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);


	GLuint pLocation = m_shader.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_tilemap.render(m_playerBatch);

	m_batch.begin();
	m_playerBatch.begin();

	glm::vec2 camPos = m_camera.getPosition();
	float camScale = m_camera.getScale();
	m_screenDims = m_game->getWindowDimentions();

	if (m_gameplayState != GameplayState::MENU)
	{

		m_batch.draw(glm::vec4(-1000, -800, 1000, 1000), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			Engine::ResourceManager::getTexture("assets/textures/papaj.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

		m_batch.draw(glm::vec4(1945, 2029, 1920 / 5, 1080 / 5), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			Engine::ResourceManager::getTexture("assets/textures/miska.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));



		m_pos.y += glm::sin(m_amt);
		m_pos.x += glm::sin(m_amt + 3.14 / 2.0);

		m_batch.draw(glm::vec4(m_pos.x, m_pos.y, 100, 50), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			Engine::ResourceManager::getTexture("assets/textures/e36.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255), m_amt + 3.14 * 1.25);


		m_furnace.draw(m_batch, m_particleSystem);
		m_bucket.draw(m_batch, m_particleSystem);
		m_shelf.draw(m_batch, m_particleSystem);

		m_particleSystem->draw(m_batch);
		m_player.draw(m_playerBatch, camScale);
	}

	if (m_gameplayState == GameplayState::MENU)
	{
		{
			// position the controls widget in the top-right corner
			ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Always);
			ImGui::SetNextWindowSize(ImVec2(400, m_game->getWindowDimentions().y));

			// create a window and append into it
			ImGui::Begin("jebac disa", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize);

			ImGui::Dummy(ImVec2(0.0f, m_game->getWindowDimentions().y / 3));

			// buttons and most other widgets return true when clicked/edited/activated
			if (ImGui::Button("Play", ImVec2(400, 50)))
			{
				m_currentState = Engine::ScreenState::CHANGE_NEXT;
			}
			ImGui::Dummy(ImVec2(0.0f, 20.0f));
			if (ImGui::Button("Load Game", ImVec2(400, 50)))
			{
				std::cout << "load game button clicked\n";
			}
			ImGui::Dummy(ImVec2(0.0f, 20.0f));
			if (ImGui::Button("Quit to Main Menu", ImVec2(400, 50)))
			{
				m_currentState = Engine::ScreenState::CHANGE_PREVIOUS;
				std::cout << "quit button clicked\n";
			}
			ImGui::Dummy(ImVec2(0.0f, 20.0f));
			if (ImGui::Button("Quit", ImVec2(400, 50)))
			{
				m_currentState = Engine::ScreenState::EXIT_APPLICATION;
				std::cout << "quit button clicked\n";
			}

			ImGui::End();
		}
	}

	if (m_gameplayState == GameplayState::INVENTORYMENU)
	{
		if (m_drawQuests)
		{
			renderImGuiQuestMenuSection();
		}

		{
			// position the controls widget in the top-right corner
			ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
			ImGui::SetNextWindowSize(ImVec2(m_game->getWindowDimentions().x, m_game->getWindowDimentions().y));

			// create a window and append into it
			ImGui::Begin("jebac disa", NULL, ImGuiWindowFlags_NoTitleBar /*| ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize*/);

			ImGui::Dummy(ImVec2(0.0f, (m_game->getWindowDimentions().y / 2) - 100));

			// buttons and most other widgets return true when clicked/edited/activated
			ImGui::Dummy(ImVec2(600.0f, 0.0f));
			ImGui::SameLine();
			if (ImGui::Button("Bestiariusz", ImVec2(64, 64)))
			{
				
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(100.0f, 0.0f));
			ImGui::SameLine();
			if (ImGui::Button("Mapa", ImVec2(64, 64)))
			{
				
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(100.0f, 0.0f));
			ImGui::SameLine();
			if (ImGui::Button("Zadania", ImVec2(64, 64)))
			{
				m_drawQuests = !m_drawQuests;
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(100.0f, 0.0f));
			ImGui::SameLine();
			if (ImGui::Button("Spanko", ImVec2(64, 64)))
			{
				std::cout << "quit button clicked\n";
			}

			ImGui::End();
		}
	}

	m_playerBatch.end();
	m_batch.end();
	m_batch.renderBatch();
	m_framebuffer->bind();
	m_tilemap.render(m_playerBatch);
	m_batch.renderBatch();
	m_framebuffer->unbind();

	m_shader.stop();


	if (m_gameplayState != GameplayState::MENU)
	{

		drawUI();

		float xPos = (camPos.x + m_screenDims.x / 2 / camScale) - m_screenDims.x / 5 / camScale;
		float yPos = (camPos.y + m_screenDims.y / 2 / camScale) - m_screenDims.y / 10 / camScale;

		glm::vec2 minimapPos = glm::vec2(xPos, yPos);


		glm::vec2 minimapDims(m_screenDims.x / 4 / camScale, m_screenDims.y / 4 / camScale);
		glm::vec4 minimapDestRect = glm::vec4(m_camera.getPosition().x + ((m_screenDims.x / 2 - 25 - minimapDims.x * camScale) / camScale),
			m_camera.getPosition().y + ((m_screenDims.y / 2 - 25 - minimapDims.y * camScale) / camScale), minimapDims.x, minimapDims.y);

		m_minimap->setDimentions(minimapDims - glm::vec2(20) / camScale);
		m_minimap->setPosition(glm::vec2(minimapDestRect.x + 10 / camScale, minimapDestRect.y + 10 / camScale));
		m_minimap->draw(m_minimapBatch);

		m_shader.start();
		m_minimapBatch.begin();




		m_minimapBatch.draw(minimapDestRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			Engine::ResourceManager::getTexture("assets/textures/minimap_frame.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

		m_minimapBatch.end();
		m_minimapBatch.renderBatch();
		m_shader.stop();
	}
}

void GameplayScene::drawUI()
{
	drawUIBackground();

	drawUIFonts();
}

void GameplayScene::drawUIFonts()
{
	m_fontShader.start();

	GLint textureLocation = m_fontShader.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);


	GLuint pLocation = m_fontShader.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_fontBatch.begin();

	float camScale = m_camera.getScale();
	glm::vec2 camPos = m_camera.getPosition();

	float xPos = (camPos.x + m_screenDims.x / 2 / camScale) - m_screenDims.x / 8 / camScale;
	float yPos = (camPos.y + m_screenDims.y / 2 / camScale) - m_screenDims.y / 2.9 / camScale;

	float resScale = m_screenDims.x / 1920.0f;

	m_furnace.drawFonts(m_fontBatch, resScale);
	m_bucket.drawFonts(m_fontBatch, resScale);
	m_shelf.drawFonts(m_fontBatch, resScale);

	Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(m_fontBatch, m_questSystem.getCurrentQuest().getName().c_str(),
		glm::vec2(xPos, yPos),
		glm::vec2(0.7f * resScale / camScale), 1.0f,
		Engine::ColorRGBA8(179, 154, 126, 255), Engine::Justification::MIDDLE);

	std::vector<Engine::Objective> objectives = m_questSystem.getCurrentQuest().getObjectives();

	for (int i = 0; i < objectives.size(); i++)
	{
		Engine::ColorRGBA8 color;
		if (objectives[i].getState() == ObjectiveState::CURRENT)
		{
			color = Engine::ColorRGBA8(255, 255, 255, 255);
		}
		if (objectives[i].getState() == ObjectiveState::PENDING)
		{
			color = Engine::ColorRGBA8(180, 180, 180, 255);
		}
		if (objectives[i].getState() == ObjectiveState::COMPLETED)
		{
			color = Engine::ColorRGBA8(0, 200, 0, 255);
		}

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(m_fontBatch, objectives[i].getName().c_str(),
			glm::vec2(xPos, yPos - 20 / camScale - (20 * (i + 1) * resScale / camScale)),
			glm::vec2(0.6f * resScale / camScale), 1.0f,
			color, Engine::Justification::MIDDLE);
	}

	glm::vec2 itemDims(300 * resScale / camScale, 50 * resScale / camScale);
	glm::vec4 itemDestRect = glm::vec4(m_camera.getPosition().x - ((m_screenDims.x / 2 - 160) / camScale),
		m_camera.getPosition().y - ((m_screenDims.y / 2) - 113) / camScale, itemDims.x, itemDims.y);


	Engine::ResourceManager::getFont("assets/fonts/NotoSans-Regular.ttf", 32)->draw(m_fontBatch, "1 Wyzimski Czempion",
		glm::vec2(itemDestRect.x, itemDestRect.y + (120 * resScale / camScale)),
		glm::vec2(0.5f * resScale / camScale), 1.0f,
		Engine::ColorRGBA8(255, 255, 255, 255), Engine::Justification::LEFT);

	Engine::ResourceManager::getFont("assets/fonts/NotoSans-Regular.ttf", 32)->draw(m_fontBatch, "1 Redanski Lager",
		glm::vec2(itemDestRect.x, itemDestRect.y + (60 * resScale / camScale)),
		glm::vec2(0.5f * resScale / camScale), 1.0f,
		Engine::ColorRGBA8(255, 255, 255, 255), Engine::Justification::LEFT);

	Engine::ResourceManager::getFont("assets/fonts/NotoSans-Regular.ttf", 32)->draw(m_fontBatch, "98 belty",
		glm::vec2(itemDestRect.x, itemDestRect.y),
		glm::vec2(0.5f * resScale / camScale), 1.0f,
		Engine::ColorRGBA8(255, 255, 255, 255), Engine::Justification::LEFT);

	m_statStream.str(std::string());
	m_statStream << m_game->getStats();
	Engine::ResourceManager::getFont("assets/fonts/NotoSans-Regular.ttf", 24)->draw(m_fontBatch, m_statStream.str().c_str(),
		glm::vec2(camPos.x - 0.45 * m_screenDims.x / camScale, camPos.y + 0.45 * m_screenDims.y / camScale),
		glm::vec2(0.75f / camScale), 1.0f,
		Engine::ColorRGBA8(255, 255, 255, 255), Engine::Justification::LEFT);

	float xPosH = (camPos.x + m_screenDims.x / 2 / camScale) - m_screenDims.x / 2.48 / camScale;
	float yPosH = (camPos.y + m_screenDims.y / 2 / camScale) - m_screenDims.y / 15.4 / camScale;

	Engine::ResourceManager::getFont("assets/fonts/NotoSans-Regular.ttf", 32)->draw(m_fontBatch, "21:37 Dom Karlosa",
		glm::vec2(xPosH, yPosH),
		glm::vec2(0.5f * resScale / camScale), 1.0f,
		Engine::ColorRGBA8(255, 255, 255, 255), Engine::Justification::LEFT);

	m_fontBatch.end();

	m_fontBatch.renderBatch();
	m_fontShader.stop();
}

void GameplayScene::drawUIBackground()
{
	m_shader.start();
	m_uiBatch.begin();

	float camScale = m_camera.getScale();
	glm::vec2 camPos = m_camera.getPosition();

	float resScale = m_screenDims.x / 1920.0f;

	float xPos = (camPos.x + m_screenDims.x / 2 / camScale) - m_screenDims.x / 5 / camScale;
	float yPos = (camPos.y + m_screenDims.y / 2 / camScale) - m_screenDims.y / 10 / camScale;


	glm::vec2 minimapDims(m_screenDims.x / 4 / camScale, m_screenDims.y / 4 / camScale);
	glm::vec4 minimapDestRect = glm::vec4(m_camera.getPosition().x + ((m_screenDims.x / 2 - 25 - minimapDims.x * camScale) / camScale),
		m_camera.getPosition().y + ((m_screenDims.y / 2 - 25 - minimapDims.y * camScale) / camScale), minimapDims.x, minimapDims.y);
	glm::vec2 infoDims = glm::vec2(200 / camScale, 32 / camScale);

	float xPosB = (camPos.x + m_screenDims.x / 2 / camScale) - m_screenDims.x / 4.22 / camScale;
	float yPosB = (camPos.y + m_screenDims.y / 2 / camScale) - m_screenDims.y / 2 / camScale;

	glm::vec2 dims(m_screenDims.x / 4.48 / camScale, m_screenDims.y / 5 / camScale);

	m_uiBatch.draw(glm::vec4(xPosB, yPosB, dims), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/quest_desc_background.png").id, 1.0f, Engine::ColorRGBA8(0, 0, 0, 180));

	m_uiBatch.draw(glm::vec4(minimapDestRect.x - 100 / camScale - infoDims.x, minimapDestRect.y + minimapDims.y - 50 / camScale, infoDims), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/info_background.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_uiBatch.draw(glm::vec4(minimapDestRect.x - 120 / camScale, minimapDestRect.y + minimapDims.y - 65 / camScale, glm::vec2(64 / camScale)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/circle.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_uiBatch.draw(glm::vec4(minimapDestRect.x + 30 / camScale - infoDims.x, minimapDestRect.y + minimapDims.y - 150 / camScale, infoDims), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/info_background.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	float xPosLeftRight = (camPos.x - m_screenDims.x / 2 / camScale) + 100 / camScale;
	float yPosLeftRight = (camPos.y + m_screenDims.y / 2 / camScale) - 150 / camScale;

	m_uiBatch.draw(glm::vec4(xPosLeftRight, yPosLeftRight, glm::vec2(512 / camScale, 50 / camScale)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/health_bar.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_uiBatch.draw(glm::vec4(xPosLeftRight + 100 / camScale, yPosLeftRight - 60 / camScale, glm::vec2(200 / camScale, 64 / camScale)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/toxicity_background.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	float toxicity = m_player.getToxicity();
	m_uiBatch.draw(glm::vec4(xPosLeftRight + 100 / camScale, yPosLeftRight - 60 / camScale, glm::vec2(200 * toxicity / camScale, 64 / camScale)), glm::vec4(0.0f, 0.0f, toxicity, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/toxicity.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_uiBatch.draw(glm::vec4(xPosLeftRight + 100 / camScale, yPosLeftRight - 60 / camScale, glm::vec2(200 / camScale, 64 / camScale)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/toxicity_frame.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_uiBatch.draw(glm::vec4(xPosLeftRight + 122 / camScale, yPosLeftRight - 43 / camScale, glm::vec2(24 / camScale, 24 / camScale)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/toxicity_icon.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_uiBatch.draw(glm::vec4(xPosLeftRight, yPosLeftRight, glm::vec2(512 / camScale, 50 / camScale)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/health_bar_frame.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_uiBatch.draw(glm::vec4(xPosLeftRight - 50 / camScale, yPosLeftRight - 50 / camScale, glm::vec2(150 / camScale, 150 / camScale)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/papaj_glowa.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	glm::vec2 itemDims(300 * resScale / camScale, 50 * resScale / camScale);
	glm::vec4 itemDestRect = glm::vec4(m_camera.getPosition().x - ((m_screenDims.x / 2 - 100) / camScale),
		m_camera.getPosition().y - ((m_screenDims.y / 2 - 100) / camScale), itemDims.x, itemDims.y);
	m_uiBatch.draw(glm::vec4(itemDestRect), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/item_background.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_uiBatch.draw(glm::vec4(itemDestRect + glm::vec4(0, 60 * resScale / camScale, 0, 0)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/item_background.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_uiBatch.draw(glm::vec4(itemDestRect + glm::vec4(0, 120 * resScale / camScale, 0, 0)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/item_background.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));
	
	m_uiBatch.draw(glm::vec4(itemDestRect.x, itemDestRect.y + 120 * resScale / camScale, 64 * 0.8 * resScale / camScale, 64 * 0.8 * resScale / camScale), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/wyzimski_czempion.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_uiBatch.draw(glm::vec4(itemDestRect.x, itemDestRect.y + 60 * resScale / camScale, 64 * 0.8 * resScale / camScale, 64 * 0.8 * resScale / camScale), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Engine::ResourceManager::getTexture("assets/textures/redanski_lager.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_bucket.drawUIBackground(m_uiBatch);
	m_furnace.drawUIBackground(m_uiBatch);
	m_shelf.drawUIBackground(m_uiBatch);

	m_uiBatch.end();
	m_uiBatch.renderBatch();
	m_shader.stop();
}

void GameplayScene::handleInput(double deltaTime)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		m_game->onSDLEvent(event);
	}
}

void GameplayScene::setupQuests()
{
	Engine::Quest karlitoQuest1("OSTATNIE PRZYGOTOWANIA", "Poloz dziadkow do spania, dojeb do pieca, pochowaj przedmioty ktorych nie mozna rozjebac, zablokuj wejscie na balkon itd.");
	karlitoQuest1.addObjective("Poloz dziadkow do spania");
	karlitoQuest1.setLastObjectiveState(ObjectiveState::COMPLETED);
	karlitoQuest1.addObjective("doloz do pieca");
	karlitoQuest1.setLastObjectiveState(ObjectiveState::CURRENT);
	karlitoQuest1.addObjective("pochowaj przedmioty ktorych nie mozna rozjebac");
	karlitoQuest1.addObjective("zablokuj wejscie na balkon");
	m_questSystem.addQuest(karlitoQuest1);

	Engine::Quest karlitoQuest2("OSTATNIA WIECZERZA", "zrob kremowke taka co nie widzial jej nikt, nastepnie poczestuj nia biesiadnikow w czasie papiezowej godziny razem spiewajac weselnie piekny hymn zoltej mordy");
	karlitoQuest2.addObjective("Odbierz skladniki od Pana Michala");
	karlitoQuest2.setLastObjectiveState(ObjectiveState::CURRENT);
	karlitoQuest2.addObjective("Polacz skladniki w boza calosc");
	karlitoQuest2.addObjective("Poczekaj az kremowka dojdzie (opcjonalnie)");
	m_questSystem.addQuest(karlitoQuest2);

	Engine::Quest karlitoQuest3("W4D CZAS ZACZAC", "Wykonaj spektakularne przemowienie ktorym rozpoczniesz najwieksza inbe w historii.");
	karlitoQuest3.addObjective("Udaj sie do pokoju goscinnego");
	karlitoQuest3.setLastObjectiveState(ObjectiveState::CURRENT);
	karlitoQuest3.addObjective("Zbierz wszystkich i wyglos przemowe");
	m_questSystem.addQuest(karlitoQuest3);

	Engine::Quest allQuest1("BOZY CZAS", "Rowno o godzinie 21:37 wszyscy uczestnicy biesiady odspiewali najglosniejsza i najbardziej majestatyczna barke.");
	allQuest1.addObjective("Udaj sie do pokoju goscinnego.");
	allQuest1.setLastObjectiveState(ObjectiveState::CURRENT);
	allQuest1.addObjective("Zaspiewaj barke z wszystkimi uczestnikami biesiady.");
	m_questSystem.addQuest(allQuest1);

	Engine::Quest dadziakQuest1("PROSTOWANIE INTERESOW", "Dadziak musi uzyc dostepnych narzedzi aby wyprostowac garba. Jedyne co ma do wyboru to duze, czarne gumowe jebadlo.");
	dadziakQuest1.addObjective("Wyprostuj garba 1.");
	dadziakQuest1.setLastObjectiveState(ObjectiveState::CURRENT);
	dadziakQuest1.addObjective("Wyprostuj garba 2.");
	dadziakQuest1.addObjective("Wyprostuj garba 3.");
	dadziakQuest1.addObjective("Wyprostuj garba 4.");
	m_questSystem.addQuest(dadziakQuest1);

	Engine::Quest kapecQuest1("AMBA FATIMA BYLECH I NIMA", "Gdy dziolszka do ciebie przyjdzie na noc strzel jej w ryj z kilometra aby poszla spac, plot twist, ma ryj z betonu, lamiesz reke i chuja z imprezy");
	kapecQuest1.addObjective("Tak kochanie 1.");
	kapecQuest1.setLastObjectiveState(ObjectiveState::CURRENT);
	kapecQuest1.addObjective("Tak kochanie 2.");
	kapecQuest1.addObjective("Tak kochanie 3.");
	kapecQuest1.addObjective("Tak kochanie 4.");
	m_questSystem.addQuest(kapecQuest1);

	Engine::Quest karzelQuest1("PO OMACKU", "Zmontuj najpotezniejsze wiadro jakie widzial swiat.");
	karzelQuest1.addObjective("Nabij wiaderko.");
	karzelQuest1.setLastObjectiveState(ObjectiveState::CURRENT);
	karzelQuest1.addObjective("Zapros innych do wspolnego smagania.");
	karzelQuest1.addObjective("Zesmagaj wiadro.");
	m_questSystem.addQuest(karzelQuest1);
}

void GameplayScene::loadMusic(const std::string& musicDirectory)
{
	for (const auto& entry : std::filesystem::directory_iterator(musicDirectory))
	{
		std::string path = entry.path().string();
		while (path.find("\\") != std::string::npos)
		{
			path.replace(path.find("\\"), 1, "/");
		}

		if (m_game->getAudioEngine().LoadSound(path) == Engine::SoundStatus::LOADED_NOW)
		{
			m_musicList.push_back(path);
		}
	}
}

void GameplayScene::renderImGuiQuestMenuSection()
{
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(m_screenDims.x, m_screenDims.y));

	ImGui::Begin("Quests", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize);

	std::vector<Engine::Quest> quests = m_questSystem.getAllQuests();

	ImGui::SetNextWindowPos(ImVec2(200, 200));
	ImGui::SetNextWindowSize(ImVec2(600, 600));

	ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize);

	if (ImGui::CollapsingHeader("ZADANIA GLOWNE"))
	{	
		for (int i = 0; i < quests.size(); i++)
		{
			if (ImGui::Button(quests[i].getName().c_str(), ImVec2(600, 50)))
			{

			}
		}
	}

	if (ImGui::CollapsingHeader("ZADANIA POBOCZNE"))
	{

		if (ImGui::Button("sd", ImVec2(600, 50)))
		{

		}
		if (ImGui::Button("quest1", ImVec2(600, 50)))
		{

		}
		if (ImGui::Button("quest1", ImVec2(600, 50)))
		{

		}
	}

	if (ImGui::CollapsingHeader("ZAKONCZONO"))
	{
		if (ImGui::Button("quest1", ImVec2(600, 50)))
		{

		}
	}



	ImGui::End();

	ImGui::End();
}




