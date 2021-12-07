#include "CreditsScene.h"

#include "../Engine/ResourceManager.h"

#include "ScreenIndices.h"

CreditsScene::CreditsScene()
{
	m_screenIndex = SCREEN_INDEX_CREDITS_SCREEN;
}

CreditsScene::~CreditsScene()
{

}

int CreditsScene::getNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

int CreditsScene::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_GAMEPLAY_SCREEN;
}

void CreditsScene::build()
{

}

void CreditsScene::destroy()
{

}

void CreditsScene::onEntry()
{
	m_batch.init();
	m_fontShader = Engine::ResourceManager::getShader("assets/shaders/fontVertex.glsl", "assets/shaders/fontFragment.glsl");
	m_screenDims = m_game->getWindowDimentions();
	m_camera.init(m_screenDims.x, m_screenDims.y);
	m_camera.setScale(1.0f);
	m_game->getAudioEngine().LoadSound("assets/sounds/ambient/cyberpunk_credits_ambient.ogg", false, true, true);
	m_game->getAudioEngine().playSound("assets/sounds/ambient/cyberpunk_credits_ambient.ogg");

	reset();
}

void CreditsScene::onExit()
{
	m_game->getAudioEngine().StopAllChannels();
	m_game->getAudioEngine().ResetPositionAllChannels();
}

void CreditsScene::update(double deltaTime)
{
	handleInput(deltaTime);

	if (m_game->getInputManager().isKeyDown(SDLK_DOWN))
	{
		m_speed = 10.0;
	}

	if (m_game->getInputManager().isKeyDown(SDLK_UP))
	{
		m_speed = 0.0;
	}

	m_yPos += deltaTime * 50.0 * m_speed;
	m_speed = 1.0;
	m_camera.update();

	m_collider.y = m_yPos;

	if (Engine::Collision::AABB(m_collider, m_trigger))
	{
		m_currentState = Engine::ScreenState::CHANGE_PREVIOUS;
	}

}

