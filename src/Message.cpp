#include "Message.h"
#include "Graphics.h"
#include "Engine.h"

void Message::setConfig(std::string id)
{
    m_id = id;
    SDL_QueryTexture(Graphics::get()->getTexture(m_id), NULL, NULL, &m_width, &m_height);
}

void Message::render(int x, int y, bool renderBackground, int r, int g, int b, int a)
{
    if (renderBackground) {
        m_rect = {x-5, y, m_width + 10, m_height + 10};
        SDL_SetRenderDrawColor(Engine::get()->getRenderer(), r, g, b, a);
        SDL_RenderFillRect(Engine::get()->getRenderer(), &m_rect);
    }
    Graphics::get()->render(m_id, x, y);
}