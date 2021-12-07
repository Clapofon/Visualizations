#include "WaterTile.h"
#include <iostream>

#include "ResourceManager.h"


namespace Engine
{
	WaterTile::WaterTile(const glm::vec2& position, const glm::vec2& dimentions, GLTexture reflectionTexture, Camera* camera) :
		m_position(position),
		m_dimentions(dimentions),
		m_texture(reflectionTexture),
		m_camera(camera)
	{}

	WaterTile::~WaterTile()
	{
		delete m_camera;
	}

	void WaterTile::init()
	{
		m_shader.compileShaders("shaders/water/waterVertex.glsl", "shaders/water/waterFragment.glsl");
		m_shader.addAttribute("vertexPosition");
		m_shader.addAttribute("vertexColor");
		m_shader.addAttribute("vertexUV");
		m_shader.linkShaders();

		m_dudvMap = ResourceManager::getTexture("assets/textures/waterDUDV.png", true);

		GLint textureLocation = m_shader.getUniformLocation("sampler");
		GLint dudvMapLocation = m_shader.getUniformLocation("dudvMap");

		m_shader.start();

		glUniform1i(textureLocation, 0);
		glUniform1i(dudvMapLocation, 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture.id);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_dudvMap.id);


		m_shader.stop();
	}

	void WaterTile::draw(SpriteBatch spriteBatch)
	{
		m_shader.start();

		GLuint pLocation = m_shader.getUniformLocation("P");
		glm::mat4 cameraMatrix = m_camera->getcameraMatrix();

		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

		spriteBatch.begin();

		glm::vec4 uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		glm::vec4 destRect = glm::vec4(m_position.x, m_position.y, m_dimentions.x, m_dimentions.y);
		
		spriteBatch.draw(destRect, uvRect, m_texture.id, 1.0f, ColorRGBA8(255, 255, 255, 255));

		spriteBatch.end();
		spriteBatch.renderBatch();
		m_shader.stop();
	}
}