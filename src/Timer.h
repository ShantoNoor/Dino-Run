#ifndef __Timer__
#define __Timer__

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer
{
    Timer(){};
    static Timer* s_timer;
    float m_deltaTime, m_lastTime;

public:
    void tick();
    float getDeltaTime() { return m_deltaTime; }

    //getters and setters
    static Timer* get() { return s_timer = (s_timer != nullptr) ? s_timer : new Timer(); }

};

#endif