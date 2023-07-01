#ifndef __Engine__
#define __Engine__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>

#include "Graphics.h"

class Engine
{
    Engine();
    static Engine* s_engine;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_running;
    int m_screenWidth, m_screenHeight, m_bg_speed;
    int m_playStartTime;

public:
    bool m_playing, m_dead;

    bool init(const char* title, int width=-1, int height=-1);
    void load();
    void handleEvents();
    void update();
    void render();
    void close();

    //Getters and Setters
    static Engine* get() { return s_engine = (s_engine != nullptr) ? s_engine : new Engine(); }
    bool isRunning() { return m_running; }
    SDL_Window* getWindow() { return m_window; }
    SDL_Renderer* getRenderer() { return m_renderer; }
    int getScreenWidth() { return m_screenWidth; }
    int getScreenHeight() { return m_screenHeight; }
    void setScreenWidth(int width) { m_screenWidth = width; }
    void setScreenHeight(int height) { m_screenHeight = height; }
    void quit(){ m_running = false; }

};

#endif