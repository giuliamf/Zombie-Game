#include "Character.h"
#include "GameObject.h"

Character::Character(GameObject& associated)
    : Component(associated),
      speed(0, 0),
      linearSpeed(800), // trocar para 300, pois 800 é para testar o mapa
      hp(100)
{
}

void Character::Start() {
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