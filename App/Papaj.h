#pragma once

#include "../Engine/SpriteBatch.h"
#include "../Engine/AnimatedSprite.h"
#include "../Engine/Collision.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Papaj
{
public:
	Papaj(int id);
	~Papaj();

	void update(double deltaTime, double speed, glm::vec2 screenDims, std::vector<Papaj>& papajs);
	void draw(Engine::SpriteBatch& batch);

	Engine::Collider2D getCollider() { return m_collider; }
	glm::vec2 getPosition() { return m_papajCoords; }
	glm::vec2 getDirection() { return m_coords; }
	int getID() { return m_id; }

	void setDirection(glm::vec2 dir) { m_coords = dir; }
	void setPosition(glm::vec2 pos) { m_papajCoords = pos; }

private:
	glm::vec2 m_papajCoords = glm::vec2(0);
	glm::vec2 m_coords = glm::vec2(0);
	int m_width = 50;

	int m_id = -1;

	Engine::FlipType m_flipType = Engine::FlipType::NONE;

	Engine::Collider2D m_collider;
	
	Engine::ColorRGBA8 m_color;
};

