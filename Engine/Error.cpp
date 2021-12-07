#include "Error.h"

#include <iostream>
#include <cstdlib>
#include <SDL.h>

namespace Engine
{
    void fatalError(std::string errorMessage)
    {
        std::cerr << errorMessage << std::endl;
        SDL_Quit();
        exit(1);
    }

    void error(std::string errorMessage)
    {
        std::cerr << errorMessage << std::endl;
    }
}
