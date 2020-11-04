#include "Background.h"
#include "Graphics.h"
#include "Engine.h"

Background::Background(std::string id, int x, int y, int width, int height, int scrollSpeed)
{
    m_id = id;
    m_x = x;
    m_x2 = x + Engine::get()->getScreenWidth();
    m_y = y;
    m_width = width;
    m_height = height;
    m_scrollSpeed = scrollSpeed;
}

void Background::update()
{
    m_x -= m_scrollSpeed;
    if(m_x < -Engine::get()->getScreenWidth()) m_x = Engine::get()->getScreenWidth() - m_scrollSpeed;

    m_x2 -= m_scrollSpeed;
    if(m_x2 < -Engine::get()->getScreenWidth()) m_x2 = Engine::get()->getScreenWidth()- m_scrollSpeed;
}

void Background::render(bool fullScreen)
{
    Graphics::get()->renderBackground(m_id, m_x, m_y, m_width, m_height, fullScreen);
    Graphics::get()->renderBackground(m_id, m_x2, m_y, m_width, m_height, fullScreen);
}
