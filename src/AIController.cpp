#include "AIController.h"
#include "GameObject.h"
#include "Game.h"
#include "State.h"
#include "Character.h"
#include "Zombie.h"

#include <iostream>

AIController::AIController(GameObject& associated, float linearSpeed)
    : Component(associated),
      target(nullptr),
      linearSpeed(linearSpeed)
{
}

void AIController::Start() {
    // Inicialização - target será encontrado no primeiro Update
    target = nullptr;
}

void AIController::Update(float dt) {
    // Verificar se o zombie está morto
    Zombie* zombie = dynamic_cast<Zombie*>(associated.GetComponent("Zombie"));
    if (zombie != nullptr && zombie->IsDead()) {
        // Zombie morto não se move
        return;
    }

    // Se não temos um target, procurar o player
    if (target == nullptr) {
        FindTarget();
    }

    // Se encontramos o target, mover em direção a ele
    if (target != nullptr) {
        // Verificar se o target ainda está vivo
        if (target->IsDead()) {
            target = nullptr;
            return;
        }

        MoveTowardsTarget(dt);
    }
}

bool AIController::Is(std::string type) const {
    return type == "AIController";
}

void AIController::SetLinearSpeed(float speed) {
    linearSpeed = speed;
}

void AIController::FindTarget() {
    // Acessar o State para buscar todos os objetos
    State& state = Game::GetInstance().GetState();
    std::vector<std::shared_ptr<GameObject>>& objects = state.GetObjectArray();

    // Procurar por um GameObject que tenha o componente Character
    for (auto& obj : objects) {
        if (obj->GetComponent("Character") != nullptr) {
            // Encontramos o player!
            target = obj.get();
            std::cout << "AIController: Target (Player) encontrado!" << std::endl;
            return;
        }
    }

    // Se chegou aqui, não encontrou o player
    target = nullptr;
}

void AIController::MoveTowardsTarget(float dt) {
    if (target == nullptr) return;

    // Calcular direção do inimigo até o player
    Vec2 direction = target->box.pos - associated.box.pos;

    // Normalizar o vetor de direção
    direction = direction.GetNormalized();

    // Aplicar movimento
    associated.box.pos += direction * linearSpeed * dt;
}

// Made with Bob
