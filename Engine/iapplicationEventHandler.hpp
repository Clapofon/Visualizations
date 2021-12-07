#pragma once

#include <glm.hpp>

namespace Engine
{
    class IApplicationEventHandler
    {
    public:
        IApplicationEventHandler() {}
        virtual ~IApplicationEventHandler() {}
        virtual void onKeyDown(int keyCode, bool isRepeat) = 0;
        virtual void onKeyUp(int keyCode, bool isRepeat) = 0;
        virtual void onMouseDown(int mouseButton, int numClicks) = 0;
        virtual void onMouseUp(int mouseButton, int numClicks) = 0;
        virtual void onMouseMove(int mousePosX, int mousePosY, int deltaX, int deltaY) = 0;

        virtual glm::vec2 getMousePos() = 0;
        virtual glm::vec2 getMouseDelta() = 0;

        virtual void setMousePos(glm::vec2 pos) = 0;
    };
}
