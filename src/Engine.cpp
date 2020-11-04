#include "Engine.h"
#include "Dino.h"
#include "Input.h"
#include "Timer.h"
#include "Background.h"
#include "Tree.h"

Engine* Engine::s_engine = nullptr;
Dino* dino = nullptr;
Background *sky, *mountains, *plateau, *ground, *plant;
Tree *tree;

Engine::Engine()
{
	m_window = nullptr;
    m_renderer = nullptr;
    m_screenWidth = 1280;
    m_screenHeight = 720;
    m_running = true;
}

void Engine::load()
{
	Graphics::get()->load("sky", "Assets/BG_Png/sky.png");
	Graphics::get()->load("mountains", "Assets/BG_Png/mountains.png");
	Graphics::get()->load("plateau", "Assets/BG_Png/plateau.png");
	Graphics::get()->load("ground", "Assets/BG_Png/ground.png");
	Graphics::get()->load("plant", "Assets/BG_Png/plant.png");

	Graphics::get()->load("dino", "Assets/Dino_SpriteSheet.png");
	dino = new Dino(new Properties("dino", 140, 420, 510, 354));

	sky = new Background("sky", 0, 0, 1920, 1080, 1);
	mountains = new Background("mountains", 0, 200, 1920, 782, 2);
	plateau = new Background("plateau", 0, 50, 1920, 751, 3);
	ground = new Background("ground", 0, 550, 1920, 198, 4);
	plant = new Background("plant", 0, 560, 1920, 216, 5);

	Graphics::get()->load("tree", "Assets/Cactus.png");
	tree = new Tree(new Properties("tree", 1000, 460, 734, 983));
}

void Engine::handleEvents()
{
    Input::get()->listen();
}

void Engine::update()
{
	float dt = Timer::get()->getDeltaTime();
	sky->update();
	mountains->update();
	plateau->update();
	ground->update();
	plant->update();

	dino->update(dt);
	tree->update(dt);
}

void Engine::render()
{
    //Clearing the renderer
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
	SDL_RenderClear( m_renderer );

	//Code Here..
	sky->render(true);
	mountains->render();
	plateau->render();
	ground->render();

	dino->render();
	tree->render();

	plant->render();



    //Update screen
	SDL_RenderPresent( m_renderer );
}

void Engine::close()
{
	Graphics::get()->free();

    //Destroy window
	SDL_DestroyRenderer( m_renderer );
	SDL_DestroyWindow( m_window );
	m_window = nullptr;
	m_renderer = nullptr;

	//Quit SDL subsystems
	Mix_Quit();
    TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Engine::init(const char* title, int width, int height)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			SDL_Log( "Warning: Linear texture filtering not enabled!" );
		}

		//setting window size
		if(width != -1) m_screenWidth = width;
		if(height != -1) m_screenHeight = height;

		//Create window
		m_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, SDL_WINDOW_SHOWN );
		if( m_window == NULL )
		{
			SDL_Log( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( m_renderer == NULL )
			{
				SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					SDL_Log( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

                //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					SDL_Log( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

                //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					SDL_Log( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return m_running = success;
}
