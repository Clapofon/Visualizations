#include "AnimatedSprite.h"

namespace Engine
{
	AnimatedSprite::AnimatedSprite(const std::string& textureAtlas, const glm::vec4& destRect, const glm::vec2& rowsAndCols, int maxIndex, double duration, bool filtering) :
		m_texture(ResourceManager::getTexture(textureAtlas, filtering)),
		m_rowsAndCols(rowsAndCols),
		m_currentIndex(0),
		m_destRect(destRect),
		m_maxIndex(maxIndex),
		m_animationDuration(duration),
		m_frameTime(m_animationDuration / m_maxIndex + 1),
		m_shouldAnimate(true)
	{
		//printf("constructor frameTime: %f\n", m_frameTime);
	}

	AnimatedSprite::AnimatedSprite(const std::string& textureAtlas, const glm::vec4& destRect, const glm::vec2& rowsAndCols, int maxIndex, double duration, 
		bool filtering, int startingIndex) :
		m_texture(ResourceManager::getTexture(textureAtlas, filtering)),
		m_rowsAndCols(rowsAndCols),
		m_destRect(destRect),
		m_maxIndex(maxIndex),
		m_currentIndex(startingIndex),
		m_animationDuration(duration),
		m_frameTime(m_animationDuration / m_maxIndex + 1),
		m_shouldAnimate(true)
	{
		//printf("constructor frameTime: %f\n", m_frameTime);
	}

	AnimatedSprite::~AnimatedSprite()
	{

	}

	void AnimatedSprite::draw(SpriteBatch& spritebatch, FlipType flipType)
	{
		int tilesetWidth = (int)m_rowsAndCols.y;
		int tilesetHeight = (int)m_rowsAndCols.x;
		int tileWidth = m_texture.width / tilesetWidth;
		int tileHeight = m_texture.height / tilesetHeight;

		glm::vec2 minPos = glm::vec2(floor((int)m_currentIndex % tilesetWidth) / (float)tilesetWidth, floor((int)m_currentIndex / (float)tilesetWidth) / (float)tilesetHeight);
		glm::vec2 maxPos = glm::vec2((floor(minPos.x + (float)tileWidth) / (float)tileWidth) / (float)tilesetWidth, (floor(minPos.y + (float)tileHeight) / (float)tileHeight) / (float)tilesetHeight);

		switch (flipType)
		{
			case FlipType::NONE:
				m_currentFrame = glm::vec4(minPos.x, minPos.y, maxPos.x, maxPos.y);
				break;
			case FlipType::FLIP_X:
				m_currentFrame = glm::vec4(minPos.x, minPos.y, -maxPos.x, maxPos.y);
				break;
			case FlipType::FLIP_Y:
				m_currentFrame = glm::vec4(minPos.x, minPos.y, maxPos.x, -maxPos.y);
				break;
			case FlipType::FLIP_BOTH:
				m_currentFrame = glm::vec4(minPos.x, minPos.y, -maxPos.x, -maxPos.y);
				break;
		}

		spritebatch.draw(m_destRect, m_currentFrame, m_texture.id, 0.0f, ColorRGBA8(255, 255, 255, 255));
	}

	void AnimatedSprite::update(double deltaTime)
	{
		if (m_frameTime > 0.0f)
		{
			m_frameTime -= deltaTime;
			//printf("1 if deltaTime: %f\n", deltaTime);
			//printf("1 if frameTime: %f\n", m_frameTime);
		}
		else
		{
			m_shouldAnimate = true;
			m_frameTime = m_animationDuration / m_maxIndex + 1;
			//printf("2 if frameTime: %f\n", m_frameTime);
			//printf("2 if anim durration: %f\n", m_animationDuration);
		}
	}

	void AnimatedSprite::playAnimation(float speed)
	{
		if (m_shouldAnimate)
		{
			if ((int)m_currentIndex <= m_maxIndex)
			{
				m_currentIndex += 1 * speed;
				//printf("index: %f\n", m_currentIndex);
			}
			else
			{
				m_currentIndex = 0;
			}
			//m_shouldAnimate = false;
		}
	}

	void AnimatedSprite::setCurrentIndex(int index)
	{
		m_currentIndex = index;
	}

	void AnimatedSprite::setPosition(glm::vec2 pos)
	{
		m_destRect.x = pos.x;
		m_destRect.y = pos.y;
	}
}