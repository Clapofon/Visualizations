#include "FrameBuffer.h"

#include <iostream>

namespace Engine
{

	FrameBuffer::FrameBuffer(const glm::vec2& displayDims, const glm::vec2& fbDims) :
		m_display(displayDims),
		m_dimentions(fbDims)
	{
		init();
	}

	FrameBuffer::~FrameBuffer()
	{
		cleanUp();
	}

	//call when closing the game
	void FrameBuffer::cleanUp()
	{
		glDeleteFramebuffers(1, &m_fbo);
		glDeleteTextures(1, &m_texture.id);
		glDeleteRenderbuffers(1, &m_rbo);
	}

	//call before rendering to this FBO
	void FrameBuffer::bind()
	{
		bindBuffer();
	}

	//call to switch to default frame buffer
	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glViewport(0, 0, m_display.x, m_display.y);
	}

	//get the resulting texture
	GLTexture FrameBuffer::getTexture()
	{
		return m_texture;
	}

	void FrameBuffer::init()
	{
		glGenFramebuffers(1, &m_fbo);
		glGenTextures(1, &(m_texture.id));
		glBindTexture(GL_TEXTURE_2D, m_texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_dimentions.x, m_dimentions.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		glGenRenderbuffers(1, &m_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_dimentions.x, m_dimentions.y);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture.id, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "ERROR framebuffer -> " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << "\n";
		}
	}

	void FrameBuffer::bindBuffer()
	{
		glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
		glViewport(0, 0, m_dimentions.x, m_dimentions.y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}