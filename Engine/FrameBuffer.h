#pragma once

#include "GLTexture.h"

#include <glew.h>
#include <glm.hpp>

namespace Engine
{

	class FrameBuffer
	{
	public:

		FrameBuffer(const glm::vec2& displayDims, const glm::vec2& fbDims);
		~FrameBuffer();

		void cleanUp();

		void bind();

		void unbind();

		GLTexture getTexture();

	private:

		void init();

		void bindBuffer();

		glm::vec2 m_dimentions;
		glm::vec2 m_display;

		GLuint m_fbo;
		GLTexture m_texture;
		GLuint m_depthBuffer;
		GLuint m_rbo;
	};

}

