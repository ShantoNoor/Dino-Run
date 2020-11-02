#ifndef __Camera__
#define __Camera__

#include "Vector2d.h"
#include <SDL.h>

class Camera
{
    Camera();
    static Camera* s_camera;
    Vector2d* m_target;
    Vector2d m_position;
    SDL_Rect m_viewBox;

public:
    void update(float dt);

    //getters and setters
    inline static Camera* get() { return s_camera = (s_camera != nullptr) ? s_camera : new Camera(); }
    inline SDL_Rect getViewBox() { return m_viewBox; }
    inline Vector2d getPosition() { return m_position; }
    inline void setTarget(Vector2d* target) { m_target = target; }

};

#endif