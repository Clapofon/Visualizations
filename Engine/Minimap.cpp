#include "Minimap.h"

#include "ResourceManager.h"

namespace Engine
{

	Minimap::Minimap(const glm::vec2& position, const glm::vec2& dimentions, GLTexture reflectionTexture, Camera* camera) :
		m_position(position),
		m_dimentions(dimentions),
		m_texture(reflectionTexture),
		m_camera(camera)
	{

	}

	Minimap::~Minimap()
	{

	}

	void Minimap::init()
	{
		m_shader = ResourceManager::getShader("assets/shaders/minimapVertex.glsl", "assets/shaders/minimapFragment.glsl");

		GLint textureLocation = m_shader.getUniformLocation("sampler");

		m_shader.start();

		glUniform1i(textureLocation, 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture.id);

		m_shader.stop();
	}

	void Minimap::draw(SpriteBatch batch)
	{
		m_shader.start();

		GLuint pLocation = m_shader.getUniformLocation("P");
		glm::mat4 cameraMatrix = m_camera->getcameraMatrix();

		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

		batch.begin();

		glm::vec4 uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		glm::vec4 destRect = glm::vec4(m_position.x, m_position.y, m_dimentions.x, m_dimentions.y);

		batch.draw(destRect, uvRect, m_texture.id, 1.0f, ColorRGBA8(255, 255, 255, 255));

		batch.end();
		batch.renderBatch();
		m_shader.stop();
	}

	void Minimap::setDimentions(glm::vec2 dims)
	{
		m_dimentions = dims;
	}

	void Minimap::setPosition(glm::vec2 pos)
	{
		m_position = pos;
	}
}