#include "Papaj.h"

#include "../Engine/Random.h"

Papaj::Papaj(int id) : m_id(id)
{
	m_collider.x = m_papajCoords.x;
	m_collider.y = m_papajCoords.y;
	m_collider.w = m_width;
	m_collider.h = m_width;

	m_papajCoords = glm::vec2(Engine::Random::randInt(-900, 900), Engine::Random::randInt(-500, 500));
}

Papaj::~Papaj()
{

}

void Papaj::update(double deltaTime, double speed, glm::vec2 screenDims, std::vector<Papaj>& papajs)
{
	double angle = Engine::Random::randDouble(0.0, 2 * glm::pi<double>());
	m_coords = glm::vec2(m_coords.x + glm::cos(angle), m_coords.y + glm::sin(angle));

	if (m_papajCoords.x > (screenDims.x / 2) - m_width)
	{
		m_coords = glm::vec2(-1, 0);
	}

	if (m_papajCoords.x < -screenDims.x / 2)
	{
		m_coords = glm::vec2(1, 0);
	}

	if (m_papajCoords.y > (screenDims.y / 2) - m_width)
	{
		m_coords = glm::vec2(0, -1);
	}

	if (m_papajCoords.y < -screenDims.y / 2)
	{
		m_coords = glm::vec2(0, 1);
	}

	m_papajCoords += glm::normalize(m_coords) * glm::vec2(speed * deltaTime);

	m_collider.x = m_papajCoords.x;
	m_collider.y = m_papajCoords.y;

	for (int i = 0; i < papajs.size(); i++)
	{
		if (m_id != papajs[i].getID())
		{
			const float PAPAJ_RADIUS = (float)m_width / 2.0f;
			const float MIN_DISTANCE = PAPAJ_RADIUS * 2.0f;
			
			glm::vec2 centerA = m_papajCoords + glm::vec2(PAPAJ_RADIUS);
			glm::vec2 centerB = papajs[i].getPosition() + glm::vec2(PAPAJ_RADIUS);
			glm::vec2 dist = centerA - centerB;

			float distance = glm::length(dist);
			float collisionDepth = MIN_DISTANCE - distance;

			if (collisionDepth > 0.0f)
			{
				glm::vec2 depth = glm::normalize(dist) * collisionDepth;

				m_papajCoords += depth / 2.0f;
				papajs[i].setPosition(papajs[i].getPosition() - depth / 2.0f);

				m_color = Engine::ColorRGBA8(Engine::Random::randInt(0, 255), Engine::Random::randInt(0, 255), Engine::Random::randInt(0, 255), 255);
			}
		}
	}
}

void Papaj::draw(Engine::SpriteBatch& batch) 
{
	m_coords.x >= 0 ? m_flipType = Engine::FlipType::NONE : m_flipType = Engine::FlipType::FLIP_X;

	glm::vec4 uv;
	switch (m_flipType)
	{
	case Engine::FlipType::NONE:
		uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case Engine::FlipType::FLIP_X:
		uv = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
		break;
	case Engine::FlipType::FLIP_Y:
		uv = glm::vec4(0.0f, 0.0f, 1.0f, -1.0f);
		break;
	case Engine::FlipType::FLIP_BOTH:
		uv = glm::vec4(0.0f, 0.0f, -1.0f, -1.0f);
		break;
	}



	batch.draw(glm::vec4(m_papajCoords, m_width, m_width), uv,
		Engine::ResourceManager::getTexture("assets/textures/papaj.png").id, 1.0f, m_color);
}