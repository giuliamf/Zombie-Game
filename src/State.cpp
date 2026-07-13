#include "State.h"

#include "Camera.h"
#include "Character.h"
#include "Collider.h"
#include "Collision.h"

#include <SDL2/SDL.h>
#include <algorithm>

State::State()
    : popRequested(false),
      quitRequested(false),
      started(false)
{
}

State::~State() {
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> ptr(go);

    // Se o jogo já começou, adicionar à fila de pendentes
    // para evitar modificar o array durante iteração
    if (started) {
        pendingObjects.push_back(ptr);
    } else {
        objectArray.push_back(ptr);
    }

    return std::weak_ptr<GameObject>(ptr);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (auto& obj : objectArray) {
        if (obj.get() == go) {
            return std::weak_ptr<GameObject>(obj);
        }
    }
    return std::weak_ptr<GameObject>();
}

std::vector<std::shared_ptr<GameObject>>& State::GetObjectArray() {
    return objectArray;
}

bool State::QuitRequested() const {
    return quitRequested;
}

bool State::PopRequested() const {
    return popRequested;
}

// Chama Start() em todos os objetos já registrados e marca o estado como iniciado
void State::StartArray() {
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
}

// Processa objetos pendentes, atualiza todos, detecta colisões e remove mortos
void State::UpdateArray(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }

    // Processar objetos pendentes ANTES do Update
    if (!pendingObjects.empty()) {
        for (auto& obj : pendingObjects) {
            obj->Start();
            objectArray.push_back(obj);
        }
        pendingObjects.clear();
    }

    for (auto& obj : objectArray) {
        obj->Update(dt);
    }

    // Detecção de colisão
    size_t arraySize = objectArray.size();
    for (size_t i = 0; i < arraySize; i++) {
        if (i >= objectArray.size()) break;

        GameObject* obj1 = objectArray[i].get();
        if (!obj1 || obj1->IsDead()) continue;

        for (size_t j = i + 1; j < arraySize; j++) {
            if (j >= objectArray.size()) break;

            GameObject* obj2 = objectArray[j].get();
            if (!obj2 || obj2->IsDead()) continue;

            Collider* c1 = (Collider*) obj1->GetComponent("Collider");
            Collider* c2 = (Collider*) obj2->GetComponent("Collider");

            if (c1 && c2) {
                if (Collision::IsColliding(c1->box, c2->box)) {
                    if (!obj1->IsDead() && !obj2->IsDead()) {
                        obj1->NotifyCollision(*obj2);
                        obj2->NotifyCollision(*obj1);
                    }
                }
            }
        }
    }

    // Remover objetos mortos
    objectArray.erase(
        std::remove_if(
            objectArray.begin(),
            objectArray.end(),
            [](std::shared_ptr<GameObject>& obj) {
                return obj->IsDead();
            }
        ),
        objectArray.end()
    );

    // Centralizar câmera no player (Character)
    for (auto& obj : objectArray) {
        for (auto comp : obj->GetComponents()) {
            Character* character = dynamic_cast<Character*>(comp);
            if (character != nullptr) {
                Camera::pos.x = obj->box.pos.x - 600;
                Camera::pos.y = obj->box.pos.y - 450;
                break;
            }
        }
    }
}

// Renderiza todos os objetos do array
void State::RenderArray() {
    for (auto& obj : objectArray) {
        obj->Render();
    }
}
