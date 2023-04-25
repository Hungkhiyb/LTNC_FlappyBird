#include "Camera.h"

Camera* Camera::s_Instance = nullptr;

void Camera::Init()
{
    m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    m_Target = nullptr;
    m_Position.X = 0;
    m_Position.Y = 0;
}


void Camera::Update()
{
    if(m_Target != nullptr)
    {
        m_ViewBox.x = m_Target->X - SCREEN_WIDTH / 2;
        m_ViewBox.y = m_Target->Y - SCREEN_HEIGHT / 2;

        if(m_ViewBox.x < 0)
            m_ViewBox.x = 0;

        if(m_ViewBox.y < 0)
            m_ViewBox.y = 0;
/*
        if(m_ViewBox.x > (SCREEN_WIDTH - m_ViewBox.w))
            m_ViewBox.x = (SCREEN_WIDTH - m_ViewBox.w);
*/
        if(m_ViewBox.y > (SCREEN_HEIGHT - m_ViewBox.h))
            m_ViewBox.y = (SCREEN_HEIGHT - m_ViewBox.h);

        m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
    }
}
