#pragma once

#include <glew.h>
#include <string>

#include "GLTexture.h"

namespace Engine
{
    class Sprite
    {
    public:
        Sprite();
        ~Sprite();

        void init(std::string texturePath, float x, float y, float w, float h);
        void draw();
        void setPos(float x, float y);
    private:
        float m_x;
        float m_y;
        float m_w;
        float m_h;

        GLuint m_vboID;
        GLTexture m_texture;
    };
}
