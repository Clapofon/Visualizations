/*#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Camera3D.h"

namespace Engine
{
	class Math
	{
	public:
		static glm::mat4 createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
		{
			glm::mat4 matrix(1.0f);
			matrix = glm::translate(matrix, translation);
			matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
			matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
			matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
			matrix = glm::scale(matrix, scale);
			return matrix;
		}

		static glm::mat4 createProjectionMatrix(glm::vec2 screenDimentions, float fov, float nearPlane, float farPlane)
		{
			float aspectRatio = (float)screenDimentions.x / (float)screenDimentions.y;
			float yScale = (float)((1.0f / glm::tan(glm::radians(fov / 2.0f))) * aspectRatio);
			float xScale = yScale / aspectRatio;
			float frustumLength = farPlane - nearPlane;

			glm::mat4 projectionMatrix = glm::mat4();
			projectionMatrix[0][0] = xScale;
			projectionMatrix[1][1] = yScale;
			projectionMatrix[2][2] = -((farPlane + nearPlane) / frustumLength);
			projectionMatrix[2][3] = -1;
			projectionMatrix[3][2] = -((2 * nearPlane * farPlane) / frustumLength);
			projectionMatrix[3][3] = 0;
			return projectionMatrix;
		}

		static glm::mat4 createViewMatrix(Camera3D* camera)
		{
			glm::mat4 viewMatrix(1.0f);
			viewMatrix = glm::rotate(viewMatrix, (float)glm::radians(camera->getPitch()), glm::vec3(1, 0, 0));
			viewMatrix = glm::rotate(viewMatrix, (float)glm::radians(camera->getYaw()), glm::vec3(0, 1, 0));
			viewMatrix = glm::rotate(viewMatrix, (float)glm::radians(camera->getRoll()), glm::vec3(0, 0, 1));
			glm::vec3 camPos = camera->getPosition();
			glm::vec3 negativePos = glm::vec3(-camPos.x, -camPos.y, -camPos.z);
			viewMatrix = glm::translate(negativePos);
			return viewMatrix;
		}
	};
}*/