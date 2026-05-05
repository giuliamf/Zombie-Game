#include "Zombie.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Animator.h"

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

    // se já morreu, nao faz mais nada
    if (isDead) {
        return;
    }

    deathTimer.Update(dt);

    if (deathTimer.Get() > 3.0f) {
        isDead = true;

        std::cout << "Zombie morreu!" << std::endl;


        for (auto comp : associated.GetComponents()) {

            // parar Animator corretamente
            Animator* anim = dynamic_cast<Animator*>(comp);
            if (anim != nullptr) {
                anim->Stop(); 
            }

            // mudar sprite
            SpriteRenderer* sr = dynamic_cast<SpriteRenderer*>(comp);
            if (sr != nullptr) {
                sr->sprite.SetFrame(5);
            }
        }
    }
}