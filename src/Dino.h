#ifndef __Dino__
#define __Dino__

#include "Charecter.h"
#include "Animation.h"
#include "Physics.h"

#define JUMPTIME 25.0f

class Dino : public Charecter
{
    Animation* m_animation;
    Physics* m_physics;

public:
    Dino(Properties* p);
    float m_jumpTime;
    bool m_isRunning;
    bool m_isFalling;
    virtual void render();
    virtual void update(float dt);
    virtual void free();

};

#endif