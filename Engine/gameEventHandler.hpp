#pragma once

#include "iapplicationEventHandler.hpp"
#include "inputControl.hpp"
#include <map>
#include <vector>
#include <glm.hpp>

namespace Engine
{
    class GameEventHandler : public IApplicationEventHandler
    {
    public:
        GameEventHandler() : m_mousePosX(0), m_mousePosY(0), m_deltaX(0), m_deltaY(0) {}
        virtual ~GameEventHandler() {}
        virtual void onKeyDown(int keyCode, bool isRepeat);
        virtual void onKeyUp(int keyCode, bool isRepeat);
        virtual void onMouseDown(int mouseButton, int numClicks);
        virtual void onMouseUp(int mouseButton, int numClicks);
        virtual void onMouseMove(int mousePosX, int mousePosY, int deltaX, int deltaY);

        virtual glm::vec2 getMousePos();
        virtual glm::vec2 getMouseDelta();

        virtual void setMousePos(glm::vec2 pos);

        void addKeyControl(int keyCode, InputControl& inputControl, float weight = 1.0f);
        void addMouseControl(int mouseButton, InputControl& inputControl, float weight = 1.0f);
    private:
        std::map<int, std::vector<std::pair<float, InputControl&> > > m_inputs;
        //std::map<int, std::vector<std::pair<float, InputControl&> > > m_previousInputs;
        void updateInput(int inputCode, float dir, bool isRepeat);

        int m_mousePosX;
        int m_mousePosY;
        int m_deltaX;
        int m_deltaY;
    };
}
