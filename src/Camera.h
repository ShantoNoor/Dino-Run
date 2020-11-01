#ifndef __Camera__
#define __Camera__

#include "Vector2d.h"

class Camera
{
    Camera(){};
    static Camera* s_camera;

public:
    static Camera* get() { return s_camera = (s_camera != nullptr) ? s_camera : new Camera(); }

};

#endif