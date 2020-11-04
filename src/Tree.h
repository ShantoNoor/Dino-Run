#ifndef __Tree__
#define __Tree__

#include "Charecter.h"
#include "Physics.h"

class Tree : public Charecter
{
    Physics* m_physics;

public:
    Tree(Properties* p);
    virtual void render();
    virtual void update(float dt);
    virtual void free();

};

#endif