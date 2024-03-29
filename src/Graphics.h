#ifndef __Graphics__
#define __Graphics__

#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <string>

class Graphics
{
    Graphics(){}
    static Graphics* s_graphics;
    TTF_Font* m_font;
    std::unordered_map<std::string, SDL_Texture*> m_textureMap;

public:
    bool load(std::string id, std::string path, bool setColorKey = false, int r = 0, int g = 0, int b = 0);

    bool loadFont(std::string path, int size);
    bool makeTextTexture(std::string id, std::string text, SDL_Color textColor);

    //Renders texture at given point
    void render( std::string id, int x, int y );
    void render( std::string id, int x, int y, int width, int height, float scale = 1, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderSprites(std::string id, int x, int y, int width, int height, int row, int frame, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    void renderBackground( std::string id, int x, int y, int width, int height, bool fullScreen = false, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Getters and Setters
    static Graphics* get(){ return s_graphics = (s_graphics != nullptr) ? s_graphics : new Graphics(); }
    SDL_Texture* getTexture(std::string id) { return m_textureMap[id]; }

};

#endif