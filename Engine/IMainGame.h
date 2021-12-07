#pragma once

#include "Engine.h"
#include "Window.h"
#include "IGameScene.h"
#include "ScreenList.h"
#include "InputManager.h"
#include "AudioEngine.h"
#include "ParticleSystem2D.h"
#include "Time.h"

#include <memory>
#include <sstream>

namespace Engine
{
	class IMainGame
	{
	public:
		IMainGame();
		virtual ~IMainGame();

		void run();
		void exit();

		virtual void onInit() = 0;
		virtual void addScreens() = 0;
		virtual void onExit() = 0;
		void onSDLEvent(SDL_Event& event);

		InputManager getInputManager() { return m_inputManager; }
		AudioEngine getAudioEngine() { return m_audioEngine; }
		Window getWindow() { return m_window; }
		std::string getStats() { return m_stat; }

		glm::vec2 getWindowDimentions() { return m_windowDimentions; }


	protected:
		bool init();
		bool initSystems();
		void update(double deltaTime);
		void draw();
		//double getTime();

		std::unique_ptr<ScreenList> m_screenList = nullptr;
		IGameScene* m_currentScreen = nullptr;
		bool m_isRunning = false;

		Window m_window;
		InputManager m_inputManager;
		AudioEngine m_audioEngine;

		Uint32 m_fps = 0;
		double m_frameCap = 60.0f;
		double m_lastTime = (double)SDL_GetTicks() / 1000.0;
		double m_fpsTimeCounter = 0.0;
		double m_updateTimer = 1.0;
		float m_frameTime = 1.0 / m_frameCap;
		double m_msPerFrame = 0.0;
		double m_deltaTime = 0.0;

		double a = 0.0;

		glm::vec2 m_windowDimentions = glm::vec2(1280, 768);
		std::string m_windowName = "Default";

		std::string m_stat;

	};
}
