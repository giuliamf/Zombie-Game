#include "Zombie.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

Zombie::Zombie(GameObject& associated)
    : Component(associated),
      lifeTime(0.0f),
      sprite(nullptr)
{
    for (auto component : associated.GetComponents()) {
        sprite = dynamic_cast<SpriteRenderer*>(component);
        if (sprite != nullptr) {
            break;
        }
    }
}

void Zombie::Update(float dt) {
    lifeTime += dt;

    if (sprite != nullptr && lifeTime > 2.0f) {
        sprite->sprite.SetFrame(1);
    }
}
