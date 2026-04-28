#pragma once

#include <string>
#include "SDL_include.h"

class Sprite {
public:
    Sprite();
    Sprite(const std::string& file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    void Open(const std::string& file);
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);

    void Render(int x, int y);

    int GetWidth();
    int GetHeight();
    bool IsOpen();

private:
    SDL_Texture* texture;
    int width;
    int height;

    int frameCountW;
    int frameCountH;
    int currentFrame;

    SDL_Rect clipRect;

    void UpdateClip();
};