#ifndef __Dino__
#define __Dino__

#include "Charecter.h"
#include "Animation.h"
#include "Physics.h"
#include <SDL.h>

#define RUNNING 0
#define DEAD 1
#define WALKING 2
#define IDLE 3
#define JUMPING 4

class Dino : public Charecter
{
    Physics* m_physics;
    SDL_Rect m_collider;
    Animation* m_animation;
    int m_animationState;

public:
    Dino(Properties* p);
    float m_jumpTime;
    virtual void render();
    virtual void update(float dt);
    virtual void free();

    int m_running = WALKING;

    void setAnimation(int animationState);
    int getAnimationState();

    SDL_Rect getCollider() { return m_collider; }
};

#endif