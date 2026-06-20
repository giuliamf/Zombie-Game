#include "Music.h"

#include <iostream>

// objeto music sem música
Music::Music()
    : music(nullptr)
{
}

// construtor com arquivo
Music::Music(const std::string& file)
    : music(nullptr)
{
    Open(file);
}

// destrutor                                                                                                             
Music::~Music() {
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }
}

void Music::Open(const std::string& file) {
    if (music != nullptr) {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    music = Mix_LoadMUS(file.c_str());

    if (music == nullptr) {
        std::cerr << "Erro ao carregar música: "
                  << file << " - "
                  << Mix_GetError() << std::endl;
    }
}

void Music::Play(int times) {
    if (music == nullptr)
        return;

    Mix_PlayMusic(music, times);
}

// para imediatamente qualquer música tocando
void Music::Stop() {
    Mix_HaltMusic();
}

bool Music::IsOpen() {
    return music != nullptr;
}