#pragma once

#include <glew.h>

namespace Engine
{

    struct Position
    {
        Position() : x(0), y(0) {}
        Position(float X, float Y) : x(X), y(Y) {}

        float x;
        float y;
    };

    struct ColorRGBA8
    {
        ColorRGBA8() : r(0), g(0), b(0), a(0) {}
        ColorRGBA8(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) : r(red), g(green), b(blue), a(alpha) {}


        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    };

    struct UV
    {
        UV() : u(0), v(0) {}
        UV(float U, float V) : u(U), v(V) {}

        float u;
        float v;
    };

    struct Vertex
    {
        Position position;
        ColorRGBA8 color;
        UV uv;

        void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
        {
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        }

        void setPosition(float x, float y)
        {
            position.x = x;
            position.y = y;
        }

        void setUV(float u, float v)
        {
            uv.u = u;
            uv.v = v;
        }
    };
}









