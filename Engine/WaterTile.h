#pragma once

#include <glm.hpp>

#include "GLSLProgram.h"
#include "GLTexture.h"
#include "SpriteBatch.h"
#include "Camera.h"

namespace Engine
{

	class WaterTile
	{
	public:

		WaterTile(const glm::vec2& position, const glm::vec2& dimentions, GLTexture reflectionTexture, Camera* camera);
		~WaterTile();

		void init();
		void draw(SpriteBatch spriteBatch);

	private:
		Camera* m_camera;

		glm::vec2 m_dimentions;
		glm::vec2 m_position;

		GLSLProgram m_shader;
		GLTexture m_texture;
		GLTexture m_dudvMap;
	};
}
