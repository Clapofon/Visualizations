#pragma once

#include <glm.hpp>

namespace Engine
{
	class Light
	{
	public:
		Light(const glm::vec3& pos, glm::vec3 color) :
			m_position(pos),
			m_color(color)
		{}
		~Light()
		{}

		glm::vec3 getPosition() { return m_position; }
		glm::vec3 getColor() { return m_color; }

		void setPosition(glm::vec3 position) { m_position = position; }
		void setColor(glm::vec3 color) { m_color = color; }

	private:
		glm::vec3 m_position;
		glm::vec3 m_color;
	};
}
