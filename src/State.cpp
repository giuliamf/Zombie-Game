#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include <SDL2/SDL.h>

// construtor
State::State()
    : quitRequested(false)
{
    LoadAssets();

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

    GameObject* zombie = new GameObject();
    zombie->box.pos.x = 600;
    zombie->box.pos.y = 450;

    zombie->AddComponent(
        new SpriteRenderer(
            *zombie,
            "Resources/img/Enemy.png",
            2, 1
        )
    );

    zombie->AddComponent(
        new Zombie(*zombie)
    );

    AddObject(zombie);
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
