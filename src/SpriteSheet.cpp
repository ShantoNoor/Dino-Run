#include "SpriteSheet.h"

SpriteSheet::SpriteSheet()
{
    m_spriteMover = 0;
    m_spritePerFrame = 8;
    m_angle = 0.0;
    m_vel = 10;
    m_xpos = 140;
    m_ypos = 360;
    m_yposFinal = 360;
    m_running = true;
    m_jumping = false;
    m_jump = 100;
    m_jumpHr = false;
}

SpriteSheet::~SpriteSheet()
{
    delete m_spriteClip;
    free();
}

void SpriteSheet::load(SDL_Renderer *renderer, std::string path, int totalChipNumber)
{
    if(!m_spriteTexture.loadFromFile(renderer, path)) 
        printf("Failled to load SpriteSheet : %s", IMG_GetError());
    m_spriteTotalChipNumber = totalChipNumber;
    m_spriteWidth = m_spriteTexture.getWidth() / m_spriteTotalChipNumber;
    m_spriteHeight = m_spriteTexture.getHeight();

    m_spriteClip = new SDL_Rect[totalChipNumber];
    for(int i = 0; i < m_spriteTotalChipNumber; i++)
    {
        m_spriteClip[i].x = m_spriteWidth * i;  
        m_spriteClip[i].y = 0; 
        m_spriteClip[i].w =  m_spriteWidth;
        m_spriteClip[i].h =  m_spriteHeight;
    }
}

void SpriteSheet::free()
{
    m_spriteTexture.free();
}

void SpriteSheet::render( SDL_Renderer* renderer)
{
    m_spriteTexture.render(renderer, m_xpos, m_ypos, &m_spriteClip[m_spriteMover/m_spritePerFrame], m_angle);
}

void SpriteSheet::update()
{
    if(m_running) run();
    else if(m_jumping) jump();
}

void SpriteSheet::input(SDL_Event ev )
{
    if(ev.type == SDL_KEYDOWN)
    {
        switch( ev.key.keysym.sym )
        {
            case SDLK_SPACE:
                m_running = false;
                m_jumping = true;
                break;
        }
    }
    else if(ev.type == SDL_KEYUP)
    {
        switch( ev.key.keysym.sym )
        {
            case SDLK_SPACE:
                m_running = true;
                m_jumping = false;
                m_jumpHr = false;
                break;
        }
    }
}

void SpriteSheet::run()
{
    m_angle = 0;
    m_ypos = m_yposFinal;
    m_spriteMover++;
    if(m_spriteMover > m_spriteTotalChipNumber * m_spritePerFrame) m_spriteMover = 0;
}

void SpriteSheet::jump()
{
    if(!m_jumpHr)
    {
        m_ypos -= m_vel;
        if(m_ypos <= m_jump) m_jumpHr = true;
    }
    else
    {
        m_ypos += m_vel;
        if(m_ypos >= m_yposFinal) 
        {
            m_jumpHr = false;
            run();
        }
    }

}