#include "gameEventHandler.hpp"
#include "Input.hpp"

#include <SDL.h>

#define MOUSE_OFFSET Input::NUM_KEYS

namespace Engine
{
    void GameEventHandler::onKeyDown(int keyCode, bool isRepeat)
    {
        updateInput(keyCode, 1.0f, isRepeat);
    }

    void GameEventHandler::onKeyUp(int keyCode, bool isRepeat)
    {
        updateInput(keyCode, -1.0f, isRepeat);
    }

    void GameEventHandler::onMouseDown(int mouseButton, int numClicks)
    {
        updateInput(mouseButton, 1.0f, false);
    }

    void GameEventHandler::onMouseUp(int mouseButton, int numClicks)
    {
        updateInput(mouseButton, -1.0f, false);
    }

    void GameEventHandler::onMouseMove(int mousePosX, int mousePosY, int deltaX, int deltaY)
    {
        m_mousePosX = mousePosX;
        m_mousePosY = mousePosY;
        m_deltaX = deltaX;
        m_deltaY = deltaY;
    }

    glm::vec2 GameEventHandler::getMousePos()
    {
        return glm::vec2(m_mousePosX, m_mousePosY);
    }

    glm::vec2 GameEventHandler::getMouseDelta()
    {
        return glm::vec2(m_deltaX, m_deltaY);
    }

    void GameEventHandler::setMousePos(glm::vec2 pos)
    {
        SDL_WarpMouseInWindow(NULL, pos.x, pos.y);
    }

    void GameEventHandler::addKeyControl(int keyCode, InputControl& inputControl, float weight)
    {
        m_inputs[keyCode].push_back(std::pair<float, InputControl&>(weight, inputControl));
    }

    void GameEventHandler::addMouseControl(int mouseButton, InputControl& inputControl, float weight)
    {
        m_inputs[mouseButton+MOUSE_OFFSET].push_back(std::pair<float, InputControl&>(weight, inputControl));
    }

    void GameEventHandler::updateInput(int inputCode, float dir, bool isRepeat)
    {
        if(isRepeat) {
            return;
        }

        for(unsigned int i = 0; i < m_inputs[inputCode].size(); i++) {
            m_inputs[inputCode][i].second.addAmt(m_inputs[inputCode][i].first * dir);
        }
    }
}
