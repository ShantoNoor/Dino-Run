#ifndef __Dino__
#define __Dino__

#include "Charecter.h"

class Dino : public Charecter
{
public:
    Dino(Properties* p);
    void render();
    void update(float dt);
    void free();

private:
    int m_row, m_frame, m_frameCount, m_animationSpeed;

};

#endif