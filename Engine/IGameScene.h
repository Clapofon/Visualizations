#pragma once

#define SCREEN_INDEX_NO_SCREEN -1

namespace Engine
{
	class IMainGame;

	enum class ScreenState
	{
		NONE,
		RUNNING,
		EXIT_APPLICATION,
		CHANGE_NEXT,
		CHANGE_PREVIOUS
	};

	class IGameScene
	{
	public:
		friend class ScreenList;

		IGameScene() {}
		~IGameScene() {}

		virtual int getNextScreenIndex() const = 0;
		virtual int getPreviousScreenIndex() const = 0;

		virtual void build() = 0;
		virtual void destroy() = 0;

		virtual void onEntry() = 0;
		virtual void onExit() = 0;

		virtual void update(double deltaTime) = 0;
		virtual void draw() = 0;

		int getScreenIndex() const { return m_screenIndex; }

		void setParentGame(IMainGame* game) { m_game = game; }

		ScreenState getState() { return m_currentState; }

		void setRunning() { m_currentState = ScreenState::RUNNING; }

	protected:
		ScreenState m_currentState = ScreenState::NONE;
		IMainGame* m_game = nullptr;
		int m_screenIndex = -1;
	};
}
