#include "FontCache.h"

namespace Engine
{
	FontCache::FontCache()
	{}

	FontCache::~FontCache()
	{
		for (std::map<std::pair<std::string, int>, SpriteFont*>::iterator mit = m_fontMap.begin(); mit != m_fontMap.end();)
		{
			mit->second->dispose();
			delete mit->second;
			m_fontMap.erase(mit++);
		}
		printf("Unloaded all fonts\n");
	}

	SpriteFont* FontCache::getFont(const std::string& font)
	{
		//auto mit = m_fontMap.find(font);
		int size = 256;

		std::map<std::pair<std::string, int>, SpriteFont*>::iterator mit;
		mit = m_fontMap.find(make_pair(font, size));

		if (mit == m_fontMap.end())
		{
			printf("Loading font: %s size: %d ... ", font.c_str(), size);
			SpriteFont* spriteFont = new SpriteFont(font.c_str(), size);
			m_fontMap.insert(make_pair(make_pair(font, size), spriteFont));
			printf("   Loaded.\n");
			return spriteFont;
		}
		return mit->second;
	}

	SpriteFont* FontCache::getFont(const std::string& font, int size)
	{
		std::map<std::pair<std::string, int>, SpriteFont*>::iterator mit;
		mit = m_fontMap.find(make_pair(font, size));

		if (mit == m_fontMap.end())
		{
			printf("Loading font: %s size: %d ... ", font.c_str(), size);
			SpriteFont* spriteFont = new SpriteFont(font.c_str(), size);
			m_fontMap.insert(make_pair(make_pair(font, size), spriteFont));
			printf("   Loaded.\n");
			return spriteFont;
		}
		return mit->second;
	}

	void FontCache::unloadFont(const std::string& font)
	{
		std::map<std::pair<std::string, int>, SpriteFont*>::iterator mit;
		mit = m_fontMap.find(make_pair(font, 256));

		if (mit != m_fontMap.end())
		{
			printf("Unloading font: %s size: %d ... ", font.c_str(), 256);
			mit->second->dispose();
			delete mit->second;
			m_fontMap.erase(mit);
			printf("   Unloaded.\n");
		}
	}

	void FontCache::unloadFont(const std::string& font, int size)
	{
		std::map<std::pair<std::string, int>, SpriteFont*>::iterator mit;
		mit = m_fontMap.find(make_pair(font, size));

		if (mit != m_fontMap.end())
		{
			printf("Unloading font: %s size: %d ... ", font.c_str(), size);
			mit->second->dispose();
			delete mit->second;
			m_fontMap.erase(mit);
			printf("   Unloaded.\n");
		}
	}
}
