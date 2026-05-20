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
    float centerX = characterPtr->box.pos.x + characterPtr->box.size.x / 2;
    float centerY = characterPtr->box.pos.y + characterPtr->box.size.y / 2;
    
    associated.box.pos.x = centerX;
    associated.box.pos.y = centerY - associated.box.size.y * 0.5f;

    float offset = 40.0f; // distância da arma
    
    
    // posição diretamente na frente (sem centralizar depois)
    associated.box.pos.x = centerX + cos(angle * M_PI / 180.0f) * offset;
    associated.box.pos.y = centerY + sin(angle * M_PI / 180.0f) * offset;

    // ajustar para desenhar centralizado
    associated.box.pos.x -= associated.box.size.x / 2;
    associated.box.pos.y -= associated.box.size.y / 2;



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