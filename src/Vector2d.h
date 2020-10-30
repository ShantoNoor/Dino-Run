#ifndef __Vector2d__
#define __Vector2d__

class Vector2d
{
public:
    float x, y;
    Vector2d(float x = 0, float y = 0) { this->x = x; this->y = y; }
    inline Vector2d operator+(const Vector2d& v) const { return Vector2d(x + v.x, y + v.y); }
    inline Vector2d operator-(const Vector2d& v) const { return Vector2d(x - v.x, y - v.y); }
    inline Vector2d operator*(const float scalar) const { return Vector2d(scalar * x, scalar * y); }
};

#endif