#ifndef __Transform__
#define __Transform__

#include "Vector2d.h"

class Transform
{
public:
    float x, y;
    Transform(float x = 0, float y = 0) { this->x = x; this->y = y; }
    inline void Translate(Vector2d v) { x + v.x; y + v.y; }

};

#endif