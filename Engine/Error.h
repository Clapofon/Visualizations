#pragma once

#include <string>

namespace Engine
{
    extern void fatalError(std::string errorMessage);
    extern void error(std::string errorMessage);

    // TODO: add more error messages, 
    //       implement seperate logger for engine and app
}
