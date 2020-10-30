#ifndef __SpriteSheet__
#define __SpriteSheet__

#include "LTexture.h"

class SpriteSheet
{
public:
    SpriteSheet();
    ~SpriteSheet();

    void load(SDL_Renderer *renderer, std::string path, int totalChipNumber);
    void render( SDL_Renderer* renderer);
    void input(SDL_Event ev);
    void update();

    void free();

    void setXpos(int xpos) { m_xpos = xpos; }
    void setYpos(int ypos) { m_ypos = ypos; }

    void run();
    void jump();

private:
    LTexture m_spriteTexture;
    int m_xpos, m_ypos, m_yposFinal;
    int m_vel;
    double m_angle;
    int m_spriteHeight;
    int m_spriteWidth;
    int m_spriteTotalChipNumber;
    int m_spriteMover;
    int m_spritePerFrame;
    SDL_Rect *m_spriteClip;
    bool m_running, m_jumping;
    int m_jump;
    bool m_jumpHr;
};

#endif