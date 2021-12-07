#pragma once

#include "TexturedModel.h"

#include <glm.hpp>

namespace Engine
{
	class Entity
	{
	public:
		Entity() :
			m_model(nullptr),
			m_position(glm::vec3(0, 0, 0)),
			m_rotation(glm::vec3(0, 0, 0)),
			m_scale(glm::vec3(1, 1, 1))
		{}
		~Entity()
		{}

		void init(TexturedModel* model, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
		{
			m_model = model;
			m_position = pos;
			m_rotation = rot;
			m_scale = scale;
		}

		TexturedModel* getModel() { return m_model; }

		glm::vec3 getPosition() { return m_position; }
		glm::vec3 getRotation() { return m_rotation; }
		glm::vec3 getScale() { return m_scale; }

		void setPosition(glm::vec3 position) { m_position = position; }
		void setRotation(glm::vec3 rotation) { m_rotation = rotation; }
		void setScale(glm::vec3 scale) { m_scale = scale; }

	private:
		TexturedModel* m_model;
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	};

}
