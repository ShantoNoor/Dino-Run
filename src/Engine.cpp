#include "Engine.h"

Engine::Engine()
{
    m_window = nullptr;
    m_renderer = nullptr;
    m_screenWidth = 1280;
    m_screenHeight = 720;
    m_running = true;
}

Engine::~Engine()
{
    close();
}

bool Engine::init(const char* title)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		m_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, SDL_WINDOW_SHOWN );
		if( m_window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( m_renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
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
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

                //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

                //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void Engine::handleEvents()
{
    SDL_Event ev;
    while(SDL_PollEvent(&ev))
    {
        //User requests quit
        if( ev.type == SDL_QUIT )
        {
            m_running = false;
        }
    }
}

void Engine::render()
{
    //Clearing the renderer
    SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( m_renderer );

    // //Render red filled quad
    // SDL_Rect fillRect = { m_screenWidth / 4, m_screenHeight / 4, m_screenWidth / 2, m_screenHeight / 2 };
    // SDL_SetRenderDrawColor( m_renderer, 0xFF, 0x00, 0x00, 0xFF );        
    // SDL_RenderFillRect( m_renderer, &fillRect );

	bg.render(m_renderer, bg_x, 0);
	bg.render(m_renderer, bg_x2, 0);

	sp.render(m_renderer, 140, 350, &spClip[spMover/ 5]);
	spMover++;
	if(spMover > 40) spMover = 0;

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(m_renderer, &testRec);

    //Update screen
	SDL_RenderPresent( m_renderer );
}

void Engine::update()
{
	bg_x -= bg_v;
	bg_x2 -= bg_v;
	if(bg_x <= -m_screenWidth) bg_x = m_screenWidth;
	if(bg_x2 <= -m_screenWidth) bg_x2 = m_screenWidth;
}

void Engine::load()
{
	//Loading Background
    bg.loadFromFile(m_renderer, "Assets/bg.png");
	bg.setWidth(1280);
	bg.setHeight(720);
	bg_v = 5;
	bg_x = 0;
	bg_x2 = m_screenWidth;

	//Loading sprite
	for(int i = 0; i < 8; i++)
	{
		spClip[i].x = spWidth * i;
		spClip[i].y = 0;
		spClip[i].h = spHeight;
		spClip[i].w = spWidth;
	}
	sp.loadFromFile(m_renderer, "Assets/Dino_run.png");

	testRec = {140, 350, spWidth, spHeight};

}

void Engine::close()
{
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

//getters and setters
bool Engine::running() { return m_running; }
SDL_Window* Engine::getWindow() { return m_window; }
SDL_Renderer* Engine::getRenderer() { return m_renderer; }
int Engine::getScreenWidth() { return m_screenWidth; }
int Engine::getScreenHeight() { return m_screenHeight; }
void Engine::setScreenWidth(int width) { m_screenWidth = width; }
void Engine::setScreenHeight(int height) { m_screenHeight = height; }