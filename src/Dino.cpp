#include "Dino.h"
#include "Graphics.h"
#include "SDL.h"
#include "Input.h"
#include "Timer.h"
#include "Engine.h"

#define JUMPTIME 25.0f
#define JUMPVELOCITY 25.0f

Dino::Dino(Properties* p) : Charecter(p)
{
    m_animation = new Animation();
    m_animation->set(m_id, 3, 10, 100); //idle
    m_physics = new Physics();
    m_isRunning = true;
    m_isFalling = false;
    m_jumpTime = JUMPTIME;
    m_collider = {(int)(m_transform->x + 12), (int)(m_transform->y + 1), 190, 208};
}

void Dino::render()
{
    m_animation->render(m_transform->x, m_transform->y, m_width, m_height);

    // for collider
    // SDL_Rect dinoBox = {(int)(m_transform->x + 12), (int)(m_transform->y + 1), 190, 208};
	// SDL_SetRenderDrawColor(Engine::get()->getRenderer(), 255, 0, 0, 255);
	// SDL_RenderDrawRect(Engine::get()->getRenderer(), &m_collider);

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
        m_physics->applyForce(Vector2d(0.0f, -JUMPVELOCITY));
    }
    else if(Input::get()->getKeyDown(SDL_SCANCODE_SPACE) && m_isFalling && m_jumpTime > 0)
    {
        m_jumpTime -= dt;
        m_physics->applyForce(Vector2d(0.0f, -JUMPVELOCITY));
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
    if(m_transform->y < 140) m_transform->y = 140;

    m_collider = {(int)(m_transform->x + 12), (int)(m_transform->y + 1), 190, 208};

    m_animation->update();
}

void Dino::free() { }

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
