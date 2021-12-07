#pragma once

#include <vector>
#include "IGameScene.h"

namespace Engine
{
	class IMainGame;

	class ScreenList
	{
	public:
		ScreenList(IMainGame* game);
		~ScreenList();
		
		IGameScene* moveNext();
		IGameScene* movePrevious();

		void addScreen(IGameScene* newScreen);
		void setScreen(int nextScreen);

		void destroy();

		IGameScene* getCurrent();
	protected:
		IMainGame* m_game = nullptr;
		std::vector<IGameScene*> m_screens;
		int m_currentScreenIndex = -1;
	};
}
