#include "Graphics.h"
#include "Engine.h"

Graphics* Graphics::s_graphics = nullptr;

bool Graphics::load(std::string id, std::string path, bool setColorKey, int r, int g, int b)
{
    //The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == nullptr )
	{
		SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
        if(setColorKey)
        {
            if(r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
            {
                if(SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, r, g, b )) != 0)
                {
                    SDL_Log("Unable to set color key %s\n", SDL_GetError());
                }
            }
            else
            {
                SDL_Log("Color values are not in range.\n");
            }
        }

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( Engine::get()->getRenderer(), loadedSurface );
		if( newTexture == nullptr )
		{
			SDL_Log( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	m_textureMap[id] = newTexture;
	return newTexture != nullptr;
}

void Graphics::render( std::string id, int x, int y, int width, int height, float scale, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect desRect = {x, y, width, height};
    desRect.w *= scale;
    desRect.h *= scale;
    SDL_RenderCopyEx( Engine::get()->getRenderer(), m_textureMap[id], &srcRect, &desRect, angle, center, flip );
}

void Graphics::renderSprites( std::string id, int x, int y, int width, int height, int row, int frame, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect srcRect = {width*frame, height*row, width, height};
    float scale = 0.6f;
    int sWidth = scale * width;
    int sHeight = scale * height;
    SDL_Rect desRect = {x, y, sWidth, sHeight};
	SDL_RenderCopyEx( Engine::get()->getRenderer(), m_textureMap[id], &srcRect, &desRect, angle, center, flip );
}

void Graphics::renderBackground( std::string id, int x, int y, int width, int height, bool fullScreen, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect desRect = {x, y, Engine::get()->getScreenWidth(), height};
    if(fullScreen) desRect.h = Engine::get()->getScreenHeight();
    SDL_RenderCopyEx( Engine::get()->getRenderer(), m_textureMap[id], &srcRect, &desRect, angle, center, flip );
}

