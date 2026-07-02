#include "StageState.h"

#include "InputManager.h"
#include "Animation.h"
#include "Animator.h"
#include "Character.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Zombie.h"
#include "WaveSpawner.h"
#include "AIController.h"

StageState::StageState()
    : mapTileSet(nullptr)
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

    // MAPA
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

    // PLAYER
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

    // WAVESPAWNER
    GameObject* spawner = new GameObject();
    spawner->AddComponent(new WaveSpawner(*spawner, this));

    AddObject(bg);
    AddObject(tileMapObject);
    AddObject(player);
    AddObject(spawner);
}

StageState::~StageState() {
}

void StageState::LoadAssets() {
    music.Open("Resources/audio/BGM.wav");
    music.Play();
}

void StageState::Start() {
    StartArray();
}

void StageState::Pause() {
}

void StageState::Resume() {
}

void StageState::Update(float dt) {
    // ESC — retorna à TitleState sem encerrar o programa
    if (InputManager::GetInstance().IsKeyDown(SDLK_ESCAPE)) {
        popRequested = true;
        return;
    }

    UpdateArray(dt);
}

void StageState::Render() {
    RenderArray();
}

GameObject* StageState::CreateZombie(float x, float y) {
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
