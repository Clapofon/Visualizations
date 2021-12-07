#include "TexturedModel.h"

#include "ResourceManager.h"

namespace Engine
{
	TexturedModel::TexturedModel(RawModel* model, const std::string& texture) :
		m_model(model),
		m_texture(ResourceManager::getTexture(texture))
	{

	}

	TexturedModel::~TexturedModel()
	{
		delete m_model;
	}
}