#include "App.h"

App::App()
{
	//m_windowDimentions = glm::vec2(1600, 900);
	//m_windowDimentions = glm::vec2(1280, 768);
	m_windowDimentions = glm::vec2(1920, 1080);
	m_windowName = "Jebanie Disa";
}

App::~App()
{
	m_screenList->destroy();
}

void App::onInit()
{

}

void App::addScreens()
{
	m_gameplayScene = std::make_unique<GameplayScene>();
	m_screenList->addScreen(m_gameplayScene.get());
	//m_screenList->setScreen(m_gameplayScene->getScreenIndex());

	m_creditsScene = std::make_unique<CreditsScene>();
	m_screenList->addScreen(m_creditsScene.get());
	//m_screenList->setScreen(m_creditsScreen->getScreenIndex());

	m_launchScene = std::make_unique<LaunchScene>();
	m_screenList->addScreen(m_launchScene.get());
	//m_screenList->setScreen(m_launchScreen->getScreenIndex());

	m_mainMenuScene = std::make_unique<MainMenuScene>();
	m_screenList->addScreen(m_mainMenuScene.get());
	//m_screenList->setScreen(m_mainMenuScreen->getScreenIndex());

	m_infScene = std::make_unique<InfScene>();
	m_screenList->addScreen(m_infScene.get());
	m_screenList->setScreen(m_infScene->getScreenIndex());
}

void App::onExit()
{

}