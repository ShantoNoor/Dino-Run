#ifndef __Charecter__
#define __Charecter__

#include <SDL.h>
#include "GameObject.h"

class Charecter : public GameObject
{
    std::string m_name;

public:
    Charecter(Properties* p) : GameObject(p) {}
    virtual void render() = 0;
    virtual void update(float dt) = 0;
    virtual void free() = 0;

};

#endif