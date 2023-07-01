#include "Sound.h"
#include "SDL.h"

Sound* Sound::s_sound = nullptr;

bool Sound::loadMusic(std::string id, std::string path)
{
    Mix_Music *music = nullptr;
    music = Mix_LoadMUS( path.c_str() );
    if( music == nullptr )
	{
		SDL_Log( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
    m_musicMap[id] = music;
    return true;
}

bool Sound::loadMusicFX(std::string id, std::string path)
{
    Mix_Chunk *musicFX = nullptr;
    musicFX = Mix_LoadWAV( path.c_str() );
	if( musicFX == NULL )
	{
		SDL_Log( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
    m_musicFXMap[id] = musicFX;
    return true;
}

void Sound::playMusic(std::string id)
{
    //If there is no music playing
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( m_musicMap[id], -1 );
    }
}

void Sound::pauseMusic()
{
    //If the music is playing
    if( Mix_PlayingMusic() )
    {
        //Pause the music
        Mix_PauseMusic();
    }
}

void Sound::resumeMusic()
{
    //If the music is paused
    if( Mix_PausedMusic() )
    {
        //Resume the music
        Mix_ResumeMusic();
    }
}

void Sound::stopMusic()
{
    //If the music is playing or If the music is paused
    if(Mix_PlayingMusic() == 1 || Mix_PausedMusic() == 1)
    {
        //Stop the music
        Mix_HaltMusic();
    }

}

void Sound::playMusicFX(std::string id)
{
    Mix_PlayChannel( -1, m_musicFXMap[id], 0 );
}
