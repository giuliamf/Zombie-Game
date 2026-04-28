#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "Animator.h"
#include "Animation.h"

#include <SDL2/SDL.h>

// construtor
State::State()
    : quitRequested(false)
{
    LoadAssets();

    // cria obj de background 
    GameObject* bg = new GameObject();
    bg->box.pos.x = 0;
    bg->box.pos.y = 0;

    bg->AddComponent(
        new SpriteRenderer(
            *bg,
            "Resources/img/background.png"
        )
    );

    AddObject(bg);

    // cria obj de inimigo
    GameObject* enemy = new GameObject();
    enemy->box.pos.x = 600;
    enemy->box.pos.y = 450;

    auto* sr = new SpriteRenderer(
        *enemy,
        "Resources/img/Enemy.png",
        3, // 3 colunas
        2  // 2 linhas
    );

    enemy->AddComponent(sr);

    auto* animator = new Animator(*enemy);
    animator->AddAnimation("walk", Animation(0, 2, 0.2f));
    animator->SetAnimation("walk");

    enemy->AddComponent(animator);

    enemy->AddComponent(new Zombie(*enemy));

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
