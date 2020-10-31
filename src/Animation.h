#ifndef __Animation__
#define __Animation__

#include <SDL.h>
#include <string>

class Animation
{
    int m_spriteFrame, m_spriteRow, m_totalFrame, m_animationSpeed;
    std::string m_id;
    SDL_RendererFlip m_flip;

public:
    Animation(std::string id, int spriteRow, int totalFrame, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void update();
    void render(int x, int y, int spriteWidth, int spriteHeight);

};

#endif