#pragma once

#include "GLTexture.h"
#include "ResourceManager.h"
#include "SpriteBatch.h"

#include <glm.hpp>

namespace Engine
{
	enum class FlipType 
	{
		NONE,
		FLIP_X,
		FLIP_Y,
		FLIP_BOTH
	};

	class AnimatedSprite
	{
	public:
		AnimatedSprite(const std::string& textureAtlas, const glm::vec4& destRect, const glm::vec2& rowsAndCols, int maxIndex, double duration, bool filtering);
		AnimatedSprite(const std::string& textureAtlas, const glm::vec4& destRect, const glm::vec2& rowsAndCols, int maxIndex, double duration, bool filtering, int startingIndex);
		~AnimatedSprite();

		void draw(SpriteBatch& spritebatch, FlipType flipType);
		void update(double deltaTime);
		void playAnimation(float speed);

		void setCurrentIndex(int index);
		void setPosition(glm::vec2 pos);

		int getCurrentIndex() { return m_currentIndex; }
		GLTexture getTexture() { return m_texture; }
		glm::vec4 getDestRect() { return m_destRect; }

	private:
		GLTexture m_texture;
		int m_maxIndex;
		float m_currentIndex;
		glm::vec2 m_rowsAndCols;
		double m_animationDuration;
		double m_frameTime;
		bool m_shouldAnimate;

		glm::vec4 m_destRect;
		glm::vec4 m_currentFrame;
	};
}

