#pragma once

#include "Component.h"
#include "SDL_include.h"

#include <string>

enum TextStyle {
    SOLID,
    SHADED,
    BLENDED
};

class Text : public Component {
public:
    Text(GameObject& associated,
         const std::string& fontFile,
         int fontSize,
         TextStyle style,
         const std::string& text,
         SDL_Color color);

    ~Text() override;

    void Update(float dt) override;
    void Render() override;

    bool Is(std::string type) const override;

    void SetText(const std::string& text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(const std::string& fontFile);
    void SetFontSize(int fontSize);

    int GetWidth() const;
    int GetHeight() const;

private:
    void RemakeTexture();

    TTF_Font*   font;
    SDL_Texture* texture;

    std::string text;
    TextStyle   style;
    std::string fontFile;
    int         fontSize;
    SDL_Color   color;
};
