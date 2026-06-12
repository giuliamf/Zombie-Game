#include "Animator.h"
#include "Collider.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include "Zombie.h"


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
        deathTimer.Update(dt);
        if (deathTimer.Get() > 2.0f) {
            associated.RequestDelete();
        }
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
    associated.AddComponent(new Collider(associated));

    for (auto component : associated.GetComponents()) {
        sprite = dynamic_cast<SpriteRenderer*>(component);
        if (sprite != nullptr) {
            break;
        }
    }
}

void Zombie::NotifyHit() {
    if (isDead) return;  // Já está morto
    
    isDead = true;
    std::cout << "Zombie morreu por bala!" << std::endl;
    
    // Parar animação e mostrar frame de morte
    for (auto comp : associated.GetComponents()) {
        Animator* anim = dynamic_cast<Animator*>(comp);
        if (anim != nullptr) {
            anim->Stop();
        }
        
        SpriteRenderer* sr = dynamic_cast<SpriteRenderer*>(comp);
        if (sr != nullptr) {
            sr->sprite.SetFrame(5);  // frame de morte
        }
    }
    
    // remover dps de 2 segundos
    deathTimer.Restart();
}

void Zombie::NotifyCollision(GameObject& other) {

    if (other.GetComponent("Bullet")) {
        NotifyHit();
    }
}

bool Zombie::Is(std::string type) const {
    return type == "Zombie";
}