#pragma once

#include "picoPNG.h"
#include "GLTexture.h"

#include <string>

namespace Engine
{
    class ImageLoader
    {
    public:
        static GLTexture loadPNG(std::string filePath);
        static GLTexture loadPNG(std::string filePath, bool filtering);
    };
}
