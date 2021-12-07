#pragma once

#include "../Engine/IMainGame.h"
#include "GameplayScene.h" 
#include "CreditsScene.h"
#include "LaunchScene.h"
#include "MainMenuScene.h"
#include "InfScene.h"

class App : public Engine::IMainGame
{
public:
	App();
	~App();

	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;
private:
	std::unique_ptr<GameplayScene> m_gameplayScene = nullptr;
	std::unique_ptr<CreditsScene> m_creditsScene = nullptr;
	std::unique_ptr<LaunchScene> m_launchScene = nullptr;
	std::unique_ptr<MainMenuScene> m_mainMenuScene = nullptr;
	std::unique_ptr<InfScene> m_infScene = nullptr;
};

