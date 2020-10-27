#ifndef __LTexture__
#define __LTexture__

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( SDL_Renderer* renderer, std::string path );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

		void setWidth(int width);
		void setHeight(int height);

	private:
		//The actual hardware texture
		SDL_Texture* m_texture;

		//Image dimensions
		int m_width;
		int m_height;
};

#endif