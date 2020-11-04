#include "Dino.h"
#include "Graphics.h"
#include "SDL.h"
#include "Input.h"
#include "Timer.h"

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
    // m_animation->set(m_id, 3, 10, 100); //idle
    m_animation->set(m_id, 0, 8, 80);
    m_physics->unSetForce();
    
    if(Input::get()->getKeyDown(SDL_SCANCODE_SPACE))
    {
        m_physics->applyForce(Vector2d(0, -25));
        m_animation->set(m_id, 4, 12, 80);
    }

    m_physics->update(Timer::get()->getDeltaTime());
    m_transform->translate(m_physics->getPosition());

    if(m_transform->y > 420) m_transform->y = 420; 
    if(m_transform->y < 150) m_transform->y = 150;

    m_animation->update();
}

void Dino::free()
{
    Graphics::get()->destroy(m_id);
}


// if(Input::get()->getKeyDown(SDL_SCANCODE_D))
    // {
    //     m_physics->applyForce(Vector2d(10, 0));
    //     m_animation->set(m_id, 0, 8, 80);
    //     m_animation->setFlip(SDL_FLIP_NONE);
    // }
    // if(Input::get()->getKeyDown(SDL_SCANCODE_A))
    // {
    //     m_physics->applyForce(Vector2d(-10, 0));
    //     m_animation->set(m_id, 0, 8, 80);
    //     m_animation->setFlip(SDL_FLIP_HORIZONTAL);
    // }

