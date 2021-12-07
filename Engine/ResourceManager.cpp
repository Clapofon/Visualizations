#include "ResourceManager.h"

namespace Engine
{
    TextureCache ResourceManager::m_textureCache;
    FontCache ResourceManager::m_fontCache;
    ShaderCache ResourceManager::m_shaderCache;

    GLTexture ResourceManager::getTexture(const std::string& texturePath)
    {
        return m_textureCache.getTexture(texturePath);
    }

    GLTexture ResourceManager::getTexture(const std::string& texturePath, bool filtering)
    {
        return m_textureCache.getTexture(texturePath, filtering);
    }

    SpriteFont* ResourceManager::getFont(const std::string& font)
    {
        return m_fontCache.getFont(font);
    }

    SpriteFont* ResourceManager::getFont(const std::string& font, int size)
    {
        return m_fontCache.getFont(font, size);
    }

    GLSLProgram ResourceManager::getShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        return m_shaderCache.getShader(vertexShader, fragmentShader);
    }

    void ResourceManager::loadTexture(const std::string& texturePath)
    {
        m_textureCache.getTexture(texturePath);
    }

    void ResourceManager::loadTexture(const std::string& texturePath, bool filtering)
    {
        m_textureCache.getTexture(texturePath, filtering);
    }

    void ResourceManager::loadFont(const std::string& font)
    {
        m_fontCache.getFont(font);
    }

    void ResourceManager::loadFont(const std::string& font, int size)
    {
        m_fontCache.getFont(font, size);
    }
    
    void ResourceManager::loadShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        m_shaderCache.getShader(vertexShader, fragmentShader);
    }

    void ResourceManager::unloadTexture(const std::string& texturePath)
    {
        m_textureCache.unloadTexture(texturePath);
    }

    void ResourceManager::unloadFont(const std::string& font)
    {
        m_fontCache.unloadFont(font);
    }

    void ResourceManager::unloadFont(const std::string& font, int size)
    {
        m_fontCache.unloadFont(font, size);
    }

    void ResourceManager::unloadShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        m_shaderCache.unloadShader(vertexShader, fragmentShader);
    }
}
