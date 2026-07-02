#include "Text.h"

#include "Camera.h"
#include "Game.h"
#include "GameObject.h"
#include "Resources.h"

#include <iostream>

Text::Text(GameObject& associated,
           const std::string& fontFile,
           int fontSize,
           TextStyle style,
           const std::string& text,
           SDL_Color color)
    : Component(associated),
      font(nullptr),
      texture(nullptr),
      text(text),
      style(style),
      fontFile(fontFile),
      fontSize(fontSize),
      color(color)
{
    RemakeTexture();
}

Text::~Text() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    // font é gerenciada pelo cache de Resources — não chamar TTF_CloseFont aqui
}

void Text::Update(float dt) {
    // Text é estático por padrão; subclasses ou chamadores externos
    // usam os setters para mudar o conteúdo
}

void Text::Render() {
    if (texture == nullptr) return;

    int w = 0;
    int h = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

    SDL_Rect dst;
    dst.x = static_cast<int>(associated.box.pos.x - Camera::pos.x);
    dst.y = static_cast<int>(associated.box.pos.y - Camera::pos.y);
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, nullptr, &dst);
}

int Text::GetWidth() const {
    return static_cast<int>(associated.box.size.x);
}

int Text::GetHeight() const {
    return static_cast<int>(associated.box.size.y);
}

bool Text::Is(std::string type) const {
    return type == "Text";
}

void Text::SetText(const std::string& text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(const std::string& fontFile) {
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {
    // descartar textura anterior
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    // obter (ou reutilizar do cache) a fonte
    font = Resources::GetFont(fontFile, fontSize);
    if (font == nullptr) return;

    // texto vazio não gera textura
    if (text.empty()) return;

    SDL_Surface* surface = nullptr;

    switch (style) {
        case SOLID:
            surface = TTF_RenderText_Solid(font, text.c_str(), color);
            break;
        case SHADED: {
            // cor de fundo preta por padrão para o modo Shaded
            SDL_Color bg = {0, 0, 0, 255};
            surface = TTF_RenderText_Shaded(font, text.c_str(), color, bg);
            break;
        }
        case BLENDED:
            surface = TTF_RenderText_Blended(font, text.c_str(), color);
            break;
    }

    if (surface == nullptr) {
        std::cerr << "Erro TTF_RenderText: " << TTF_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(
        Game::GetInstance().GetRenderer(),
        surface
    );
    SDL_FreeSurface(surface);

    if (texture == nullptr) {
        std::cerr << "Erro SDL_CreateTextureFromSurface: "
                  << SDL_GetError() << std::endl;
        return;
    }

    // atualizar dimensões do box com o tamanho real do texto renderizado
    int w = 0;
    int h = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    associated.box.size.x = static_cast<float>(w);
    associated.box.size.y = static_cast<float>(h);
}
