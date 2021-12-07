#include "DefaultShader.h"

#include "Math.h";

namespace Engine
{
	DefaultShader::DefaultShader()
	{

	}

	DefaultShader::~DefaultShader()
	{

	}

	void DefaultShader::getAllUniformLocations()
	{
		m_tranformationLocation = getUniformLocation("transformationMatrix");
		m_projectionLocation = getUniformLocation("projectionMatrix");
		m_viewLocation = getUniformLocation("viewMatrix");
		m_lightColorLocation = getUniformLocation("lightColor");
		m_lightPositionLocation = getUniformLocation("lightPosition");
	}

	void DefaultShader::loadTranformationMatrix(glm::mat4 mat)
	{
		loadMat4(m_tranformationLocation, mat);
	}

	void DefaultShader::loadProjectionMatrix(glm::mat4 mat)
	{
		loadMat4(m_projectionLocation, mat);
	}

	void DefaultShader::loadViewMatrix(glm::mat4 mat)
	{
		loadMat4(m_viewLocation, mat);
	}

	void DefaultShader::loadLight(glm::vec3 pos, glm::vec3 color)
	{
		loadVector3f(m_lightColorLocation, color);
		loadVector3f(m_lightPositionLocation, pos);
	}
}