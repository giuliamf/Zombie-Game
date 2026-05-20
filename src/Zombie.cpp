#include "Zombie.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Animator.h"
#include "InputManager.h"

#include <iostream>

Zombie::Zombie(GameObject& associated)
    : Component(associated),
      lifeTime(0.0f),
      sprite(nullptr)
{
    isDead = false;


}


void Zombie::Update(float dt) {

    // se já morreu, nao faz mais nada
    if (isDead) {
        return;
    }

    // matar com tecla (espaço)
    if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
        isDead = true;

        std::cout << "Zombie morreu por tecla!" << std::endl;

        if (sprite == nullptr) return;

        for (auto comp : associated.GetComponents()) {

            // parar animator
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

        return; // impede qualquer lógica depois
    }


    deathTimer.Update(dt);

    if (deathTimer.Get() > 3.0f) {
        isDead = true;

        std::cout << "Zombie morreu!" << std::endl;
        if (sprite == nullptr) return;

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

void Zombie::Start() {
    for (auto component : associated.GetComponents()) {
        sprite = dynamic_cast<SpriteRenderer*>(component);
        if (sprite != nullptr) {
            break;
        }
    }
}