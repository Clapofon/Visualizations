#include "InputManager.h"

namespace Engine
{

	InputManager::InputManager() :
		m_mouseCoords(glm::vec2(0, 0)),
		m_mouseCoordsRel(glm::vec2(0, 0))
	{}

	InputManager::~InputManager()
	{}

	void InputManager::update()
	{
		for (auto it = m_keyMap.begin(); it != m_keyMap.end(); it++)
		{
			m_previousKeyMap[it->first] = it->second;
		}
		m_mouseCoordsRel = glm::vec2(0);
	}

	void InputManager::onKeyDown(unsigned int keyID)
	{
		m_keyMap[keyID] = true;
	}

	void InputManager::onKeyUp(unsigned int keyID)
	{
		m_keyMap[keyID] = false;
	}

	bool InputManager::isKeyDown(unsigned int keyID)
	{
		auto it = m_keyMap.find(keyID);

		if (it != m_keyMap.end())
		{
			return it->second;
		}
		else
		{
			return false;
		}
	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		bool isPressed;
		if (isKeyDown(keyID) && !wasKeyDown(keyID))
		{
			return true;
		}

		return false;
	}

	bool InputManager::wasKeyDown(unsigned int keyID)
	{
		auto it = m_previousKeyMap.find(keyID);

		if (it != m_previousKeyMap.end())
		{
			return it->second;
		}
		else
		{
			return false;
		}
	}

	glm::vec2 InputManager::getMouseCoords()
	{
		return m_mouseCoords;
	}

	glm::vec2 InputManager::getMouseCoordsRel()
	{
		return m_mouseCoordsRel;
	}

	void InputManager::onMouseMove(float x, float y, float xrel, float yrel)
	{
		m_mouseCoords.x = x;
		m_mouseCoords.y = y;
		m_mouseCoordsRel.x = xrel;
		m_mouseCoordsRel.y = yrel;
	}
}