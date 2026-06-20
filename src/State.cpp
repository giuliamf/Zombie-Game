#include "Animation.h"
#include "Animator.h"
#include "Camera.h"
#include "Character.h"
#include "Collider.h"
#include "Collision.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "State.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Zombie.h"
#include "WaveSpawner.h"
#include "AIController.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <algorithm>

// construtor
State::State()
    : quitRequested(false),
      mapTileSet(nullptr),
      started(false)
{
    LoadAssets();

    // BACKGROUND
    GameObject* bg = new GameObject();
    bg->box.pos.x = 0;
    bg->box.pos.y = 0;

    bg->AddComponent(
        new SpriteRenderer(
            *bg,
            "Resources/img/background.png"
        )
    );

    // AQUI ENTRA O MAPA (WaveSpawner será adicionado depois do player)

    mapTileSet = std::make_unique<TileSet>(
        64, 64,
        "Resources/img/Tileset.png"
    );

    GameObject* tileMapObject = new GameObject();
    tileMapObject->box.pos.x = 0;
    tileMapObject->box.pos.y = 0;

    tileMapObject->AddComponent(
        new TileMap(
            *tileMapObject,
            "Resources/map/map.txt",
            mapTileSet.get()
        )
    );

    // CRIANDO O PLAYER
    GameObject* player = new GameObject();

    player->box.pos.x = 1280;
    player->box.pos.y = 1300;

    player->box.size.x = 72;
    player->box.size.y = 72;

    player->AddComponent(
        new SpriteRenderer(
            *player,
            "Resources/img/Player.png",
            3, 4
        )
    );

    Animator* playerAnimator = new Animator(*player);
    playerAnimator->AddAnimation("walk", Animation(0, 2, 0.2f));

    player->AddComponent(playerAnimator);
    player->AddComponent(new Character(*player));
    player->AddComponent(new PlayerController(*player));

    playerAnimator->SetAnimation("walk");

    // Criar WaveSpawner
    GameObject* spawner = new GameObject();
    spawner->AddComponent(new WaveSpawner(*spawner, this));
    
    AddObject(bg);
    AddObject(tileMapObject);
    AddObject(player);
    AddObject(spawner);
}


State::~State() {
}

GameObject* State::CreateZombie(float x, float y) {
    GameObject* zombie = new GameObject();
    
    zombie->box.pos.x = x;
    zombie->box.pos.y = y;
    zombie->box.size.x = 72;
    zombie->box.size.y = 72;
    
    auto* sr = new SpriteRenderer(
        *zombie,
        "Resources/img/Enemy.png",
        3, 2
    );
    zombie->AddComponent(sr);
    
    auto* animator = new Animator(*zombie);
    animator->AddAnimation("walk", Animation(0, 2, 0.2f));
    zombie->AddComponent(animator);
    zombie->AddComponent(new Zombie(*zombie));
    zombie->AddComponent(new AIController(*zombie, 150.0f));
    animator->SetAnimation("walk");
    
    return zombie;
}


void State::LoadAssets() {
    music.Open("Resources/audio/BGM.wav");
    music.Play();
}

void State::Start() {
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
}


std::weak_ptr<GameObject> State::AddObject(GameObject* go) {

    std::shared_ptr<GameObject> ptr(go);

    // Se o jogo já começou, adicionar à fila de pendentes
    // para evitar modificar o array durante iteração
    if (started) {
        pendingObjects.push_back(ptr);
    } else {
        // Se ainda não começou, adicionar diretamente
        objectArray.push_back(ptr);
    }
    
    return std::weak_ptr<GameObject>(ptr);
}

    void State::Update(float dt) {
        //Camera::Update(dt);

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

        // Cachear o tamanho antes do loop para evitar problemas se objetos forem adicionados
        size_t arraySize = objectArray.size();
        
        for (size_t i = 0; i < arraySize; i++) {
            // Verificar se o índice ainda é válido (objetos podem ter sido removidos)
            if (i >= objectArray.size()) {
                break;
            }
            
            GameObject* obj1 = objectArray[i].get();
            
            // Verificar se o ponteiro é válido
            if (!obj1) {
                continue;
            }
            
            // Pular se objeto está morto
            if (obj1->IsDead()) {
                continue;
            }
            
            for (size_t j = i + 1; j < arraySize; j++) {
                // Verificar se o índice ainda é válido
                if (j >= objectArray.size()) {
                    break;
                }
                
                GameObject* obj2 = objectArray[j].get();
                
                // Verificar se o ponteiro é válido
                if (!obj2) {
                    continue;
                }
                
                // Pular se objeto está morto
                if (obj2->IsDead()) {
                    continue;
                }
                
                Collider* c1 = (Collider*) obj1->GetComponent("Collider");
                Collider* c2 = (Collider*) obj2->GetComponent("Collider");
    
                if (c1 && c2) {
                    if (Collision::IsColliding(c1->box, c2->box)) {
                        // Verificar novamente antes de notificar (pode ter morrido em outra colisão)
                        if (!obj1->IsDead() && !obj2->IsDead()) {
                            obj1->NotifyCollision(*obj2);
                            obj2->NotifyCollision(*obj1);
                        }
                    }
                }
            }
        }


    // remover objetos mortos
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


    // buscar o player (Character)
    for (auto& obj : objectArray) {
        for (auto comp : obj->GetComponents()) {

            Character* character = dynamic_cast<Character*>(comp);

            if (character != nullptr) {

                // centralizar câmera no player
                Camera::pos.x = obj->box.pos.x - 600;
                Camera::pos.y = obj->box.pos.y - 450;

                break;
            }
        }
}
}

void State::Render() {
    for (auto& obj : objectArray) {
        obj->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
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