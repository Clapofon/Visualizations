#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtx/transform.hpp>


namespace Engine
{
	class Camera3D
	{
	public:
		Camera3D(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
		{
			this->pos = pos;
			this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
			this->up = glm::vec3(0.0f, 1.0f, 0.0f);
			this->projection = glm::perspective(fov, aspect, zNear, zFar);
		}

		inline glm::mat4 GetViewProjection() const
		{
			return projection * glm::lookAt(pos, pos + forward, up);
		}

		void updateProjection(float fov, float aspect, float zNear, float zFar)
		{
			this->projection = glm::perspective(fov, aspect, zNear, zFar);
		}

		void moveForward(float amt)
		{
			pos += forward * amt;
		}

		void moveRight(float amt)
		{
			pos += glm::cross(up, forward) * amt;
		}

		void moveUp(float amt)
		{
			pos += glm::vec3(0, amt, 0);
		}

		void Pitch(float angle)
		{
			glm::vec3 right = glm::normalize(glm::cross(up, forward));

			forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
			up = glm::normalize(glm::cross(forward, right));
		}

		void RotateY(float angle)
		{
			static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

			glm::mat4 rotation = glm::rotate(angle, UP);

			forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
			up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
		}

		glm::vec3 getPosition() { return pos; }

	private:
		glm::mat4 projection;
		glm::vec3 pos;
		glm::vec3 forward;
		glm::vec3 up;
	};
}
