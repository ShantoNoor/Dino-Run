#include "Animation.h"
#include "Graphics.h"

void Animation::set(std::string id, int spriteRow, int totalFrame, int animationSpeed, bool playOnlyOnce)
{
    m_spriteRow = spriteRow;
    m_animationSpeed = animationSpeed;
    m_totalFrame = totalFrame;
    m_id = id;
    m_playOnlyOnce = playOnlyOnce;
}

void Animation::update()
{
    if(m_playOnlyOnce && m_frameCount > m_totalFrame) {
        m_spriteFrame = m_totalFrame - 1;
    } else {
        m_spriteFrame = ( SDL_GetTicks() / m_animationSpeed ) % m_totalFrame;
    }
}

void Animation::render(int x, int y, int spriteWidth, int spriteHeight)
{
    m_frameCount++;
    Graphics::get()->renderSprites(m_id, x, y, spriteWidth, spriteHeight, m_spriteRow, m_spriteFrame, 0.0, NULL, m_flip);
}
