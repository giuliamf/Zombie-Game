#include "Character.h"
#include "GameObject.h"

Character::Character(GameObject& associated)
    : Component(associated),
      speed(0, 0),
      linearSpeed(200),
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