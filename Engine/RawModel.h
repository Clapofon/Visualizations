#pragma once

#include <glew.h>

namespace Engine
{
	class RawModel
	{
	public:
		RawModel(GLuint vaoID, int vertexCount);
		~RawModel();

		GLuint getVaoID() { return m_vaoID; }
		int getVertexCount() { return m_vertexCount; }

	private:
		GLuint m_vaoID;
		int m_vertexCount;
	};

}