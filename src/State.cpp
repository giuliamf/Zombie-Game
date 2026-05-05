#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "Animator.h"
#include "Animation.h"

#include "TileMap.h"
#include "TileSet.h"

#include <SDL2/SDL.h>

#include <iostream>

// construtor
State::State()
    : quitRequested(false),
      mapTileSet(nullptr)
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

    
    AddObject(bg);
    AddObject(tileMapObject);
    AddObject(enemy);
    
}


State::~State() {
}


void State::LoadAssets() {
    std::cout << "LoadAssets rodando" << std::endl;
    music.Open("Resources/audio/BGM.wav");
    music.Play();
}

void State::Start() {
}

void State::AddObject(GameObject* go) {
    objectArray.emplace_back(go);
}

void State::Update(float dt) {
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
