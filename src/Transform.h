#ifndef __Transform__
#define __Transform__

#include "Vector2d.h"

class Transform
{
public:
    float x, y;
    Transform(float x = 0, float y = 0) { this->x = x; this->y = y; }
    inline void translate(Vector2d v) { x += v.x; y += v.y; }
    inline void translateX(Vector2d v) { x += v.x; }
    inline void translateY(Vector2d v) { y += v.y; }

};

#endif