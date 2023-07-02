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

void AudioManager::setSoundVolume(const char* soundId, int volume) {
    auto it = sounds.find(soundId);
    if (it != sounds.end()) {
        // Set the volume of the sound
        Mix_VolumeChunk(it->second, volume);
    }
}

void AudioManager::setSoundPan(const char* soundId, int pan) {
    auto it = sounds.find(soundId);
    if (it != sounds.end()) {
        // Set the pan (left-right balance) of the sound
        Mix_SetPanning(-1, 255 - pan, pan);
    }
}

void AudioManager::setSoundPosition(const char* soundId, Uint8 angle, int distance) {
    auto it = sounds.find(soundId);
    if (it != sounds.end()) {
        // Set the position of the sound in a 2D sound space
        Mix_SetPosition(-1, angle, distance);
    }
}

void AudioManager::freeSound(const const char* soundId) {
    auto it = sounds.find(soundId);
    if (it != sounds.end()) {
        Mix_FreeChunk(it->second);
        sounds.erase(it);
    }
}

void AudioManager::playMusic(const char* filePath, int loops) {
    stopMusic(); // Stop any previously playing music

    music = Mix_LoadMUS(filePath);
    if (music) {
        Mix_PlayMusic(music, loops);
    } else {
        std::cerr << "[ERROR] Failed to load music. Err: " << Mix_GetError() << std::endl;
    }
}

void AudioManager::setMusicVolume(int volume) {
    Mix_VolumeMusic(volume);
}

void AudioManager::stopMusic() {
    if (music) {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = nullptr;
    }
}