void CreditsScene::draw()
{
	glActiveTexture(GL_TEXTURE0);
	m_fontShader.start();

	GLint textureLocation = m_fontShader.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);


	GLuint pLocation = m_fontShader.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getcameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));



	m_batch.begin();
	{
		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 64)->draw(
			m_batch,
			"DEVELOPED BY WADOWICE MONSTERS",
			glm::vec2(0, m_yPos),
			glm::vec2(0.7f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"GAME DIRECTOR",
			glm::vec2(-10, m_yPos - m_padding * 2),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"JAN PAWEL II",
			glm::vec2(10, m_yPos - m_padding * 2),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"SECOND DIRECTOR AND HEAD OF PRODUCTION",
			glm::vec2(-10, m_yPos - m_padding * 3),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"MICHAL NOWROT",
			glm::vec2(10, m_yPos - m_padding * 3),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(240, 210, 170, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"STORY DIRECTORS",
			glm::vec2(-10, m_yPos - m_padding * 4),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"WOJCIECH WITEK",
			glm::vec2(10, m_yPos - m_padding * 4),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"BARTOSZ RITAU",
			glm::vec2(10, m_yPos - m_padding * 5),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"PAWEL MROZIK",
			glm::vec2(10, m_yPos - m_padding * 6),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"MICHAL NOWROT",
			glm::vec2(10, m_yPos - m_padding * 7),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"QUEST DIRECTORS",
			glm::vec2(-10, m_yPos - m_padding * 8),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"WOJCIECH WITEK",
			glm::vec2(10, m_yPos - m_padding * 8),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"BARTOSZ RITAU",
			glm::vec2(10, m_yPos - m_padding * 9),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"PAWEL MROZIK",
			glm::vec2(10, m_yPos - m_padding * 10),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"MICHAL NOWROT",
			glm::vec2(10, m_yPos - m_padding * 11),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"CHARACTERS AND VISUAL EFFECTS",
			glm::vec2(-10, m_yPos - m_padding * 12),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"KAROL WIECZOREK",
			glm::vec2(10, m_yPos - m_padding * 12),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"BARTOSZ RITAU",
			glm::vec2(10, m_yPos - m_padding * 13),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"BARTLOMIEJ KUS",
			glm::vec2(10, m_yPos - m_padding * 14),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"MICHAL NOWROT",
			glm::vec2(10, m_yPos - m_padding * 15),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 48)->draw(
			m_batch,
			"STORY",
			glm::vec2(0, m_yPos - m_padding * 18),
			glm::vec2(0.66f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"SENIOR WRITERS",
			glm::vec2(-10, m_yPos - m_padding * 20),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"KAROL WIECZOREK",
			glm::vec2(10, m_yPos - m_padding * 20),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"BARTOSZ RITAU",
			glm::vec2(10, m_yPos - m_padding * 21),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"BARTLOMIEJ KUS",
			glm::vec2(10, m_yPos - m_padding * 22),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"MICHAL NOWROT",
			glm::vec2(10, m_yPos - m_padding * 23),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"WOJCIECH WITEK",
			glm::vec2(10, m_yPos - m_padding * 24),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"PAWEL MROZIK",
			glm::vec2(10, m_yPos - m_padding * 25),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 48)->draw(
			m_batch,
			"QUESTS",
			glm::vec2(0, m_yPos - m_padding * 28),
			glm::vec2(0.66f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"LEAD QUEST DESIGNER",
			glm::vec2(-10, m_yPos - m_padding * 30),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"MICHAL NOWROT",
			glm::vec2(10, m_yPos - m_padding * 30),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"SENIOR QUEST DESIGNERS",
			glm::vec2(-10, m_yPos - m_padding * 31),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"BARTOSZ RITAU",
			glm::vec2(10, m_yPos - m_padding * 31),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"MICHAL NOWROT",
			glm::vec2(10, m_yPos - m_padding * 32),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"WOJCIECH WITEK",
			glm::vec2(10, m_yPos - m_padding * 33),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"JUNIOR QUEST DESIGNER",
			glm::vec2(-10, m_yPos - m_padding * 34),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"PAWEL MROZIK",
			glm::vec2(10, m_yPos - m_padding * 34),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 48)->draw(
			m_batch,
			"LEVEL DESIGN",
			glm::vec2(0, m_yPos - m_padding * 37),
			glm::vec2(0.66f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"LEAD LEVEL DESIGNER",
			glm::vec2(-10, m_yPos - m_padding * 39),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"MICHAL NOWROT",
			glm::vec2(10, m_yPos - m_padding * 39),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"SENIOR LEVEL DESIGNERS",
			glm::vec2(-10, m_yPos - m_padding * 40),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"BARTOSZ RITAU",
			glm::vec2(10, m_yPos - m_padding * 40),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"WOJCIECH WITEK",
			glm::vec2(10, m_yPos - m_padding * 41),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"JUNIOR LEVEL DESIGNERS",
			glm::vec2(-10, m_yPos - m_padding * 42),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"KAROL WIECZOREK",
			glm::vec2(10, m_yPos - m_padding * 42),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 48)->draw(
			m_batch,
			"ENGINE",
			glm::vec2(0, m_yPos - m_padding * 45),
			glm::vec2(0.66f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"LEAD ENGINE PROGRAMMER",
			glm::vec2(-10, m_yPos - m_padding * 47),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"MICHAL NOWROT",
			glm::vec2(10, m_yPos - m_padding * 47),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 48)->draw(
			m_batch,
			"GAMEPLAY CODE",
			glm::vec2(0, m_yPos - m_padding * 50),
			glm::vec2(0.66f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"LEAD GAMEPLAY PROGRAMMER",
			glm::vec2(-10, m_yPos - m_padding * 52),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"MICHAL NOWROT",
			glm::vec2(10, m_yPos - m_padding * 52),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 48)->draw(
			m_batch,
			"CHARACTER ART",
			glm::vec2(0, m_yPos - m_padding * 55),
			glm::vec2(0.66f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"LEAD CHARACTER ARTIST",
			glm::vec2(-10, m_yPos - m_padding * 57),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"MICHAL NOWROT",
			glm::vec2(10, m_yPos - m_padding * 57),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"SENIOR CHARACTER ARTISTS",
			glm::vec2(-10, m_yPos - m_padding * 58),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"BARTOSZ RITAU",
			glm::vec2(10, m_yPos - m_padding * 58),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"KAROL WIECZOREK",
			glm::vec2(10, m_yPos - m_padding * 59),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"JUNIOR CHARACTER ARTISTS",
			glm::vec2(-10, m_yPos - m_padding * 60),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"BARTLOMIEJ KUS",
			glm::vec2(10, m_yPos - m_padding * 60),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 48)->draw(
			m_batch,
			"AUDIO",
			glm::vec2(0, m_yPos - m_padding * 63),
			glm::vec2(0.66f),
			1.0f,
			Engine::ColorRGBA8(255, 235, 212, 255),
			Engine::Justification::MIDDLE);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"LEAD SOUND DESIGNER",
			glm::vec2(-10, m_yPos - m_padding * 65),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"MICHAL NOWROT",
			glm::vec2(10, m_yPos - m_padding * 65),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"SENIOR SOUND DESIGNER",
			glm::vec2(-10, m_yPos - m_padding * 66),
			glm::vec2(0.75f),
			1.0f,
			Engine::ColorRGBA8(179, 154, 126, 255),
			Engine::Justification::RIGHT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"BARTOSZ RITAU",
			glm::vec2(10, m_yPos - m_padding * 66),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);

		Engine::ResourceManager::getFont("assets/fonts/PTSansNarrow-Regular.ttf", 32)->draw(
			m_batch,
			"WOJCIECH WITEK",
			glm::vec2(10, m_yPos - m_padding * 67),
			glm::vec2(0.75),
			1.0f,
			Engine::ColorRGBA8(255, 225, 185, 255),
			Engine::Justification::LEFT);
	}


	m_batch.end();
	m_batch.renderBatch();

	m_fontShader.stop();
}


void CreditsScene::handleInput(double deltaTime)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		m_game->onSDLEvent(event);
	}
}

void CreditsScene::reset()
{
	m_trigger.x = 0;
	m_trigger.y = 3500;
	m_trigger.w = 100;
	m_trigger.h = 100;

	m_collider.x = 0;
	m_collider.y = 0;
	m_collider.w = 100;
	m_collider.h = 100;

	m_yPos = -600.0;

	glClearColor(0.0, 0.0, 0.0, 0.0);
}