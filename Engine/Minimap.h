#pragma once

#include <glm.hpp>
#include "GLTexture.h"
#include "Camera.h"
#include "SpriteBatch.h"
#include "GLSLProgram.h"

namespace Engine
{
	class Minimap
	{
	public:
		Minimap(const glm::vec2& position, const glm::vec2& dimentions, GLTexture reflectionTexture, Camera* camera);
		~Minimap();

		void init();
		void draw(SpriteBatch spriteBatch);
		void setDimentions(glm::vec2 dims);
		void setPosition(glm::vec2 pos);

	private:
		Camera* m_camera;

		glm::vec2 m_dimentions;
		glm::vec2 m_position;

		GLSLProgram m_shader;
		GLTexture m_texture;
	};
}
