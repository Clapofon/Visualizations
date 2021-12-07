#pragma once

#include "SpriteFont.h"
#include <unordered_map>

namespace Engine 
{
	class FontCache
	{
	public:
		FontCache();
		~FontCache();

		SpriteFont* getFont(const std::string& font);
		SpriteFont* getFont(const std::string& font, int size);

		void unloadFont(const std::string& font);
		void unloadFont(const std::string& font, int size);

	private:

		//std::unordered_map<std::string, SpriteFont*> m_fontMap;

		std::map<std::pair<std::string, int>, SpriteFont*> m_fontMap;
	};
}


