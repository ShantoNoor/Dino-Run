#ifndef __Tree__
#define __Tree__

#include "Charecter.h"
#include "Physics.h"
#include <SDL.h>

class Tree : public Charecter
{
    Physics* m_physics;
    SDL_Rect m_collider;
    float m_treeVelocity;
public:
    Tree(Properties* p);
    virtual void render();
    virtual void update(float dt);
    virtual void free();

    void setTreeVelocity(float newTreeVelocity);
    void reset(float x);

    SDL_Rect getCollider() { return m_collider; }

};

#endif