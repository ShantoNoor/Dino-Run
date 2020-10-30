#include "Dino.h"
#include "Graphics.h"
#include "SDL.h"

// Dino::Dino() // Idel=10, Dead=8, Run=, Walk=10, 

Dino::Dino(Properties* p) : Charecter(p)
{
    m_row = 4;
    m_frameCount = 10; 
    m_animationSpeed = 60;
}

void Dino::render()
{
    Graphics::get()->renderSprites(m_id, m_transform->x, m_transform->y, m_width, m_height, m_row, m_frame);
}

void Dino::update(float dt)
{
    m_frame = (SDL_GetTicks() / m_animationSpeed) % m_frameCount;
}

void Dino::free()
{
    Graphics::get()->destroy(m_id);
}
