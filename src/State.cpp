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


    // ENEMIES - Criar múltiplos zombies
    GameObject* enemy1 = CreateZombie(1800, 1300);  // Direita
    GameObject* enemy2 = CreateZombie(1280, 900);   // Acima
    GameObject* enemy3 = CreateZombie(800, 1300);   // Esquerda
    GameObject* enemy4 = CreateZombie(1500, 1600);  // Abaixo-direita
    GameObject* enemy5 = CreateZombie(1000, 1000);  // Diagonal superior-esquerda

    // AQUI ENTRA O MAPA

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

    AddObject(bg);
    AddObject(tileMapObject);
    AddObject(player);
    AddObject(enemy1);
    AddObject(enemy2);
    AddObject(enemy3);
    AddObject(enemy4);
    AddObject(enemy5);
    
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

    objectArray.push_back(ptr);
    
    // só chamar Start se o jogo já começou
    if (started) {
        ptr->Start();
    }
    
    return std::weak_ptr<GameObject>(ptr);
}

    void State::Update(float dt) {
        //Camera::Update(dt);

        if (SDL_QuitRequested()) {
            quitRequested = true;
        }


        for (auto& obj : objectArray) {
            obj->Update(dt);
        }

        for (int i = 0; i < objectArray.size(); i++) {
        for (int j = i + 1; j < objectArray.size(); j++) {

            GameObject* obj1 = objectArray[i].get();
            GameObject* obj2 = objectArray[j].get();

            Collider* c1 = (Collider*) obj1->GetComponent("Collider");
            Collider* c2 = (Collider*) obj2->GetComponent("Collider");

            if (c1 && c2) {

                if (Collision::IsColliding(
                    c1->box,
                    c2->box
                )) {

                    obj1->NotifyCollision(*obj2);
                    obj2->NotifyCollision(*obj1);
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