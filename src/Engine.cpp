#include "Engine.h"
#include "Dino.h"
#include "Input.h"
#include "Timer.h"
#include "Background.h"
#include "Tree.h"
#include "CollisionHandler.h"
#include "Sound.h"
#include "Message.h"

Engine* Engine::s_engine = nullptr;
Dino* dino = nullptr;
Background *sky, *mountains, *plateau, *ground, *plant;
Tree *tree;
Message tminfo, tmplay, tmhome;

Engine::Engine()
{
	m_window = nullptr;
    m_renderer = nullptr;
    m_screenWidth = 1280;
    m_screenHeight = 720;
    m_running = true;
	m_playing = false;
	m_dead = false;
	m_bg_speed = 3;
}

void Engine::load()
{
	//Loading font...
	Graphics::get()->loadFont("Assets/font.otf", 100);

	//Making textTexture...
	Graphics::get()->makeTextTexture("t_info", "PRESS SPACE TO JUMP", {171, 235, 52});
	tminfo.setConfig("t_info");

	Graphics::get()->makeTextTexture("t_play", "PRESS S TO PLAY", {171, 235, 52});
	tmplay.setConfig("t_play");

	Graphics::get()->makeTextTexture("t_home", "PRESS R TO RELOAD", {171, 235, 52});
	tmhome.setConfig("t_home");

	//Loading images...
	Graphics::get()->load("sky", "Assets/BG_Png/sky.png");
	Graphics::get()->load("mountains", "Assets/BG_Png/mountains.png");
	Graphics::get()->load("plateau", "Assets/BG_Png/plateau.png");
	Graphics::get()->load("ground", "Assets/BG_Png/ground.png");
	Graphics::get()->load("plant", "Assets/BG_Png/plant.png");

	Graphics::get()->load("dino", "Assets/Dino_SpriteSheet.png");
	dino = new Dino(new Properties("dino", 140, 420, 510, 354));

	sky = new Background("sky", 0, 0, 1920, 1080, m_bg_speed);
	mountains = new Background("mountains", 0, 200, 1920, 782, 2 * m_bg_speed);
	plateau = new Background("plateau", 0, 50, 1920, 751, 3 * m_bg_speed);
	ground = new Background("ground", 0, 550, 1920, 198, 4 * m_bg_speed);
	plant = new Background("plant", 0, 560, 1920, 216, 5 * m_bg_speed);

	Graphics::get()->load("tree", "Assets/Cactus.png");
	tree = new Tree(new Properties("tree", 900, 450, 734, 983), 0.28);
	tree->setTreeVelocity(4 * m_bg_speed);

	//Loading Sound...
	Sound::get()->loadMusic("play", "Assets/BG_Music/play.mp3");
	Sound::get()->loadMusic("bg", "Assets/BG_Music/start.mp3");
	Sound::get()->loadMusicFX("jump0", "Assets/Music_Fx/jump0.wav");
	Sound::get()->loadMusicFX("dead", "Assets/Music_Fx/jump1.wav");
	Sound::get()->loadMusicFX("runLoop", "Assets/Music_Fx/running_loop.wav");

	Sound::get()->playMusic("bg");
}

void Engine::handleEvents()
{
	if((!m_playing && Input::get()->getKeyDown(SDL_SCANCODE_S))
		|| (m_dead && Input::get()->getKeyDown(SDL_SCANCODE_R)))
	{
		m_dead = false;
		m_bg_speed = 3;
		sky->set(0, 0, 1920, 1080, m_bg_speed);
		mountains->set(0, 200, 1920, 782, 2 * m_bg_speed);
		plateau->set(0, 50, 1920, 751, 3 * m_bg_speed);
		ground->set(0, 550, 1920, 198, 4 * m_bg_speed);
		plant->set(0, 560, 1920, 216, 5 * m_bg_speed);
		tree->reset(900);
		tree->setTreeVelocity(4 * m_bg_speed);
		m_playStartTime = 0;

		if (Input::get()->getKeyDown(SDL_SCANCODE_S)) {
			m_playing = true;
			Sound::get()->stopMusic();
			Sound::get()->playMusic("play");
		} else if (Input::get()->getKeyDown(SDL_SCANCODE_R)){
			m_playing = false;
			Sound::get()->stopMusic();
			Sound::get()->playMusic("bg");
		}	
	}
    Input::get()->listen();
}

void Engine::update()
{
	float dt = Timer::get()->getDeltaTime();

	dino->update(dt);

	if (m_playing) {
		m_playStartTime++;

		sky->update();
		mountains->update();
		plateau->update();
		ground->update();
		plant->update();

		tree->update(dt);

		if(
			CollisionHandler::get()->checkCollision(dino->getCollider(), tree->m_collider) ||
			CollisionHandler::get()->checkCollision(dino->getCollider(), tree->m_collider1) ||
			CollisionHandler::get()->checkCollision(dino->getCollider(), tree->m_collider2) 
		)
		{
			SDL_Log("Collided->%f\n", dt);
			m_playing = false;
			m_dead = true;
			dino->setAnimation(DEAD);

		    Sound::get()->playMusicFX("dead");
			Sound::get()->stopMusic();
			Sound::get()->playMusic("bg");
		}

		if ((m_playStartTime % 1200) == 0) {
			m_bg_speed++;
			sky->setScrollSpeed(1 * m_bg_speed);
			mountains->setScrollSpeed(2 * m_bg_speed);
			plateau->setScrollSpeed(3 * m_bg_speed);
			ground->setScrollSpeed(4 * m_bg_speed);
			tree->setTreeVelocity(4 * m_bg_speed);
			plant->setScrollSpeed(5 * m_bg_speed);
			dino->m_running = RUNNING;
		} 
	}
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

	tree->render();
	dino->render();
	tree->partialRender(0, 0, 490, 0);

	plant->render();

	if (!m_playing) {
		tminfo.render(700, 30, true);
		tmplay.render(700, 170, true);
		if (m_dead) tmhome.render(700, 310, true);
	}

    //Update screen
	SDL_RenderPresent( m_renderer );
}

void Engine::close()
{
    //Destroy window
	SDL_DestroyRenderer( m_renderer );
	SDL_DestroyWindow( m_window );
	m_window = nullptr;
	m_renderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
    TTF_Quit();
	Mix_Quit();
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
		m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, SDL_WINDOW_SHOWN );
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
