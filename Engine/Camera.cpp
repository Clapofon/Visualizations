#include "Camera.h"

namespace Engine
{
    Camera::Camera() : m_needsChange(true), m_position(0.0f, 0.0f), m_cameraMatrix(1.0f), m_orthoMatrix(1.0f), m_scale(1.0f), m_screenWidth(1200), m_screenHeight(720)
    {}

    Camera::~Camera()
    {}

    void Camera::init(int screenWidth, int screenHeight)
    {
        m_screenWidth = screenWidth;
        m_screenHeight = screenHeight;
        m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
    }

    void Camera::update()
    {
        //Update only if something changed
        if (m_needsChange)
        {
            //Camera translation
            glm::vec3 translate(-m_position.x + m_screenWidth/2, -m_position.y + m_screenHeight/2, 0.0f);
            m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

            //Camera scale
            glm::vec3 scale(m_scale, m_scale, 0.0f);
            m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

            m_needsChange = false;
        }
    }

    glm::vec2 Camera::convertScreenToWorld(glm::vec2 screenCoords)
    {
        //Invert Y axis
        screenCoords.y = m_screenHeight - screenCoords.y;
        //Make it so that 0 is in the center
        screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
        //Scale the coordinates
        screenCoords /= m_scale;
        //Translate with camera position
        screenCoords += m_position;

        return screenCoords;
    }

    bool Camera::isBoxInView(const glm::vec2& position, const glm::vec2& dimensions)
    {
        glm::vec2 scaledScreenDimensions = glm::vec2(1920, 1080) / m_scale;

        const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
        const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

        glm::vec2 centerPosition = glm::vec2(position + dimensions / 2.0f);

        glm::vec2 distVec = centerPosition - m_position;

        float xDepth = MIN_DISTANCE_X - abs(distVec.x);
        float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

        return (xDepth > 0 && yDepth > 0);
    }
}












