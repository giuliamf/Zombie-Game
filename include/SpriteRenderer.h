#pragma once

#include "Component.h"
#include "Sprite.h"

class SpriteRenderer : public Component {
public:
    SpriteRenderer(GameObject& associated, const std::string& file, int frameCountW = 1, int frameCountH = 1);

    void Render() override;

    Sprite sprite;
};