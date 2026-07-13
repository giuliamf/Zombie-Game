#include "Character.h"
#include "GameObject.h"
#include "Gun.h"
#include "SpriteRenderer.h"
#include "Game.h"
#include "State.h"

Character::Character(GameObject& associated)
    : Component(associated),
      speed(0, 0),
      linearSpeed(800), // trocar para 300, pois 800 é para testar o mapa
      hp(100)
{
}

void Character::Start() {

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

    associated.box.pos.x += speed.x * dt;
    associated.box.pos.y += speed.y * dt;
}

void Character::Render() {
}

void Character::SetSpeed(Vec2 dir) {
    speed.x = dir.x * linearSpeed;
    speed.y = dir.y * linearSpeed;
}