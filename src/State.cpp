#include "State.h"
#include <SDL2/SDL.h>

State::State()
    : quitRequested(false)
{
    LoadAssets();
}

State::~State() {
}

void State::LoadAssets() {
    music.Open("Resources/audio/bgm.mp3");
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
