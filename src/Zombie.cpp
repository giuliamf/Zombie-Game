#include "Zombie.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

#include <iostream>

Zombie::Zombie(GameObject& associated)
    : Component(associated),
      lifeTime(0.0f),
      sprite(nullptr)
{
    isDead = false;

    for (auto component : associated.GetComponents()) {
        sprite = dynamic_cast<SpriteRenderer*>(component);
        if (sprite != nullptr) {
            break;
        }
    }

}


void Zombie::Update(float dt) {
    deathTimer.Update(dt);

    if (!isDead && deathTimer.Get() > 3.0f) {
        isDead = true;

        std::cout << "Zombie morreu!" << std::endl;
    }
}
