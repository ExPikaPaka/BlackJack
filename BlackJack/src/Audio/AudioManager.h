#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    void loadSound(const char* soundId, const char* filePath);
    void playSound(const char* soundId, int loops = 0, int channel = -1);
    void setSoundVolume(const char* soundId, float volume);
    void setAllSoundsVolume(float volume);
    void setSoundPan(const char* soundId, int pan);
    void setSoundPosition(const char* soundId, Uint8 angle, int distance);

    void playMusic(const char* filePath, int loops = -1);
    void setMusicVolume(float volume);
    void stopMusic();

private:
    std::unordered_map<const char*, Mix_Chunk*> sounds;
    Mix_Music* music = nullptr;

    void freeSound(const char* soundId);
};

