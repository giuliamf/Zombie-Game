#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "Animator.h"
#include "Animation.h"
#include "Camera.h"
#include "Character.h" 
#include "PlayerController.h"
#include "TileMap.h"
#include "TileSet.h"

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


    // ENEMY
    GameObject* enemy = new GameObject();
    
    enemy->box.pos.x = 1400;
    enemy->box.pos.y = 1300;

    enemy->box.size.x = 72;
    enemy->box.size.y = 72;

    auto* sr = new SpriteRenderer(
        *enemy,
        "Resources/img/Enemy.png",
        3, 2
    );

    enemy->AddComponent(sr);

    auto* animator = new Animator(*enemy);
    animator->AddAnimation("walk", Animation(0, 2, 0.2f));
    
    enemy->AddComponent(animator);
    enemy->AddComponent(new Zombie(*enemy));
    animator->SetAnimation("walk");

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
    player->box.pos.y = 1280;

    player->box.size.x = 64;
    player->box.size.y = 64;

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
    AddObject(enemy);
    
}


State::~State() {
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

    /** se o jogo já começou, chamar start imediatamente
    if (started) {
        ptr->Start();
    }
    */
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