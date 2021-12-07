#pragma once

#include <string>

#include "RawModel.h"
#include "GLTexture.h"

namespace Engine
{
	class TexturedModel
	{
	public:
		TexturedModel(RawModel* model, const std::string& texture);
		~TexturedModel();

		RawModel* getModel() { return m_model; }
		GLTexture getTexture() { return m_texture; }

	private:
		RawModel* m_model;
		GLTexture m_texture;
	};
}