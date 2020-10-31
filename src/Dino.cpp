#include "Dino.h"
#include "Graphics.h"
#include "SDL.h"

// Dino::Dino() // Idel=10, Dead=8, Run=, Walk=10, 

Dino::Dino(Properties* p) : Charecter(p)
{
    m_animation = new Animation(m_id, 4, 10, 60);
    m_physics = new Physics();
}

void Dino::render()
{
    m_animation->render(m_transform->x, m_transform->y, m_width, m_height);
}

void Dino::update(float dt)
{
    m_animation->update();
    m_physics->applyForce(Vector2d(10, 0));
    m_physics->update(0.5);
    m_transform->translate(m_physics->getPosition());
}

void Dino::free()
{
    Graphics::get()->destroy(m_id);
}
