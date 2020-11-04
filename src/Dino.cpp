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
    m_isRunning = true;
    m_isFalling = false;
    m_jumpTime = JUMPTIME;
}

void Dino::render()
{
    m_animation->render(m_transform->x, m_transform->y, m_width, m_height);
}

void Dino::update(float dt)
{
    if(m_isRunning) m_animation->set(m_id, 0, 8, 80);

    m_physics->unSetForce();

    if(Input::get()->getKeyDown(SDL_SCANCODE_SPACE) && m_isRunning && m_jumpTime == JUMPTIME)
    {
        m_animation->set(m_id, 4, 12, 80);
        m_isRunning = false;
        m_isFalling = true;
        m_physics->applyForce(Vector2d(0, -23));
    }
    else if(Input::get()->getKeyDown(SDL_SCANCODE_SPACE) && m_isFalling && m_jumpTime > 0)
    {
        m_jumpTime -= dt;
        m_physics->applyForce(Vector2d(0, -23));
    }
    else if(m_isFalling && m_transform->y == 420)
    {
        m_isFalling = false;
        m_isRunning = true;
        m_transform->y = 420;
        m_jumpTime = JUMPTIME;
    }

    m_physics->update(dt);
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
