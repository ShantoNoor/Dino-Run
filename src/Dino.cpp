#include "Dino.h"
#include "Graphics.h"
#include "SDL.h"

#include "Input.h"

// Dino::Dino() // Idel=10, Dead=8, Run=, Walk=10, 

Dino::Dino(Properties* p) : Charecter(p)
{
    m_animation = new Animation();
    m_animation->set(m_id, 3, 10, 100); //idle
    m_physics = new Physics();
}

void Dino::render()
{
    m_animation->render(m_transform->x, m_transform->y, m_width, m_height);
}

void Dino::update(float dt)
{
    m_animation->set(m_id, 3, 10, 100); //idle
    m_physics->unSetForce();

    if(Input::get()->getKeyDown(SDL_SCANCODE_D))
    {
        m_physics->applyForce(Vector2d(10, 0));
        m_animation->set(m_id, 0, 8, 80);
    }
    if(Input::get()->getKeyDown(SDL_SCANCODE_A))
    {
        m_physics->applyForce(Vector2d(-10, 0));
        m_animation->set(m_id, 0, 8, 80, SDL_FLIP_HORIZONTAL);
    }
    m_physics->update(0.5);
    m_transform->translateX(m_physics->getPosition());
    m_animation->update();
}

void Dino::free()
{
    Graphics::get()->destroy(m_id);
}
