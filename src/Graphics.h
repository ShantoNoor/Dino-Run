#ifndef __Graphics__
#define __Graphics__

#include <SDL.h>
#include <unordered_map>
#include <string>

class Graphics
{
    Graphics(){}
    static Graphics* s_graphics;
    std::unordered_map<std::string, SDL_Texture*> m_textureMap;

public:
    bool load(std::string id, std::string path, bool setColorKey = false, int r = 0, int g = 0, int b = 0);
    //Renders texture at given point
	void render(std::string id, int x, int y, bool fullScreen = false, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    void destroy(std::string id);
    void free();

    //Getters and Setters
    static Graphics* get(){ return s_graphics = (s_graphics != nullptr) ? s_graphics : new Graphics(); }

};

#endif