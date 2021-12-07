#include "Bucket.h"

#include "../Engine/ParticleSystem2D.h"

Bucket::Bucket(const std::string& texture, glm::vec4 destRect, Engine::Camera* camera) : InteractiveItem(texture, destRect, camera)
{
	
}

Bucket::~Bucket()
{

}

void Bucket::init(Engine::AudioEngine audioEngine)
{
	audioEngine.LoadSound("assets/sounds/items/bucket_smoke.ogg", false, true, false);
	m_smokeSound = audioEngine.playSound("assets/sounds/items/bucket_smoke.ogg");
}

void Bucket::interract()
{
	m_bucketReady = !m_bucketReady;
}

void Bucket::onDraw(Engine::SpriteBatch& batch, Engine::ParticleSystem2D* particleSystem)
{
	if (m_bucketReady)
	{
		if (m_amt % 5 == 0)
		{
			std::uniform_real_distribution<float> randX(-0.05f, 0.05f);
			std::uniform_real_distribution<float> randRot(0.0f, 6.28f);
			std::uniform_real_distribution<float> randScale(0.6f, 1.2f);
			float x = randX(m_rng);
			float rot = randRot(m_rng);
			float scale = randScale(m_rng);
			particleSystem->emit("assets/textures/bucket_smoke.png", m_pos + glm::vec2(m_dimentions.x / 2, m_dimentions.y), glm::vec2(16, 16),
				glm::vec2(x, 0.2f), 0.0f, 10.0f, rot, scale, true);
		}
	}
}

void Bucket::onUpdate(Engine::AudioEngine audioEngine, Engine::QuestSystem& qSystem, double deltaTime)
{
	m_amt += 1;

	if (m_bucketReady)
	{
		if (!audioEngine.IsPlaying(m_smokeSound))
		{
			audioEngine.StartChannel(m_smokeSound);
		}
	}

	if (!m_bucketReady)
	{
		if (audioEngine.IsPlaying(m_smokeSound))
		{
			audioEngine.StopChannel(m_smokeSound);
		}
	}
}