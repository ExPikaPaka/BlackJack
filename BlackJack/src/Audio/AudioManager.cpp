#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager() {
    // Initialize SDL_mixer
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

AudioManager::~AudioManager() {
    // Free loaded sounds
    for (const std::pair<const char*, Mix_Chunk*>& sound : sounds) {
        freeSound(sound.first);
    }

    // Free music
    stopMusic();

    // Quit SDL_mixer
    Mix_Quit();
}

void AudioManager::loadSound(const char* soundId, const char* filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath);
    if (sound) {
        // If the sound with the given ID already exists, free the previous sound
        freeSound(soundId);

        sounds.emplace(soundId, sound);
    } else {
        // Write error
        std::cerr << "[ERROR] Failed to load sound. Err: " << Mix_GetError() << std::endl;
    }
}

void AudioManager::playSound(const char* soundId, int loops, int channel) {
    auto it = sounds.find(soundId);
    if (it != sounds.end()) {
        // Play the sound
        Mix_PlayChannel(channel, it->second, loops);
    }
}

void AudioManager::setSoundVolume(const char* soundId, float volume) {
    auto it = sounds.find(soundId);
    if (it != sounds.end()) {
        // Set the volume of the sound
        Mix_VolumeChunk(it->second, volume * MIX_MAX_VOLUME);
    }
}

void AudioManager::setAllSoundsVolume(float volume) {
    for (auto& sound : sounds) {
        // Set the volume of the sound
        Mix_VolumeChunk(sound.second, volume * MIX_MAX_VOLUME);
    }
}

void AudioManager::freeSound(const char* soundId) {
    auto it = sounds.find(soundId);
    if (it != sounds.end()) {
        Mix_FreeChunk(it->second);
        sounds.erase(it);
    }
}

void AudioManager::playMusic(const char* filePath, int loops) {
    stopMusic(); // Stop any previously playing music

    // Play music from file
    music = Mix_LoadMUS(filePath);
    if (music) {
        Mix_PlayMusic(music, loops);
    } else {
        // Write error
        std::cerr << "[ERROR] Failed to load music. Err: " << Mix_GetError() << std::endl;
    }
}

void AudioManager::setMusicVolume(float volume) {
    Mix_VolumeMusic(volume * MIX_MAX_VOLUME);
}

void AudioManager::stopMusic() {
    if (music) {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = nullptr;
    }
}