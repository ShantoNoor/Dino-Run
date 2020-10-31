#ifndef __Input__
#define __Input__

#include <SDL.h>

class Input
{
    Input();
    static Input* s_input;
    void keyUp();
    void keyDown();
    const Uint8* m_keyStates;

public:
    SDL_Event ev;
    void listen();
    bool getKeyDown(SDL_Scancode key);

    //getters and setters
    static Input* get() { return s_input = (s_input != nullptr) ? s_input : new Input(); }

};

#endif