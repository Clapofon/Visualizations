#pragma once

#include "TextureCache.h"
#include "FontCache.h"
#include "ShaderCache.h"

namespace Engine
{
    // TODO: 

    class ResourceManager
    {
    public:
        static GLTexture getTexture(const std::string& texturePath);
        static GLTexture getTexture(const std::string& texturePath, bool filtering);
        static SpriteFont* getFont(const std::string& font);
        static SpriteFont* getFont(const std::string& font, int size);
        static GLSLProgram getShader(const std::string& vertexShader, const std::string& fragmentShader);

        static void loadTexture(const std::string& texturePath);
        static void loadTexture(const std::string& texturePath, bool filtering);
        static void loadFont(const std::string& font);
        static void loadFont(const std::string& font, int size);
        static void loadShader(const std::string& vertexShader, const std::string& fragmentShader);

        static void unloadTexture(const std::string& texturePath);
        static void unloadFont(const std::string& font);
        static void unloadFont(const std::string& font, int size);
        static void unloadShader(const std::string& vertexShader, const std::string& fragmentShader);

         /* //  TODO: make it work
        template <bool filtering, typename... Ttextures>
        static void loadTextures(Ttextures... textures)
        {
            for (auto t : textures)
            {
                loadTexture(std::forward<Ttextures>(t), filtering);
            }
        }

        template <typename... Ttextures>
        static void loadTextures(Ttextures... textures)
        {
            //for (auto t : textures)
            //{
                loadTexture(std::forward<Ttextures>(textures)..., true);
            //}
        }*/

    private:
        static TextureCache m_textureCache;
        static FontCache m_fontCache;
        static ShaderCache m_shaderCache;
    };
}
