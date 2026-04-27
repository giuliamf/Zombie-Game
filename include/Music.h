#pragma once

#include <string>
#include "SDL_include.h"

class Music {
public:
    Music();
    Music(const std::string& file);
    ~Music();

    void Open(const std::string& file);
    void Play(int times = -1);
    void Stop();
    bool IsOpen();

private:
    Mix_Music* music;
};