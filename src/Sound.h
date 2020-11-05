#ifndef __Sound__
#define __Sound__

#include<SDL_mixer.h>
#include <unordered_map>
#include <string>

class Sound
{
    Sound(){};
    static Sound* s_sound;
    std::unordered_map<std::string, Mix_Music*> m_musicMap;
    std::unordered_map<std::string, Mix_Chunk*> m_musicFXMap;

public:
    bool loadMusic(std::string id, std::string path);
    bool loadMusicFX(std::string id, std::string path);

    void playMusic(std::string id);
    void pauseMusic();
    void resumeMusic();
    void stopMusic();

    void playMusicFX(std::string id);

    void destroyMusic(std::string id);
    void destroyMusicFX(std::string id);
    void free();

    //getters and setters
    static Sound* get() { return s_sound = (s_sound != nullptr) ? s_sound : new Sound(); }

};

#endif