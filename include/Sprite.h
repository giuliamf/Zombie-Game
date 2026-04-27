#pragma once

#include <string>
#include "SDL_include.h"

class Sprite {
public:
    Sprite();
    Sprite(const std::string& file);
    ~Sprite();

    void Open(const std::string& file);
    void SetClip(int x, int y, int w, int h);

    void Render(int x, int y);

    int GetWidth();
    int GetHeight();
    bool IsOpen();

private:
    SDL_Texture* texture;   // img carregada na gpu
    int width;
    int height;
    SDL_Rect clipRect;  // "qual parte da imagem eu quero desenhar"
};