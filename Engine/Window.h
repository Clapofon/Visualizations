#pragma once

#include <SDL.h>
#include <string>

namespace Engine
{
    enum WindowFlags
    {
        INVISIBLE = 0x1,
        FULLSCREEN = 0x2,
        BORDERLESS = 0x4
    };

    // TODO: add support for all window flags

    class Window
    {
    public:
        Window();
        ~Window();

        int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

        SDL_Window* get();

        void swapBuffer();

    private:
        SDL_Window* m_sdlWindow;
    };
}
