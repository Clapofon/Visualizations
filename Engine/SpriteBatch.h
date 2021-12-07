#pragma once

#include <glew.h>
#include <glm.hpp>
#include <vector>

#include "Vertex.h"

namespace Engine
{
    enum class GlyphSortType
    {
        NONE,
        FRONT_TO_BACK,
        BACK_TO_FRONT,
        TEXTURE
    };

    struct Glyph
    {
        Glyph() {}
        Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& Texture, float Depth, const ColorRGBA8& color);
        Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& Texture, float Depth, const ColorRGBA8& color, float angle);
        Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& Texture, float Depth, const ColorRGBA8& color, float angle, glm::vec2 rotateCenterPoint);



        GLuint texture;
        float depth;

        Vertex topLeft;
        Vertex bottomLeft;
        Vertex topRight;
        Vertex bottomRight;

    private:
        glm::vec2 rotatePoint(glm::vec2 pos, float angle);
    };

    class RenderBatch
    {
    public:
        RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture)
        {}

        GLuint offset;
        GLuint numVertices;
        GLuint texture;
    };

    class SpriteBatch
    {
    public:
        SpriteBatch();
        ~SpriteBatch();

        void init();

        void begin(GlyphSortType glyphsortType = GlyphSortType::TEXTURE);
        void end();

        void draw(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& texture, float depth, const ColorRGBA8& color);
        void draw(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& texture, float depth, const ColorRGBA8& color, float angle);
        void draw(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& texture, float depth, const ColorRGBA8& color, const glm::vec2 dir);

        void draw(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& texture, float depth, const ColorRGBA8& color, float angle, glm::vec2 rotateCenterPoint);
        void draw(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& texture, float depth, const ColorRGBA8& color, const glm::vec2 dir, glm::vec2 rotateCenterPoint);

        void renderBatch();

    private:
        void createRenderBatches();
        void createVertexArray();
        void sortGlyphs();

        static bool compareFrontToBack(Glyph* a, Glyph* b);
        static bool compareBackToFront(Glyph* a, Glyph* b);
        static bool compareTexture(Glyph* a, Glyph* b);


        GlyphSortType m_glyphSortType;

        GLuint m_vbo;
        GLuint m_vao;

        std::vector<Glyph*> m_glyphPointers;
        std::vector<Glyph> m_glyphs;
        std::vector<RenderBatch> m_renderBatches;

    };
}







