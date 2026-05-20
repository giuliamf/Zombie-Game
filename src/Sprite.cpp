#include "Sprite.h"
#include "Game.h"
#include "Camera.h"

#include <iostream>

Sprite::Sprite()
    : texture(nullptr),
      width(0),
      height(0),
      frameCountW(1),
      frameCountH(1),
      currentFrame(0)
{
}

Sprite::Sprite(const std::string& file, int frameCountW, int frameCountH)
    : Sprite()
{
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    Open(file);
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(const std::string& file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    texture = IMG_LoadTexture(renderer, file.c_str());

    if (texture == nullptr) {
        std::cerr << "Erro ao carregar textura: "
                  << file << " - "
                  << SDL_GetError() << std::endl;
        return;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    UpdateClip();
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    currentFrame = 0;
    UpdateClip();
}

void Sprite::SetFrame(int frame) {
    currentFrame = frame;
    UpdateClip();
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::UpdateClip() {
    int frameWidth = width / frameCountW;
    int frameHeight = height / frameCountH;

    clipRect.w = frameWidth;
    clipRect.h = frameHeight;

    clipRect.x = (currentFrame % frameCountW) * frameWidth;
    clipRect.y = (currentFrame / frameCountW) * frameHeight;
}

void Sprite::Render(int x, int y) {
    if (texture == nullptr)
        return;

    SDL_Rect dstRect;
    
    dstRect.x = x - Camera::pos.x; 
    dstRect.y = y - Camera::pos.y;

    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    SDL_RenderCopy(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dstRect
    );
}

/*** apagar:
void Sprite::Render(int x, int y) {

    SDL_Rect dstRect;

    dstRect.x = 200;
    dstRect.y = 200;

    dstRect.w = 64;
    dstRect.h = 64;

    SDL_RenderCopy(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dstRect
    );
}
 até aqui. */

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}
