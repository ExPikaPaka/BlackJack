#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>

// AudioManager class. 
// Can play 1 background music (.mp3 .ogg .flac .wav), and a vector of sounds (.wav).
// Mixes all sounds currently playing
class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    // Load .wav sound with 'id' (map keyID)
    void loadSound(const char* soundId, const char* filePath);

    // Plays early loaded .wav sound.
    void playSound(const char* soundId, int loops = 0, int channel = -1);

    // Set .wav sound volume
    void setSoundVolume(const char* soundId, float volume);

    // Set volume to all .wav sounds
    void setAllSoundsVolume(float volume);


    // Loads & Plays background music
    void playMusic(const char* filePath, int loops = -1);

    // Set background music volume
    void setMusicVolume(float volume);

    // Stop playing background music
    void stopMusic();

private:
    // Map of .wav sounds & keyID
    std::unordered_map<const char*, Mix_Chunk*> sounds;

    // .mp3 music
    Mix_Music* music = nullptr;

    // Removes .wav sound from map & frees chunk
    void freeSound(const char* soundId);
};

