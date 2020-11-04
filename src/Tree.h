#ifndef __Tree__
#define __Tree__

#include "Charecter.h"
#include "Physics.h"
#include <SDL.h>

class Tree : public Charecter
{
    Physics* m_physics;
    SDL_Rect m_collider;
public:
    Tree(Properties* p);
    virtual void render();
    virtual void update(float dt);
    virtual void free();

    SDL_Rect getCollider() { return m_collider; }

};

#endif