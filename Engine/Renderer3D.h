#pragma once

#include <glew.h>

#include "RawModel.h"
#include "Entity.h"
#include "GLSLProgram.h"
#include "Light.h"
#include "Camera3D.h"

namespace Engine
{
	class Renderer3D
	{
	public:
		Renderer3D(GLSLProgram shader);
		~Renderer3D();

		void prepare();
		void render(Entity entity, GLSLProgram shader, Light* light, Camera3D* camera);
	private:
		float m_fov = 70.0f;
		float m_nearPlane = 0.1f;
		float m_farPlane = 1000.0f;
		glm::mat4 m_projectionMatrix;
	};

}
