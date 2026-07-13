#include "Bullet.h"
#include "Camera.h"
#include "Character.h"
#include "Game.h"
#include "GameObject.h"
#include "Gun.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include "State.h"

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character)
    : Component(associated),
      character(character),
      angle(0.0f),
      cooldownTime(0.1f)
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
    cooldownTimer.Update(dt);

    // 1. pegar referência do player
    if (character.expired()) {
        associated.RequestDelete();
        return;
    }

    auto characterPtr = character.lock();

    if (!characterPtr) {
        return;
    }
    
    // 2. Verificar se o player está morto
    Character* charComp = (Character*)characterPtr->GetComponent("Character");
    if (charComp && charComp->IsDead()) {
        // Player morreu, não atualizar mais
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

    // 10. atirar se o mouse estiver pressionado
    if (InputManager::GetInstance().IsMouseDown(SDL_BUTTON_LEFT) && cooldownTimer.Get() >= cooldownTime) {

        cooldownTimer.Restart();

        GameObject* bulletGO = new GameObject();

                bulletGO->box.pos.x = associated.box.pos.x;
                bulletGO->box.pos.y = associated.box.pos.y;

                bulletGO->box.pos.x += cos(angle * M_PI / 180.0f) * 20;
                bulletGO->box.pos.y += sin(angle * M_PI / 180.0f) * 20;

                bulletGO->box.size.x = 20;
                bulletGO->box.size.y = 20;

                bulletGO->AddComponent(
                    new SpriteRenderer(
                        *bulletGO,
                        "Resources/img/Bullet.png",
                        1, 1
                    )
                );

        Bullet* bullet = new Bullet(*bulletGO, angle, 2500.0f, 800.0f);

        bulletGO->AddComponent(bullet);

        Game::GetInstance().GetCurrentState().AddObject(bulletGO);

    }
}

void Gun::Render() {
}