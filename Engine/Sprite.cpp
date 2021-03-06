#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

namespace Engine
{
    Sprite::Sprite() : m_vboID(0)
    {

    }

    Sprite::~Sprite()
    {
        if (m_vboID != 0)
        {
            glDeleteBuffers(1, &m_vboID);
        }
    }

    void Sprite::init(std::string texturePath, float x, float y, float w, float h)
    {
        m_x = x;
        m_h = y;
        m_w = w;
        m_h = h;

        m_texture = ResourceManager::getTexture(texturePath);

        if (m_vboID == 0)
        {
            glGenBuffers(1, &m_vboID);
        }

        Vertex vertexData[6];

        vertexData[0].setPosition(x + w, y + h);
        vertexData[0].setUV(1.0f, 1.0f);

        vertexData[1].setPosition(x, y + h);
        vertexData[1].setUV(0.0f, 1.0f);

        vertexData[2].setPosition(x, y);
        vertexData[2].setUV(0.0f, 0.0f);

        vertexData[3].setPosition(x, y);
        vertexData[3].setUV(0.0f, 0.0f);

        vertexData[4].setPosition(x + w, y);
        vertexData[4].setUV(1.0f, 0.0f);

        vertexData[5].setPosition(x + w, y + h);
        vertexData[5].setUV(1.0f, 1.0f);

        vertexData[0].setColor(255, 0, 0, 255);
        vertexData[1].setColor(0, 255, 0, 255);
        vertexData[2].setColor(0, 0, 255, 255);
        vertexData[3].setColor(0, 0, 255, 255);
        vertexData[4].setColor(255, 255, 255, 255);
        vertexData[5].setColor(255, 0, 0, 255);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Sprite::draw()
    {
        glBindTexture(GL_TEXTURE_2D, m_texture.id);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Sprite::setPos(float x, float y)
    {
        m_x = x;
        m_y = y;
    }
}











