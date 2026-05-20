#include "Gun.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Camera.h"
#include "SpriteRenderer.h"
#include <cmath>

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character)
    : Component(associated),
      character(character),
      angle(0.0f)
{
}

void Gun::Start() {
    for (auto comp : associated.GetComponents()) {
            SpriteRenderer* sr = dynamic_cast<SpriteRenderer*>(comp);
            if (sr != nullptr) {
                sr->sprite.SetFrame(0); // frame inicial
                break;
            }
        }
}

void Gun::Update(float dt) {

    // pega o Character
    
    if (character.expired()) {
        return;
    }

    auto characterPtr = character.lock();

    if (!characterPtr) {
        return;
    }

    // posiciona a arma no centro do player
    //associated.box.pos.x = characterPtr->box.pos.x;
    //associated.box.pos.y = characterPtr->box.pos.y;
    associated.box.pos.x = associated.box.pos.x;
    associated.box.pos.y = associated.box.pos.y;


    // pegar posição do mouse
    int mouseX = InputManager::GetInstance().GetMouseX();
    int mouseY = InputManager::GetInstance().GetMouseY();

    // ajustar para coordenada do mundo
    mouseX += Camera::pos.x;
    mouseY += Camera::pos.y;

    // calcular direção
    float dx = mouseX - associated.box.pos.x;
    float dy = mouseY - associated.box.pos.y;

    angle = atan2(dy, dx) * (180.0 / M_PI);

    // salvar no GameObject
    //associated.angleDeg = angle;
}

void Gun::Render() {
}