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
    enemy->box.pos.x = 600;
    enemy->box.pos.y = 450;

    auto* sr = new SpriteRenderer(
        *enemy,
        "Resources/img/Enemy.png",
        3, 2
    );

    enemy->AddComponent(sr);

    auto* animator = new Animator(*enemy);
    animator->AddAnimation("walk", Animation(0, 2, 0.2f));
    animator->SetAnimation("walk");

    enemy->AddComponent(animator);
    enemy->AddComponent(new Zombie(*enemy));


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

    GameObject* player = new GameObject();

    player->box.pos.x = Camera::pos.x + 100;
    player->box.pos.y = Camera::pos.y + 100;

    //player->box.pos.x = Camera::pos.x + 600;
    //player->box.pos.y = Camera::pos.y + 450;
    player->box.size.x = 64;
    player->box.size.y = 64;

    std::cout << "PLAYER CRIADO" << std::endl;

    player->AddComponent(
        new SpriteRenderer(
            *player,
            "Resources/img/Enemy.png",
            3, 2
        )
    );

    // ANIMAÇÃO
    Animator* playerAnimator = new Animator(*player);
    playerAnimator->AddAnimation("walk", Animation(0, 2, 0.2f));
    playerAnimator->SetAnimation("walk");

    player->AddComponent(playerAnimator);

    // CHARACTER
    player->AddComponent(new Character(*player));

    // CONTROLLER
    player->AddComponent(new PlayerController(*player));

    AddObject(player);
    std::cout << "PLAYER ADICIONADO" << std::endl;
    AddObject(bg);
    AddObject(tileMapObject);
    AddObject(enemy);
    
}


State::~State() {
}


void State::LoadAssets() {
    music.Open("Resources/audio/BGM.wav");
    music.Play();
}

void State::Start() {

    for (auto& obj : objectArray) {
        obj->Start();
    }

    started = true;
}


std::weak_ptr<GameObject> State::AddObject(GameObject* go) {

    std::shared_ptr<GameObject> ptr(go);

    objectArray.push_back(ptr);

    // se o jogo já começou, chamar start imediatamente
    if (started) {
        ptr->Start();
    }

    return std::weak_ptr<GameObject>(ptr);
}

void State::Update(float dt) {
    Camera::Update(dt);


    if (SDL_QuitRequested()) {
        quitRequested = true;
    }


    for (auto& obj : objectArray) {
        obj->Update(dt);
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
