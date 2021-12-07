#include "InteractiveItem.h"


InteractiveItem::InteractiveItem(const std::string& texture, glm::vec4 destRect, Engine::Camera* camera)
{
	m_texture = Engine::ResourceManager::getTexture(texture, false);
	m_pos = glm::vec2(destRect.x, destRect.y);
	m_dimentions = glm::vec2(destRect.z, destRect.w);

	m_collider.x = m_pos.x;
	m_collider.y = m_pos.y;
	m_collider.w = m_dimentions.x;
	m_collider.h = m_dimentions.y;

	m_camera = camera;
}

InteractiveItem::~InteractiveItem()
{

}

void InteractiveItem::update(const Engine::Collider2D& collider, Engine::InputManager inputManager, Engine::AudioEngine audioEngine, Engine::QuestSystem& qSystem, double deltaTime)
{
	m_canInterract = Engine::Collision::AABB(collider, m_collider);

	if (m_canInterract && inputManager.isKeyPressed(SDLK_e))
	{
		interract();
	}
	onUpdate(audioEngine, qSystem, deltaTime);
}

void InteractiveItem::draw(Engine::SpriteBatch& batch, Engine::ParticleSystem2D* particleSystem)
{
	if (m_drawStaticTexture)
	{
		batch.draw(glm::vec4(m_pos, m_dimentions), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_texture.id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));
	}

	onDraw(batch, particleSystem);
}

void InteractiveItem::drawUIBackground(Engine::SpriteBatch& batch)
{
	if (m_canInterract)
	{
		float scale = m_camera->getScale();
		m_buttonDestRect = glm::vec4(m_pos + glm::vec2((m_dimentions.x / 2) - (32 / scale), m_dimentions.y + 100 / scale), glm::vec2(64, 64) / glm::vec2(scale));

		batch.draw(m_buttonDestRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			Engine::ResourceManager::getTexture("assets/textures/action_button_background.png").id, 1.0f, Engine::ColorRGBA8(255, 255, 255, 255));
	}
}

void InteractiveItem::drawFonts(Engine::SpriteBatch& batch, float resScale)
{
	if (m_canInterract)
	{
		float scale = m_camera->getScale();
		m_buttonDestRect = glm::vec4(m_pos + glm::vec2((m_dimentions.x / 2) - (32 / scale), m_dimentions.y + 100 / scale), glm::vec2(64, 64) / glm::vec2(scale));

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(batch, "E",
			glm::vec2(m_buttonDestRect.x + 32 / scale , m_buttonDestRect.y + 10 / scale),
			glm::vec2(1.0f * resScale / scale), 1.0f,
			Engine::ColorRGBA8(255, 255, 255, 255), Engine::Justification::MIDDLE);
	}
}

void InteractiveItem::addTextureAtlas(const std::string& textureAtlas, const glm::vec4& destRect, const glm::vec2& rowsAndCols, int maxIndex, double duration, 
	int startingIndex, bool filtering)
{
	m_textureAtlases.push_back(Engine::AnimatedSprite(textureAtlas, destRect, rowsAndCols, maxIndex, duration, startingIndex));
}