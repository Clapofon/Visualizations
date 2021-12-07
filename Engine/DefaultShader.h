#pragma once

#include "GLSLProgram.h"

namespace Engine
{
	class DefaultShader : public GLSLProgram
	{
	public:

		DefaultShader();
		~DefaultShader();

		void getAllUniformLocations();
		void loadTranformationMatrix(glm::mat4 mat);
		void loadProjectionMatrix(glm::mat4 mat);
		void loadViewMatrix(glm::mat4 mat);
		void loadLight(glm::vec3 pos, glm::vec3 color);
	private:
		GLint m_lightPositionLocation = 0;
		GLint m_lightColorLocation = 0;
		GLint m_tranformationLocation = 0;
		GLint m_viewLocation = 0;
		GLint m_projectionLocation = 0;
	};
}
