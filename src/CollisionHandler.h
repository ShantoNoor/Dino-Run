#ifndef __CollisionHandler__
#define __CollisionHandler__

#include <SDL.h>

class CollisionHandler
{
    CollisionHandler(){};
    static CollisionHandler* s_collisionHandler;

public:
    bool checkCollision(SDL_Rect a, SDL_Rect b);

    //getters and setters
    static CollisionHandler* get() { return s_collisionHandler = (s_collisionHandler != nullptr) ? s_collisionHandler : new CollisionHandler(); }
};

#endif