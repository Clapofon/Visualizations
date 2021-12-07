#include "Particle2D.h"
#include "ResourceManager.h"

namespace Engine
{
	Particle2D::Particle2D(GLuint textureId, const glm::vec2& position, const glm::vec2& dimentions, const glm::vec2& velocity, 
		float gravityEffect, float lifeTime, float rotation, float scale, bool linearAlphaDecrease) :
		m_destRect(position.x, position.y, dimentions.x * scale, dimentions.y * scale),
		m_velocity(velocity),
		m_gravityEffect(gravityEffect),
		m_lifeTime(lifeTime),
		m_rotation(rotation),
		m_scale(scale),
		m_textureId(textureId),
		m_uvRect(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)),
		m_maxLifeTime(lifeTime),
		m_linearAlphaDecrease(linearAlphaDecrease)
	{
		
	}

	Particle2D::~Particle2D()
	{

	}

	bool Particle2D::update(double deltaTime)
	{
		m_velocity.y -= m_gravityEffect * deltaTime;
		m_destRect.x += m_velocity.x;
		m_destRect.y += m_velocity.y;

		m_lifeTime -= deltaTime;
		return m_lifeTime < 0.0;
	}

	void Particle2D::draw(SpriteBatch& spritebatch)
	{
		float alpha = 0.0f;
		(m_linearAlphaDecrease) ? alpha = 255 * (m_lifeTime / m_maxLifeTime) : alpha = 255;
		spritebatch.draw(glm::vec4(m_destRect.x - (m_destRect.z / 2), m_destRect.y - (m_destRect.w / 2), m_destRect.z * m_scale, m_destRect.w * m_scale), m_uvRect, m_textureId, 1.0f, ColorRGBA8(255, 255, 255, alpha), m_rotation);
		//printf("rotation: %f\n", m_rotation);
		//printf("position: (%f, %f)\n dims: (%f, %f)\n", m_destRect.x, m_destRect.y, m_destRect.z, m_destRect.w);
	}

	void Particle2D::draw(SpriteBatch& spritebatch, AnimatedSprite sprite, float speed)
	{
		sprite.setPosition(glm::vec2(m_destRect.x, m_destRect.y));
		sprite.draw(spritebatch, FlipType::NONE);
		sprite.playAnimation(speed);
	}

	void Particle2D::setPosition(const glm::vec2& position)
	{
		m_destRect.x = position.x;
		m_destRect.y = position.y;
	}

	void Particle2D::setDimentions(const glm::vec2& dims)
	{
		m_destRect.z = dims.x;
		m_destRect.w = dims.y;
	}

	void Particle2D::setVelocity(const glm::vec2& velocity)
	{
		m_velocity = velocity;
	}

	void Particle2D::setGravityEffect(float gravityEffect)
	{
		m_gravityEffect = gravityEffect;
	}

	void Particle2D::setLifeTime(double lifeTime)
	{
		m_lifeTime = lifeTime;
	}

	void Particle2D::setRotation(float rotation)
	{
		m_rotation = rotation;
	}

	void Particle2D::setScale(float scale)
	{
		m_scale = scale;
	}
}