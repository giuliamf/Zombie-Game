#include "Character.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PlayerController.h"

PlayerController::PlayerController(GameObject& associated)
    : Component(associated)
{
}

void PlayerController::Start() {
}

void PlayerController::Update(float dt) {

    Character* character = nullptr;

    // encontrar o Character do GameObject
    for (auto comp : associated.GetComponents()) {
        character = dynamic_cast<Character*>(comp);
        if (character != nullptr) {
            break;
        }
    }

    if (character == nullptr) return;

    Vec2 direction(0, 0);

    // teclado
    if (InputManager::GetInstance().IsKeyDown(SDLK_w)) {
        direction.y -= 1;
    }

    if (InputManager::GetInstance().IsKeyDown(SDLK_s)) {
        direction.y += 1;
    }

    if (InputManager::GetInstance().IsKeyDown(SDLK_a)) {
        direction.x -= 1;
    }

    if (InputManager::GetInstance().IsKeyDown(SDLK_d)) {
        direction.x += 1;
    }

    // normalizar direção
    if (direction.x != 0 || direction.y != 0) {
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction.x /= length;
        direction.y /= length;
    }

    character->SetSpeed(direction);
}

void PlayerController::Render() {
}