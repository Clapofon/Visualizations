#pragma once

#include <vector>
#include <string>

#include "Particle2D.h"
#include "SpriteBatch.h"
#include "AnimatedSprite.h"
#include "GLSLProgram.h"
#include "Camera.h"

namespace Engine 
{
	class ParticleSystem2D
	{
	public:
		ParticleSystem2D(Camera* camera);
		~ParticleSystem2D();

		void emit(const std::string& texture, const glm::vec2& position, const glm::vec2& dimentions, const glm::vec2& velocity, 
			float gravityEffect, float lifeTime, float rotation, float scale, bool linearAlphaDecrease);
		void emitAnimated(int id, const glm::vec2& position, const glm::vec2& dimentions, const glm::vec2& velocity, float gravityEffect, float lifeTime, float rotation, float scale);
		void draw(SpriteBatch& batch);
		void update(double deltaTime);
		void addAnimatedSprite(const std::string& textureAtlas, const glm::vec2& dims, const glm::vec2& rowsAndCols, int maxIndex, double duration);

	private:
		std::vector<Particle2D> m_particles;
		std::vector<Particle2D> m_animatedParticles;
		SpriteBatch m_spriteBatch;
		std::vector<AnimatedSprite> m_animatedSprites;
		GLSLProgram m_shader;
		Camera* m_camera;
	};
}

