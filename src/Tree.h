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
    float m_scale;

public:
    Tree(Properties* p, float scale);
    virtual void render();
    virtual void update(float dt);
    virtual void free();

    void setTreeVelocity(float newTreeVelocity);
    void reset(float x);
    void partialRender(int xOffset, int yOffset, int widthOffset, int heightOffset);

    SDL_Rect getCollider() { return m_collider; }
};

#endif