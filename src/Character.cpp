#include "Character.h"
#include "Animator.h"
#include "Collider.h"
#include "Game.h"
#include "GameObject.h"
#include "Gun.h"
#include "SpriteRenderer.h"
#include "State.h"

#include <iostream>


Character::Character(GameObject& associated)
    : Component(associated),
      speed(0, 0),
      linearSpeed(800), // trocar para 300, pois 800 é para testar o mapa
      hp(2),
      damageCooldown(1.0),
      isDead(false)
{
}

void Character::Start() {

    associated.AddComponent(new Collider(associated));

    GameObject* gunObject = new GameObject();

    gunObject->box.size.x = 32; // ajustar direito dps
    gunObject->box.size.y = 32;

    // posição inicial (vai ser ajustada no Update da Gun)
    gunObject->box.pos.x = associated.box.pos.x;
    gunObject->box.pos.y = associated.box.pos.y;

    // sprite da arma
    gunObject->AddComponent(
        new SpriteRenderer(
            *gunObject,
            "Resources/img/Gun.png",
            3, 2
        )
    );

    /** pegar referência segura do player
    std::weak_ptr<GameObject> characterPtr =
        Game::GetInstance().GetState().GetObjectPtr(&associated); */

    
    // criar componente Gun
    std::weak_ptr<GameObject> characterPtr =
        Game::GetInstance().GetState().GetObjectPtr(&associated);

    Gun* gunComp = new Gun(*gunObject, characterPtr);

    gunObject->AddComponent(gunComp);

    // adicionar ao State e guardar referência
    gun = Game::GetInstance().GetState().AddObject(gunObject);
}


void Character::Update(float dt) {
    // Se já está morto, não faz mais nada
    if (isDead) return;

    damageTimer.Update(dt);

    // Movimentação só acontece se estiver vivo
    associated.box.pos.x += speed.x * dt;
    associated.box.pos.y += speed.y * dt;

    // Verificar se morreu
    if (hp <= 0) {
        isDead = true;
        
        std::cout << "Player morreu!" << std::endl;
        
        // Parar animação e mostrar frame de morte
        for (auto comp : associated.GetComponents()) {
            // Parar Animator
            Animator* anim = dynamic_cast<Animator*>(comp);
            if (anim != nullptr) {
                anim->Stop();
            }
            
            // Mudar para frame de morte (frame 12)
            SpriteRenderer* sr = dynamic_cast<SpriteRenderer*>(comp);
            if (sr != nullptr) {
                sr->sprite.SetFrame(12);
            }
        }
        
        // Deletar a arma
        if (!gun.expired()) {
            auto gunPtr = gun.lock();
            if (gunPtr) {
                gunPtr->RequestDelete();
            }
        }
    }
}

void Character::Render() {
}

void Character::SetSpeed(Vec2 dir) {
    speed.x = dir.x * linearSpeed;
    speed.y = dir.y * linearSpeed;
}

void Character::NotifyCollision(GameObject& other) {
    // Se o player já está morto, não processar colisões
    if (isDead) return;
    
    // Verificar se o outro objeto está morto
    if (other.IsDead()) return;

    if (other.GetComponent("Zombie")) {

        if (damageTimer.Get() > damageCooldown) {

            hp--;
            damageTimer.Restart();

            std::cout << "Player tomou dano! HP: " << hp << std::endl;
        }
    }
}