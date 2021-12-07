#include "ParticleSystem2D.h"
#include "ResourceManager.h"


namespace Engine
{
	ParticleSystem2D::ParticleSystem2D(Camera* camera) :
		m_camera(camera),
		m_shader(ResourceManager::getShader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"))
	{
		m_spriteBatch.init();
	}

	ParticleSystem2D::~ParticleSystem2D()
	{
		if (m_camera)
		{
			delete m_camera;
		}
	}

	void ParticleSystem2D::emit(const std::string& texture, const glm::vec2& position, const glm::vec2& dimentions, const glm::vec2& velocity, 
		float gravityEffect, float lifeTime, float rotation, float scale, bool linearAlphaDecrease)
	{
		m_particles.push_back(Particle2D(ResourceManager::getTexture(texture).id, position, dimentions, velocity, gravityEffect, lifeTime, rotation, scale, linearAlphaDecrease));
		//printf("Emmiting particle1.\n");

	}

	void ParticleSystem2D::emitAnimated(int id, const glm::vec2& position, const glm::vec2& dimentions, const glm::vec2& velocity, float gravityEffect, float lifeTime, float rotation, float scale)
	{
		m_animatedParticles.push_back(Particle2D(m_animatedSprites[id].getTexture().id, position, dimentions, velocity, gravityEffect, lifeTime, rotation, scale, false));
		//printf("Emmiting particle2.\n");
	}

	void ParticleSystem2D::draw(SpriteBatch& batch)
	{
		/*m_shader.start();
		GLint textureLocation = m_shader.getUniformLocation("sampler");
		glUniform1i(textureLocation, 0);

		GLuint pLocation = m_shader.getUniformLocation("P");
		glm::mat4 cameraMatrix = m_camera->getcameraMatrix();

		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

		m_spriteBatch.begin();*/

		for (int i = 0; i < m_particles.size(); i++)
		{
			m_particles[i].draw(batch);
			//printf("Drawing %d particles\n", m_particles.size());
		}

		for (int i = 0; i < m_animatedParticles.size(); i++)
		{
			m_animatedParticles[i].draw(batch, m_animatedSprites[0], 1.0f);
		}

		/*m_spriteBatch.end();
		m_spriteBatch.renderBatch();
		m_shader.stop();*/
	}

	void ParticleSystem2D::update(double deltaTime)
	{
		for (unsigned int i = 0; i < m_particles.size();)
		{
			if (m_particles[i].update(deltaTime))
			{
				m_particles[i] = m_particles.back();
				m_particles.pop_back();
			}
			else
			{
				i++;
			}
		}

		for (unsigned int i = 0; i < m_animatedParticles.size();)
		{
			if (m_animatedParticles[i].update(deltaTime))
			{
				m_animatedParticles[i] = m_animatedParticles.back();
				m_animatedParticles.pop_back();
			}
			else
			{
				i++;
			}
		}
	}

	void ParticleSystem2D::addAnimatedSprite(const std::string& textureAtlas, const glm::vec2& dims, const glm::vec2& rowsAndCols, int maxIndex, double duration)
	{
		m_animatedSprites.push_back(AnimatedSprite(textureAtlas, glm::vec4(0, 0, dims), rowsAndCols, maxIndex, duration, true));
	}
}