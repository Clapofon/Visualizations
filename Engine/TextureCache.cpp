#include "TextureCache.h"
#include "ImageLoader.h"

#include <iostream>

namespace Engine
{
    TextureCache::TextureCache()
    {}

    TextureCache::~TextureCache()
    {
        for (std::map<std::string, GLTexture>::iterator mit = m_textureMap.begin(); mit != m_textureMap.end();)
        {
            glDeleteTextures(1, &mit->second.id);
            m_textureMap.erase(mit++);
        }
        printf("Unloaded all textures\n");
    }

    GLTexture TextureCache::getTexture(const std::string& texturePath)
    {
        auto mit = m_textureMap.find(texturePath);

        if (mit == m_textureMap.end())
        {
            printf("Loading texture: %s ... ", texturePath.c_str());
            GLTexture newTexture = ImageLoader::loadPNG(texturePath);

            m_textureMap.insert(make_pair(texturePath, newTexture));

            printf("   Loaded.\n");
            return newTexture;
        }
        return mit->second;
    }

    GLTexture TextureCache::getTexture(const std::string& texturePath, bool filtering)
    {
        auto mit = m_textureMap.find(texturePath);

        if (mit == m_textureMap.end())
        {
            printf("Loading texture: %s ... ", texturePath.c_str());
            GLTexture newTexture = ImageLoader::loadPNG(texturePath, filtering);

            m_textureMap.insert(make_pair(texturePath, newTexture));

            printf("   Loaded.\n");
            return newTexture;
        }
        return mit->second;
    }

    void TextureCache::unloadTexture(const std::string& texturePath)
    {
        auto mit = m_textureMap.find(texturePath);

        if (mit != m_textureMap.end())
        {
            printf("Unloading texture: %s ... ", texturePath.c_str());
            glDeleteTextures(1, &mit->second.id);
            m_textureMap.erase(mit);
            printf("   Unloaded.\n");
        }
    }
}
