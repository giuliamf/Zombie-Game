#include "SpriteRenderer.h"
#include "GameObject.h"

#include <iostream>

SpriteRenderer::SpriteRenderer(GameObject& associated, const std::string& file, int frameCountW, int frameCountH)
    : Component(associated),
      sprite(file, frameCountW, frameCountH)
{
}

void SpriteRenderer::Render() {
    sprite.Render(
        associated.box.pos.x,
        associated.box.pos.y
    );
}