#pragma once

#include <unordered_map>

#include <glm.hpp>

namespace Engine
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void onKeyDown(unsigned int keyID);
		void onKeyUp(unsigned int keyID);

		bool isKeyDown(unsigned int keyID);
		bool isKeyPressed(unsigned int keyID);

		glm::vec2 getMouseCoords();
		glm::vec2 getMouseCoordsRel();
		void onMouseMove(float x, float y, float xrel, float yrel);

	private:

		bool wasKeyDown(unsigned int keyID);

		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previousKeyMap;

		glm::vec2 m_mouseCoords;
		glm::vec2 m_mouseCoordsRel;

	};

}