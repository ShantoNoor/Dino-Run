#include "Dino.h"
#include "Graphics.h"
#include "SDL.h"
#include "Input.h"
#include "Timer.h"
#include "Engine.h"

#define JUMPTIME 25.0f
#define JUMPVELOCITY 25.0f

#define COLLIDER_OFFSET_X 40
#define COLLIDER_OFFSET_Y 40
#define COLLIDER_WIDTH 140
#define COLLIDER_HEIGHT 135

#define MAX_Y 440

Dino::Dino(Properties* p) : Charecter(p)
{
    m_animation = new Animation();
    m_physics = new Physics();
    m_jumpTime = JUMPTIME;
    m_collider = {(int)(m_transform->x + COLLIDER_OFFSET_X), (int)(m_transform->y + COLLIDER_OFFSET_Y), COLLIDER_WIDTH, COLLIDER_HEIGHT};
    setAnimation(IDLE);
}

void Dino::render()
{
    m_animation->render(m_transform->x, m_transform->y, m_width, m_height);

    // for collider
	// SDL_SetRenderDrawColor(Engine::get()->getRenderer(), 255, 0, 0, 255);
	// SDL_RenderDrawRect(Engine::get()->getRenderer(), &m_collider);

}

void Dino::update(float dt)
{
    m_physics->unSetForce();

    if(!Engine::get()->m_dead) {
        if(Input::get()->getKeyDown(SDL_SCANCODE_SPACE) && m_animationState != JUMPING && m_jumpTime == JUMPTIME)
        {
            setAnimation(JUMPING);
            m_physics->applyForce(Vector2d(0.0f, -JUMPVELOCITY));
        }
        else if(Input::get()->getKeyDown(SDL_SCANCODE_SPACE) && m_jumpTime > 0)
        {
            m_jumpTime -= dt;
            m_physics->applyForce(Vector2d(0.0f, -JUMPVELOCITY));
        }
        else if(m_transform->y == MAX_Y)
        {
            m_transform->y = MAX_Y;
            m_jumpTime = JUMPTIME;
            if(Engine::get()->m_playing) {
                setAnimation(m_running);
            } else {
                setAnimation(IDLE);
            }
        }

    }

    m_physics->update(dt);
    m_transform->translate(m_physics->getPosition());

    if(m_transform->y > MAX_Y) m_transform->y = MAX_Y; 
    if(m_transform->y < 140) m_transform->y = 140;

    m_collider = {(int)(m_transform->x + COLLIDER_OFFSET_X), (int)(m_transform->y + COLLIDER_OFFSET_Y), COLLIDER_WIDTH, COLLIDER_HEIGHT};
    
    m_animation->update();
}

void Dino::setAnimation(int animationState) 
{
    if (animationState == RUNNING) {
        m_animation->set(m_id, RUNNING, 8, 90);
        m_animationState = RUNNING;
    } else if (animationState == IDLE) {
        m_animation->set(m_id, IDLE, 10, 90);
        m_animationState = IDLE;
    } else if (animationState == WALKING) {
        m_animation->set(m_id, WALKING, 10, 90);
        m_animationState = WALKING;
    } else if (animationState == DEAD) {
        m_animation->set(m_id, DEAD, 8, 90, true);
        m_animationState = DEAD;
    } else if (animationState == JUMPING) {
        m_animation->set(m_id, JUMPING, 12, 90);
        m_animationState = JUMPING;
    }
}

int Dino::getAnimationState() 
{
    return m_animationState;
}

void Dino::free() { }
