#pragma once

#include <glm.hpp>

#include "SpriteBatch.h"
#include "AnimatedSprite.h"

namespace Engine
{
	class Particle2D
	{
	public:

		Particle2D(GLuint textureId, const glm::vec2& position, const glm::vec2& dimentions, const glm::vec2& velocity, float gravityEffect, float lifeTime, float rotation, float scale, bool linearAlphaDecrease);
		~Particle2D();

		bool update(double deltaTime);
		void draw(SpriteBatch& spritebatch);
		void draw(SpriteBatch& spritebatch, AnimatedSprite sprite, float speed);

		void setPosition(const glm::vec2& position);
		void setDimentions(const glm::vec2& dims);
		void setVelocity(const glm::vec2& velocity);
		void setGravityEffect(float gravityEffect);
		void setLifeTime(double lifeTime);
		void setRotation(float rotation);
		void setScale(float scale);

		glm::vec2 getPosition() { return glm::vec2(m_destRect.x, m_destRect.y); }
		glm::vec2 getDimentions() { return glm::vec2(m_destRect.z, m_destRect.w); }
		glm::vec2 getVelocity() { return m_velocity; }
		float getGravityEffect() { return m_gravityEffect; }
		double getLifeTime() { return m_lifeTime; }
		float getRotation() { return m_rotation; }
		float getScale() { return m_scale; }

	private:
		glm::vec2 m_velocity;
		float m_gravityEffect;
		double m_lifeTime;
		double m_maxLifeTime;
		float m_rotation;
		float m_scale;

		bool m_linearAlphaDecrease = false;

		GLuint m_textureId;

		glm::vec4 m_destRect;
		glm::vec4 m_uvRect;
	};
}
