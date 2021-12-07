#pragma once

#include <map>
#include <string>

#include "GLTexture.h"

namespace Engine
{
    class TextureCache
    {
    public:
        TextureCache();
        ~TextureCache();

        GLTexture getTexture(const std::string& texturePath);
        GLTexture getTexture(const std::string& texturePath, bool filtering);

        void unloadTexture(const std::string& texturePath);

    private:

        std::map<std::string, GLTexture> m_textureMap;
    };
}
