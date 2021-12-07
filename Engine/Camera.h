#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Engine
{
    class Camera
    {
    public:
        Camera();
        ~Camera();

        void init(int screenWidth, int screenHeight);

        void update();

        glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

        bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

        void setPosition(const glm::vec2& newPosition) { m_position = newPosition; m_needsChange = true; }
        void setScale(float newScale) { m_scale = newScale; m_needsChange = true; }

        glm::vec2 getPosition() { return m_position; }
        float getScale() { return m_scale; }

        glm::mat4 getcameraMatrix() { return m_cameraMatrix; }

    private:
        bool m_needsChange;

        glm::vec2 m_position;
        glm::mat4 m_cameraMatrix;
        glm::mat4 m_orthoMatrix;

        float m_scale;

        int m_screenWidth;
        int m_screenHeight;
    };

    //TODO: add Camera3D class
}
