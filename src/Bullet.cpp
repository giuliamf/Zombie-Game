#include "Bullet.h"
#include "Collider.h"
#include "Collision.h"
#include "Game.h"
#include "GameObject.h"
#include "State.h"
#include "Zombie.h"

#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
    associated.AddComponent(new Collider(associated, Vec2{0.3, 0.3}));
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
}

void Bullet::Render() {
}

void Bullet::NotifyCollision(GameObject& other) {
    // Se a bala já foi marcada para deletar, não processar colisões
    if (associated.IsDead()) return;
    
    // Verificar se o outro objeto está morto
    if (other.IsDead()) return;

    if (other.GetComponent("Zombie")) {
        associated.RequestDelete();
    }
}

bool Bullet::Is(std::string type) const {
    return type == "Bullet";
}