#ifndef __Engine__
#define __Engine__

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
// #incldue <sstring>

#include "LTexture.h"
#include "SpriteSheet.h"

class Engine
{
public:
    Engine();
    ~Engine();
    bool init(const char* title);
    void load();
    void render();
    void update();
    void handleEvents();
    void close();
    bool running();

    //Getters and Setters
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();
    int getScreenWidth();
    int getScreenHeight();
    void setScreenWidth(int width);
    void setScreenHeight(int height);


private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    bool m_running;
    int m_screenWidth, m_screenHeight;

public: // for game 
    int bgXscrolling;
    int bgXscrolling2;
    int bgXscrollingVelocity;
    LTexture bg;
    SpriteSheet sp;
};

#endif 