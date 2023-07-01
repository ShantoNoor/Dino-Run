#ifndef __Animation__
#define __Animation__

#include <SDL.h>
#include <string>

class Animation
{
    int m_spriteFrame, m_spriteRow, m_totalFrame, m_animationSpeed;
    std::string m_id;
    SDL_RendererFlip m_flip;
    int m_frameCount = 0;
    bool m_playOnlyOnce;

public:
    Animation() { m_flip = SDL_FLIP_NONE; };
    void update();
    void render(int x, int y, int spriteWidth, int spriteHeight);

    //getters and setters
    void set(std::string id, int spriteRow, int totalFrame, int animationSpeed, bool playOnlyOnce = false);
    void setFlip(SDL_RendererFlip flip) { m_flip = flip; }
};

#endif