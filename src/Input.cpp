#include "Input.h"
#include "Engine.h"

Input* Input::s_input = nullptr;

Input::Input()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::listen()
{
    while (SDL_PollEvent(&ev))
    {
        switch(ev.type)
        {
            case SDL_QUIT: Engine::get()->quit(); break;
            case SDL_KEYDOWN: keyDown(); break;
            case SDL_KEYUP: keyUp(); break;
        }
    }
    
}

bool Input::getKeyDown(SDL_Scancode key)
{
    return (m_keyStates[key] == 1);
}

void Input::keyUp()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::keyDown()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}
