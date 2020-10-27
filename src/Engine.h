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
    int bg_x;
    int bg_x2;
    int bg_v;
    LTexture bg;

    LTexture sp;
    int spHeight = 301;
    int spWidth = 3460/8;
    SDL_Rect spClip[8];
    int spMover = 0;

    SDL_Rect testRec;
};

#endif 