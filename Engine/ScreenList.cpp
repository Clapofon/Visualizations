#include "ScreenList.h"

namespace Engine
{
	ScreenList::ScreenList(IMainGame* game) :
		m_game(game)
	{

	}

	ScreenList::~ScreenList()
	{
		destroy();
	}

	IGameScene* ScreenList::moveNext()
	{
		IGameScene* currentScreen = getCurrent();
		if (currentScreen->getNextScreenIndex() != SCREEN_INDEX_NO_SCREEN)
		{
			m_currentScreenIndex = currentScreen->getNextScreenIndex();
		}
		return getCurrent();
	}

	IGameScene* ScreenList::movePrevious()
	{
		IGameScene* currentScreen = getCurrent();
		if (currentScreen->getPreviousScreenIndex() != SCREEN_INDEX_NO_SCREEN)
		{
			m_currentScreenIndex = currentScreen->getPreviousScreenIndex();
		}
		return getCurrent();
	}

	void ScreenList::addScreen(IGameScene* newScreen)
	{
		newScreen->m_screenIndex = m_screens.size();
		m_screens.push_back(newScreen);
		newScreen->build();
		newScreen->setParentGame(m_game);
	}

	void ScreenList::setScreen(int nextScreen)
	{
		m_currentScreenIndex = nextScreen;
	}

	void ScreenList::destroy()
	{
		for (size_t i = 0; i < m_screens.size(); i++)
		{
			m_screens[i]->destroy();
			delete m_screens[i];
		}
		m_screens.resize(0);
		m_currentScreenIndex = SCREEN_INDEX_NO_SCREEN;
	}

	IGameScene* ScreenList::getCurrent()
	{
		if (m_currentScreenIndex == SCREEN_INDEX_NO_SCREEN) return nullptr;
		return m_screens[m_currentScreenIndex];
	}
}