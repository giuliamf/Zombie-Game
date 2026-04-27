#include "Sprite.h"
#include "Game.h"
#include <iostream>

// cria um sprite sem imagem nenhuma -> inicializa texture p evitar crash
Sprite::Sprite()
    : texture(nullptr), width(0), height(0)
{
}

// construtor com arquivo
Sprite::Sprite(const std::string& file)
    : texture(nullptr), width(0), height(0)
{
    Open(file);
}

// destrutor
Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(const std::string& file) {
    // carrega a imagem acima de outra
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    // garante acesso global controlado
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();

    texture = IMG_LoadTexture(renderer, file.c_str());

    if (texture == nullptr) {
        std::cerr << "Erro ao carregar textura: "
                  << file << " - "
                  << SDL_GetError() << std::endl;
        return;
    }

    // descobre o tamanho da imagem
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    if (texture == nullptr)
        return;

    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    // pega a textura, o recorte e desenha na janela
    SDL_RenderCopy(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dstRect
    );
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}