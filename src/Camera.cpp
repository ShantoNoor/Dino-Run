#include "Camera.h"
#include "Engine.h"

Camera* Camera::s_camera = nullptr;

Camera::Camera()
{
    m_viewBox = {0, 0, Engine::get()->getScreenWidth(), Engine::get()->getScreenHeight()};
}

void Camera::update(float dt)
{
    if(m_target != nullptr)
    {
        m_viewBox.x = m_target->x - Engine::get()->getScreenWidth() / 2;
        m_viewBox.y = m_target->y - Engine::get()->getScreenHeight() / 2;

        if(m_viewBox.x < 0) m_viewBox.x = 0; 

        if(m_viewBox.y < 0) m_viewBox.y = 0; 

        if(m_viewBox.x > 2 * Engine::get()->getScreenWidth() - m_viewBox.w)
            m_viewBox.x =  2 * Engine::get()->getScreenWidth() - m_viewBox.w;

        if(m_viewBox.y > Engine::get()->getScreenHeight() - m_viewBox.h)
            m_viewBox.y =  Engine::get()->getScreenHeight() - m_viewBox.h;
        
        m_position = Vector2d(m_viewBox.x, m_viewBox.y);
    }
}
