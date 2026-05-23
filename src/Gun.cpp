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

    // 1. pegar referência do player
    if (character.expired()) {
        return;
    }

    auto characterPtr = character.lock();

    if (!characterPtr) {
        return;
    }

    // 2. pegar posição do mouse (tela)
    int mouseX = InputManager::GetInstance().GetMouseX();
    int mouseY = InputManager::GetInstance().GetMouseY();

    // 3. converter para mundo
    mouseX += Camera::pos.x;
    mouseY += Camera::pos.y;

    // 4. calcular centro do player
    float centerX = characterPtr->box.pos.x + characterPtr->box.size.x / 2;
    float centerY = characterPtr->box.pos.y + characterPtr->box.size.y * 0.8f;

    // 5. calcular direção (ângulo)
    float dx = mouseX - centerX;
    float dy = mouseY - centerY;

    angle = atan2(dy, dx) * (180.0 / M_PI);

    // 6. definir distância da arma até o player
    float offset = 40.0f;

    // 7. calcular posição da arma no mundo (orbita correta)
    float gunX = centerX + cos(angle * M_PI / 180.0f) * offset;
    float gunY = centerY + sin(angle * M_PI / 180.0f) * offset;

    // 8. ajustar para o canto superior esquerdo do sprite
    associated.box.pos.x = gunX - associated.box.size.x / 2;
    associated.box.pos.y = gunY - associated.box.size.y / 2;

    // 9. salvar ângulo para renderização
    associated.angleDeg = angle;
}

void Gun::Render() {
}