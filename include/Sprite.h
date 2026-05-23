#pragma once

#include <string>
#include "SDL_include.h"

class Sprite {
public:
    Sprite();
    Sprite(const std::string& file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;

    void Open(const std::string& file);
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);
    void SetClip(int x, int y, int w, int h);

    void Render(int x, int y, double angle = 0.0);

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