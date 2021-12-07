#include "Furnace.h"

Furnace::Furnace(const std::string& texture, glm::vec4 destRect, Engine::Camera* camera) : InteractiveItem(texture, destRect, camera)
{
	//m_drawStaticTexture = false;
}

Furnace::~Furnace()
{

}

void Furnace::interract()
{
	if (!m_burningComplete)
	{
		m_drawStaticTexture = !m_drawStaticTexture;
	}
}

void Furnace::onDraw(Engine::SpriteBatch& batch, Engine::ParticleSystem2D* particleSystem)
{
	if (!m_drawStaticTexture)
	{
		if (m_amt % 120 == 0)
		{
			std::uniform_real_distribution<float> randX(-0.05f, 0.05f);
			std::uniform_real_distribution<float> randRot(0.0f, 6.28f);
			std::uniform_real_distribution<float> randScale(0.6f, 1.2f);
			float x = randX(m_rng);
			float rot = randRot(m_rng);
			float scale = randScale(m_rng);
			particleSystem->emit("assets/textures/bucket_smoke.png", m_pos + glm::vec2(m_dimentions.x / 1.5, m_dimentions.y), glm::vec2(16, 16),
				glm::vec2(x, 0.2f), 0.0f, 10.0f, rot, scale, true);
		}

		if ((m_amt + 60) % 90 == 0)
		{
			std::uniform_real_distribution<float> randX(-0.05f, 0.05f);
			std::uniform_real_distribution<float> randRot(0.0f, 6.28f);
			std::uniform_real_distribution<float> randScale(0.6f, 1.2f);
			float x = randX(m_rng);
			float rot = randRot(m_rng);
			float scale = randScale(m_rng);

			particleSystem->emit("assets/textures/bucket_smoke.png", m_pos + glm::vec2(m_dimentions.x / 3, m_dimentions.y / 1.1), glm::vec2(16, 16),
				glm::vec2(x, 0.2f), 0.0f, 10.0f, rot, scale, true);
		}

		m_textureAtlases[0].draw(batch, Engine::FlipType::NONE);
		m_textureAtlases[0].playAnimation(1.0f / 40.0f);
	}
}

void Furnace::onUpdate(Engine::AudioEngine audioEngine, Engine::QuestSystem& qSystem, double deltaTime)
{
	m_textureAtlases[0].setPosition(m_pos);
	m_textureAtlases[0].update(deltaTime);
	m_amt += 1;
	
	if (!m_drawStaticTexture)
	{
		m_timer += deltaTime;
	}

	if (m_timer >= 10.0)
	{
		m_burningComplete = true;
	}
}