#include "Bullet.h"
#include "Collider.h"
#include "Collision.h"
#include "Game.h"
#include "GameObject.h"
#include "State.h"
#include "Zombie.h"

#include <cmath>

Bullet::Bullet(GameObject& associated, float angle, float speed, float maxDistance)
    : Component(associated)
{
    // converte ângulo para vetor
    float rad = angle * M_PI / 180.0f;

    speedVec.x = cos(rad) * speed;
    speedVec.y = sin(rad) * speed;

    distanceLeft = maxDistance;
}

void Bullet::Start() {
    associated.AddComponent(new Collider(associated));
}

void Bullet::Update(float dt) {

    // mover a bala
    associated.box.pos.x += speedVec.x * dt;
    associated.box.pos.y += speedVec.y * dt;

    // diminuir distância restante
    float distance = (abs(speedVec.x) + abs(speedVec.y)) * dt;
    distanceLeft -= distance;

    // se acabou → remover do jogo
    if (distanceLeft <= 0) {
        associated.RequestDelete();
        return;
    }

    auto& objects = Game::GetInstance().GetState().GetObjectArray();

    for (auto& obj : objects) {

        // ignora si mesma
        if (obj.get() == &associated) continue;

        for (auto comp : obj->GetComponents()) {

            Zombie* zombie = dynamic_cast<Zombie*>(comp);

            if (zombie != nullptr) {

                if (Collision::IsColliding(associated.box, obj->box)) {

                    zombie->NotifyHit();
                    associated.RequestDelete(); // mata bala

                    return;
                }
            }
        }
    }
}

void Bullet::Render() {
}