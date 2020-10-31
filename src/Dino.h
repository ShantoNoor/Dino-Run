#ifndef __Dino__
#define __Dino__

#include "Charecter.h"
#include "Animation.h"
#include "Physics.h"

class Dino : public Charecter
{
public:
    Dino(Properties* p);
    virtual void render();
    virtual void update(float dt);
    virtual void free();

private:
    Animation* m_animation;
    Physics* m_physics;

};

#endif